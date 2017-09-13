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
	std::shared_ptr<Server> m_Server;
	std::vector<PeerSP> m_Players;

	void CreateDefaultEntityForPeer(PeerSP p);
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
	void BroadCastEventFromPeer(PeerSP pFrom, const ByteStream* buffer);
	void BroadCast(const ByteStream* buffer);
	void AddAndWelcomePeer(PeerSP p);
	void SendWelcomeMessage(unsigned int playerId);

};
