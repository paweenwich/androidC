-- Generated By protoc-gen-lua Do not Edit
local protobuf = protobuf
autoImport("xCmd_pb") 
local xCmd_pb = xCmd_pb
module('PveCard_pb')


EPVECARDPARAM = protobuf.EnumDescriptor();
EPVECARDPARAM_EPVE_INVITE_TEAM_CMD_ENUM = protobuf.EnumValueDescriptor();
EPVECARDPARAM_EPVE_REPLY_TEAM_CMD_ENUM = protobuf.EnumValueDescriptor();
EPVECARDPARAM_EPVE_ENTER_RAID_CMD_ENUM = protobuf.EnumValueDescriptor();
EPVECARDPARAM_EPVE_QUERY_ALL_CARD_CMD_ENUM = protobuf.EnumValueDescriptor();
EPVECARDPARAM_EPVE_SELECT_CARD_CMD_ENUM = protobuf.EnumValueDescriptor();
EPVECARDPARAM_EPVE_SELECTED_CARD_CMD_ENUM = protobuf.EnumValueDescriptor();
EPVECARDPARAM_EPVE_UPDATE_CARD_CMD_ENUM = protobuf.EnumValueDescriptor();
EPVECARDPARAM_EPVE_BEGIN_FIRE_CMD_ENUM = protobuf.EnumValueDescriptor();
EPVECARDPARAM_EPVE_FINISH_CARD_CMD_ENUM = protobuf.EnumValueDescriptor();
EPVECARDPARAM_EPVE_PLAY_CARD_CMD_ENUM = protobuf.EnumValueDescriptor();
INVITEPVECARDCMD = protobuf.Descriptor();
INVITEPVECARDCMD_CMD_FIELD = protobuf.FieldDescriptor();
INVITEPVECARDCMD_PARAM_FIELD = protobuf.FieldDescriptor();
INVITEPVECARDCMD_CONFIGID_FIELD = protobuf.FieldDescriptor();
INVITEPVECARDCMD_ISCANCEL_FIELD = protobuf.FieldDescriptor();
REPLYPVECARDCMD = protobuf.Descriptor();
REPLYPVECARDCMD_CMD_FIELD = protobuf.FieldDescriptor();
REPLYPVECARDCMD_PARAM_FIELD = protobuf.FieldDescriptor();
REPLYPVECARDCMD_AGREE_FIELD = protobuf.FieldDescriptor();
REPLYPVECARDCMD_CHARID_FIELD = protobuf.FieldDescriptor();
ENTERPVECARDCMD = protobuf.Descriptor();
ENTERPVECARDCMD_CMD_FIELD = protobuf.FieldDescriptor();
ENTERPVECARDCMD_PARAM_FIELD = protobuf.FieldDescriptor();
ENTERPVECARDCMD_CONFIGID_FIELD = protobuf.FieldDescriptor();
PVECARDINFO = protobuf.Descriptor();
PVECARDINFO_INDEX_FIELD = protobuf.FieldDescriptor();
PVECARDINFO_CARDIDS_FIELD = protobuf.FieldDescriptor();
QUERYCARDINFOCMD = protobuf.Descriptor();
QUERYCARDINFOCMD_CMD_FIELD = protobuf.FieldDescriptor();
QUERYCARDINFOCMD_PARAM_FIELD = protobuf.FieldDescriptor();
QUERYCARDINFOCMD_CARDS_FIELD = protobuf.FieldDescriptor();
SELECTPVECARDCMD = protobuf.Descriptor();
SELECTPVECARDCMD_CMD_FIELD = protobuf.FieldDescriptor();
SELECTPVECARDCMD_PARAM_FIELD = protobuf.FieldDescriptor();
SELECTPVECARDCMD_INDEX_FIELD = protobuf.FieldDescriptor();
SYNCPROCESSPVECARDCMD = protobuf.Descriptor();
SYNCPROCESSPVECARDCMD_CMD_FIELD = protobuf.FieldDescriptor();
SYNCPROCESSPVECARDCMD_PARAM_FIELD = protobuf.FieldDescriptor();
SYNCPROCESSPVECARDCMD_CARD_FIELD = protobuf.FieldDescriptor();
SYNCPROCESSPVECARDCMD_PROCESS_FIELD = protobuf.FieldDescriptor();
UPDATEPROCESSPVECARDCMD = protobuf.Descriptor();
UPDATEPROCESSPVECARDCMD_CMD_FIELD = protobuf.FieldDescriptor();
UPDATEPROCESSPVECARDCMD_PARAM_FIELD = protobuf.FieldDescriptor();
UPDATEPROCESSPVECARDCMD_PROCESS_FIELD = protobuf.FieldDescriptor();
BEGINFIREPVECARDCMD = protobuf.Descriptor();
BEGINFIREPVECARDCMD_CMD_FIELD = protobuf.FieldDescriptor();
BEGINFIREPVECARDCMD_PARAM_FIELD = protobuf.FieldDescriptor();
FINISHPLAYCARDCMD = protobuf.Descriptor();
FINISHPLAYCARDCMD_CMD_FIELD = protobuf.FieldDescriptor();
FINISHPLAYCARDCMD_PARAM_FIELD = protobuf.FieldDescriptor();
PLAYPVECARDCMD = protobuf.Descriptor();
PLAYPVECARDCMD_CMD_FIELD = protobuf.FieldDescriptor();
PLAYPVECARDCMD_PARAM_FIELD = protobuf.FieldDescriptor();
PLAYPVECARDCMD_NPCGUID_FIELD = protobuf.FieldDescriptor();
PLAYPVECARDCMD_CARDIDS_FIELD = protobuf.FieldDescriptor();

