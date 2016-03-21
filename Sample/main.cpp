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
 
#include<iostream>
#include "KinectStreamsMat.h"

int main() {
	//Obtain a CKinectStramsMat Object
	CKinectStreamsMat* kinectStream = new CKinectStreamsMat();

	HRESULT hr = E_FAIL;

	//Initialize Sensor;
	hr = kinectStream->initSensor();

	//Exit With Error Code If Kinect Sensor Failed to Initialize
	if (FAILED(hr)) {
		return hr;
	}

	cv::Mat depthImage,colorImage,irImage;

	while (true) {
		//Get a single depth frame from kinect
		depthImage = kinectStream->getFrame(KS_DEPTH);

		//Get a single color frame from kinect
		colorImage = kinectStream->getFrame(KS_COLOR);
		
		//Get a single IR frame from Kinect
		irImage = kinectStream->getFrame(KS_IR);

		//ensure depthImage has data
		if (depthImage.data)
		    cv::imshow("Depth Image", depthImage);

		//ensure colorImage has data
		if(colorImage.data)
		   cv::imshow("Color", colorImage);
	   
	   //ensure irImage has data
	   if(irImage.data)
		   cv::imshow("Infrared",irImage);

		//exit if escape key is pressed
		if (cv::waitKey(20) == 27) {
			break;
		}
	}
	return 0;
}
