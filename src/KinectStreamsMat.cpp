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
 
#include "KinectStreamsMat.h"

CKinectStreamsMat::CKinectStreamsMat()
{
	_sensor = nullptr;
	_depth_reader = nullptr;
	_depth_source = nullptr;
	_color_reader = nullptr;
	_color_source = nullptr;
	_ir_source = nullptr;
	_ir_reader = nullptr;
}

CKinectStreamsMat::~CKinectStreamsMat()
{
	SafeRelease(_depth_source);
	SafeRelease(_depth_reader);
	SafeRelease(_color_source);
	SafeRelease(_color_reader);
	SafeRelease(_ir_source);
	SafeRelease(_ir_reader);
	if (_sensor) {
		_sensor->Close();
	}
	SafeRelease(_sensor);
}

cv::Mat CKinectStreamsMat::getDepthFrame()
{
	HRESULT hr = E_FAIL;
	IDepthFrame* frame = nullptr;
	cv::Mat depthImage;
	IFrameDescription* frame_desc = nullptr;
	hr = _depth_reader->AcquireLatestFrame(&frame);
	if (SUCCEEDED(hr)) {
		hr = frame->get_FrameDescription(&frame_desc);
		if (SUCCEEDED(hr)) {
			int frameWidth = 0, frameHeight = 0;
			hr = frame_desc->get_Width(&frameWidth);
			if (SUCCEEDED(hr))
			{
				hr = frame_desc->get_Height(&frameHeight);
			}
			if (SUCCEEDED(hr)) {
				const int imgSize = frameWidth*frameHeight;
				UINT16* pixelData = new UINT16[imgSize];
				hr = frame->CopyFrameDataToArray(imgSize, pixelData);
				if (SUCCEEDED(hr)) {
					depthImage = cv::Mat(frameHeight, frameWidth, CV_8U);
					for (int i = 0; i < imgSize; i++) {
						UINT16 depth = pixelData[i];
						depthImage.at<UINT8>(i) = depth & 0xffff;
					}
				}
			}
		}
		SafeRelease(frame_desc);
		SafeRelease(frame);
	}
	return depthImage;
}

cv::Mat CKinectStreamsMat::getColorFrame()
{
	HRESULT hr = E_FAIL;
	IColorFrame* frame = NULL;
	IFrameDescription* frameDesc;
	cv::Mat colorImage;
	hr = _color_reader->AcquireLatestFrame(&frame);
	if (SUCCEEDED(hr)) {
		hr = frame->get_FrameDescription(&frameDesc);
		if (SUCCEEDED(hr)) {
			int frameWidth = 0, frameHeight = 0;
			hr = frameDesc->get_Width(&frameWidth);
			if (SUCCEEDED(hr)) {
				hr = frameDesc->get_Height(&frameHeight);
			}
			if (SUCCEEDED(hr)) {
				const int imgSize = frameWidth*frameHeight * 4; //4 Channels(BGRA)
				BYTE* frameData = new BYTE[imgSize];
				hr = frame->CopyConvertedFrameDataToArray(imgSize, frameData, ColorImageFormat_Bgra);
				if (SUCCEEDED(hr)) {
					colorImage = cv::Mat(frameHeight, frameWidth, CV_8UC4, reinterpret_cast<void*>(frameData));
				}
			}
		}
		SafeRelease(frameDesc);
		SafeRelease(frame);
	}
	return colorImage;
}

cv::Mat CKinectStreamsMat::getIRframe()
{
	HRESULT hr = E_FAIL;
	IInfraredFrame* frame = nullptr;
	IFrameDescription* frameDesc;
	cv::Mat infraredImage;
	hr = _ir_reader->AcquireLatestFrame(&frame);
	if (SUCCEEDED(hr)) {
		hr = frame->get_FrameDescription(&frameDesc);
		if (SUCCEEDED(hr)) {
			int frameWidth = 0, frameHeight = 0;
			hr = frameDesc->get_Width(&frameWidth);
			if (SUCCEEDED(hr)) {
				hr = frameDesc->get_Height(&frameHeight);
			}
			if (SUCCEEDED(hr)) {
				const int imgSize = frameWidth*frameHeight;
				UINT16* frameData = new UINT16[imgSize];
				BYTE* frameDataBytes = new BYTE[imgSize];
				hr = frame->CopyFrameDataToArray(imgSize,frameData);
				for (int i = 0; i < imgSize; i++) {
					frameDataBytes[i] = (BYTE)(frameData[i] >> 7);
				}
				if (SUCCEEDED(hr)) {
					infraredImage = cv::Mat(frameHeight, frameWidth, CV_8U, reinterpret_cast<void*>(frameDataBytes));
				}
			}
		}
		SafeRelease(frameDesc);
		SafeRelease(frame);
	}
	return infraredImage;

}

cv::Mat CKinectStreamsMat::getFrame(FRAME_TYPE TYPE)
{
	if (TYPE == KS_DEPTH) {
		return getDepthFrame();
	}
	else if (TYPE == KS_IR) {
		return getIRframe();
	}
	else if (TYPE == KS_COLOR) {
		return getColorFrame();
	}
	else {
		return cv::Mat();
	}
}

HRESULT CKinectStreamsMat::initSensor()
{
	HRESULT hr = GetDefaultKinectSensor(&_sensor);
	if (FAILED(hr)) {
		return hr;
	}

	if (_sensor) {
		hr = _sensor->Open();
		if (SUCCEEDED(hr)) {
			hr = _sensor->get_DepthFrameSource(&_depth_source);
		}

		if (SUCCEEDED(hr)) {
			hr = _depth_source->OpenReader(&_depth_reader);
		}

		if (SUCCEEDED(hr)) {
			hr = _sensor->get_ColorFrameSource(&_color_source);
		}

		if (SUCCEEDED(hr)) {
			hr = _color_source->OpenReader(&_color_reader);
		}

		if (SUCCEEDED(hr)) {
			hr = _sensor->get_InfraredFrameSource(&_ir_source);
		}
		if (SUCCEEDED(hr)) {
			hr = _ir_source->OpenReader(&_ir_reader);
		}
	}
	return hr;
}