EPVECARDPARAM_EPVE_INVITE_TEAM_CMD_ENUM.name = "EPVE_INVITE_TEAM_CMD"
EPVECARDPARAM_EPVE_INVITE_TEAM_CMD_ENUM.index = 0
EPVECARDPARAM_EPVE_INVITE_TEAM_CMD_ENUM.number = 1
EPVECARDPARAM_EPVE_REPLY_TEAM_CMD_ENUM.name = "EPVE_REPLY_TEAM_CMD"
EPVECARDPARAM_EPVE_REPLY_TEAM_CMD_ENUM.index = 1
EPVECARDPARAM_EPVE_REPLY_TEAM_CMD_ENUM.number = 2
EPVECARDPARAM_EPVE_ENTER_RAID_CMD_ENUM.name = "EPVE_ENTER_RAID_CMD"
EPVECARDPARAM_EPVE_ENTER_RAID_CMD_ENUM.index = 2
EPVECARDPARAM_EPVE_ENTER_RAID_CMD_ENUM.number = 3
EPVECARDPARAM_EPVE_QUERY_ALL_CARD_CMD_ENUM.name = "EPVE_QUERY_ALL_CARD_CMD"
EPVECARDPARAM_EPVE_QUERY_ALL_CARD_CMD_ENUM.index = 3
EPVECARDPARAM_EPVE_QUERY_ALL_CARD_CMD_ENUM.number = 4
EPVECARDPARAM_EPVE_SELECT_CARD_CMD_ENUM.name = "EPVE_SELECT_CARD_CMD"
EPVECARDPARAM_EPVE_SELECT_CARD_CMD_ENUM.index = 4
EPVECARDPARAM_EPVE_SELECT_CARD_CMD_ENUM.number = 5
EPVECARDPARAM_EPVE_SELECTED_CARD_CMD_ENUM.name = "EPVE_SELECTED_CARD_CMD"
EPVECARDPARAM_EPVE_SELECTED_CARD_CMD_ENUM.index = 5
EPVECARDPARAM_EPVE_SELECTED_CARD_CMD_ENUM.number = 6
EPVECARDPARAM_EPVE_UPDATE_CARD_CMD_ENUM.name = "EPVE_UPDATE_CARD_CMD"
EPVECARDPARAM_EPVE_UPDATE_CARD_CMD_ENUM.index = 6
EPVECARDPARAM_EPVE_UPDATE_CARD_CMD_ENUM.number = 7
EPVECARDPARAM_EPVE_BEGIN_FIRE_CMD_ENUM.name = "EPVE_BEGIN_FIRE_CMD"
EPVECARDPARAM_EPVE_BEGIN_FIRE_CMD_ENUM.index = 7
EPVECARDPARAM_EPVE_BEGIN_FIRE_CMD_ENUM.number = 8
EPVECARDPARAM_EPVE_FINISH_CARD_CMD_ENUM.name = "EPVE_FINISH_CARD_CMD"
EPVECARDPARAM_EPVE_FINISH_CARD_CMD_ENUM.index = 8
EPVECARDPARAM_EPVE_FINISH_CARD_CMD_ENUM.number = 9
EPVECARDPARAM_EPVE_PLAY_CARD_CMD_ENUM.name = "EPVE_PLAY_CARD_CMD"
EPVECARDPARAM_EPVE_PLAY_CARD_CMD_ENUM.index = 9
EPVECARDPARAM_EPVE_PLAY_CARD_CMD_ENUM.number = 10
EPVECARDPARAM.name = "EPveCardParam"
EPVECARDPARAM.full_name = ".Cmd.EPveCardParam"
EPVECARDPARAM.values = {EPVECARDPARAM_EPVE_INVITE_TEAM_CMD_ENUM,EPVECARDPARAM_EPVE_REPLY_TEAM_CMD_ENUM,EPVECARDPARAM_EPVE_ENTER_RAID_CMD_ENUM,EPVECARDPARAM_EPVE_QUERY_ALL_CARD_CMD_ENUM,EPVECARDPARAM_EPVE_SELECT_CARD_CMD_ENUM,EPVECARDPARAM_EPVE_SELECTED_CARD_CMD_ENUM,EPVECARDPARAM_EPVE_UPDATE_CARD_CMD_ENUM,EPVECARDPARAM_EPVE_BEGIN_FIRE_CMD_ENUM,EPVECARDPARAM_EPVE_FINISH_CARD_CMD_ENUM,EPVECARDPARAM_EPVE_PLAY_CARD_CMD_ENUM}
INVITEPVECARDCMD_CMD_FIELD.name = "cmd"
INVITEPVECARDCMD_CMD_FIELD.full_name = ".Cmd.InvitePveCardCmd.cmd"
INVITEPVECARDCMD_CMD_FIELD.number = 1
INVITEPVECARDCMD_CMD_FIELD.index = 0
INVITEPVECARDCMD_CMD_FIELD.label = 1
INVITEPVECARDCMD_CMD_FIELD.has_default_value = true
INVITEPVECARDCMD_CMD_FIELD.default_value = 66
INVITEPVECARDCMD_CMD_FIELD.enum_type = XCMD_PB_COMMAND
INVITEPVECARDCMD_CMD_FIELD.type = 14
INVITEPVECARDCMD_CMD_FIELD.cpp_type = 8

INVITEPVECARDCMD_PARAM_FIELD.name = "param"
INVITEPVECARDCMD_PARAM_FIELD.full_name = ".Cmd.InvitePveCardCmd.param"
INVITEPVECARDCMD_PARAM_FIELD.number = 2
INVITEPVECARDCMD_PARAM_FIELD.index = 1
INVITEPVECARDCMD_PARAM_FIELD.label = 1
INVITEPVECARDCMD_PARAM_FIELD.has_default_value = true
INVITEPVECARDCMD_PARAM_FIELD.default_value = 1
INVITEPVECARDCMD_PARAM_FIELD.enum_type = EPVECARDPARAM
INVITEPVECARDCMD_PARAM_FIELD.type = 14
INVITEPVECARDCMD_PARAM_FIELD.cpp_type = 8

