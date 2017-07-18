#pragma once
class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	virtual void Update(float delta) = 0;
};

