#include "GameClient.h"



GameClient::GameClient()
{
	m_Engine.reset(new Engine());
	m_Engine->Init();
}


GameClient::~GameClient()
{
}