INVITEPVECARDCMD_CONFIGID_FIELD.name = "configid"
INVITEPVECARDCMD_CONFIGID_FIELD.full_name = ".Cmd.InvitePveCardCmd.configid"
INVITEPVECARDCMD_CONFIGID_FIELD.number = 3
INVITEPVECARDCMD_CONFIGID_FIELD.index = 2
INVITEPVECARDCMD_CONFIGID_FIELD.label = 1
INVITEPVECARDCMD_CONFIGID_FIELD.has_default_value = true
INVITEPVECARDCMD_CONFIGID_FIELD.default_value = 0
INVITEPVECARDCMD_CONFIGID_FIELD.type = 13
INVITEPVECARDCMD_CONFIGID_FIELD.cpp_type = 3

INVITEPVECARDCMD_ISCANCEL_FIELD.name = "iscancel"
INVITEPVECARDCMD_ISCANCEL_FIELD.full_name = ".Cmd.InvitePveCardCmd.iscancel"
INVITEPVECARDCMD_ISCANCEL_FIELD.number = 4
INVITEPVECARDCMD_ISCANCEL_FIELD.index = 3
INVITEPVECARDCMD_ISCANCEL_FIELD.label = 1
INVITEPVECARDCMD_ISCANCEL_FIELD.has_default_value = true
INVITEPVECARDCMD_ISCANCEL_FIELD.default_value = false
INVITEPVECARDCMD_ISCANCEL_FIELD.type = 8
INVITEPVECARDCMD_ISCANCEL_FIELD.cpp_type = 7

INVITEPVECARDCMD.name = "InvitePveCardCmd"
INVITEPVECARDCMD.full_name = ".Cmd.InvitePveCardCmd"
INVITEPVECARDCMD.nested_types = {}
INVITEPVECARDCMD.enum_types = {}
INVITEPVECARDCMD.fields = {INVITEPVECARDCMD_CMD_FIELD, INVITEPVECARDCMD_PARAM_FIELD, INVITEPVECARDCMD_CONFIGID_FIELD, INVITEPVECARDCMD_ISCANCEL_FIELD}
INVITEPVECARDCMD.is_extendable = false
INVITEPVECARDCMD.extensions = {}
REPLYPVECARDCMD_CMD_FIELD.name = "cmd"
REPLYPVECARDCMD_CMD_FIELD.full_name = ".Cmd.ReplyPveCardCmd.cmd"
REPLYPVECARDCMD_CMD_FIELD.number = 1
REPLYPVECARDCMD_CMD_FIELD.index = 0
REPLYPVECARDCMD_CMD_FIELD.label = 1
REPLYPVECARDCMD_CMD_FIELD.has_default_value = true
REPLYPVECARDCMD_CMD_FIELD.default_value = 66
REPLYPVECARDCMD_CMD_FIELD.enum_type = XCMD_PB_COMMAND
REPLYPVECARDCMD_CMD_FIELD.type = 14
REPLYPVECARDCMD_CMD_FIELD.cpp_type = 8

REPLYPVECARDCMD_PARAM_FIELD.name = "param"
REPLYPVECARDCMD_PARAM_FIELD.full_name = ".Cmd.ReplyPveCardCmd.param"
REPLYPVECARDCMD_PARAM_FIELD.number = 2
REPLYPVECARDCMD_PARAM_FIELD.index = 1
REPLYPVECARDCMD_PARAM_FIELD.label = 1
REPLYPVECARDCMD_PARAM_FIELD.has_default_value = true
REPLYPVECARDCMD_PARAM_FIELD.default_value = 2
REPLYPVECARDCMD_PARAM_FIELD.enum_type = EPVECARDPARAM
REPLYPVECARDCMD_PARAM_FIELD.type = 14
REPLYPVECARDCMD_PARAM_FIELD.cpp_type = 8

REPLYPVECARDCMD_AGREE_FIELD.name = "agree"
REPLYPVECARDCMD_AGREE_FIELD.full_name = ".Cmd.ReplyPveCardCmd.agree"
REPLYPVECARDCMD_AGREE_FIELD.number = 3
REPLYPVECARDCMD_AGREE_FIELD.index = 2
REPLYPVECARDCMD_AGREE_FIELD.label = 1
REPLYPVECARDCMD_AGREE_FIELD.has_default_value = true
REPLYPVECARDCMD_AGREE_FIELD.default_value = false
REPLYPVECARDCMD_AGREE_FIELD.type = 8
REPLYPVECARDCMD_AGREE_FIELD.cpp_type = 7

REPLYPVECARDCMD_CHARID_FIELD.name = "charid"
REPLYPVECARDCMD_CHARID_FIELD.full_name = ".Cmd.ReplyPveCardCmd.charid"
REPLYPVECARDCMD_CHARID_FIELD.number = 4
REPLYPVECARDCMD_CHARID_FIELD.index = 3
REPLYPVECARDCMD_CHARID_FIELD.label = 1
REPLYPVECARDCMD_CHARID_FIELD.has_default_value = true
REPLYPVECARDCMD_CHARID_FIELD.default_value = 0
REPLYPVECARDCMD_CHARID_FIELD.type = 4
REPLYPVECARDCMD_CHARID_FIELD.cpp_type = 4

