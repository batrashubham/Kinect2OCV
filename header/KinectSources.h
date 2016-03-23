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

#include "helper.h"
#include "KinectStreamsMat.h"
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <Windows.h>
#include <Kinect.h>
#include<Kinect.Face.h>

	class CKinectSources {
	public:

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
		IFaceFrameSource* _face_source;
		//standard face source reader
		IFaceFrameReader* _face_reader;
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

		/*********     Constructor ***********/

		CKinectSources();

		/*********     Destructor  **********/

		~CKinectSources();

		/*********     Methods     **********/
		
		//Initialize the default Kinect Sensor
		HRESULT initSensor();
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
		cv::Mat getFrame(FRAMETYPE);

	private:

		/***********       Fields       ****************/

		//ensures that reader was successfuly initialized
		HRESULT depthReaderInit;
		//ensures that reader was successfuly initialized
		HRESULT irReaderInit;
		//ensures that reader was successfuly initialized
		HRESULT colorReaderInit;


		/***********       Methods      ****************/

		//Intialize Color Frame Reader
		HRESULT initColorFrameReader();
		//Initialize Depth Frame Reader
		HRESULT initDepthFrameReader();
		//Initialize Infrared Frame Reader
		HRESULT initIRframeReader();
		//Initialize Face Frame Reader
		HRESULT initFaceFrameReader();				/* To be implemented later */
		//Initialize HD Face Reader
		HRESULT initHDFaceFrameReader();			/* To be implemented later */
		//Initialize Body Frame Reader
		HRESULT initBodyFrameReader();             /* To be implemented later */
		//Initialize Body Index Frame Reader
		HRESULT initBodyIndexFrameReader();        /* To be implemented later */
	};