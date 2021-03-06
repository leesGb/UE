﻿#include "MyProject.h"
#include "TaskQueue.h"
#include "ITask.h"
#include "TaskThreadPool.h"

MY_BEGIN_NAMESPACE(MyNS)

TaskQueue::TaskQueue(std::string name)
    : Super(name)
{
	mTaskThreadPool = MY_NEW TaskThreadPool();
}

void TaskQueue::push(ITask* item)
{
	Super::push(item);

    // 检查是否有线程空闲，如果有就唤醒
    mTaskThreadPool->notifyIdleThread();
}

MY_END_NAMESPACE