REPLYPVECARDCMD.name = "ReplyPveCardCmd"
REPLYPVECARDCMD.full_name = ".Cmd.ReplyPveCardCmd"
REPLYPVECARDCMD.nested_types = {}
REPLYPVECARDCMD.enum_types = {}
REPLYPVECARDCMD.fields = {REPLYPVECARDCMD_CMD_FIELD, REPLYPVECARDCMD_PARAM_FIELD, REPLYPVECARDCMD_AGREE_FIELD, REPLYPVECARDCMD_CHARID_FIELD}
REPLYPVECARDCMD.is_extendable = false
REPLYPVECARDCMD.extensions = {}
ENTERPVECARDCMD_CMD_FIELD.name = "cmd"
ENTERPVECARDCMD_CMD_FIELD.full_name = ".Cmd.EnterPveCardCmd.cmd"
ENTERPVECARDCMD_CMD_FIELD.number = 1
ENTERPVECARDCMD_CMD_FIELD.index = 0
ENTERPVECARDCMD_CMD_FIELD.label = 1
ENTERPVECARDCMD_CMD_FIELD.has_default_value = true
ENTERPVECARDCMD_CMD_FIELD.default_value = 66
ENTERPVECARDCMD_CMD_FIELD.enum_type = XCMD_PB_COMMAND
ENTERPVECARDCMD_CMD_FIELD.type = 14
ENTERPVECARDCMD_CMD_FIELD.cpp_type = 8

ENTERPVECARDCMD_PARAM_FIELD.name = "param"
ENTERPVECARDCMD_PARAM_FIELD.full_name = ".Cmd.EnterPveCardCmd.param"
ENTERPVECARDCMD_PARAM_FIELD.number = 2
ENTERPVECARDCMD_PARAM_FIELD.index = 1
ENTERPVECARDCMD_PARAM_FIELD.label = 1
ENTERPVECARDCMD_PARAM_FIELD.has_default_value = true
ENTERPVECARDCMD_PARAM_FIELD.default_value = 3
ENTERPVECARDCMD_PARAM_FIELD.enum_type = EPVECARDPARAM
ENTERPVECARDCMD_PARAM_FIELD.type = 14
ENTERPVECARDCMD_PARAM_FIELD.cpp_type = 8

ENTERPVECARDCMD_CONFIGID_FIELD.name = "configid"
ENTERPVECARDCMD_CONFIGID_FIELD.full_name = ".Cmd.EnterPveCardCmd.configid"
ENTERPVECARDCMD_CONFIGID_FIELD.number = 3
ENTERPVECARDCMD_CONFIGID_FIELD.index = 2
ENTERPVECARDCMD_CONFIGID_FIELD.label = 1
ENTERPVECARDCMD_CONFIGID_FIELD.has_default_value = true
ENTERPVECARDCMD_CONFIGID_FIELD.default_value = 0
ENTERPVECARDCMD_CONFIGID_FIELD.type = 13
ENTERPVECARDCMD_CONFIGID_FIELD.cpp_type = 3

ENTERPVECARDCMD.name = "EnterPveCardCmd"
ENTERPVECARDCMD.full_name = ".Cmd.EnterPveCardCmd"
ENTERPVECARDCMD.nested_types = {}
ENTERPVECARDCMD.enum_types = {}
ENTERPVECARDCMD.fields = {ENTERPVECARDCMD_CMD_FIELD, ENTERPVECARDCMD_PARAM_FIELD, ENTERPVECARDCMD_CONFIGID_FIELD}
ENTERPVECARDCMD.is_extendable = false
ENTERPVECARDCMD.extensions = {}
PVECARDINFO_INDEX_FIELD.name = "index"
PVECARDINFO_INDEX_FIELD.full_name = ".Cmd.PveCardInfo.index"
PVECARDINFO_INDEX_FIELD.number = 1
PVECARDINFO_INDEX_FIELD.index = 0
PVECARDINFO_INDEX_FIELD.label = 1
PVECARDINFO_INDEX_FIELD.has_default_value = true
PVECARDINFO_INDEX_FIELD.default_value = 0
PVECARDINFO_INDEX_FIELD.type = 13
PVECARDINFO_INDEX_FIELD.cpp_type = 3

PVECARDINFO_CARDIDS_FIELD.name = "cardids"
PVECARDINFO_CARDIDS_FIELD.full_name = ".Cmd.PveCardInfo.cardids"
PVECARDINFO_CARDIDS_FIELD.number = 2
PVECARDINFO_CARDIDS_FIELD.index = 1
PVECARDINFO_CARDIDS_FIELD.label = 3
PVECARDINFO_CARDIDS_FIELD.has_default_value = false
PVECARDINFO_CARDIDS_FIELD.default_value = {}
PVECARDINFO_CARDIDS_FIELD.type = 13
PVECARDINFO_CARDIDS_FIELD.cpp_type = 3

PVECARDINFO.name = "PveCardInfo"
PVECARDINFO.full_name = ".Cmd.PveCardInfo"
PVECARDINFO.nested_types = {}
PVECARDINFO.enum_types = {}
PVECARDINFO.fields = {PVECARDINFO_INDEX_FIELD, PVECARDINFO_CARDIDS_FIELD}
PVECARDINFO.is_extendable = false
PVECARDINFO.extensions = {}
QUERYCARDINFOCMD_CMD_FIELD.name = "cmd"
QUERYCARDINFOCMD_CMD_FIELD.full_name = ".Cmd.QueryCardInfoCmd.cmd"
QUERYCARDINFOCMD_CMD_FIELD.number = 1
QUERYCARDINFOCMD_CMD_FIELD.index = 0
QUERYCARDINFOCMD_CMD_FIELD.label = 1
QUERYCARDINFOCMD_CMD_FIELD.has_default_value = true
QUERYCARDINFOCMD_CMD_FIELD.default_value = 66
QUERYCARDINFOCMD_CMD_FIELD.enum_type = XCMD_PB_COMMAND
QUERYCARDINFOCMD_CMD_FIELD.type = 14
QUERYCARDINFOCMD_CMD_FIELD.cpp_type = 8

