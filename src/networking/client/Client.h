#pragma once

#include <enet/enet.h>
#include <queue>
#include <memory>
#include <mutex>
#include "networking/networkutil/Buffer.h"

class Client
{
private:
	ENetHost* m_Client;
	ENetPeer* m_RemoteServer;
	ENetAddress m_ServerAddress;
	volatile bool m_IsRunning;
	std::mutex m_DataSendQueueMutex;
	std::queue <ByteStream> m_SendData;

	std::mutex m_DataRecievedMutex;
	std::queue<ENetEvent> m_Events;

	std::unique_ptr<std::thread> m_ClientThread;
	int InitENet();
	void RecievePendingMessages();
public:
	Client();
	void Init();
	void Start();
	bool Connect(const char* ip, int port);
	bool PollEvent(ENetEvent& event);
	void Send(const ByteStream* buffer);
	void StartAsync();
	void Stop();
	void SendPendingMessages();
	void WaitFinish() { m_ClientThread->join(); }
	~Client();
};