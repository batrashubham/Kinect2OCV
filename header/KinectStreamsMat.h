/*Copyright (C) 2016, Shubham Batra (https://www.github.com/batrashubham)

Licensed under the Apache License, Version 2.0 (the "License"); 
you may not use this file except in compliance with the License. 
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, 
software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, 
either express or implied.
See the License for the specific language governing permissions and limitations under the License.*/



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
