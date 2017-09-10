#include "Server.h"
#include "ServerController.h"
#include "networking/networkutil/Buffer.h"
#include "networking/networkutil/networkutils.h"
#include "engine/core/Engine.h"
#include "game/SimpleVisualComponent.h"
#include <iostream>
#include <sstream>


ServerController::ServerController()
{
	m_Server = new Server();
}

void ServerController::Init(const char* ip, int port)
{
	m_Server->Init(ip, port);
}

void ServerController::CreateDefaultEntityForPeer(Peer* p)
{
	// TODO Remove hardcoded stuff later
	ByteStream bs;
	bs.BeginCommand(NetCommand::CreateEntity);
	m_Engine->DoCreationSnapShot(&bs);

	EntitySP entity = m_Engine->CreateEntity("SimpleEntity");
	m_Engine->AddEntity(entity);
	p->SetEntity(entity);

	// Send the new peer his entity
	int entityID = entity->GetID();
	int objectType = 999;
	bs.BeginCommand(NetCommand::CreateEntity);
	short numEntities = 1;
	bs.AddData(&numEntities, sizeof(short));
	bs.AddData(&entityID, sizeof(int));
	bs.AddData(&objectType, sizeof(int));
	m_Server->SendDataTo(p->GetPeerPtr(), &bs);

	// Now send everyone else the new peer's entity
	bs.EmptyByteStream();
	bs.BeginCommand(NetCommand::CreateEntity);
	objectType = 2;
	bs.AddData(&numEntities, sizeof(short));
	bs.AddData(&entityID, sizeof(int));
	bs.AddData(&objectType, sizeof(int));
	BroadCastEventFromPeer(p, &bs);
}

void ServerController::UnpackRecievedData(ByteStream & bs)
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
				//int id = bs.ReadType<int>();
				//int objectTypeId = bs.ReadType<int>();
				//break;
			}
			case NetCommand::UpdateEntity:
			{
				int objectID = bs.ReadType<int>();
				m_Engine->GetEntityByID(objectID)->DeSerialize(&bs);
				break;
			}
			case NetCommand::RemoveEntity:
			{
				int objectID = bs.ReadType<int>();
				m_Engine->RemoveEntityByID(objectID);
				break;
			}
		}
	}
}

void ServerController::Start()
{
	m_Server->StartAsync();
	m_Engine->SetNetworkManager(this);
	m_Engine->Run();

}

void ServerController::SendDataTo(unsigned int playerId, const ByteStream* data)
{
	m_Server->SendDataTo(m_Players[playerId].GetPeerPtr(), data);
}

void ServerController::BroadCastEventFromPeer(Peer* pFrom, const ByteStream* buffer)
{
	for (int i = 0; i < m_Players.size(); ++i)
	{
		if (pFrom == &m_Players[i])
			continue;
		SendDataTo(i, buffer);
	}
}

void ServerController::BroadCast(const ByteStream* buffer)
{
	for (int i = 0; i < ((int)m_Players.size()) - 1; ++i)
	{
		SendDataTo(i, buffer);
	}
}

//TODO fix this
void ServerController::AddAndWelcomePeer(Peer* p)
{
	CreateDefaultEntityForPeer(p);
	m_Players.push_back(*p);
	SendWelcomeMessage(m_Players.size() - 1);
}

void ServerController::SendWelcomeMessage(unsigned int playerId)
{
	ByteStream buff;
	NetCommand cmd = NetCommand::TextMessage;
	buff.AddData(&cmd, sizeof(NetCommand));
	buff.AddData("Welcome !\0", strlen("Welcome !") + 1);
	SendDataTo(playerId, &buff);
}

ServerController::~ServerController()
{
	m_Server->Stop();
	m_Server->WaitFinish();
	delete m_Server;
}

void ServerController::HandleRecievedPackets()
{
	ENetEvent e;
	while (m_Server->PollEvent(&e))
	{
		switch (e.type)
		{
		case ENET_EVENT_TYPE_CONNECT:
		{
			/* Store any relevant client information here. */
			e.peer->data = "Client information";

			//TODO remove the ugly new when shared_ptr is used
			Peer* newPeer = new Peer(e.peer);
			AddAndWelcomePeer(newPeer);
		}
		break;
		case ENET_EVENT_TYPE_RECEIVE:
		{
			ByteStream bs(e.packet->data, e.packet->dataLength);
			enet_packet_destroy(e.packet);
			UnpackRecievedData(bs);
		}
		break;
		case ENET_EVENT_TYPE_DISCONNECT:
		{
			e.peer->data = NULL;
			RemovePeer(e.peer);
		}
		}
	}
}

void ServerController::RemovePeer(ENetPeer* p)
{
	for (int i = 0; i < m_Players.size(); ++i)
	{
		if (m_Players[i].GetPeerPtr() == p)
		{
			ByteStream bs;
			bs.BeginCommand(NetCommand::RemoveEntity);
			int id = m_Players[i].GetGameEntityPtr()->GetID();
			bs.AddData(&id, sizeof(int));
			BroadCastEventFromPeer(&m_Players[i], &bs);
			m_Engine->RemoveEntityByID(id);

			m_Players.erase(m_Players.begin() + i);
			break;
		}
	}
}

void ServerController::SendPendingPackets()
{
	m_Server->BradCast(&m_BStream);
	m_Server->SendPendingData();
	m_BStream.EmptyByteStream();
}

void ServerController::OnEntityRemoved(const Entity* entity)
{
	for (int i = 0; i < m_Players.size(); ++i)
	{
		if (m_Players[i].GetGameEntityPtr().get() == entity)
		{
			m_Players.erase(m_Players.begin() + i);
			break;
		}
	}
}

void ServerController::DoSnapShot()
{
	m_BStream.BeginCommand(NetCommand::UpdateEntity);
	m_Engine->DoSnapShot(&m_BStream);
}
