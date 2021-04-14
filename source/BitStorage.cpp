
#include "BitStorage.h"

#include <cmath>

BitStorage::BitStorage(int capacity)
{
	if (capacity <= 0)
	{
		capacity = 1;
	}

	chunkSize = sizeof(unsigned char) * 8;
	storedData = new unsigned char[ceil(capacity / chunkSize)];
	length = 0;
}

BitStorage::~BitStorage()
{
	delete[] storedData;
}

bool BitStorage::Get(int index)
{
	if (index < 0 || index > length)
	{
		return false;
	}

	int chunk = floor(index / chunkSize);
	unsigned char byte = *(storedData + chunk);
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
		*(storedData + chunk) += valueToSet;
	}
	else
	{
		*(storedData + chunk) -= valueToSet;
	}
}

unsigned int BitStorage::GetLength()
{
	return length;
}
