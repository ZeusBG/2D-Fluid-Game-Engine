#pragma once
class Engine;
class IModule
{
public:
	virtual void Init(Engine* engine) = 0;
	virtual void Update(float delta) = 0;
	virtual void Destroy() = 0;
	virtual const char* GetName() = 0;
	virtual ~IModule() {}
};

