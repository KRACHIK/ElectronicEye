#ifndef C_APPLICATION_H
#define C_APPLICATION_H 
#include <opencv2\core\core.hpp>

#include "DriverBridge.h"
#include "BaseType.h"

class CAverageValue;
class CHSVManager;

class CApplication
{
public:
	CApplication(CSetting Setting);
	void WhileTrue(); // while(true)

private:
	void ComputeFrame(cv::Mat Frame);
	void SendToDriver(const CAverageValue & AverageValue);
	void DebugRender(CHSVManager HSVManager, cv::Mat ImgCenter);

private:
	CSetting	_Setting;
	CSender		_Sender;
};

#endif	C_APPLICATION_H

