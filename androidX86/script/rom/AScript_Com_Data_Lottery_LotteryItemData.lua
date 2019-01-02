LotteryItemData = class("LotteryItemData")

function LotteryItemData:ctor(data)
	self:SetData(data)
end

function LotteryItemData:SetData(data)
	if data then
		self.id = data.id
		self.itemid = data.itemid

		self.female_itemid = data.female_itemid

		self.count = data.count
		self.recoverPrice = data.recover_price
		self.recoverItemid = data.recover_itemid
		self.rate = data.rate
		self.rarity = data.rarity
		self.isCurBatch = data.cur_batch	--是否是当前批次
	end
end

function LotteryItemData:GetItemData()
	if self.itemData == nil then
		local itemid = self.itemid;
		if(self.female_itemid and self.female_itemid~=0)then
			local sex = Game.Myself.data.userdata:Get(UDEnum.SEX) or 1;
			if(sex == 2)then
				itemid = self.female_itemid;
			end
		end
		self.itemData = ItemData.new("LotteryItem", itemid)
		self.itemData.num = self.count
	end

	return self.itemData
end

function LotteryItemData:GetRateString()
	if self.rate then
		local rate = self.rate / 10000
		if math.floor(rate) < rate then
			return string.format("%s%%", rate)
		else
			return string.format("%d%%", rate)
		end
	end

	return "0%"
end