import KBEngine
from KBEDebug import *

class TRoleInfo(list):

    def __init__(self):
        list.__init__(self)

    def asDict(self):
        Data = {
            "Dbid": self[0],
            "Name": self[1],
            "RoleType": self[2],
            "Data": self[3]
        }
        return Data
    
    def createFromDict(self, DictData):
        self.extend(DictData["Dbid"], DictData["Name"], DictData["RoleType"], DictData["Data"])
        return self
    

class ROLE_INFO_PICKLER: # 序列化反序列化类
    
    def __init__(self):
        pass

    def createObjFromDict(self, dict):
        return TRoleInfo.createFromDict(dict)
    
    def getDictFromObj(self, obj):
        return obj.asDict()
    
    def isSameType(self, obj):
        return isinstance(obj, TRoleInfo)
    
RoleInfoInst = ROLE_INFO_PICKLER()

class TRoleList(dict):

    def __init__(self):
        dict.__init__(self)

    def asDict(self):
        Data = []
        for key, val in self.items():
            Data.append(val)
        Dict = {"Value": Data}
        return Dict
    
    def createFromDict(self, DictData):
        for data in DictData["Value"]:
            Prop = {"Dbid": data[0], "Name": data[1], "RoleType": data[2], "Data": data[3]}
            # 键: 数据库id, 值: TRoleInfo
            self[data[0]] = RoleInfoInst.createObjFromDict(Prop)
        return self
    
class ROLE_LIST_PICKLER:
    def __init__(self):
        pass

    def createObjFromDict(self, dict):
        return TRoleList.createFromDict(dict)
    
    def getDictFromObj(self, obj):
        return obj.asDict()
    
    def isSameType(self, obj):
        return isinstance(obj, TRoleList)
    