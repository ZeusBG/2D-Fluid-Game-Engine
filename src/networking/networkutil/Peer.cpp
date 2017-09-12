#include "Peer.h"
#include "engine/object/Entity.h"

#include <enet/enet.h>

Peer::Peer(ENetPeer* peer, std::shared_ptr<Entity> entity) : m_ENetPeer(peer)
{
	m_GameEntity = entity;
}
Peer::Peer(ENetPeer* peer) : m_ENetPeer(peer)
{
	m_GameEntity = nullptr;
}

bool Peer::operator==(const Peer & other)
{
	return m_ENetPeer == other.m_ENetPeer && m_GameEntity == other.m_GameEntity;
}