QUERYCARDINFOCMD_PARAM_FIELD.name = "param"
QUERYCARDINFOCMD_PARAM_FIELD.full_name = ".Cmd.QueryCardInfoCmd.param"
QUERYCARDINFOCMD_PARAM_FIELD.number = 2
QUERYCARDINFOCMD_PARAM_FIELD.index = 1
QUERYCARDINFOCMD_PARAM_FIELD.label = 1
QUERYCARDINFOCMD_PARAM_FIELD.has_default_value = true
QUERYCARDINFOCMD_PARAM_FIELD.default_value = 4
QUERYCARDINFOCMD_PARAM_FIELD.enum_type = EPVECARDPARAM
QUERYCARDINFOCMD_PARAM_FIELD.type = 14
QUERYCARDINFOCMD_PARAM_FIELD.cpp_type = 8

QUERYCARDINFOCMD_CARDS_FIELD.name = "cards"
QUERYCARDINFOCMD_CARDS_FIELD.full_name = ".Cmd.QueryCardInfoCmd.cards"
QUERYCARDINFOCMD_CARDS_FIELD.number = 3
QUERYCARDINFOCMD_CARDS_FIELD.index = 2
QUERYCARDINFOCMD_CARDS_FIELD.label = 3
QUERYCARDINFOCMD_CARDS_FIELD.has_default_value = false
QUERYCARDINFOCMD_CARDS_FIELD.default_value = {}
QUERYCARDINFOCMD_CARDS_FIELD.message_type = PVECARDINFO
QUERYCARDINFOCMD_CARDS_FIELD.type = 11
QUERYCARDINFOCMD_CARDS_FIELD.cpp_type = 10

QUERYCARDINFOCMD.name = "QueryCardInfoCmd"
QUERYCARDINFOCMD.full_name = ".Cmd.QueryCardInfoCmd"
QUERYCARDINFOCMD.nested_types = {}
QUERYCARDINFOCMD.enum_types = {}
QUERYCARDINFOCMD.fields = {QUERYCARDINFOCMD_CMD_FIELD, QUERYCARDINFOCMD_PARAM_FIELD, QUERYCARDINFOCMD_CARDS_FIELD}
QUERYCARDINFOCMD.is_extendable = false
QUERYCARDINFOCMD.extensions = {}
SELECTPVECARDCMD_CMD_FIELD.name = "cmd"
SELECTPVECARDCMD_CMD_FIELD.full_name = ".Cmd.SelectPveCardCmd.cmd"
SELECTPVECARDCMD_CMD_FIELD.number = 1
SELECTPVECARDCMD_CMD_FIELD.index = 0
SELECTPVECARDCMD_CMD_FIELD.label = 1
SELECTPVECARDCMD_CMD_FIELD.has_default_value = true
SELECTPVECARDCMD_CMD_FIELD.default_value = 66
SELECTPVECARDCMD_CMD_FIELD.enum_type = XCMD_PB_COMMAND
SELECTPVECARDCMD_CMD_FIELD.type = 14
SELECTPVECARDCMD_CMD_FIELD.cpp_type = 8

SELECTPVECARDCMD_PARAM_FIELD.name = "param"
SELECTPVECARDCMD_PARAM_FIELD.full_name = ".Cmd.SelectPveCardCmd.param"
SELECTPVECARDCMD_PARAM_FIELD.number = 2
SELECTPVECARDCMD_PARAM_FIELD.index = 1
SELECTPVECARDCMD_PARAM_FIELD.label = 1
SELECTPVECARDCMD_PARAM_FIELD.has_default_value = true
SELECTPVECARDCMD_PARAM_FIELD.default_value = 5
SELECTPVECARDCMD_PARAM_FIELD.enum_type = EPVECARDPARAM
SELECTPVECARDCMD_PARAM_FIELD.type = 14
SELECTPVECARDCMD_PARAM_FIELD.cpp_type = 8

SELECTPVECARDCMD_INDEX_FIELD.name = "index"
SELECTPVECARDCMD_INDEX_FIELD.full_name = ".Cmd.SelectPveCardCmd.index"
SELECTPVECARDCMD_INDEX_FIELD.number = 3
SELECTPVECARDCMD_INDEX_FIELD.index = 2
SELECTPVECARDCMD_INDEX_FIELD.label = 2
SELECTPVECARDCMD_INDEX_FIELD.has_default_value = false
SELECTPVECARDCMD_INDEX_FIELD.default_value = 0
SELECTPVECARDCMD_INDEX_FIELD.type = 13
SELECTPVECARDCMD_INDEX_FIELD.cpp_type = 3

SELECTPVECARDCMD.name = "SelectPveCardCmd"
SELECTPVECARDCMD.full_name = ".Cmd.SelectPveCardCmd"
SELECTPVECARDCMD.nested_types = {}
SELECTPVECARDCMD.enum_types = {}
SELECTPVECARDCMD.fields = {SELECTPVECARDCMD_CMD_FIELD, SELECTPVECARDCMD_PARAM_FIELD, SELECTPVECARDCMD_INDEX_FIELD}
SELECTPVECARDCMD.is_extendable = false
SELECTPVECARDCMD.extensions = {}
SYNCPROCESSPVECARDCMD_CMD_FIELD.name = "cmd"
SYNCPROCESSPVECARDCMD_CMD_FIELD.full_name = ".Cmd.SyncProcessPveCardCmd.cmd"
SYNCPROCESSPVECARDCMD_CMD_FIELD.number = 1
SYNCPROCESSPVECARDCMD_CMD_FIELD.index = 0
SYNCPROCESSPVECARDCMD_CMD_FIELD.label = 1
SYNCPROCESSPVECARDCMD_CMD_FIELD.has_default_value = true
SYNCPROCESSPVECARDCMD_CMD_FIELD.default_value = 66
SYNCPROCESSPVECARDCMD_CMD_FIELD.enum_type = XCMD_PB_COMMAND
SYNCPROCESSPVECARDCMD_CMD_FIELD.type = 14
SYNCPROCESSPVECARDCMD_CMD_FIELD.cpp_type = 8

