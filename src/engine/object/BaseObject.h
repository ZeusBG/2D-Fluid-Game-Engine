#pragma once
class BaseObject
{
public:
    virtual void Init() {}

    virtual ~BaseObject() {}
    virtual void Update(float delta) = 0;
};

