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

#include <Windows.h>

	typedef unsigned long long SOURCETYPE;

    #define FEATURETYPE SOURCETYPE

	#define FRAMETYPE SOURCETYPE

	//typecast to SOURCETYPE
    #define MAKE_SOURCETYPE(VAL)		static_cast<SOURCETYPE>(VAL)


	
	/**************      Available Source Types     ****************/
	 enum SourceTypes {
		BODY_S								= MAKE_SOURCETYPE(0x1000000),
		COLOR_S								= MAKE_SOURCETYPE(0x0100000),
		DEPTH_S								= MAKE_SOURCETYPE(0x0010000),
		IR_S								= MAKE_SOURCETYPE(0x0001000),
		LONG_EXPOSURE_IR_S						= MAKE_SOURCETYPE(0x0000100),
		BODY_INDEX_S							= MAKE_SOURCETYPE(0x0000010),
		AUDIO_S								= MAKE_SOURCETYPE(0x0000001)
	};



	 /*************      Available Face Features     ****************/
	 enum FaceFeatures {
		 //Ignore Warning C4309 
		BOUNDING_BOX_IN_COLOR_SAPCE					= MAKE_SOURCETYPE(0x10000000000),
		POINTS_IN_COLOR_SPACE						= MAKE_SOURCETYPE(0x01000000000),
		ROTATION_ORIENTATION						= MAKE_SOURCETYPE(0x00100000000),
		HAPPY								= MAKE_SOURCETYPE(0x00010000000),
		RIGHT_EYE_CLOSED						= MAKE_SOURCETYPE(0x00001000000),
		LEFT_EYE_CLOSED							= MAKE_SOURCETYPE(0x00000100000),
		MOUTH_OPEN							= MAKE_SOURCETYPE(0x00000010000),
		MOUTH_MOVED							= MAKE_SOURCETYPE(0x00000001000),
		LOOKING_AWAY							= MAKE_SOURCETYPE(0x00000000100),
		GLASSES								= MAKE_SOURCETYPE(0x00000000010),
		FACE_ENGAGEMENT							= MAKE_SOURCETYPE(0x00000000001)
	};




	 /*************        Available Frame Types          ****************/
	  enum FrameType {
		DEPTH_F			= MAKE_SOURCETYPE(0x1000000),
		IR_F			= MAKE_SOURCETYPE(0x0100000),
		COLOR_F			= MAKE_SOURCETYPE(0x0010000),
		FACE_F			= MAKE_SOURCETYPE(0x0001000),
		HDFACE_F		= MAKE_SOURCETYPE(0x0000100),
		BODY_F			= MAKE_SOURCETYPE(0x0000010),
		BODY_INDEX_F		= MAKE_SOURCETYPE(0x0000001),
	};




	template<class Interface>
	inline void SafeRelease(Interface *& pInterfaceToRelease)
	{
		if (pInterfaceToRelease != NULL)
		{
			pInterfaceToRelease->Release();
			pInterfaceToRelease = NULL;
		}
	}
