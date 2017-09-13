#pragma once
#include <memory>


class Entity;
struct _ENetPeer;
typedef _ENetPeer ENetPeer;

class Peer
{
	ENetPeer* m_ENetPeer;
	std::shared_ptr<Entity> m_GameEntity;

public:

	Peer(ENetPeer* peer, std::shared_ptr<Entity> entity);
	Peer(ENetPeer* peer);

	bool operator==(const Peer& other);

	inline ENetPeer* GetPeerPtr() { return m_ENetPeer; }
	inline void SetPeer(ENetPeer* p){ m_ENetPeer = p; }
	inline std::shared_ptr<Entity> GetGameEntityPtr() { return m_GameEntity; }
	inline void SetEntity(std::shared_ptr<Entity> e) { m_GameEntity = e; }
};

typedef std::shared_ptr<Peer> PeerSP;