#ifndef C_IMAGE_TOOLS_H
#define C_IMAGE_TOOLS_H 

#include "BaseType.h"
#include <deque>

class CSubFrameArr : public CBaseImage
{
public:
	CSubFrameArr(cv::Mat mat, CSetting Setting);

	std::deque <cv::Mat> & GetArrSubFram() { return _MatDeq; }

	static cv::Point GetCenterPos(cv::Size _SizeImg, CSetting _Setting, int nCutFrame);

private:
	void Init();

private:
	CSetting				_Setting;
	std::deque <cv::Mat>	_MatDeq;
};


class CImageTools
{
public:
	static cv::Mat CutCenter(cv::Mat Img, int Percent);
	static void AddText(cv::Mat Img, const std::vector<std::string> Texts, cv::Point Pos);
	static void AddGrid(cv::Mat Img, const CSetting &Setting);
	static void AddCircle(cv::Mat Img, const cv::Point &Pos);
};

#endif