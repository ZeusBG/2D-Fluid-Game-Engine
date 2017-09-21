#pragma once
#include "SimpleVisualComponent.h"

class SimpleTexturedVC : public SimpleVisualComponent
{
    ADD_SOLID_CLASS_METADATA(SimpleTexturedVC)
public:
	SimpleTexturedVC();

    virtual void Update(float dt) override;
	virtual void Init() override;
	virtual void Destroy() override;

private:
	int m_TextureID;
};

using CharacterControllerComponentSP = std::shared_ptr<SimpleTexturedVC>;
