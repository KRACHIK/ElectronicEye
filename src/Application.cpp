#include "Application.h"
#include "ImageTools.h"
#include "HSVAverage.h"

void CApplication::ComputeFrame(cv::Mat new_frame)
{
	// reduces field of view
	cv::Mat ImgCut = CImageTools::CutCenter(new_frame, _Setting._Percent);

	// breaks a frame into an array of squares
	CSubFrameArr ArrSubIMG(ImgCut, _Setting);

	// analyzes the illumination of frames
	CHSVManager HSVManager(_Setting, ArrSubIMG);

	//displays the result on the form¶
	DebugRender(HSVManager, ImgCut);

	// sends the packet to the microcontroller
	SendToDriver(HSVManager.GetMaxContrastSubFrame());
}

void CApplication::DebugRender(CHSVManager HSVManager, cv::Mat Image)
{
	CAverageValue Value = HSVManager.GetMaxContrastSubFrame();

	//draw a circle in the area of the photo wich having the maximum brightness¶
	CImageTools::AddCircle(Image, CSubFrameArr::GetCenterPos(Image.size(), _Setting, Value._Index));

	CImageTools::AddGrid(Image, _Setting);

	if (_Setting._DebugInfo)
	{
		for (auto it : HSVManager.GetMeanValueArr())
		{
			CImageTools::AddText(
				/*Image*/	Image
				/*Text */, { std::to_string(it._Index), std::to_string(it._fValue) }
				/*Pos  */, CSubFrameArr::GetCenterPos(Image.size(), _Setting, it._Index)
				);
		}
	}

	cv::imshow("AlgoV1", Image);
}

void CApplication::SendToDriver(const CAverageValue & AverageValue)
{
#if 0
	std::cout << "[CApplication::SendToDriver] : " << sText << " index: " << AverageValue._Index << " Value: " << AverageValue._fValue << "\n";
	CImpulsePackage IndexFramePackage(AverageValue._Index, AverageValue._fValue);
	_Sender.Send(IndexFramePackage.SerializeBox());
#endif
}

CApplication::CApplication(CSetting Setting) : _Setting(Setting)
{
	_Sender.SetAddress("127.0.0.1");
}

void CApplication::WhileTrue()
{
	std::cout << (" ** Press 'c' for reload setting \n");

	cv::VideoCapture cap(0);
	cv::Mat new_frame;

	int c;

	while (true)
	{
		c = cv::waitKey(1);

		if ((char)c == 'c')
		{
			cv::destroyAllWindows();

			break;
		}
		else
		{
			cap >> new_frame;

			if (new_frame.empty())
				break;

			ComputeFrame(new_frame);
		}
	}
}

