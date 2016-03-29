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


/**************      Available Source Types     ****************/
enum SourceTypes {
	BODY_S = 1,
	COLOR_S = 2,
	DEPTH_S = 4,
	IR_S = 8,
	LONG_EXPOSURE_IR_S = 16,
	BODY_INDEX_S = 32,
	AUDIO_S = 64,
	FACE_S = 128
};



/*************      Available Face Features     ****************/
enum FaceFeatures {
	//Ignore Warning C4309 
	BOUNDING_BOX_IN_IR_SPACE = 1,
	POINTS_IN_IR_SPACE = 2,
	BOUNDING_BOX_IN_COLOR_SAPCE = 4,
	POINTS_IN_COLOR_SPACE = 8,
	ROTATION_ORIENTATION = 16,
	HAPPY = 32,
	RIGHT_EYE_CLOSED = 64,
	LEFT_EYE_CLOSED = 128,
	MOUTH_OPEN = 256,
	MOUTH_MOVED = 512,
	LOOKING_AWAY = 1024,
	GLASSES = 2048,
	FACE_ENGAGEMENT = 4096
};




/*************        Available Frame Types          ****************/
enum FrameType {
	DEPTH_F = 1,
	IR_F = 2,
	COLOR_F = 4,
	FACE_F = 8,
	HDFACE_F = 16,
	BODY_F = 32,
	BODY_INDEX_F = 64,
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
