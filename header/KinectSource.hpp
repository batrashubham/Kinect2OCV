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

#pragma once

#include "helper.hpp"

namespace K2OCV {

//Forward Declarations
class CKinectFaceMat;
class CKinectStreamsMat;

	class CKinectSource {

		/***********    Fields      *************/

		//default kinect sensor
		IKinectSensor* _sensor;
		//Multiple source frame reader
		IMultiSourceFrameReader* _multi_source_frame_reader;
		//depth source
		IDepthFrameSource* _depth_source;
		//depth source reader
		IDepthFrameReader* _depth_reader;
		//color source
		IColorFrameSource* _color_source;
		//color source reader
		IColorFrameReader* _color_reader;
		//Infrared source
		IInfraredFrameSource* _ir_source;
		//Infrared source reader
		IInfraredFrameReader* _ir_reader;
		//standard face source
		IFaceFrameSource* _face_source[BODY_COUNT];
		//standard face source reader
		IFaceFrameReader* _face_reader[BODY_COUNT];
		//High Definition face source
		IHighDefinitionFaceFrameSource* _hd_face_source;
		//High Definition face source reader
		IHighDefinitionFaceFrameReader* _hd_face_reader;
		//Body Frame Source
		IBodyFrameSource* _body_source;
		//Body Frame Source Reader
		IBodyFrameReader* _body_reader;
		//Body Index Frame Source
		IBodyIndexFrameSource* _body_index_source;
		//Body Index Frame Source Reader
		IBodyIndexFrameReader* _body_index_reader;
		//Coordinate Mapper
		ICoordinateMapper* _coordinate_mapper;

		//To Obtain Kinect Face Data
		CKinectFaceMat* faceMatSource;
		//To Obtain Kinect Streams Data
		CKinectStreamsMat* streamsMatSource;

		//ensures that reader was successfuly initialized
		HRESULT depthReaderInit;
		//ensures that reader was successfuly initialized
		HRESULT irReaderInit;
		//ensures that reader was successfuly initialized
		HRESULT colorReaderInit;
		//ensure face reader was successfuly initialized
		HRESULT faceReaderInit;
		//ensure Body reader was successfuly initialized
		HRESULT bodyReaderInit;
		//ensure coordinate mapper was successfuly initialized
		HRESULT c_mapperInit;


		/***********       Methods      ****************/

		//Intialize Color Frame Reader
		HRESULT initColorFrameReader();
		//Initialize Depth Frame Reader
		HRESULT initDepthFrameReader();
		//Initialize Infrared Frame Reader
		HRESULT initIRframeReader();
		//Initialize Face Frame Reader
		HRESULT initFaceFrameReader(FEATURETYPE);
		//Initialize HD Face Reader
		HRESULT initHDFaceFrameReader();			/* To be implemented later */
		//Initialize Body Frame Reader
		HRESULT initBodyFrameReader();
		//Initialize Body Index Frame Reader
		HRESULT initBodyIndexFrameReader();        /* To be implemented later */

	public:
		CKinectSource();
		~CKinectSource();
		//Initialize the default Kinect Sensor
		HRESULT initSensor();
		//Pause the Kinect Sensor
		HRESULT stopSensor();
		//Resume the Kinect Sensor
		HRESULT restartSensor();
		//Initialize Multi Source Frame Reader
		//pass in types of sources to be initialized
		HRESULT initMultiSourceReader(SOURCETYPE);      /* To be implemented later */
		//Initialize Single sources of different types
		//Pass in the types of source to be initialized
		HRESULT initSourceReader(SOURCETYPE);
		//Get a frame from the Multi Source Frame Reader
		//Pass in the type of frame to be fetched
		cv::Mat getMultiFrame(FRAMETYPE);
		//Get a frame from a Single source
		//Pass in the type of frame to be fetched
		cv::Mat getFrame(FRAMETYPE, bool rawData = false);
		//Get Face Bounding Box
		//In IR or Color Space
		cv::Rect* getFaceRect(int& trackedFaces, bool color = false);
		//Initialize Coordinate Mapper
		HRESULT initCoordinateMapper();
		//get Color Pixel Depth
		float getColorPixelDepth(HRESULT c_mapperInit, cv::Mat depthMat, int x = -1, int y = -1);

	};

}