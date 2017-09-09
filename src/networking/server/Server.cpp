#pragma once
#include "networking/networkutil/Buffer.h"
#include "Server.h"
#include <iostream>

SendInfo::SendInfo(ENetPeer* reciever, const ByteStream* buffer) : Reciever(reciever)
{
	Data = *buffer;
}


int Server::InitENet()
{
	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return EXIT_FAILURE;
	}
}

Server::Server()
{
	m_IsRunning = false;
}
void Server::Init(const char* ip, int port)
{
	if (InitENet())
		return;
	enet_address_set_host(&m_Address, ip);
	m_Address.host = ENET_HOST_ANY;
	/* Bind the server to port 1234. */
	m_Address.port = port;

	m_Server = enet_host_create(&m_Address /* the address to bind the server host to */,
		32      /* allow up to 32 clients and/or outgoing connections */,
		2      /* allow up to 2 channels to be used, 0 and 1 */,
		0      /* assume any amount of incoming bandwidth */,
		0      /* assume any amount of outgoing bandwidth */);

	if (m_Server == NULL)
	{
		fprintf(stderr,
			"An error occurred while trying to create an ENet server host.\n");
		exit(EXIT_FAILURE);
	}
}

void Server::SendPendingData()
{

	std::queue<SendInfo> sendInfoQueue;
	{
		std::lock_guard <std::mutex> lock(m_DataSendQueueMutex);
		sendInfoQueue = std::move(m_SendData);
	}
	while (!sendInfoQueue.empty())
	{
		auto sendInfo = sendInfoQueue.front();
		sendInfoQueue.pop();
		ENetPacket* packet = enet_packet_create(sendInfo.Data.Data,
			sendInfo.Data.Index,
			ENET_PACKET_FLAG_RELIABLE);
		if (sendInfo.Reciever == nullptr)
			enet_host_broadcast(m_Server, 0, packet);
		else
			enet_peer_send(sendInfo.Reciever, 0, packet);
	}
}

void Server::BradCast(const ByteStream* stream)
{
	std::lock_guard<std::mutex> lg(m_DataSendQueueMutex);
	m_SendData.push({ nullptr, stream });
}

void Server::Start()
{
	m_IsRunning = true;
	while (m_IsRunning)
	{
		ENetEvent event;
		/* Wait up to 1000 milliseconds for an event. */
		while (enet_host_service(m_Server, &event, 32) > 0)
		{
			{
				std::lock_guard <std::mutex> lock(m_DataRecievedMutex);

				m_Events.push(event);
			}
			SendPendingData();
		}
		std::cout << "searching ..." << std::endl;
	}
}

bool Server::PollEvent(ENetEvent* event)
{
	if (m_Events.empty())
		return false;
	{
		std::lock_guard<std::mutex> lock(m_DataRecievedMutex);
		*event = m_Events.front();
		m_Events.pop();
	}
	return true;
}

void Server::SendDataTo(ENetPeer* p, const ByteStream* buff)
{
	std::lock_guard <std::mutex> lock(m_DataSendQueueMutex);
	m_SendData.push(SendInfo(p, buff));
}

void Server::StartAsync()
{
	m_ServerThread.reset(new std::thread(&Server::Start, this));
}
void Server::Stop()
{
	m_IsRunning = false;
}

Server::~Server()
{
	enet_host_destroy(m_Server);
	atexit(enet_deinitialize);
}
