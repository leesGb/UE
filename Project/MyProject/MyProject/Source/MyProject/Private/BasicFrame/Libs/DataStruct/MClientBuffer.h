#ifndef __MClientBuffer_H
#define __MClientBuffer_H

#include "MyProject.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MMsgBuffer;
template <class T> class MDynBuffer;
class MByteBuffer;
class MCircularBuffer;
class MMutex;

/**
* @brief 消息缓冲区
*/
class MClientBuffer : public GObject
{
protected:
	MMsgBuffer* mRawBuffer;			// 直接从服务器接收到的原始的数据，可能压缩和加密过
	MMsgBuffer* mMsgBuffer;			// 可以使用的缓冲区
	//MByteBuffer* mSendTmpBA;		// 发送临时缓冲区，发送的数据都暂时放在这里
	MMsgBuffer* mSendTmpBuffer;		// 发送临时缓冲区，发送的数据都暂时放在这里
	MByteBuffer* mSocketSendBA;     // 真正发送缓冲区

	MDynBuffer<char>* mDynBuffer;				// 接收到的临时数据，将要放到 mRawBuffer 中去
	MByteBuffer* mUnCompressHeaderBA;	// 存放解压后的头的长度
	MByteBuffer* mSendData;				// 存放将要发送的数据，将要放到 m_sendBuffer 中去
	MByteBuffer* mTmpData;				// 临时需要转换的数据放在这里
	MByteBuffer* mTmp1fData;			// 临时需要转换的数据放在这里

	MMutex* mReadMutex;				// 读互斥
	MMutex* mWriteMutex;				// 写互斥

#ifdef MSG_ENCRIPT
	CryptContext* mCryptContext;
#endif

public:
	MClientBuffer();
	~MClientBuffer();

	void init();
	void dispose();

	MDynBuffer<char>* getDynBuffer();
	MMsgBuffer* getSendTmpBuffer();
	MByteBuffer* getSendBuffer();
	MByteBuffer* getSendData();

#ifdef MSG_ENCRIPT
	void setCryptKey(byte[] encrypt)
	void checkDES()
#endif

	MMsgBuffer* getRawBuffer();
	void SetRevBufferSize(int32 size);
	void moveDyn2Raw();
	void moveRaw2Msg();
	void send(bool bnet = true);
	MByteBuffer* getMsg();
	// 获取数据，然后压缩加密
	void getSocketSendData();

protected:
	// 压缩加密每一个包
	void CompressAndEncryptEveryOne();
	// 压缩解密作为一个包
	void CompressAndEncryptAllInOne();
	// 消息格式
	// |------------- 加密的整个消息  -------------------------------------|
	// |----4 Header----|-压缩的 body----|----4 Header----|-压缩的 body----|
	// |                |                |                |                |
	void UnCompressAndDecryptEveryOne();
	void UnCompressAndDecryptAllInOne();
};

MY_END_NAMESPACE

#endif				// __MClientBuffer_H