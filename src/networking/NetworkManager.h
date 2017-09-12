#pragma once
#include <memory>
#include <string>

#include "networking/networkutil/Buffer.h"

class Entity;
class Engine;
struct SystemSettings;

struct NetInfo
{
	std::string IP;
	unsigned port;
};

class NetworkManager
{
protected:
	Engine* m_Engine;
	NetInfo m_NetInfo;
	ByteStream m_BStream;
	std::shared_ptr<SystemSettings> m_SystemSettings;
public:
	inline void SetEngine(Engine* engine) { m_Engine = engine; }
	inline void SetSystemSettings(std::shared_ptr<SystemSettings> settings) { m_SystemSettings = settings; }
	inline void OnUpdateEnd() { m_BStream.EmptyByteStream(); }
	inline void SetNetInfo(const NetInfo& info) { m_NetInfo = info; }

	virtual void Init(const char* ip, int port) = 0;
	virtual void DoSnapShot() = 0;
	virtual void HandleRecievedPackets() = 0;
	virtual void SendPendingPackets() = 0;
	virtual void OnEntityRemoved(const Entity* entity) = 0;
	virtual void Start() = 0;
	virtual ~NetworkManager() {}
};