SYNCPROCESSPVECARDCMD_PARAM_FIELD.name = "param"
SYNCPROCESSPVECARDCMD_PARAM_FIELD.full_name = ".Cmd.SyncProcessPveCardCmd.param"
SYNCPROCESSPVECARDCMD_PARAM_FIELD.number = 2
SYNCPROCESSPVECARDCMD_PARAM_FIELD.index = 1
SYNCPROCESSPVECARDCMD_PARAM_FIELD.label = 1
SYNCPROCESSPVECARDCMD_PARAM_FIELD.has_default_value = true
SYNCPROCESSPVECARDCMD_PARAM_FIELD.default_value = 6
SYNCPROCESSPVECARDCMD_PARAM_FIELD.enum_type = EPVECARDPARAM
SYNCPROCESSPVECARDCMD_PARAM_FIELD.type = 14
SYNCPROCESSPVECARDCMD_PARAM_FIELD.cpp_type = 8

SYNCPROCESSPVECARDCMD_CARD_FIELD.name = "card"
SYNCPROCESSPVECARDCMD_CARD_FIELD.full_name = ".Cmd.SyncProcessPveCardCmd.card"
SYNCPROCESSPVECARDCMD_CARD_FIELD.number = 3
SYNCPROCESSPVECARDCMD_CARD_FIELD.index = 2
SYNCPROCESSPVECARDCMD_CARD_FIELD.label = 1
SYNCPROCESSPVECARDCMD_CARD_FIELD.has_default_value = false
SYNCPROCESSPVECARDCMD_CARD_FIELD.default_value = nil
SYNCPROCESSPVECARDCMD_CARD_FIELD.message_type = PVECARDINFO
SYNCPROCESSPVECARDCMD_CARD_FIELD.type = 11
SYNCPROCESSPVECARDCMD_CARD_FIELD.cpp_type = 10

SYNCPROCESSPVECARDCMD_PROCESS_FIELD.name = "process"
SYNCPROCESSPVECARDCMD_PROCESS_FIELD.full_name = ".Cmd.SyncProcessPveCardCmd.process"
SYNCPROCESSPVECARDCMD_PROCESS_FIELD.number = 4
SYNCPROCESSPVECARDCMD_PROCESS_FIELD.index = 3
SYNCPROCESSPVECARDCMD_PROCESS_FIELD.label = 1
SYNCPROCESSPVECARDCMD_PROCESS_FIELD.has_default_value = true
SYNCPROCESSPVECARDCMD_PROCESS_FIELD.default_value = 0
SYNCPROCESSPVECARDCMD_PROCESS_FIELD.type = 13
SYNCPROCESSPVECARDCMD_PROCESS_FIELD.cpp_type = 3

SYNCPROCESSPVECARDCMD.name = "SyncProcessPveCardCmd"
SYNCPROCESSPVECARDCMD.full_name = ".Cmd.SyncProcessPveCardCmd"
SYNCPROCESSPVECARDCMD.nested_types = {}
SYNCPROCESSPVECARDCMD.enum_types = {}
SYNCPROCESSPVECARDCMD.fields = {SYNCPROCESSPVECARDCMD_CMD_FIELD, SYNCPROCESSPVECARDCMD_PARAM_FIELD, SYNCPROCESSPVECARDCMD_CARD_FIELD, SYNCPROCESSPVECARDCMD_PROCESS_FIELD}
SYNCPROCESSPVECARDCMD.is_extendable = false
SYNCPROCESSPVECARDCMD.extensions = {}
UPDATEPROCESSPVECARDCMD_CMD_FIELD.name = "cmd"
UPDATEPROCESSPVECARDCMD_CMD_FIELD.full_name = ".Cmd.UpdateProcessPveCardCmd.cmd"
UPDATEPROCESSPVECARDCMD_CMD_FIELD.number = 1
UPDATEPROCESSPVECARDCMD_CMD_FIELD.index = 0
UPDATEPROCESSPVECARDCMD_CMD_FIELD.label = 1
UPDATEPROCESSPVECARDCMD_CMD_FIELD.has_default_value = true
UPDATEPROCESSPVECARDCMD_CMD_FIELD.default_value = 66
UPDATEPROCESSPVECARDCMD_CMD_FIELD.enum_type = XCMD_PB_COMMAND
UPDATEPROCESSPVECARDCMD_CMD_FIELD.type = 14
UPDATEPROCESSPVECARDCMD_CMD_FIELD.cpp_type = 8

UPDATEPROCESSPVECARDCMD_PARAM_FIELD.name = "param"
UPDATEPROCESSPVECARDCMD_PARAM_FIELD.full_name = ".Cmd.UpdateProcessPveCardCmd.param"
UPDATEPROCESSPVECARDCMD_PARAM_FIELD.number = 2
UPDATEPROCESSPVECARDCMD_PARAM_FIELD.index = 1
UPDATEPROCESSPVECARDCMD_PARAM_FIELD.label = 1
UPDATEPROCESSPVECARDCMD_PARAM_FIELD.has_default_value = true
UPDATEPROCESSPVECARDCMD_PARAM_FIELD.default_value = 7
UPDATEPROCESSPVECARDCMD_PARAM_FIELD.enum_type = EPVECARDPARAM
UPDATEPROCESSPVECARDCMD_PARAM_FIELD.type = 14
UPDATEPROCESSPVECARDCMD_PARAM_FIELD.cpp_type = 8

