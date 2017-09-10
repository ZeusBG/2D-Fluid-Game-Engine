#include "Client.h"
#include "ClientController.h"
#include "networking/networkutil/networkutils.h"
#include "game/GameClient.h"
#include "engine/logging/Logging.h"
// TODO thois shouldnt be here
// Remove when prototype file is made
#include "game/CharacterControllerComponent.h"
#include "game/SimpleVisualComponent.h"
#include <iostream>

ClientController::ClientController()
{
	m_Client = new Client();
}
ClientController::~ClientController()
{
	m_Client->Stop();
	m_Client->WaitFinish();
	delete m_Client;
}

void ClientController::HandleRecievedPackets()
{
	ENetEvent e;
	while (m_Client->PollEvent(e))
	{
		switch (e.type)
		{
		case ENET_EVENT_TYPE_CONNECT:
		{
			e.peer->data = "Client information";
			break;
		}
		case ENET_EVENT_TYPE_RECEIVE:
		{
			printf("A packet of length %u containing %s was received from %s on channel %u.\n",
				e.packet->dataLength,
				e.packet->data,
				e.peer->data,
				e.channelID);
			ByteStream bs(e.packet->data, e.packet->dataLength);
			enet_packet_destroy(e.packet);
			UnpackRecievedData(bs);
			break;
		}

		case ENET_EVENT_TYPE_DISCONNECT:
		{
			printf("%s disconnected.\n", e.peer->data);
			/* Reset the peer's client information. */
			e.peer->data = NULL;
		}
		}
	}
}

void ClientController::SendPendingPackets()
{
	m_Client->Send(&m_BStream);
	m_BStream.EmptyByteStream();
}

void ClientController::Init(const char* ip, int port)
{
	m_Client->Init();
	m_ServerIp = ip;
	m_ServerPort = port;

}
void ClientController::UnpackRecievedData(ByteStream& bs)
{
	if (bs.Empty())
		return;
	while (!bs.Empty())
	{
		NetCommand cmd = bs.ReadType<NetCommand>();
		switch (cmd)
		{
			case NetCommand::CreateEntity:
			{
				short numEntities = bs.ReadType<short>();
				for (int i = 0; i < numEntities; ++i)
				{
					int id = bs.ReadType<int>();
					int objectTypeId = bs.ReadType<int>();
					SpawnEntity(objectTypeId, id);
				}
				break;
			}
			case NetCommand::UpdateEntity:
			{
				short numEntities = bs.ReadType<short>();
				for (int i = 0; i < numEntities; ++i)
				{
					int objectID = bs.ReadType<int>();
					if (objectID != m_Player->GetID())
					{
						auto entity = m_Engine->GetEntityByID(objectID);
						entity->DeSerialize(&bs);
					}
					else 
					{
						// TODO remove this later when extrapolation is done
						bs.SkipBytes(9u * sizeof(float));
					}
				}
				break;
			}
			case NetCommand::RemoveEntity:
			{
				int objectID = bs.ReadType<int>();
				m_Engine->RemoveEntityByID(objectID);
				break;
			}
			case NetCommand::TextMessage:
			{
				std::string message = bs.ReadString();
				LOG_L1(INFO, INFO, "%s", message.c_str());
			}
		}
	}
}

void ClientController::SpawnEntity(int entityTypeId, int id)
{
	// TODO Remove this ugly code when prototype file
	// is made. These entities should be inflated from the prototype
	if (entityTypeId == 999)
	{
		m_Player = m_Engine->CreateEntityWithID("SimpleEntity", id);
		m_Player->AddComponent(std::make_shared<CharacterControllerComponent>());
		m_Player->AddComponent(std::make_shared<SimpleVisualComponent>());
		m_Engine->AddEntity(m_Player);
	}
	else if (entityTypeId == 2)
	{
		auto entity = m_Engine->CreateEntityWithID("SimpleEntity", id);
		entity->AddComponent(std::make_shared<SimpleVisualComponent>());
		m_Engine->AddEntity(entity);
	}
}

void ClientController::Start()
{
	m_Client->StartAsync();
	if (!m_Client->Connect(m_ServerIp.c_str(), m_ServerPort))
		return;
	m_Engine->SetNetworkManager(this);
	m_Engine->Run();
}
void ClientController::SendDataTo(const ByteStream* data)
{
	m_Client->Send(data);
}

void ClientController::DoSnapShot()
{
	if (m_Player)
	{
		m_BStream.BeginCommand(NetCommand::UpdateEntity);
		m_Player->Serialize(&m_BStream);
	}
}