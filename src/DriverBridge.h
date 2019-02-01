#ifndef C_DRIVE_BRIDGE_H
#define C_DRIVE_BRIDGE_H 

#include <iostream>
#include <cassert>
#include <sstream>
#include <string>

#define ID_INDEX_FRAME_PACKAGE 1

class CSender
{
public:
	void SetAddress(const std::string &sIP);
	void Send(const std::string &sData);

private:
	std::string _sIP;
};

class IPackage{

protected:
	IPackage(){};
	virtual ~IPackage(){};

	virtual void          SetID(size_t ID) = 0;
	virtual std::string   SerializeBox() = 0;
	virtual void          SerializeUnBox() = 0;

public:
	std::string ToByte(float Val) {
		return  std::string((char*)&Val, sizeof(float));
	}

protected:
	size_t _ID = 0;
};

//electric impulse for bus
class CImpulsePackage : public IPackage
{
public:
	~CImpulsePackage(){}
	CImpulsePackage(int Index, double fValue);
	CImpulsePackage(std::string sByteArr);

	std::string	SerializeBox();
	void SerializeUnBox();
	void SetID(size_t ID);

private:
	/* 0 */ // ID
	/* 1 */ int		_index;
	/* 2 */ float	_fValue;
	std::string		_sByteArr;
};

#endif	C_DRIVE_BRIDGE_H 
