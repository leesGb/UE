﻿#pragma once

#include "InsResBase.h"

/**
* @brief
UE4:C++中使用材质
http://blog.csdn.net/lzt20007/article/details/51285926
*/

class MatRes : InsResBase
{
    protected Material m_mat;

    public MatRes()
    {

    }

    public Material getMat()
    {
        return m_mat;
    }

    override protected void initImpl(ResItem res)
    {
        // 获取资源单独保存
        m_mat = res.getObject(res.getPrefabName()) as Material;

        base.initImpl(res);
    }

    public override void unload()
    {
        if (m_mat != null)
        {
            // 这个接口不知道行不行
            UtilApi.UnloadAsset(m_mat);
            m_mat = null;

            // 这个接口肯定可以
            //UtilApi.UnloadUnusedAssets();
        }

        base.unload();
    }
}