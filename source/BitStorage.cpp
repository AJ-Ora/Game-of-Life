
#include "BitStorage.h"

#include <cmath>

BitStorage::BitStorage(int capacity)
{
	if (capacity <= 0)
	{
		capacity = 1;
	}

	chunkSize = sizeof(unsigned char) * 8;
	rawData = new unsigned char[ceil(capacity / chunkSize)];
	length = 0;
}

BitStorage::~BitStorage()
{
	delete[] rawData;
}

bool BitStorage::Get(int index)
{
	if (index < 0 || index > length)
	{
		return false;
	}

	int chunk = floor(index / chunkSize);
	unsigned char byte = *(rawData + chunk);
	return (byte >> (index - chunk * chunkSize)) & 1;
}

void BitStorage::Set(int index, bool value)
{
	if (index < 0 || index > length)
	{
		return;
	}

	if (value == Get(index))
	{
		return;
	}

	int chunk = floor(index / chunkSize);
	unsigned char valueToSet = 1 << (index - chunk);

	if (value == true)
	{
		*(rawData + chunk) += valueToSet;
	}
	else
	{
		*(rawData + chunk) -= valueToSet;
	}
}

unsigned int BitStorage::GetLength()
{
	return length;
}
