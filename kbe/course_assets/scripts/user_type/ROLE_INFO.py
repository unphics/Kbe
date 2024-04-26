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