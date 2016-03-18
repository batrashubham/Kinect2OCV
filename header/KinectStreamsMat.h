#pragma once

#include <Kinect.h>
#include <Windows.h>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

template<class Interface>
inline void SafeRelease(Interface *& pInterfaceToRelease)
{
  if (pInterfaceToRelease != NULL)
	{
		pInterfaceToRelease->Release();
		pInterfaceToRelease = NULL;
	}
}


class CKinectStreamsMat {
private:
	IKinectSensor* _sensor;
	IDepthFrameSource* _depth_source;
	IDepthFrameReader* _depth_reader;
	IColorFrameSource* _color_source;
	IColorFrameReader* _color_reader;
public:
	CKinectStreamsMat();
	~CKinectStreamsMat();
	cv::Mat getDepthFrame();
	cv::Mat getColorFrame();
	HRESULT initSensor();
};