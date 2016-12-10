#ifndef __CIRCULARBUFFER_H
#define __CIRCULARBUFFER_H

#include "Platform.h"
#include <cstddef>
#include <iostream>
#include <vector>
#include "BufferCV.h"
#include "DynBuffer.h"

//template <class T> class DynBuffer<char>;
class ByteBuffer;

/**
 *@brief �˷�һ���Լ��������ж�Ҳ���жϣ���������Ҳ���ü� 1 ������˷�һ���ֽ�
 */
class MCircularBuffer
{
protected:
	DynBuffer<char>* m_dynBuffer;
	uint32 m_first;             // ��ǰ���������ݵĵ�һ������
	uint32 m_last;              // ��ǰ���������ݵ����һ�������ĺ���һ���������˷�һ���ֽ�
	ByteBuffer* m_tmpBA;        // ��ʱ����

protected:
	bool canAddData(uint32 num);
	void setCapacity(size_t newCapacity);

public:
	MCircularBuffer(size_t initCapacity = BufferCV::INIT_CAPACITY, size_t maxCapacity = BufferCV::MAX_CAPACITY);
	~MCircularBuffer();

public:
	uint32 getFirst();
	uint32 getLast();
	std::size_t getSize();
	void setSize(std::size_t value);
	char* getBuff();

	bool isLinearized();
	bool empty();
	size_t getCapacity();
	bool full();
	void linearize();
	void clear();

	// ���Ӻͻ�ȡ����
	void pushBackArr(char* items, uint32 start, std::size_t len);
	void pushBackBA(ByteBuffer* bu);
	void pushFrontArr(char* items, std::size_t len);
	void popFrontBA(ByteBuffer* bytearray, std::size_t len);
	void frontBA(ByteBuffer* bytearray, std::size_t len);
	void popFrontLen(uint32 len);
	void pushBackCB(MCircularBuffer* rhv);
};


#endif				// __CIRCULARBUFFER_H