#include "DriverBridge.h"

void CSender::SetAddress(const std::string &sIP)
{
	std::cout << "[CSender::SetAddress] : " << sIP << "\n";
}

void CSender::Send(const std::string &sData)
{
	std::cout << "[CSender::Send] : " << sData << "\n";
}

CImpulsePackage::CImpulsePackage(std::string sByteArr) : _sByteArr(sByteArr)
{
	SerializeUnBox();
}

CImpulsePackage::CImpulsePackage(int Index, double fValue) : _index(Index)
, _fValue(fValue)
{
	SetID(ID_INDEX_FRAME_PACKAGE);
	SerializeBox();
}

std::string CImpulsePackage::SerializeBox()
{
	_sByteArr = ToByte(_ID) + ToByte(_index) + ToByte(_fValue);
	return _sByteArr;
}

void CImpulsePackage::SerializeUnBox()
{
	assert(!_sByteArr.empty());

	std::stringstream byteArr(_sByteArr);

	byteArr.read((char*)&_ID, sizeof(size_t));
	byteArr.read((char*)&_fValue, sizeof(float));
	byteArr.read((char*)&_index, sizeof(int));
}

void CImpulsePackage::SetID(size_t ID)
{
	_ID = ID;
}
