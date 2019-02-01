#pragma  once
#ifndef C_BASE_TYPE_H
#define C_BASE_TYPE_H 

#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

struct CAverageValue
{
	int		_Index;
	double	_fValue;
};

struct CSetting
{
	CSetting(){
		Init();
	}

	void Init()
	{
		std::cout << "enter the number of columns:     ";	std::cin >> _n;
		std::cout << "enter the number of lines:       ";	std::cin >> _m;
		std::cout << "enter scaling percentage:        ";	std::cin >> _Percent;
		std::cout << "render debug info [1 or 0]:      ";	std::cin >> _DebugInfo;

		assert(_n > 0 && _m > 0);
		assert(_Percent > 0 && _Percent <= 100);

		_nCountFrame = _n*_m;
	}

	/*1*/ int	_n = 0;
	/*2*/ int	_m = 0;
	/*3*/ int	_Percent = 0;
	/*4*/ int	_DebugInfo = 0;
	/*-*/ int	_nCountFrame = 0;
};

class CBaseImage
{
public:
	CBaseImage(std::string sPath) { _SourceMat = cv::imread(sPath); }
	CBaseImage(cv::Mat mat) : _SourceMat(mat){}
	CBaseImage(){}
	~CBaseImage(){}

	void LoadSourceImage(const std::string & Path) { _SourceMat = cv::imread(Path.c_str()); }
	void LoadSourceImage(cv::Mat mat) { _SourceMat = mat; }

	cv::Mat GetImageMat() { return _SourceMat; }
	void SetImageMat(cv::Mat val) { _SourceMat = val; }

protected:
	cv::Mat _SourceMat;
};

#endif	C_BASE_TYPE_H
