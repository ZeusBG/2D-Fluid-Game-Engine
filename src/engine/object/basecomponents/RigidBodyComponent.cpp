#include "engine/object/basecomponents/RigidBodyComponent.h"
#include "engine/object/Entity.h"
#include "engine/core/Engine.h"
#include "engine/physics/Physics.h"
#include <rapidjson/document.h>
#include <Box2D/Box2D.h>

IMPLEMENT_METADATA(RigidBodyComponent);

RigidBodyComponent::RigidBodyComponent() : m_Collider(nullptr), m_PhysicsHandle(nullptr)
{
}

void RigidBodyComponent::Init()
{

}

void RigidBodyComponent::Update(float dt)
{
	Transform& transform = m_Owner->GetTransform();
	Vec2 pos = { m_PhysicsHandle->GetPosition().x, m_PhysicsHandle->GetPosition().y };
	transform.SetTranslate(pos);
}

void RigidBodyComponent::DeSerializeFromJSON(const rapidjson::Value& val)
{
	if (m_PhysicsHandle)
		g_Engine->GetModule<Physics>()->DestroyObject(m_PhysicsHandle);

	Vec2 translate = m_Owner->GetTransform().GetTranslate();
	Vec2 scale = m_Owner->GetTransform().GetScale();


	b2BodyDef def;

	def.type = b2_staticBody;
	def.position = { translate.x, translate.y };
	def.bullet = false;

	if (val.HasMember("Type") && strcmp(val["Type"].GetString(), "Dynamic") == 0)
	{
		def.type = b2_dynamicBody;
	}

	if (val.HasMember("Bullet"))
		def.bullet = val["Bullet"].GetBool();

	if(val.HasMember("Active"))
		def.active = val["Active"].GetBool();

	if (val.HasMember("AllowSleep"))
		def.allowSleep = val["AllowSleep"].GetBool();

	if (val.HasMember("Angle"))
		def.angle = val["Angle"].GetFloat();

	if (val.HasMember("AngularDamping"))
		def.angularDamping = val["AngularDamping"].GetFloat();

	if (val.HasMember("AngularVelocity"))
		def.angularVelocity = val["AngularVelocity"].GetFloat();

	if (val.HasMember("FixedRotation"))
		def.fixedRotation = val["FixedRotation"].GetBool();

	if (val.HasMember("GravityScale"))
		def.gravityScale = val["GravityScale"].GetFloat();

	if (val.HasMember("LinearDamping"))
		def.linearDamping = val["LinearDamping"].GetFloat();

	if (val.HasMember("LinearVelocity"))
		def.linearVelocity = { val["LinearVelocity"]["x"].GetFloat(), val["LinearVelocity"]["y"].GetFloat() };

	
	m_PhysicsHandle = g_Engine->GetModule<Physics>()->CreateObject(def);

	b2FixtureDef fixtureDef;
	fixtureDef.density = 0.5f;
	fixtureDef.friction = 0.4f;
	fixtureDef.restitution = 0.0f;

	if (val.HasMember("Fixture"))
	{
		const auto& fixtureInfo = val["Fixture"];

		if (strcmp(fixtureInfo["Name"].GetString(), "Circle") == 0)
		{
			auto circle = std::make_shared<b2CircleShape>();
			circle->m_radius = val["Fixture"]["R"].GetFloat();
			circle->m_p = { translate.x, translate.y };
			m_Collider = circle;
		}
		else if (strcmp(fixtureInfo["Name"].GetString(), "Box") == 0)
		{
			auto box = std::make_shared<b2PolygonShape>();
			box->SetAsBox(val["Fixture"]["h"].GetFloat(), val["Collider"]["w"].GetFloat());
			m_Collider = box;
		}
		else if (strcmp(fixtureInfo["Name"].GetString(), "None") == 0)
		{
			m_Collider = nullptr;
		}
		else
		{
			// Create default box collider if no collider is specified
			auto box = std::make_shared<b2PolygonShape>();
			box->SetAsBox(scale.x, scale.y);
			m_Collider = box;
		}

		if (fixtureInfo.HasMember("Density"))
			fixtureDef.density = fixtureInfo["Density"].GetFloat();

		if (fixtureInfo.HasMember("Friction"))
			fixtureDef.friction = fixtureInfo["Friction"].GetFloat();

		if (fixtureInfo.HasMember("Restitution"))
			fixtureDef.restitution = fixtureInfo["Restitution"].GetFloat();
	}
	else
	{
		// Create default box collider if no collider is specified
		auto box = std::make_shared<b2PolygonShape>();
		box->SetAsBox(scale.x, scale.y);
		m_Collider = box;
	}

	fixtureDef.shape = m_Collider.get();

	m_PhysicsHandle->CreateFixture(&fixtureDef);
}

void RigidBodyComponent::AddForce(const Vec2& force)
{
	m_PhysicsHandle->ApplyForceToCenter({ force.x, force.y }, true);
}

void RigidBodyComponent::ApplyLinearImpulse(const Vec2& impulse)
{
	Vec2 pos = m_Owner->GetTransform().GetTranslate();
	m_PhysicsHandle->ApplyLinearImpulse({ impulse.x, impulse.y }, { pos.x, pos.y }, true);
}

void RigidBodyComponent::SetLinearVelocity(const Vec2& vel)
{
	m_PhysicsHandle->SetLinearVelocity({ vel.x, vel.y });
}

void RigidBodyComponent::AddAngularVelocity(float angularVelocity)
{
	m_PhysicsHandle->ApplyAngularImpulse(angularVelocity, true);
}