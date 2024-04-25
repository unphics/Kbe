#include "EntityCallExAccountBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_ExAccountBase::EntityBaseEntityCall_ExAccountBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_ExAccountBase::~EntityBaseEntityCall_ExAccountBase()
{
}



EntityCellEntityCall_ExAccountBase::EntityCellEntityCall_ExAccountBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_ExAccountBase::~EntityCellEntityCall_ExAccountBase()
{
}


}