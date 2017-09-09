#pragma once

#include <enet/enet.h>
#include <queue>
#include <memory>
#include <mutex>
#include "networking/networkutil/Buffer.h"

struct SendInfo
{
	ENetPeer* Reciever;
	ByteStream Data;

	SendInfo(ENetPeer* reciever, const ByteStream* buffer);
};

class Server
{
private:
	ENetHost* m_Server;
	ENetAddress m_Address;
	volatile bool m_IsRunning;
	std::mutex m_DataRecievedMutex;
	std::queue<ENetEvent> m_Events;
	std::unique_ptr<std::thread> m_ServerThread;

	std::mutex m_DataSendQueueMutex;
	std::queue <SendInfo> m_SendData;

	int InitENet();
public:
	Server();
	~Server();
	void Init(const char* ip, int port);
	void SendPendingData();
	void BradCast(const ByteStream* stream);
	void Start();
	bool PollEvent(ENetEvent* event);
	void SendDataTo(ENetPeer* p, const ByteStream* buff);
	void StartAsync();
	void WaitFinish() { m_ServerThread->join(); }
	void Stop();

};