#include "networkutils.h"
#include "networking/networkutil/Buffer.h"
#include "engine/object/Transform.h"

bool SerializeInt(ByteStream* buffer, int value)
{
	*((uint32_t*)(buffer->Data + buffer->Index)) = value;
	buffer->Index += 4;
	return true;
}

int DeSerializeInt(ByteStream* buffer)
{
	int val = *((uint32_t*)(buffer->Data + buffer->Index));
	buffer->Index += 4;
	return val;
}

float DeSerializeFloat(ByteStream* buffer)
{
	float val = *((float*)(buffer->Data + buffer->Index));
	buffer->Index += 4;
	return val;
}

std::string DeSerializeString(ByteStream* buffer)
{
	int oldIndex = buffer->Index;
	buffer->Index += strlen(reinterpret_cast<char*>(&buffer->Data[buffer->Index]));
	std::string result = reinterpret_cast<char*>(&buffer->Data[oldIndex]);
	return result;
}

void SerializeTransform(const Transform* transform, ByteStream* buffer)
{
	const auto& mat = transform->GetMatrix();
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			buffer->AddData(&mat[i][j], sizeof(float));
		}
	}
}

void DeSerializeTransform(Transform* transform, ByteStream* buffer)
{
	auto& mat = transform->GetMatrix();
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			mat[i][j] = buffer->ReadType<float>();
		}
	}
}
