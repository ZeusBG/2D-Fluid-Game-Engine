#pragma once
#include "engine/object/basecomponents/Component.h"
#include "util/math/Vec.h"

class b2Body;
class b2Shape;

class RigidBodyComponent : public Component
{
    ADD_SOLID_CLASS_METADATA(RigidBodyComponent);
	
public:
	RigidBodyComponent();

	virtual void Init() override;
	virtual void Update(float delta) override;
	virtual void DeSerializeFromJSON(const rapidjson::Value& val) override;
	virtual void Serialize(ByteStream* buffer) override {}
	virtual void DeSerialize(ByteStream* buffer) override {}

	void ApplyLinearImpulse(const Vec2& impulse);
	void SetLinearVelocity(const Vec2& other);
	void AddForce(const Vec2& force);
	void AddAngularVelocity(float angularVelocity);
private:
	Vec2 m_Pos;
	Vec2 m_Velocity;
	Vec2 m_AngularVelocity;
	float m_Friction;

	b2Body* m_PhysicsHandle;
	std::shared_ptr<b2Shape> m_Collider;
};

