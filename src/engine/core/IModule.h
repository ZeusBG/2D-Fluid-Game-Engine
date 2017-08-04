#pragma once

class Engine;
class IModule
{
public:
	virtual void Init(Engine* engine) = 0;

	// Called after Init. In this methods modules shoud
	// do some pre-processing on the data, they had been added.
	virtual void Start() = 0;
	virtual void Update(float delta) = 0;
	virtual void Destroy() = 0;
	virtual const char* GetName() = 0;
	virtual ~IModule() {}
};

