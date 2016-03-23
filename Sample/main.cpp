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

using namespace cv;

int main() {
	//Create a CKinectSources Object
	CKinectSources* source = new CKinectSources();
	//Initialize the Kinect Sensor
	HRESULT hr = source->initSensor();

	Mat color, ir, depth;

	//Initialize Sources if Sensor Successfuly Initialized
	if (SUCCEEDED(hr)) {
		hr = source->initSourceReader(DEPTH_S | IR_S | COLOR_S);
	}

	//if sources successfuly initialized start obtainig frames
	if (SUCCEEDED(hr)) {
		while (true) {
			//get color frame
			color = source->getFrame(COLOR_F);
			//get IR frame
			ir = source->getFrame(IR_F);
			//get depth frame
			depth = source->getFrame(DEPTH_F);

			//ensure color image has data
			if (color.data) {
				imshow("color", color);
			}

			//ensure IR image has data
			if (ir.data) {
				imshow("ir", ir);
			}

			//ensure depth image has data
			if (depth.data) {
				imshow("depth", depth);
			}

			//exit if user presses escape key
			if (waitKey(20) == 27) {
				break;
			}
		}
	}

	delete source;
	return 0;
}