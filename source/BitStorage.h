
#ifndef BITSTORAGE_H
#define BITSTORAGE_H

#pragma once

class BitStorage
{
public:
	BitStorage(int capacity);
	~BitStorage();

	bool Get(int index);
	void Set(int index, bool value);

	unsigned int GetLength();

//private:
	int chunkSize;
	int length;
	unsigned char* rawData;
};

#endif
