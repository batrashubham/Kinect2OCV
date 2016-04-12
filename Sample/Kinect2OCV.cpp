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

// Kinect2OCV.cpp : Defines the entry point for the console application.
//

#include"KinectSources.h"
#include<iostream>
#include "helper.h"

using namespace cv;

void drawStreams();
void drawFaceRect();

int main(int argc, char *argv[])
{
	int choice=0;
	std::cin>>choice;
	//1. for face   2. for streams
	switch(choice){
		case 1:
		drawFaceRect();
		break;
		case 2:
		drawStreams();
		break;
		default:
		std::cout<<"Invalid Input\n";
	}
	
	return 0;
}

void drawStreams() {
	//create a CKinectSources object
	CKinectSources* src = new CKinectSources();
	//Initialize the Kinect Sensor
	src->initSensor();
	//Initialize the required Streams
	//As many as needed
	src->initSourceReader(COLOR_S | DEPTH_S | IR_S);
	//Create Mats for the images
	Mat depthImage, colorImage, irImage;
	
	//start the drawing loop
	while(true){
		//obtain the depth frame
		depthImage = src->getFrame(DEPTH_F);
		//obtain the color frame
		colorImage = src->getFrame(COLOR_F);
		//obtain the ir frame
		irImage = src->getFrame(IR_F);

		//ensure the frames have data
		if (depthImage.data) {
			imshow("depth", depthImage);
		}

		if (colorImage.data) {
			imshow("color", colorImage);
		}

		if (irImage.data) {
			imshow("infrared", irImage);
		}

		//wait for 30ms
		//quit if escape key pressed
		if (waitKey(20) == 27) {
			destroyAllWindows();
			break;
		}
	}
}

void drawFaceRect() {
	//create CKinectSources object
	CKinectSources* src = new CKinectSources();
	//initialize the Kinect Sensor
	src->initSensor();
	//initialize streams
	//for face tracking valid body tracking id is required
	//so initialize body source too
	src->initSourceReader(COLOR_S | FACE_S | BODY_S);
	//create a color mat to draw face rect on
	Mat colorImage;
	//Create an array of rects in case more than 1 face is tracked
	Rect* faceRects;

	//start the drawing loop
	while (true) {
		//gives the no. of currently tracked faces
		int trackedFaces = 0;
		faceRects = src->getFaceRect(trackedFaces);
		colorImage = src->getFrame(COLOR_F);

		//ensure color frame has data
		if (colorImage.data) {
			//repeat for no. of tracked faces
			for (int i = 0; i < trackedFaces; i++) {
				//ensure current rect has area greater than zero
				if (faceRects[i].height > 0 && faceRects[i].width > 0) {
					rectangle(colorImage, faceRects[i], Scalar(0, 255, 0), 2);
				}
			}
			resize(colorImage, colorImage, Size(), 0.5, 0.5);
			imshow("faces", colorImage);
			if (waitKey(20) == 27) {
				destroyAllWindows();
				break;
			}
		}
	}
}