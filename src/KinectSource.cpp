/*
* Copyright (C) 2019, Shubham Batra (https://www.github.com/batrashubham)
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

#include "helper.hpp"
#include "KinectSource.hpp"
#include "KinectFaceMat.hpp"
#include "KinectStreamsMat.hpp"

namespace K2OCV {

	//Face Features to be initialized
	FEATURETYPE features = BOUNDING_BOX_IN_COLOR_SAPCE
		| BOUNDING_BOX_IN_IR_SPACE
		| POINTS_IN_COLOR_SPACE
		| POINTS_IN_IR_SPACE
		| ROTATION_ORIENTATION
		| HAPPY
		| RIGHT_EYE_CLOSED
		| LEFT_EYE_CLOSED
		| MOUTH_OPEN
		| MOUTH_MOVED
		| LOOKING_AWAY
		| GLASSES
		| FACE_ENGAGEMENT;


	CKinectSource::CKinectSource() :
		_sensor(nullptr),
		_depth_reader(nullptr),
		_depth_source(nullptr),
		_color_reader(nullptr),
		_color_source(nullptr),
		_ir_source(nullptr),
		_ir_reader(nullptr),
		_hd_face_reader(nullptr),
		_hd_face_source(nullptr),
		_multi_source_frame_reader(nullptr),
		_body_source(nullptr),
		_body_reader(nullptr),
		_body_index_reader(nullptr),
		_body_index_source(nullptr),
		depthReaderInit(E_FAIL),
		colorReaderInit(E_FAIL),
		irReaderInit(E_FAIL),
		faceReaderInit(E_FAIL),
		bodyReaderInit(E_FAIL),
		c_mapperInit(E_FAIL)
	{
		FORI0(BODY_COUNT)
		{
			_face_source[i] = nullptr;
			_face_source[i] = nullptr;
		}

		faceMatSource = new CKinectFaceMat();
		streamsMatSource = new CKinectStreamsMat();

	}

	CKinectSource::~CKinectSource()
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
		SafeRelease(_coordinate_mapper);

		if (nullptr != faceMatSource) {
			delete faceMatSource;
			faceMatSource = nullptr;
		}

		if (nullptr != streamsMatSource) {
			delete streamsMatSource;
			streamsMatSource = nullptr;
		}

		FORI0(BODY_COUNT)
		{
			SafeRelease(_face_source[i]);
			SafeRelease(_face_reader[i]);
		}

		if (_sensor) {
			_sensor->Close();
		}
		SafeRelease(_sensor);
	}


	//Initialize and Open the Default Kinect Sensor
	HRESULT CKinectSource::initSensor()
	{
		HRESULT hr = E_FAIL;
		hr = GetDefaultKinectSensor(&_sensor);
		if (FAILED(hr)) {
			return hr;
		}
		else {
			hr = _sensor->Open();
		}
		return hr;
	}

	//Stop the Kinect Sensor
	HRESULT CKinectSource::stopSensor()
	{
		BOOLEAN isOpen;
		HRESULT hr;
		hr = _sensor->get_IsOpen(&isOpen);
		if (SUCCEEDED(hr) && isOpen) {
			hr = _sensor->Close();
		}

		return hr;
	}
	
	//Restart the Kinect Sensor
	HRESULT CKinectSource::restartSensor()
	{
		HRESULT hr;
		BOOLEAN isOpen;
		hr = _sensor->get_IsOpen(&isOpen);
		if (SUCCEEDED(hr) && !isOpen) {
			hr = _sensor->Open();
		}
		return hr;
	}

	//Initialize a Multi Source Frame Reader
	HRESULT CKinectSource::initMultiSourceReader(SOURCETYPE sourceTypes)
	{
		/******     To be implemented later     ********/
		return E_NOTIMPL;
	}

	//Initialize Single Source Readers
	//Can initialize more than one at a time
	//Currently Supported Sources :- IR,COLOR,DEPTH,FACE BASICS
	//Rest to be implemented later
	HRESULT CKinectSource::initSourceReader(SOURCETYPE sourceType)
	{
		HRESULT hrIR = S_OK, hrColor = S_OK, hrDepth = S_OK,
			hrFace = S_OK, hrBody = S_OK;

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

		if (sourceType & FACE_S) {
			hrFace = initFaceFrameReader(features);
			faceReaderInit = hrFace;
		}

		if (sourceType & BODY_S) {
			hrBody = initBodyFrameReader();
			bodyReaderInit = hrBody;
		}

		if (FAILED(hrFace)) {
			std::cout << "Face Reader Failed to Initialize\n";
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

		if (FAILED(hrBody)) {
			std::cout << "Body Reader Failed to Initialize\n";
		}

		if (FAILED(hrIR) && FAILED(hrDepth) && FAILED(hrColor)
			&& FAILED(hrFace) && FAILED(hrBody)) {
			return E_FAIL;
		}
		else {
			return S_OK;
		}
	}

	//Returns a Single frame of type "frameType" from the initialized Multi Source Reader
	cv::Mat CKinectSource::getMultiFrame(FRAMETYPE frameType)
	{
		/**** To be implemented later *****/
		return cv::Mat();
	}

	//Returns a Single Frame of type "frameType"
	cv::Mat CKinectSource::getFrame(FRAMETYPE frameType, bool rawData)
	{
		HRESULT hr = E_FAIL;

		if (frameType & DEPTH_F) {
			return streamsMatSource->getDepthFrame(this->_depth_reader, this->depthReaderInit, rawData);
		}

		if (frameType & IR_F) {
			return streamsMatSource->getIRframe(this->_ir_reader, this->irReaderInit);
		}

		if (frameType & COLOR_F) {
			return streamsMatSource->getColorFrame(this->_color_reader, this->colorReaderInit);
		}
	}

	//Returns Face Bounding Box
	cv::Rect * CKinectSource::getFaceRect(int & trackedFaces, bool color)
	{
		return faceMatSource->getSDFaceRect(this->_body_reader, this->_face_reader, 
			this->_face_source, trackedFaces, this->faceReaderInit,this-> bodyReaderInit, color);
	}

	//Initialize Color Source and Color Reader
	HRESULT CKinectSource::initColorFrameReader()
	{
		HRESULT hr = E_FAIL;

		hr = _sensor->get_ColorFrameSource(&_color_source);

		if (SUCCEEDED(hr)) {
			hr = _color_source->OpenReader(&_color_reader);
		}

		return hr;
	}

	//Initialize Depth Source and Depth Reader
	HRESULT CKinectSource::initDepthFrameReader()
	{
		HRESULT hr = E_FAIL;

		hr = _sensor->get_DepthFrameSource(&_depth_source);

		if (SUCCEEDED(hr)) {
			hr = _depth_source->OpenReader(&_depth_reader);
		}

		return hr;
	}

	//Initialize IR Source and IR Reader
	HRESULT CKinectSource::initIRframeReader()
	{
		HRESULT hr = E_FAIL;

		hr = _sensor->get_InfraredFrameSource(&_ir_source);

		if (SUCCEEDED(hr)) {
			hr = _ir_source->OpenReader(&_ir_reader);
		}

		return hr;
	}

	//Initialize Standard Face Frame Reader
	HRESULT CKinectSource::initFaceFrameReader(FEATURETYPE features)
	{
		HRESULT hr = S_OK;

		for (int i = 0; i < BODY_COUNT; i++) {
			if (SUCCEEDED(hr)) {
				hr = CreateFaceFrameSource(_sensor, 0, features, &_face_source[i]);
			}

			if (SUCCEEDED(hr)) {
				hr = _face_source[i]->OpenReader(&_face_reader[i]);
			}
		}

		return hr;
	}

	//Initialize HD Face Source
	HRESULT CKinectSource::initHDFaceFrameReader()
	{
		/****** To be implemented later ********/
		return E_NOTIMPL;
	}

	//Initialize Body Frame Reader
	HRESULT CKinectSource::initBodyFrameReader()
	{
		HRESULT hr = E_FAIL;

		hr = _sensor->get_BodyFrameSource(&_body_source);

		if (SUCCEEDED(hr)) {
			_body_source->OpenReader(&_body_reader);
		}

		return hr;
	}

	//Initialize Coordinate Mapper
	HRESULT CKinectSource::initCoordinateMapper()
	{
		HRESULT hr = E_FAIL;
		hr = _sensor->get_CoordinateMapper(&_coordinate_mapper);
		c_mapperInit = hr;
		return hr;
	}

	//Returns Depth of Given Color Frame Coordinate (X,Y)
	float CKinectSource::getColorPixelDepth(HRESULT c_mapperInit, cv::Mat depthMat, int x, int y)
	{
		float depth = -1;
		HRESULT hr;
		UINT16* depthBuffer;
		UINT depthBufferSize;
		DepthSpacePoint* depthPoints = NULL;
		cv::Mat depthImage;
		if (SUCCEEDED(c_mapperInit)) {
			depthPoints = new DepthSpacePoint[1080 * 1920];
			cv::Mat tempDepth = depthMat;

			hr = _coordinate_mapper->MapColorFrameToDepthSpace(512 * 424,
				reinterpret_cast<UINT16*>(depthMat.data), 1920 * 1080, depthPoints);

			if (SUCCEEDED(hr)) {
				DepthSpacePoint p = depthPoints[x + 1920 * y];

				if (p.X != -std::numeric_limits<float>::infinity() && p.Y != -std::numeric_limits<float>::infinity()) {
					int depthX = static_cast<int>(p.X + 0.5);
					int depthY = static_cast<int>(p.Y + 0.5);
					if (SUCCEEDED(hr)) {
						if (tempDepth.data) {
							if (depthX <= 512 && depthX > 0 && depthY <= 424 && depthY > 0)
							{
								depth = tempDepth.at<UINT16>(depthX, depthY);
							}
						}
					}
				}
				if (depthPoints != NULL) {
					delete[] depthPoints;
					depthPoints = NULL;
				}
			}
		}
		return depth;
	}
	
	//Initialize Body Index Frame Reader
	HRESULT CKinectSource::initBodyIndexFrameReader()
	{
		/**** To be implemented later *****/
		return E_NOTIMPL;
	}
}