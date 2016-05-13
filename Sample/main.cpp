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

#include "KinectSource.hpp"
#include "helper.hpp"

using namespace K2OCV;
using namespace cv;

int main() {
	
	Mat dimg , iimg , cimg;
	CKinectSource* src = new CKinectSource();
	src->initSensor();
	src->initSourceReader(IR_S | COLOR_S | DEPTH_S | BODY_S | FACE_S);

	while (true) {
		cimg = src->getFrame(COLOR_F);
		iimg = src->getFrame(IR_F);
		dimg = src->getFrame(DEPTH_F);

		if (cimg.data) {
			imshow("color", cimg);
		}

		if (iimg.data) {
			imshow("ir", iimg);
		}

		if (dimg.data) {
			imshow("depth", dimg);
		}

		if (waitKey(20) == 27) {
			break;
		}
	}

	return 0;
}