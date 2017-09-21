#pragma once

#include "engine/rendering/shaderobjects/SimpleVS.h"


class VisualComponent;
class SimpleTexturedVS : public SimpleVS
{
	ADD_SOLID_CLASS_METADATA(SimpleTexturedVS);
public:
	SimpleTexturedVS(const char* fileName) : SimpleVS(fileName) {}
	SimpleTexturedVS() {}
    virtual void Init() override;
};

using SimpleVSUniquePtr = std::unique_ptr<SimpleVS, IShaderDeleter>;