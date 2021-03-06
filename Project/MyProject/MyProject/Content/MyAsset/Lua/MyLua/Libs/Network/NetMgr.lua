MLoader("MyLua.Libs.Network.NetCommand");
MLoader("MyLua.Libs.ProtoBuf.ProtobufUtil");
MLoader("MyLua.Libs.Network.CmdDispatch.CmdDispatchInfo");

local g_CmdDispInfo = GlobalNS.CmdDispatchInfo;

local M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "NetMgr";
GlobalNS[M.clsName] = M;

function M:init()
    GlobalNS.ProtobufUtil.registerAll();
end

function M:sendCmd(id, data, isNetSend)
    if(isNetSend == nil or isNetSend == true) then
        local command = NetCommand[id];
		
        if(data == nil) then
            data = {};
        end
		
        if(command ~= nil) then
            Ctx.mLogSys:log("NetMgr::sendCmd id = " .. id .. " Proto: " .. command.proto, GlobalNS.LogTypeId.eLogCommon);
            local buffer = GlobalNS.ProtobufUtil.encode(command.proto, data);
            GlobalNS.CSSystem.sendFromLua(id, buffer);
        end
    end
end

-- RPC 包
function M:sendCmdRpc(id, rpc, data, isNetSend)
    if(isNetSend == nil or isNetSend == true) then
        local command = NetCommand[id];
		
        if(data == nil) then
            data = {};
        end
		
        if(command ~= nil) then
            Ctx.mLogSys:log("NetMgr::sendCmd id = " .. id .. " Proto: " .. command.proto, GlobalNS.LogTypeId.eLogCommon);
            local buffer = GlobalNS.ProtobufUtil.encode(command.proto, data);
			rpc.request.content = buffer;
			
			command = NetCommand[3];
			
			if(command ~= nil) then
				local rpcBuffer = GlobalNS.ProtobufUtil.encode(command.proto, rpc);
				GlobalNS.CSSystem.sendFromLuaRpc(rpcBuffer);
			end
        end
    end
end

function M:receiveCmd(id, buffer)
    Ctx.mLogSys:log("NetMgr::receiveCmd id = " .. id, GlobalNS.LogTypeId.eLogCommon);
    local command = NetCommand[id];
	
    if(command ~= nil) then
        local data = GlobalNS.ProtobufUtil.decode(command.proto, buffer, buffer.mLength);
		
        if(data ~= nil) then
            Ctx.mLogSys:log("NetMgr handleMsg", GlobalNS.LogTypeId.eLogCommon);
            Ctx.mNetCmdNotify:handleMsg(data);
        end
    end
end

-- RPC 包
function M:receiveCmdRpc(buffer, length)
    Ctx.mLogSys:log("NetMgr::receiveCmdRpc", GlobalNS.LogTypeId.eLogCommon);
    local command = NetCommand[3];
	
    if(command ~= nil) then
        local rpcData = GlobalNS.ProtobufUtil.decode(command.proto, buffer, length);
		--local rpcData = GlobalNS.ProtobufUtil.decode(command.proto, buffer);
		
        if(rpcData ~= nil and rpcData.response ~= nil) then
			Ctx.mLogSys:log("NetMgr::receiveCmdRpc id = " .. rpcData.response.id, GlobalNS.LogTypeId.eLogCommon);
			command = NetCommand[rpcData.response.id + 1];
			
			if(command ~= nil) then
				local msgBody = GlobalNS.ProtobufUtil.decode(command.proto, rpcData.response.content);
				Ctx.mLogSys:log("NetMgr handleMsg", GlobalNS.LogTypeId.eLogCommon);
				
				g_CmdDispInfo.byCmd = rpcData.response.id + 1;
				g_CmdDispInfo.byParam = rpcData.response.id + 1;
				g_CmdDispInfo.bu = msgBody;
				
				Ctx.mNetCmdNotify:handleMsg(g_CmdDispInfo);
			end
        end
    end
end

return M;