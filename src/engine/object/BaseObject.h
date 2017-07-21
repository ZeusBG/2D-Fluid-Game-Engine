#pragma once
class BaseObject
{
public:
	virtual ~BaseObject() {}
	virtual void Update(float delta) = 0;
};