UPDATEPROCESSPVECARDCMD_PROCESS_FIELD.name = "process"
UPDATEPROCESSPVECARDCMD_PROCESS_FIELD.full_name = ".Cmd.UpdateProcessPveCardCmd.process"
UPDATEPROCESSPVECARDCMD_PROCESS_FIELD.number = 3
UPDATEPROCESSPVECARDCMD_PROCESS_FIELD.index = 2
UPDATEPROCESSPVECARDCMD_PROCESS_FIELD.label = 1
UPDATEPROCESSPVECARDCMD_PROCESS_FIELD.has_default_value = true
UPDATEPROCESSPVECARDCMD_PROCESS_FIELD.default_value = 0
UPDATEPROCESSPVECARDCMD_PROCESS_FIELD.type = 13
UPDATEPROCESSPVECARDCMD_PROCESS_FIELD.cpp_type = 3

UPDATEPROCESSPVECARDCMD.name = "UpdateProcessPveCardCmd"
UPDATEPROCESSPVECARDCMD.full_name = ".Cmd.UpdateProcessPveCardCmd"
UPDATEPROCESSPVECARDCMD.nested_types = {}
UPDATEPROCESSPVECARDCMD.enum_types = {}
UPDATEPROCESSPVECARDCMD.fields = {UPDATEPROCESSPVECARDCMD_CMD_FIELD, UPDATEPROCESSPVECARDCMD_PARAM_FIELD, UPDATEPROCESSPVECARDCMD_PROCESS_FIELD}
UPDATEPROCESSPVECARDCMD.is_extendable = false
UPDATEPROCESSPVECARDCMD.extensions = {}
BEGINFIREPVECARDCMD_CMD_FIELD.name = "cmd"
BEGINFIREPVECARDCMD_CMD_FIELD.full_name = ".Cmd.BeginFirePveCardCmd.cmd"
BEGINFIREPVECARDCMD_CMD_FIELD.number = 1
BEGINFIREPVECARDCMD_CMD_FIELD.index = 0
BEGINFIREPVECARDCMD_CMD_FIELD.label = 1
BEGINFIREPVECARDCMD_CMD_FIELD.has_default_value = true
BEGINFIREPVECARDCMD_CMD_FIELD.default_value = 66
BEGINFIREPVECARDCMD_CMD_FIELD.enum_type = XCMD_PB_COMMAND
BEGINFIREPVECARDCMD_CMD_FIELD.type = 14
BEGINFIREPVECARDCMD_CMD_FIELD.cpp_type = 8

BEGINFIREPVECARDCMD_PARAM_FIELD.name = "param"
BEGINFIREPVECARDCMD_PARAM_FIELD.full_name = ".Cmd.BeginFirePveCardCmd.param"
BEGINFIREPVECARDCMD_PARAM_FIELD.number = 2
BEGINFIREPVECARDCMD_PARAM_FIELD.index = 1
BEGINFIREPVECARDCMD_PARAM_FIELD.label = 1
BEGINFIREPVECARDCMD_PARAM_FIELD.has_default_value = true
BEGINFIREPVECARDCMD_PARAM_FIELD.default_value = 8
BEGINFIREPVECARDCMD_PARAM_FIELD.enum_type = EPVECARDPARAM
BEGINFIREPVECARDCMD_PARAM_FIELD.type = 14
BEGINFIREPVECARDCMD_PARAM_FIELD.cpp_type = 8

BEGINFIREPVECARDCMD.name = "BeginFirePveCardCmd"
BEGINFIREPVECARDCMD.full_name = ".Cmd.BeginFirePveCardCmd"
BEGINFIREPVECARDCMD.nested_types = {}
BEGINFIREPVECARDCMD.enum_types = {}
BEGINFIREPVECARDCMD.fields = {BEGINFIREPVECARDCMD_CMD_FIELD, BEGINFIREPVECARDCMD_PARAM_FIELD}
BEGINFIREPVECARDCMD.is_extendable = false
BEGINFIREPVECARDCMD.extensions = {}
FINISHPLAYCARDCMD_CMD_FIELD.name = "cmd"
FINISHPLAYCARDCMD_CMD_FIELD.full_name = ".Cmd.FinishPlayCardCmd.cmd"
FINISHPLAYCARDCMD_CMD_FIELD.number = 1
FINISHPLAYCARDCMD_CMD_FIELD.index = 0
FINISHPLAYCARDCMD_CMD_FIELD.label = 1
FINISHPLAYCARDCMD_CMD_FIELD.has_default_value = true
FINISHPLAYCARDCMD_CMD_FIELD.default_value = 66
FINISHPLAYCARDCMD_CMD_FIELD.enum_type = XCMD_PB_COMMAND
FINISHPLAYCARDCMD_CMD_FIELD.type = 14
FINISHPLAYCARDCMD_CMD_FIELD.cpp_type = 8

FINISHPLAYCARDCMD_PARAM_FIELD.name = "param"
FINISHPLAYCARDCMD_PARAM_FIELD.full_name = ".Cmd.FinishPlayCardCmd.param"
FINISHPLAYCARDCMD_PARAM_FIELD.number = 2
FINISHPLAYCARDCMD_PARAM_FIELD.index = 1
FINISHPLAYCARDCMD_PARAM_FIELD.label = 1
FINISHPLAYCARDCMD_PARAM_FIELD.has_default_value = true
FINISHPLAYCARDCMD_PARAM_FIELD.default_value = 9
FINISHPLAYCARDCMD_PARAM_FIELD.enum_type = EPVECARDPARAM
FINISHPLAYCARDCMD_PARAM_FIELD.type = 14
FINISHPLAYCARDCMD_PARAM_FIELD.cpp_type = 8

