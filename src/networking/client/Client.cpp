#include "Client.h"
#include "networking/networkutil/Buffer.h"
#include <iostream>
int Client::InitENet()
{
	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return EXIT_FAILURE;
	}
}

void Client::RecievePendingMessages()
{
	ENetEvent event;
	while (enet_host_service(m_Client, &event, 32) > 0)
	{
		{
			std::lock_guard <std::mutex> lock(m_DataRecievedMutex);

			m_Events.push(event);
		}
		std::cout << "DATA RECIEVED NO SWITCH HANDLE!!!" << std::endl;
	}
}

void Client::SendPendingMessages()
{
	std::queue<ByteStream> sendInfoQueue;
	{
		std::lock_guard <std::mutex> lock(m_DataSendQueueMutex);
		sendInfoQueue = std::move(m_SendData);
	}
	while (!sendInfoQueue.empty())
	{
		ENetPacket * packet = enet_packet_create(sendInfoQueue.front().Data,
			sendInfoQueue.front().Index,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(m_RemoteServer, 0, packet);
		sendInfoQueue.pop();
	}
}

Client::Client()
{
	m_IsRunning = false;
}
void Client::Init()
{
	if (InitENet())
		return;

	m_Client = enet_host_create(NULL /* create a client host */,
		1 /* only allow 1 outgoing connection */,
		2 /* allow up 2 channels to be used, 0 and 1 */,
		57600 / 8 /* 56K modem with 56 Kbps downstream bandwidth */,
		14400 / 8 /* 56K modem with 14 Kbps upstream bandwidth */);

	if (m_Client == NULL)
	{
		fprintf(stderr,
			"An error occurred while trying to create an ENet server host.\n");
		exit(EXIT_FAILURE);
	}
}

void Client::Start()
{
	m_IsRunning = true;
	while (m_IsRunning)
	{
		RecievePendingMessages();
		SendPendingMessages();
	}
}

bool Client::Connect(const char* ip, int port)
{
	enet_address_set_host(&m_ServerAddress, ip);
	//address.host = ENET_HOST_ANY;
	m_ServerAddress.port = port;
	m_RemoteServer = enet_host_connect(m_Client, &m_ServerAddress, 2, 0);
	if (m_RemoteServer == NULL) {
		fprintf(stderr, "No available peers for initializing an ENet connection");
		return false;
	}
}

bool Client::PollEvent(ENetEvent& event)
{
	if (m_Events.empty())
		return false;
	{
		std::lock_guard<std::mutex> lock(m_DataRecievedMutex);
		event = m_Events.front();
		m_Events.pop();
	}
	return true;
}

void Client::Send(const ByteStream* buffer)
{
	std::lock_guard<std::mutex> l(m_DataSendQueueMutex);
	m_SendData.push(*buffer);
}

void Client::StartAsync()
{
	m_ClientThread.reset(new std::thread(&Client::Start, this));
}
void Client::Stop()
{
	m_IsRunning = false;
}

Client::~Client()
{
	atexit(enet_deinitialize);
	enet_host_destroy(m_Client);
}