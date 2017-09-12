#pragma once
#include <vector>
#include "networking/NetworkManager.h"
#include "networking/networkutil/Peer.h"

struct ByteStream;
class Server;
class Engine;
class Entity;

class ServerController : public NetworkManager
{
	Server* m_Server;
	std::vector<Peer> m_Players;

	void CreateDefaultEntityForPeer(Peer* p);
	void RemovePeer(ENetPeer* p);
public:
	ServerController();
	~ServerController();

	virtual void HandleRecievedPackets() override;
	virtual void SendPendingPackets() override;
	virtual void OnEntityRemoved(const Entity* entity) override;
	virtual void DoSnapShot() override;
	virtual void Init(const char* ip, int port) override;

	void UnpackRecievedData(ByteStream& bs);
	void Start();
	void SendDataTo(unsigned int playerId, const ByteStream* data);
	void BroadCastEventFromPeer(Peer* pFrom, const ByteStream* buffer);
	void BroadCast(const ByteStream* buffer);
	void AddAndWelcomePeer(Peer* p);
	void SendWelcomeMessage(unsigned int playerId);

};
