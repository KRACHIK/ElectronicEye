#include "ImageTools.h"

cv::Mat CImageTools::CutCenter(cv::Mat Img, int Percent_)
{
	const int SizeX = Img.size().width;
	const int SizeY = Img.size().height;

	int WidthRect = SizeX  * Percent_ / 100.0f;
	int HeightRect = SizeY *   Percent_ / 100.0f;

	int X_LeftUp = (SizeX - WidthRect) / 2;
	int Y_LeftUp = (SizeY - HeightRect) / 2;

	cv::Rect ROI(X_LeftUp, Y_LeftUp, WidthRect, HeightRect);

	return Img(ROI);
}

void CImageTools::AddText(cv::Mat Img, const std::vector<std::string> Texts, cv::Point Pos)
{
	cv::Point offset(0, 20);

	for (auto itText : Texts)
	{
		cv::putText(Img
			, itText
			, Pos
			, cv::FONT_HERSHEY_COMPLEX_SMALL
			, 0.6
			, cvScalar(0, 0, 250)
			, 1
			, CV_AA);

		Pos += offset;
	}
}

void CImageTools::AddGrid(cv::Mat Img, const CSetting &Setting)
{
	auto AddGrid = [=](cv::Mat Img)
	{
		const int SizeX = Img.size().width;
		const int SizeY = Img.size().height;

		int nCountVerical = Setting._n + 1;
		int nCountGorizontal = Setting._m + 1;

		int currX = 0, currY = 0;

		//draw vertical stripes 
		for (int i = 0; i < nCountVerical; i++)
		{
			line(Img, cv::Point(currX, currY), cv::Point(currX, Img.size().height), cv::Scalar(255), 1, 1);
			currX += SizeX / Setting._n;
		}

		// draw horizontal stripes 
		for (int j = 0; j < nCountGorizontal; j++)
		{
			line(Img, cv::Point(0, currY), cv::Point(Img.size().width, currY), cv::Scalar(255), 1, 1);
			currY += SizeY / Setting._m;
		}
	};

	AddGrid(Img);
}

void CImageTools::AddCircle(cv::Mat Image, const cv::Point &Pos)
{
	auto AddFilledCircle = [=](cv::Mat Image)
	{
		int thickness = -1;
		int lineType = 8;
		int Radius = 9;
		circle(Image, Pos, Radius, cv::Scalar(255, 0, 0), thickness, lineType);
	};

	AddFilledCircle(Image);
}

CSubFrameArr::CSubFrameArr(cv::Mat mat, CSetting Setting) : _Setting(Setting)
, CBaseImage(mat)
{
	assert(_SourceMat.data);

	Init();
}

cv::Point CSubFrameArr::GetCenterPos(cv::Size SizeImg, CSetting Setting, int nCutFrame)
{
	assert(nCutFrame > -1);

	const int SizeX = SizeImg.width;
	const int SizeY = SizeImg.height;

	int WidthRect = SizeX / Setting._n;
	int HeightRect = SizeY / Setting._m;

	int currX = 0, currY = 0;
	int nSearchCutFrame = 0;

	for (int i = 0; i < Setting._m; i++)
	{
		for (int j = 0; j < Setting._n; j++)
		{
			if (nCutFrame == nSearchCutFrame)
			{
				return cv::Point(currX + WidthRect / 2, currY + HeightRect / 2);
			}

			nSearchCutFrame++;
			currX += WidthRect;
		}
		currY += HeightRect;
		currX = 0;
	}

	// will be work, if the photo is divided into 3.3 parts, and for the search we specified the 10th subframe
	assert(false);

	return cv::Point(-1, -1);
}

void CSubFrameArr::Init()
{
	const int SizeX = _SourceMat.size().width;
	const int SizeY = _SourceMat.size().height;

	int WidthRect = SizeX / _Setting._n;
	int HeightRect = SizeY / _Setting._m;

	auto PushBack = [=](int x, int y)
	{
		cv::Rect ROI(x, y, WidthRect, HeightRect);
		cv::Mat tmp = _SourceMat(ROI);
		_MatDeq.push_back(tmp);
	};

	int currX = 0, currY = 0;

	for (int i = 0; i < _Setting._m; i++)
	{
		for (int j = 0; j < _Setting._n; j++)
		{
			PushBack(currX, currY);
			currX += WidthRect;
		}
		currY += HeightRect;
		currX = 0;
	}
}
