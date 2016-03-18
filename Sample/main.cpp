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

	cv::Mat depthImage,colorImage;

	while (true) {
		//Get a single depth frame from kinect
		depthImage = kinectStream->getDepthFrame();

		//Get a single color frame from kinect
		colorImage = kinectStream->getColorFrame();

		//ensure depthImage has data
		if (depthImage.data)
		    cv::imshow("Depth Image", depthImage);

		//ensure colorImage has data
		if(colorImage.data)
		   cv::imshow("color", colorImage);

		//exit if escape key is pressed
		if (cv::waitKey(20) == 27) {
			break;
		}
	}
	return 0;
}
