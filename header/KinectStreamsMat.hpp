/*
* Copyright (C) 2016, Shubham Batra (https://www.github.com/batrashubham)
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* http://www.apache.org/licenses/LICENSE-2.0
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
* either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
*
*/

#pragma once

#include "helper.hpp"

namespace K2OCV {

	class CKinectStreamsMat {
	
	public:
		/********************     Functions   *************************/

	//Obtain Color Frame from Kinect If Color Source Successfuly Initialized
	cv::Mat getColorFrame(IColorFrameReader * _color_reader, HRESULT sourceInitHresult);

	//Obtain Depth Frame from Kinect If Depth Source Successfuly Initialized
	cv::Mat getDepthFrame(IDepthFrameReader * _depth_reader, HRESULT sourceInitHresult, bool rawData = false);

	//Obtain Infrared Frame from Kinect If IR Source Successfuly Initialized
	cv::Mat getIRframe(IInfraredFrameReader * _ir_reader, HRESULT sourceInitHresult);

	};


}