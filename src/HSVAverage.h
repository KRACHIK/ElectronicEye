#ifndef C_HSVAVERAGE_H
#define C_HSVAVERAGE_H 

#include "ImageTools.h"
#include "BaseType.h"

class CHSVAverage : CBaseImage
{
public:
	CHSVAverage(){}
	CHSVAverage(cv::Mat Mat);

	double GetVAverage(){ return _Average; }

private:
	void Init();

private:
	double _Average = 0;
};

class CHSVManager
{
public:
	CHSVManager(CSetting Setting, CSubFrameArr ArrSubFrame);

	CAverageValue						GetMaxContrastSubFrame();
	const std::deque<CAverageValue> &	GetMeanValueArr();
	cv::Point							GetCenterPos(int nCutFrame);

private:
	void InitDifference();
	double GetAverage();

private:
	CSetting					_Setting;
	CSubFrameArr				_ArrSubFrame;
	std::deque<CHSVAverage>		_HSVAverages;
	std::deque<CAverageValue>	_MeanValueVec;
};

#endif