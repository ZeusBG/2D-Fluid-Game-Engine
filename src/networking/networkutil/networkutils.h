#pragma once

#include <string>

class Transform;
struct ByteStream;

bool SerializeInt(ByteStream* buffer, int value);
int DeSerializeInt(ByteStream* buffer);
std::string DeSerializeString(ByteStream* buffer);
void SerializeTransform(const Transform* transform, ByteStream* buffer);
void DeSerializeTransform(Transform* transform, ByteStream* buffer);