OverseaHostHelper = {}

OverseaHostHelper.hostList = nil
OverseaHostHelper.curServerData = nil
OverseaHostHelper.PlayerPrefsMYServer = "PlayerPrefsMYServer";


OverseaHostHelper.hostList = nil
OverseaHostHelper.regions = nil
OverseaHostHelper.langZone = ApplicationInfo.GetSystemLanguage();

function OverseaHostHelper:RefreshHostInfo(hostList)
    OverseaHostHelper.hostList = hostList
end

function OverseaHostHelper:RefreshLangZone(accData)
    helplog('OverseaHostHelper:RefreshLangZone')
    local langZone = accData.lang_zone
    local regions = accData.regions
    if langZone ~=nil then
        helplog("RefreshLangZone:" .. langZone)
        OverseaHostHelper.langZone = langZone
    end
    helplog(#accData.regions)
    if regions ~= nil then
        helplog("set regions")
        OverseaHostHelper.regions = regions
    end
end

function OverseaHostHelper:ResetSectors(serverid)
    helplog('OverseaHostHelper:ResetSectors:'..serverid)
    if OverseaHostHelper.regions ~= nil then
        for _,v in pairs(OverseaHostHelper.regions) do
            helplog("in:"..v.serverid)
            if tostring(v.serverid) == tostring(serverid) then
                helplog("find sectors:"..tostring(serverid))
                UnionConfig.Zone.zone_name = v.sectors
                break
            end
        end
    else
        helplog("OverseaHostHelper.regions is nil")
    end
    
    helplog('cur sectors');
    for _,v in pairs(UnionConfig.Zone.zone_name) do
        helplog(v.name_prefix .. ":" .. "min:"..v.min.."-".."max:"..v.max)
    end
end

function OverseaHostHelper:RefreshServerInfo(serverData)
    --todo xde 全球版多个区域选择
--    OverseaHostHelper.curServerData = serverData
--    if OverseaHostHelper.curServerData ~= nil then
--        OverseaHostHelper.curServerData.id = OverseaHostHelper.curServerData.serverid
--    end
end

function OverseaHostHelper:GetHosts()
    --todo xde 全球版多个区域选择
--    return OverseaHostHelper.curServerData.gateways

    local hosts = {}
    if OverseaHostHelper.hostList~=nil then
        for k,v in pairs(OverseaHostHelper.hostList) do
            table.insert(hosts, v.host)
        end
    end
    return hosts
end

function OverseaHostHelper:GetRoleIde()
    local roleInfo = ServiceUserProxy.Instance:GetNewRoleInfo()
    roleInfo = roleInfo ~=nil and roleInfo or ServiceUserProxy.Instance:GetRoleInfo()
    local roleId = roleInfo.id
    local timestamp = os.time()
    local ide = roleId .. tostring(timestamp)
    helplog(ide)
    return ide
end

function OverseaHostHelper:CheckStoreIap()
    -- 判断是否有用户
    if(ServiceUserProxy.Instance:GetRoleInfo()~=nil) then
        local promotingIap = PlayerPrefs.GetString("PromotingIAP")
        local curProduct = nil
        for _,v in pairs(Table_Deposit) do
            local tpro = v
            if(promotingIap ~= "" and tpro.ProductID == promotingIap) then
                curProduct = tpro
                break
            end
        end
        if(curProduct ~= nil) then
            helplog("OverseaHostHelper:CheckStoreIap:" .. promotingIap);
            EventManager.Me():AddEventListener(ServiceEvent.UserEventQueryChargeCnt, self.OnReceiveQueryChargeCnt, self)
            ServiceUserEventProxy.Instance:CallQueryChargeCnt()
        else
            helplog("不存在缓存的Store 预售,不触发")
        end
    else
        helplog("还未登录,不触发")
    end
end

function OverseaHostHelper:OnReceiveQueryChargeCnt(data)
    EventManager.Me():RemoveEventListener(ServiceEvent.UserEventQueryChargeCnt, self.OnReceiveQueryChargeCnt, self)
    GameFacade.Instance:sendNotification(UIEvent.JumpPanel,{view = PanelConfig.StorePayPanel, viewdata = {}});
end

function OverseaHostHelper:StoreIap(msg)
    --    helplog(msg)
    PlayerPrefs.SetString("PromotingIAP",msg)
    OverseaHostHelper:CheckStoreIap()
end

function OverseaHostHelper:ZoneInfoToNum(name,zid)
    local info
    for _,v in pairs(UnionConfig.Zone.zone_name) do
        if v.name_prefix == name then
            info = v
            break
        end
    end
    if info == nil then
        MsgManager.FloatMsg("",ZhString.ZoneStrError)
        return nil
    end
    local min = info.min
    local max = info.max
    local range = max - min + 1
    local numberZid = tonumber(zid)
    local rNum = min + numberZid - 1
    if numberZid == nil or numberZid == 0 or numberZid > range then
        MsgManager.FloatMsg("",string.format(ZhString.ChangeZoneError,tostring(range)))
        return nil
    end
    return rNum
end

function OverseaHostHelper:GetCurZoneInfo()
    return self:GetZoneInfo(MyselfProxy.Instance:GetZoneId())
end

function OverseaHostHelper:GetZoneInfo(num)
    if(num and num > 0)then
        if(num >= 9000)then
            return {
                name = ZhString.ChangeZoneProxy_PvpLine,
                id = ""
            };
        end
        
        local unionZoneList = UnionConfig.Zone.zone_name
        if unionZoneList then
            for i=1,#unionZoneList do
                local zone = unionZoneList[i]
                if num >= zone.min and num <= zone.max then
                    return {
                        name = zone.name_prefix,
                        id = (num - zone.min + 1)
                    };
                end
            end
        end
    end
end            
            
function OverseaHostHelper:RefreshPriceInfo()
    local pIds = {};
    for _, v in pairs(Table_Deposit) do
        local productConf = v
        table.insert(pIds,productConf.ProductID)
    end
    local pIdStr = ""
    for i=1,#pIds do
        local pId = pIds[i]
        pIdStr = pIdStr .. pId
        if i<#pIds then
            pIdStr = pIdStr .. ","
        end
    end
    Debug.Log(pIdStr)
--    local msg = "com.gravity.romg.zeny12|¥12,_com.gravity.romg.zeny30|¥30,com.gravity.romg.zeny68|¥68,com.gravity.romg.coin30|¥30,com.gravity.romg.yueka|aa"
    OverSeas_TW.OverSeasManager.GetInstance():QueryProduct(pIdStr,function(msg)
        Debug.Log("QueryProduct result!")
        Debug.Log(msg)
        local infos = string.split(msg,'#')
        for _,v in pairs(infos) do
            local pInfo = string.split(v,'|')
            local pId = pInfo[1]
            local priceStr = pInfo[2]
            for _, v in pairs(Table_Deposit) do
                local productConf = v
                if productConf.ProductID == pId then
                    productConf.priceStr = priceStr
                    break
                end
            end
        end
    end)
end

function OverseaHostHelper:FilterLangStr(origin)
    if(AppBundleConfig.GetSDKLang() == 'th') then
        origin = string.gsub(origin, "×", "x")
        origin = string.gsub(origin, "{uiicon=tips_icon_01} \n", "")
        origin = string.gsub(origin, "{uiicon=tips_icon_01} \r\n", "")
    end
    -- 英文需要将全角加号换位半角的，不然影响 string parseText (string text, int line)
    if(AppBundleConfig.GetSDKLang() == 'en' or AppBundleConfig.GetSDKLang() == 'th') then
        origin = string.gsub(origin, "＋", "+")
        -- 0003087: 恶魔波利卡片的描述中有一条属性换行显示（仅泰文语言环境）
        -- 插入空格制造换行
        origin = origin:gsub('ได้รับความเสียหายจากธาตุทั้งหมด', 'ได้รับความเสียหายจากธาตุทั้งหมด ')
        -- 0003067: 泰文模式下，巴风特卡片的道具描述，换行显示
        origin = origin:gsub('สร้างความเสียหายต่อมอนสเตอร์ทั้งหมด', 'สร้างความเสียหายต่อมอนสเตอร์ทั้งหมด ')
        origin = origin:gsub('ทำให้เกิดความเสียหายต่อเป้าหมายและเป้', 'ทำให้เกิดความเสียหายต่อเป้าหมายและเป้ ')
    end
    -- 去除换行符前的空格
    if(AppBundleConfig.GetSDKLang() == 'id')  and origin:find("每个大类下不同道具抽取概率略有不同") == nil then
        origin = string.gsub(origin, "＋", "+")
        origin, tmp = string.gsub(origin, "%s\n", "\n")
        -- helplog(origin, tmp)
    end
    return origin
end

-- 将全角字符转化成半角字符，优先翻译不然转化后会找不到翻译
function OverseaHostHelper:FullWidthToHalfWidth(str)
    local ret = OverSea.LangManager.Instance():GetLangByKey(str)
    ret = ret:gsub("＋", "+")
    ret = ret:gsub("，", ",")
    ret = ret:gsub("：", ":")
    return ret
end

-- 因为 parseText 有 bug，需要特殊处理
function OverseaHostHelper:SpecialProcess(str)
    if(AppBundleConfig.GetSDKLang() == 'th') then
        str = str:gsub("Christmas Song 30%%  : Atk %+3%%", "Christmas Song 30%%: Atk +3%%")
        -- xdlog(str)
    end
    if(AppBundleConfig.GetSDKLang() == 'vi') then
        str = OverseaHostHelper:FullWidthToHalfWidth(str)
        str = str:gsub("Phổ công có 30%% xác suất diễn tấu Ca khúc Noel:Atk%+3%%,Equip.ASPD%+3%%,liên tục 10s", "Phổ công có 30%% xác suất   diễn tấu Ca khúc Noel: Atk+3%%, Equip.ASPD+3%%, liên tục 10s")
        -- xdlog(str)
    end
    if(AppBundleConfig.GetSDKLang() == 'id') then
        str = OverseaHostHelper:FullWidthToHalfWidth(str)
    end
    return str
end

function OverseaHostHelper:IsChinese()
    return OverSea.LangManager.Instance().CurSysLang == 'ChineseSimplified'
end

function OverseaHostHelper:FixLabelOver(label,width)
    label.overflowMethod = 3
    label.width = width
end

function OverseaHostHelper:ShrinkFixLabelOver(label,width)
    label.overflowMethod = 0
    label.width = width
end

function OverseaHostHelper:FixLabelOverV1(label, overflow, width)
    label.overflowMethod = overflow
    label.width = width
end

function OverseaHostHelper:FixAnchor(fromAnchor, target, relative, absolute)
    fromAnchor.target = target
    fromAnchor.relative = relative
    fromAnchor.absolute = absolute
end

OverseaHostHelper.isGuest = 0
function OverseaHostHelper:GuestExchangeForbid()
    if OverseaHostHelper.isGuest == 1 then
        MsgManager.FloatMsg("",ZhString.GuestExchangeForbid)
    end
    return OverseaHostHelper.isGuest
end

TransformExtenstion = {}

function TransformExtenstion:AddLocalPositionX(transform, offsetX)
    local exPos = transform.localPosition
    local v=Vector3(exPos.x+offsetX, exPos.y, exPos.z)
    transform.localPosition = v
end