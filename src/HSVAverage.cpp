#include "HSVAverage.h"
#include "opencv2\imgproc\imgproc.hpp"

CHSVAverage::CHSVAverage(cv::Mat Mat) 
	: CBaseImage(Mat)
{
	Init();
}

CHSVManager::CHSVManager(CSetting Setting, CSubFrameArr ArrSubFrame)
	: _Setting(Setting)
	, _ArrSubFrame(ArrSubFrame)
{
	//Search for the most different piece of the frame by brightness
	for (cv::Mat itMat : _ArrSubFrame.GetArrSubFram())
		_HSVAverages.push_back(CHSVAverage(itMat));

	InitDifference();
}

CAverageValue CHSVManager::GetMaxContrastSubFrame()
{
	std::sort(_MeanValueVec.begin(), _MeanValueVec.end(), [](const CAverageValue &A, const CAverageValue &B){
		return A._fValue > B._fValue;
	});

	return _MeanValueVec[0];
}

const std::deque<CAverageValue> & CHSVManager::GetMeanValueArr()
{
	return _MeanValueVec;
}

void CHSVManager::InitDifference()
{
	double fMean = GetAverage();

	_MeanValueVec.resize(_HSVAverages.size());

	for (int i = 0; i < _HSVAverages.size(); i++)
	{
		_MeanValueVec[i]._fValue = abs(_HSVAverages[i].GetVAverage() - fMean);
		_MeanValueVec[i]._Index = i;
	}
}

double CHSVManager::GetAverage()
{
	// finds arithmetic average
	double SumVAverage = 0;
	for (auto it : _HSVAverages)
		SumVAverage += it.GetVAverage();

	return SumVAverage / _HSVAverages.size();
}

void CHSVAverage::Init()
{
	_Average = 0;
	int v1 = 0;

	cv::Mat hsv1;
	std::vector<cv::Mat> channel1;

	cv::cvtColor(GetImageMat(), hsv1, CV_BGR2HSV);
	cv::split(hsv1, channel1);

	for (int i = 0; i < hsv1.rows; i++)
	{
		for (int j = 0; j < hsv1.cols; j++)
		{
			v1 += channel1[2].at<uchar>(i, j);
		}
	}

	_Average = v1 / (hsv1.rows * hsv1.cols);
}
