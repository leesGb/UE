#include "MyProject.h"
#include "TableSys.h"
#include "TableBase.h"
#include "TableItemBase.h"
#include "Util.h"
#include "SystemEndian.h"
#include "TableObject.h"
#include "TableCard.h"
#include "TableSkill.h"
#include "TableItemHeader.h"
#include "TableItemBodyBase.h"
#include "ByteBuffer.h"

TableSys::TableSys()
{
    m_dicTable[TableID::TABLE_OBJECT] = new TableBase("ObjectBase_client", "ObjectBase_client", "ObjectBase_client");
    m_dicTable[TableID::TABLE_CARD] = new TableBase("CardBase_client", "CardBase_client", "CardBase_client");
    m_dicTable[TableID::TABLE_SKILL] = new TableBase("SkillBase_client", "SkillBase_client", "SkillBase_client");    // 添加一个表的步骤三
}

// 返回一个表
std::vector<TableItemBase*>* TableSys::getTable(TableID::TableID tableID)
{
	TableBase* table = m_dicTable[tableID];
	if (table == nullptr)
	{
		loadOneTable(tableID);
		table = m_dicTable[tableID];
	}
	return table->m_List;
}
		
// 返回一个表中一项，返回的时候表中数据全部加载到 Item 中
TableItemBase* TableSys::getItem(TableID::TableID tableID, uint32 itemID)
{
    TableBase* table = m_dicTable[tableID];
	if (nullptr == table->m_byteBuffer)
	{
		loadOneTable(tableID);
		table = m_dicTable[tableID];
	}
    TableItemBase* ret = TableSys::findDataItem(table, itemID);

	if (nullptr != ret && nullptr == ret->m_itemBody)
    {
        loadOneTableOneItemAll(tableID, table, ret);
    }

    if (ret == nullptr)
    {
		
    }

	return ret;
}
		
// 加载一个表
void TableSys::loadOneTable(TableID::TableID tableID)
{
	TableBase* table = m_dicTable[tableID];

    //LoadParam param = Ctx.m_instance.m_poolSys.newObject<LoadParam>();
    //param.m_path = Ctx.m_instance.m_cfg.m_pathLst[(int)ResPathType.ePathTablePath] + table.m_resName;
    //param.m_prefabName = table.m_prefabName;
    //param.m_loaded = onloaded;
    //param.m_loadNeedCoroutine = false;
    //param.m_resNeedCoroutine = false;
    //Ctx.m_instance.m_resLoadMgr.loadResources(param);
    ////TextAsset textAsset = Resources.Load(param.m_path, typeof(TextAsset)) as TextAsset;
    //Ctx.m_instance.m_poolSys.deleteObj(param);
}

// 加载一个表完成
//void TableSys::onloaded(IDispatchObject resEvt)
//{
//    m_res = resEvt as IResItem;                         // 类型转换
//    TextAsset textAsset = m_res.getObject("") as TextAsset;
//    if (textAsset != null)
//    {
//        m_byteArray = Ctx.m_instance.m_factoryBuild.buildByteArray();
//        m_byteArray.clear();
//        m_byteArray.writeBytes(textAsset.bytes, 0, (uint)textAsset.bytes.Length);
//        m_byteArray.setPos(0);
//        readTable(getTableIDByPath(m_res.GetPath()), m_byteArray);
//    }
//}

// 根据路径查找表的 ID
TableID::TableID TableSys::getTableIDByPath(std::string& path)
{
	TableMapIte beginIte = m_dicTable.begin();
	TableMapIte endIte = m_dicTable.end();
	for(; beginIte != endIte; ++beginIte)
    {
		if (beginIte->second->m_prefabName == path)
        {
			return beginIte->first;
        }
    }

	return (TableID::TableID)0;
}

// 加载一个表中一项的所有内容
void TableSys::loadOneTableOneItemAll(TableID::TableID tableID, TableBase* table, TableItemBase* itemBase)
{
    if (TableID::TABLE_OBJECT == tableID)
    {
		itemBase->parseBodyByteArray<TableObjectItemBody>(table->m_byteBuffer, itemBase->m_itemHeader->m_offset);
    }
    else if (TableID::TABLE_CARD == tableID)
    {
		itemBase->parseBodyByteArray<TableCardItemBody>(table->m_byteBuffer, itemBase->m_itemHeader->m_offset);
    }
	else if (TableID::TABLE_SKILL == tableID)  // 添加一个表的步骤四
    {
		itemBase->parseBodyByteArray<TableSkillItemBody>(table->m_byteBuffer, itemBase->m_itemHeader->m_offset);
    }
}
		
// 获取一个表的名字
std::string& TableSys::getTableName(TableID::TableID tableID)
{
	TableBase* table = m_dicTable[tableID];
	if (table != nullptr)
	{
		return table->m_tableName;
	}			
	return Util::m_sDefaultStr;
}

// 读取一个表，仅仅读取表头
void TableSys::readTable(TableID::TableID tableID, ByteBuffer* bytes)
{
    TableBase* table = m_dicTable[tableID];
	table->m_byteBuffer = bytes;

	bytes->setEndian(eSys_LITTLE_ENDIAN);
	uint32 len;
	bytes->readUnsignedInt32(len);
    uint32 i = 0;
    TableItemBase* item = nullptr;
    for (i = 0; i < len; i++)
    {
        //if (TableID.TABLE_OBJECT == tableID)
        //{
        //    item = new TableItemObject();
        //}
        item = new TableItemBase();
        item->parseHeaderByteArray(bytes);
        // 加载完整数据
        //loadOneTableOneItemAll(tableID, table, item);
        //if (TableID.TABLE_OBJECT == tableID)
        //{
            //item.parseAllByteArray<TableObjectItemBody>(bytes);
        //}
        table->m_List->push_back(item);
    }
}

// 查找表中的一项
TableItemBase* TableSys::findDataItem(TableBase* table, uint32 id)
{
	int size = table->m_List->size();
	int low = 0;
	int high = size - 1;
	int middle = 0;
	uint32 idCur;
			
	while (low <= high)
	{
		middle = (low + high) / 2;
        idCur = (*(table->m_List))[middle]->m_itemHeader->m_uID;
		if (idCur == id)
		{
			break;
		}
		if (id < idCur)
		{
			high = middle - 1;
		}
		else
		{
			low = middle + 1;
		}
	}
			
	if (low <= high)
	{
        return (*(table->m_List))[middle];
	}
	return nullptr;
}