FINISHPLAYCARDCMD.name = "FinishPlayCardCmd"
FINISHPLAYCARDCMD.full_name = ".Cmd.FinishPlayCardCmd"
FINISHPLAYCARDCMD.nested_types = {}
FINISHPLAYCARDCMD.enum_types = {}
FINISHPLAYCARDCMD.fields = {FINISHPLAYCARDCMD_CMD_FIELD, FINISHPLAYCARDCMD_PARAM_FIELD}
FINISHPLAYCARDCMD.is_extendable = false
FINISHPLAYCARDCMD.extensions = {}
PLAYPVECARDCMD_CMD_FIELD.name = "cmd"
PLAYPVECARDCMD_CMD_FIELD.full_name = ".Cmd.PlayPveCardCmd.cmd"
PLAYPVECARDCMD_CMD_FIELD.number = 1
PLAYPVECARDCMD_CMD_FIELD.index = 0
PLAYPVECARDCMD_CMD_FIELD.label = 1
PLAYPVECARDCMD_CMD_FIELD.has_default_value = true
PLAYPVECARDCMD_CMD_FIELD.default_value = 66
PLAYPVECARDCMD_CMD_FIELD.enum_type = XCMD_PB_COMMAND
PLAYPVECARDCMD_CMD_FIELD.type = 14
PLAYPVECARDCMD_CMD_FIELD.cpp_type = 8

PLAYPVECARDCMD_PARAM_FIELD.name = "param"
PLAYPVECARDCMD_PARAM_FIELD.full_name = ".Cmd.PlayPveCardCmd.param"
PLAYPVECARDCMD_PARAM_FIELD.number = 2
PLAYPVECARDCMD_PARAM_FIELD.index = 1
PLAYPVECARDCMD_PARAM_FIELD.label = 1
PLAYPVECARDCMD_PARAM_FIELD.has_default_value = true
PLAYPVECARDCMD_PARAM_FIELD.default_value = 10
PLAYPVECARDCMD_PARAM_FIELD.enum_type = EPVECARDPARAM
PLAYPVECARDCMD_PARAM_FIELD.type = 14
PLAYPVECARDCMD_PARAM_FIELD.cpp_type = 8

PLAYPVECARDCMD_NPCGUID_FIELD.name = "npcguid"
PLAYPVECARDCMD_NPCGUID_FIELD.full_name = ".Cmd.PlayPveCardCmd.npcguid"
PLAYPVECARDCMD_NPCGUID_FIELD.number = 3
PLAYPVECARDCMD_NPCGUID_FIELD.index = 2
PLAYPVECARDCMD_NPCGUID_FIELD.label = 2
PLAYPVECARDCMD_NPCGUID_FIELD.has_default_value = false
PLAYPVECARDCMD_NPCGUID_FIELD.default_value = 0
PLAYPVECARDCMD_NPCGUID_FIELD.type = 4
PLAYPVECARDCMD_NPCGUID_FIELD.cpp_type = 4

PLAYPVECARDCMD_CARDIDS_FIELD.name = "cardids"
PLAYPVECARDCMD_CARDIDS_FIELD.full_name = ".Cmd.PlayPveCardCmd.cardids"
PLAYPVECARDCMD_CARDIDS_FIELD.number = 4
PLAYPVECARDCMD_CARDIDS_FIELD.index = 3
PLAYPVECARDCMD_CARDIDS_FIELD.label = 3
PLAYPVECARDCMD_CARDIDS_FIELD.has_default_value = false
PLAYPVECARDCMD_CARDIDS_FIELD.default_value = {}
PLAYPVECARDCMD_CARDIDS_FIELD.type = 13
PLAYPVECARDCMD_CARDIDS_FIELD.cpp_type = 3

PLAYPVECARDCMD.name = "PlayPveCardCmd"
PLAYPVECARDCMD.full_name = ".Cmd.PlayPveCardCmd"
PLAYPVECARDCMD.nested_types = {}
PLAYPVECARDCMD.enum_types = {}
PLAYPVECARDCMD.fields = {PLAYPVECARDCMD_CMD_FIELD, PLAYPVECARDCMD_PARAM_FIELD, PLAYPVECARDCMD_NPCGUID_FIELD, PLAYPVECARDCMD_CARDIDS_FIELD}
PLAYPVECARDCMD.is_extendable = false
PLAYPVECARDCMD.extensions = {}

BeginFirePveCardCmd = protobuf.Message(BEGINFIREPVECARDCMD)
EPVE_BEGIN_FIRE_CMD = 8
EPVE_ENTER_RAID_CMD = 3
EPVE_FINISH_CARD_CMD = 9
EPVE_INVITE_TEAM_CMD = 1
EPVE_PLAY_CARD_CMD = 10
EPVE_QUERY_ALL_CARD_CMD = 4
EPVE_REPLY_TEAM_CMD = 2
EPVE_SELECTED_CARD_CMD = 6
EPVE_SELECT_CARD_CMD = 5
EPVE_UPDATE_CARD_CMD = 7
EnterPveCardCmd = protobuf.Message(ENTERPVECARDCMD)
FinishPlayCardCmd = protobuf.Message(FINISHPLAYCARDCMD)
InvitePveCardCmd = protobuf.Message(INVITEPVECARDCMD)
PlayPveCardCmd = protobuf.Message(PLAYPVECARDCMD)
PveCardInfo = protobuf.Message(PVECARDINFO)
QueryCardInfoCmd = protobuf.Message(QUERYCARDINFOCMD)
ReplyPveCardCmd = protobuf.Message(REPLYPVECARDCMD)
SelectPveCardCmd = protobuf.Message(SELECTPVECARDCMD)
SyncProcessPveCardCmd = protobuf.Message(SYNCPROCESSPVECARDCMD)
UpdateProcessPveCardCmd = protobuf.Message(UPDATEPROCESSPVECARDCMD)

