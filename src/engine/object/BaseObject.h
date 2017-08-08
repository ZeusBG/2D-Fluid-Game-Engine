#pragma once
#include "engine/core/MetaData.h"
class BaseObject : public std::enable_shared_from_this<BaseObject>
{
public:
    virtual void Init() {}

    virtual ~BaseObject() {}
    virtual void Update(float delta) = 0;
    virtual void BeginPlay() {}
};

using BaseObjectSP = std::shared_ptr<BaseObject>;

