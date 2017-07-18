#pragma once
class Engine;
class Interface
{
protected:
	Engine* m_Engine;
public:
	Interface();
	virtual void Init(Engine* engine) = 0;
	virtual const char* GetName() = 0;
	virtual ~Interface();
};

