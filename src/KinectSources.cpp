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

#include "KinectSources.h"
#include <iostream>




/********    Constructor      *********/
CKinectSources::CKinectSources()
{
	_sensor = nullptr;
	_depth_reader = nullptr;
	_depth_source = nullptr;
	_color_reader = nullptr;
	_color_source = nullptr;
	_ir_source = nullptr;
	_ir_reader = nullptr;
	_face_source = nullptr;
	_face_reader = nullptr;
	_hd_face_source = nullptr;
	_hd_face_reader = nullptr;
	_multi_source_frame_reader = nullptr;
	_body_index_source = nullptr;
	_body_index_reader = nullptr;
	_body_reader = nullptr;
	_body_source = nullptr;

	depthReaderInit = E_FAIL;
	colorReaderInit = E_FAIL;
	irReaderInit = E_FAIL;

}





/********    Destructor      *********/

CKinectSources::~CKinectSources()
{
	//Release all acquired resources
	SafeRelease(_multi_source_frame_reader);
	SafeRelease(_hd_face_source);
	SafeRelease(_hd_face_reader);
	SafeRelease(_depth_source);
	SafeRelease(_depth_reader);
	SafeRelease(_color_source);
	SafeRelease(_color_reader);
	SafeRelease(_ir_source);
	SafeRelease(_ir_reader);
	SafeRelease(_body_source);
	SafeRelease(_body_reader);
	SafeRelease(_body_index_source);
	SafeRelease(_body_index_reader);
	if (_sensor) {
		_sensor->Close();
	}
	SafeRelease(_sensor);
}





//Initialize and Open the Default Kinect Sensor
HRESULT CKinectSources::initSensor()
{
	HRESULT hr = E_FAIL;
	hr = GetDefaultKinectSensor(&_sensor);
	if (FAILED(hr)) {
		return hr;
	}
	else {
		_sensor->Open();
	}

	return hr;
}





//Initialize a Multi Source Frame Reader
HRESULT CKinectSources::initMultiSourceReader(SOURCETYPE sourceTypes)
{
	/******     To be implemented later     ********/
	return E_NOTIMPL;
}





//Initialize Single Source Readers
//Can initialize more than one at a time
//Currently Supported Sources :- IR,COLOR,DEPTH
//Rest to be implemented later
HRESULT CKinectSources::initSourceReader(SOURCETYPE sourceType)
{
	HRESULT hrIR = S_OK, hrColor = S_OK, hrDepth = S_OK;

	if (sourceType & IR_S) {
		hrIR = initIRframeReader();
		irReaderInit = hrIR;
	}

	if (sourceType & DEPTH_S) {
		hrDepth = initDepthFrameReader();
		depthReaderInit = hrDepth;
	}

	if (sourceType & COLOR_S) {
		hrColor = initColorFrameReader();
		colorReaderInit = hrColor;
	}

	if (FAILED(hrIR)) {
		std::cout << "Infrared Reader Failed to Initialize\n";
	}

	if (FAILED(hrDepth)) {
		std::cout << "Depth Reader Failed to Initialize\n";
	}

	if (FAILED(hrColor)) {
		std::cout << "Color Reader Failed to Initialize\n";
	}

	if (FAILED(hrIR) && FAILED(hrDepth) && FAILED(hrColor)) {
		return E_FAIL;
	}
	else {
		return S_OK;
	}
}





//Returns a Single frame of type "frameType" from the initialized Multi Source Reader
cv::Mat CKinectSources::getMultiFrame(FRAMETYPE frameType)
{
	/**** To be implemented later *****/
	return cv::Mat();
}



//Returns a Single Frame of type "frameType"
cv::Mat CKinectSources::getFrame(FRAMETYPE frameType)
{
	HRESULT hr = E_FAIL;

	if (frameType & DEPTH_F) {
		return getDepthFrame(_depth_reader, depthReaderInit);
	}

	if (frameType & IR_F) {
		return getIRframe(_ir_reader, irReaderInit);
	}

	if (frameType & COLOR_F) {
		return getColorFrame(_color_reader, colorReaderInit);
	}
	
}





//Initialize Color Source and Color Reader
HRESULT CKinectSources::initColorFrameReader()
{
	HRESULT hr = S_OK;

	if (SUCCEEDED(hr)) {
		hr = _sensor->get_ColorFrameSource(&_color_source);
	}

	if (SUCCEEDED(hr)) {
		hr = _color_source->OpenReader(&_color_reader);
	}
	
	return hr;
}





//Initialize Depth Source and Depth Reader
HRESULT CKinectSources::initDepthFrameReader()
{
	HRESULT hr = S_OK;

	if (SUCCEEDED(hr)) {
		hr = _sensor->get_DepthFrameSource(&_depth_source);
	}

	if (SUCCEEDED(hr)) {
		hr = _depth_source->OpenReader(&_depth_reader);
	}
	
	return hr;
}





//Initialize IR Source and IR Reader
HRESULT CKinectSources::initIRframeReader()
{
	HRESULT hr = S_OK;
	if (SUCCEEDED(hr)) {
		hr = _sensor->get_InfraredFrameSource(&_ir_source);
	}
	if (SUCCEEDED(hr)) {
		hr = _ir_source->OpenReader(&_ir_reader);
	}
	
	return hr;
}





HRESULT CKinectSources::initFaceFrameReader()
{
	/****** To be implemented later *******/
	return E_NOTIMPL;
}





HRESULT CKinectSources::initHDFaceFrameReader()
{
	/****** To be implemented later ********/
	return E_NOTIMPL;
}





HRESULT CKinectSources::initBodyFrameReader()
{

	/***** To be implemented later ******/
	return E_NOTIMPL;
}





HRESULT CKinectSources::initBodyIndexFrameReader()
{
	/**** To be implemented later *****/
	return E_NOTIMPL;
}