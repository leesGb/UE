﻿#include "MyProject.h"
#include "TaskThread.h"
#include "MCondition.h"
#include "TaskQueue.h"

TaskThread::TaskThread(std::string name, TaskQueue* taskQueue)
    : Super(name)
{
    mTaskQueue = taskQueue;
    mCondition = new MCondition(name);
}

/**
 *brief 线程回调函数
 */
uint32 TaskThread::Run(void)
{
    while (!mIsExitFlag)
    {
        mCurTask = mTaskQueue->pop();
        if(mCurTask != nullptr)
        {
            mCurTask->runTask();
        }
        else
        {
            mCondition->wait();
        }
    }
}

bool TaskThread::notifySelf()
{
    if(mCondition->canEnterWait)
    {
        mCondition->notifyAll();
        return true;
    }

    return false;
}