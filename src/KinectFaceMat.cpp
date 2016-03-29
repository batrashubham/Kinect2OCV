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


#include "KinectFaceMat.h"


cv::Rect* getHDfaceRect()
{
	/********    To be implemented later   *********/

	return nullptr;
}




cv::Rect* getSDFaceRect(IBodyFrameReader* _body_reader, IFaceFrameReader* _face_reader[],
	IFaceFrameSource* _face_source[], int& trackedFaces, HRESULT faceReaderinit, HRESULT bodyReaderInit)
{
	cv::Rect faceRect[BODY_COUNT];
	HRESULT hr;
	if (SUCCEEDED(faceReaderinit) && SUCCEEDED(bodyReaderInit)) {
		IBody* Bodies[BODY_COUNT] = { 0 };
		if (_body_reader != nullptr)
		{
			IBodyFrame* BodyFrame = nullptr;
			hr = _body_reader->AcquireLatestFrame(&BodyFrame);
			if (SUCCEEDED(hr))
			{
				hr = BodyFrame->GetAndRefreshBodyData(BODY_COUNT, Bodies);
			}
			SafeRelease(BodyFrame);
		}
		bool gotBodyData = SUCCEEDED(hr);

		// iterate through each face reader
		for (int iFace = 0; iFace < BODY_COUNT; ++iFace)
		{
			// fetch the latest face frame from current reader
			IFaceFrame* frame = nullptr;
			hr = _face_reader[iFace]->AcquireLatestFrame(&frame);

			BOOLEAN isFaceTracked = false;
			if (SUCCEEDED(hr) && nullptr != frame)
			{
				// check if a valid face is tracked in this face frame
				hr = frame->get_IsTrackingIdValid(&isFaceTracked);
			}

			if (SUCCEEDED(hr))
			{
				if (isFaceTracked)
				{
					IFaceFrameResult* FaceFrameResult = nullptr;
					RectI faceBox = { 0 };
					PointF facePoints[FacePointType::FacePointType_Count];

					hr = frame->get_FaceFrameResult(&FaceFrameResult);

					// ensure FaceFrameResult contains data before trying to access it
					if (SUCCEEDED(hr) && FaceFrameResult != nullptr)
					{
						hr = FaceFrameResult->get_FaceBoundingBoxInColorSpace(&faceBox);

						if (SUCCEEDED(hr))
						{
							hr = FaceFrameResult->GetFacePointsInColorSpace(FacePointType::FacePointType_Count, facePoints);
						}

						if (SUCCEEDED(hr)) {
							//gives the number of faces tracked
							trackedFaces++;
						}

						//Set the values of corresponding cv::Rect
						faceRect[iFace].x = faceBox.Left;
						faceRect[iFace].y = faceBox.Top;
						faceRect[iFace].width = faceBox.Right - faceBox.Left;
						faceRect[iFace].height = faceBox.Bottom - faceBox.Top;

					}

					SafeRelease(FaceFrameResult);
				}
				else
				{
					// face tracking is not valid - attempt to fix the issue
					// a valid body is required to perform this step
					if (gotBodyData)
					{
						// check if the corresponding body is tracked 
						// if this is true then update the face frame source to track this body
						IBody* Body = Bodies[iFace];
						if (Body != nullptr)
						{
							BOOLEAN isTracked = false;
							hr = Body->get_IsTracked(&isTracked);

							UINT64 bodyTId;
							if (SUCCEEDED(hr) && isTracked)
							{
								// get the tracking ID of this body
								hr = Body->get_TrackingId(&bodyTId);
								if (SUCCEEDED(hr))
								{
									// update the face frame source with the tracking ID
									_face_source[iFace]->put_TrackingId(bodyTId);
								}
							}
						}
					}
				}
			}

			SafeRelease(frame);
		}

		if (gotBodyData)
		{
			for (int i = 0; i < _countof(Bodies); ++i)
			{
				SafeRelease(Bodies[i]);
			}
		}
	}
	return faceRect;
}
