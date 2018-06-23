﻿#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 鼠标分发系统
 */
class MMouseDispatch : public GObject
{
    private AddOnceEventDispatch mOnMouseDownDispatch;
    private AddOnceEventDispatch mOnMouseUpDispatch;
    private AddOnceEventDispatch mOnMousePressDispatch;
    private AddOnceEventDispatch mOnMouseMoveDispatch;
    private AddOnceEventDispatch mOnMousePressMoveDispatch;
    private AddOnceEventDispatch mOnMouseCanceledDispatch;

    public MMouseDispatch()
    {
        this.mOnMouseDownDispatch = new AddOnceEventDispatch();
        this.mOnMouseUpDispatch = new AddOnceEventDispatch();
        this.mOnMousePressDispatch = new AddOnceEventDispatch();
        this.mOnMouseMoveDispatch = new AddOnceEventDispatch();
        this.mOnMousePressMoveDispatch = new AddOnceEventDispatch();
        this.mOnMouseCanceledDispatch = new AddOnceEventDispatch();
    }

    public void init()
    {

    }

    public void dispose()
    {

    }

    public void addMouseListener(InputEventId evtID, MEventDispatchAction<IDispatchObject> handle)
    {
        if (InputEventId.MOUSEDOWN_EVENT == evtID)
        {
            this.mOnMouseDownDispatch.addEventHandle(null, handle);
        }
        else if (InputEventId.MOUSEUP_EVENT == evtID)
        {
            this.mOnMouseUpDispatch.addEventHandle(null, handle);
        }
        else if (InputEventId.MOUSEPRESS_EVENT == evtID)
        {
            this.mOnMousePressDispatch.addEventHandle(null, handle);
        }
        else if (InputEventId.MOUSEMOVE_EVENT == evtID)
        {
            this.mOnMouseMoveDispatch.addEventHandle(null, handle);
        }
        else if (InputEventId.MOUSEPRESS_MOVE_EVENT == evtID)
        {
            this.mOnMousePressMoveDispatch.addEventHandle(null, handle);
        }
    }

    public void removeMouseListener(InputEventId evtID, MEventDispatchAction<IDispatchObject> handle)
    {
        if (InputEventId.KEYUP_EVENT == evtID)
        {
            this.mOnMouseDownDispatch.removeEventHandle(null, handle);
        }
        else if (InputEventId.KEYDOWN_EVENT == evtID)
        {
            this.mOnMouseUpDispatch.removeEventHandle(null, handle);
        }
        else if (InputEventId.KEYPRESS_EVENT == evtID)
        {
            this.mOnMousePressDispatch.removeEventHandle(null, handle);
        }
        else if (InputEventId.MOUSEMOVE_EVENT == evtID)
        {
            this.mOnMouseMoveDispatch.removeEventHandle(null, handle);
        }
        else if (InputEventId.MOUSEPRESS_MOVE_EVENT == evtID)
        {
            this.mOnMousePressMoveDispatch.removeEventHandle(null, handle);
        }
    }

    // 是否还有需要处理的事件
    public bool hasEventHandle()
    {
        if (this.mOnMouseDownDispatch.hasEventHandle())
        {
            return true;
        }
        if (this.mOnMouseUpDispatch.hasEventHandle())
        {
            return true;
        }
        if (this.mOnMousePressDispatch.hasEventHandle())
        {
            return true;
        }
        if (this.mOnMousePressMoveDispatch.hasEventHandle())
        {
            return true;
        }

        return false;
    }

    public void handleMouseDown(MMouseOrTouch mouse)
    {
        if (null != this.mOnMouseDownDispatch)
        {
            this.mOnMouseDownDispatch.dispatchEvent(mouse);
        }
    }

    public void handleMouseUp(MMouseOrTouch mouse)
    {
        if (null != this.mOnMouseUpDispatch)
        {
            this.mOnMouseUpDispatch.dispatchEvent(mouse);
        }
    }

    public void handleMousePress(MMouseOrTouch mouse)
    {
        if (null != this.mOnMousePressDispatch)
        {
            this.mOnMousePressDispatch.dispatchEvent(mouse);
        }
    }

    public void handleMousePressOrMove(MMouseOrTouch mouse)
    {
        if (null != this.mOnMouseMoveDispatch)
        {
            this.mOnMouseMoveDispatch.dispatchEvent(mouse);
        }
    }

    public void handleMousePressMove(MMouseOrTouch mouse)
    {
        if (null != this.mOnMousePressMoveDispatch)
        {
            this.mOnMousePressMoveDispatch.dispatchEvent(mouse);
        }
    }
};

MY_END_NAMESPACE