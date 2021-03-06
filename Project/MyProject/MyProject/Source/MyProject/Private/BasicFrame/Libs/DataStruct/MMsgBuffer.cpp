#include "MyProject.h"
#include "MMsgBuffer.h"
#include "MCircularBuffer.h"
#include "MByteBuffer.h"
#include "MsgCV.h"
#include "SafePointer.h"

MY_BEGIN_NAMESPACE(MyNS)

MMsgBuffer::MMsgBuffer(uint32 initCapacity, uint32 maxCapacity)
{
	this->mCircularBuffer = MY_NEW MCircularBuffer(initCapacity, maxCapacity);
	this->mHeaderBA = MY_NEW MByteBuffer();
	this->mMsgBodyBA = MY_NEW MByteBuffer();
}

MMsgBuffer::~MMsgBuffer()
{
	//this->dispose();
}

void MMsgBuffer::init()
{

}

void MMsgBuffer::dispose()
{
	MY_SAFE_DISPOSE(this->mCircularBuffer);
	MY_SAFE_DISPOSE(this->mHeaderBA);
	MY_SAFE_DISPOSE(this->mMsgBodyBA);
}

MByteBuffer* MMsgBuffer::getHeaderBA()
{
	return this->mHeaderBA;
}

MByteBuffer* MMsgBuffer::getMsgBodyBA()
{
	return this->mMsgBodyBA;
}

MCircularBuffer* MMsgBuffer::getCircularBuffer()
{
	return this->mCircularBuffer;
}

bool MMsgBuffer::checkHasMsg()
{
	this->mCircularBuffer->frontBA(this->mHeaderBA, MsgCV::HEADER_SIZE);  // 将数据读取到 mHeaderBA
	uint32 msglen = 0;
	this->mHeaderBA->readUnsignedInt32(msglen);

#ifdef MSG_COMPRESS
	if ((msglen & MsgCV::PACKET_ZIP) > 0)         // 如果有压缩标志
	{
		msglen &= (~MsgCV::PACKET_ZIP);         // 去掉压缩标志位
	}
#endif

	if (msglen <= this->mCircularBuffer->getSize() - MsgCV::HEADER_SIZE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
* @brief 获取前面的第一个完整的消息数据块
*/
bool MMsgBuffer::popFront()
{
	bool ret = false;
	if (this->mCircularBuffer->getSize() > MsgCV::HEADER_SIZE)         // 至少要是 DataCV.HEADER_SIZE 大小加 1 ，如果正好是 DataCV.HEADER_SIZE ，那只能说是只有大小字段，没有内容
	{
		this->mCircularBuffer->frontBA(this->mHeaderBA, MsgCV::HEADER_SIZE);  // 如果不够整个消息的长度，还是不能去掉消息头的
		uint32 msglen = 0;
		this->mHeaderBA->readUnsignedInt32(msglen);

#ifdef MSG_COMPRESS
		if ((msglen & MsgCV.PACKET_ZIP) > 0)         // 如果有压缩标志
		{
			msglen &= (~MsgCV.PACKET_ZIP);         // 去掉压缩标志位
		}
#endif

		if (msglen <= this->mCircularBuffer->getSize() - MsgCV::HEADER_SIZE)
		{
			this->mCircularBuffer->popFrontLen(MsgCV::HEADER_SIZE);
			this->mCircularBuffer->popFrontBA(this->mMsgBodyBA, msglen);
			ret = true;
		}
	}

	if (this->mCircularBuffer->empty())     // 如果已经清空，就直接重置
	{
		this->mCircularBuffer->clear();    // 读写指针从头开始，方式写入需要写入两部分
	}

	return ret;
}

MY_END_NAMESPACE