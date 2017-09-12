#include <cstring>
#include "Buffer.h"

ByteStream::ByteStream()
{
	Data = new uint8_t[DEFAULT_SIZE];
	Size = DEFAULT_SIZE;
	Index = 0;
}

ByteStream::ByteStream(void* data, unsigned int dataSize)
{
	Data = new uint8_t[dataSize];
	Size = dataSize;
	Index = 0;
	memcpy(Data, data, dataSize);
}

ByteStream::ByteStream(unsigned size)
{
	Data = new uint8_t[size];
	Size = size;
	Index = 0;
}

ByteStream::ByteStream(const ByteStream& other)
{
	Data = new uint8_t[other.Size];
	memcpy(Data, other.Data, other.Size);
	Size = other.Size;
	Index = other.Index;
}

ByteStream& ByteStream::operator=(const ByteStream& other)
{
	if (&other == this)
	{
		return *this;
	}
	delete Data;
	Data = new uint8_t[other.Size];

	memcpy(Data, other.Data, other.Size);
	Size = other.Size;
	Index = other.Index;
}

void ByteStream::EmptyByteStream()
{
	Index = 0;
}

void ByteStream::AddData(const void* data, unsigned size)
{
	memcpy(Data + Index, data, size);
	Index += size;
}

void ByteStream::BeginCommand(NetCommand cmd)
{
	AddData(&cmd, sizeof(NetCommand));
}

void ByteStream::SkipBytes(unsigned int numBytes)
{
	Index += numBytes;
}

std::string ByteStream::ReadString()
{
	std::string result(reinterpret_cast<char*>(Data) + Index);
	Index += result.length() + 1;
	return result;
}

ByteStream::~ByteStream()
{
	delete Data;
}