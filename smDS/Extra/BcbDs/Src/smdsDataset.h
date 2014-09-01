//---------------------------------------------------------------------------
#ifndef smdsDatasetH
#define smdsDatasetH
//---------------------------------------------------------------------------
#include <Db.hpp>
#include <memory>
#include <dsData.h>
//---------------------------------------------------------------------------
class PACKAGE TsmdsDataset : public TDataSet
{
private:
    std::auto_ptr<smds::Table>  FTable;
protected:
	virtual TGetResult __fastcall GetRecord(char * Buffer, TGetMode GetMode, bool DoCheck);
	virtual void __fastcall InternalClose();
	virtual void __fastcall InternalHandleException();
	virtual void __fastcall InternalInitFieldDefs();
	virtual void __fastcall InternalOpen();
	virtual bool __fastcall IsCursorOpen();
public:
    __fastcall TsmdsDataset( TComponent *aOwner );
    virtual __fastcall ~TsmdsDataset();
};
//---------------------------------------------------------------------------
#endif
