#pragma once

#include <stdint.h>
#include <string>

enum NetCommand
{
	CreateEntity = 0,
	UpdateEntity,
	RemoveEntity,
	TextMessage
};


struct ByteStream
{
	static const unsigned DEFAULT_SIZE = 1500;
	uint8_t* Data;
	unsigned int Size;
	unsigned int Index;

	ByteStream();
	ByteStream(void* data, unsigned int dataSize);
	ByteStream(unsigned size);
	ByteStream(const ByteStream& other);
	ByteStream& operator=(const ByteStream& other);
	void EmptyByteStream();
	void AddData(const void* data, unsigned size);
	bool Empty() const { return Index >= Size; }
	void BeginCommand(NetCommand cmd);
	void SkipBytes(unsigned int numBytes);
	std::string ReadString();

	template <typename T>
	T ReadType()
	{
		T* cmd = reinterpret_cast<T*>(Data + Index);
		Index += sizeof(T);
		return *cmd;
	}

	~ByteStream();

};