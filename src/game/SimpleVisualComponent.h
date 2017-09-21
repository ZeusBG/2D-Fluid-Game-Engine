#pragma once
#include "engine/object/basecomponents/VisualComponent.h"

class SimpleVisualComponent : public VisualComponent
{
    ADD_SOLID_CLASS_METADATA(SimpleVisualComponent)
public:
    SimpleVisualComponent();

	void DeSerializeFromJSON(const rapidjson::Value& val) override;
};

using SimpleVisualComponentSP = std::shared_ptr<SimpleVisualComponent>;