#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/// course lesson face recognition ///

int FacialRecognition() {

	string objectType = "person";
	string path[4] = {
		{"resources/thom.jpg"},
		{"resources/multiplePersons.jpg"},
		{"resources/nathan.jpg"},
		{"resources/arno.png"}};
	Mat img = imread(path[1]);
	Mat imgCrop;

	resize(img, imgCrop, Size(), 0.3, 0.3);

	CascadeClassifier faceCascade;
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");

	if (faceCascade.empty()) {cout << "XML file not found" << endl;}

	vector<Rect> faces;
	faceCascade.detectMultiScale(imgCrop, faces, 1.1, 10); // look up detectMultiScale for more setting options

	for (int i = 0; i < faces.size(); i++) {
		rectangle(imgCrop, faces[i].tl(), faces[i].br(), Scalar(255,0,255),3);
		putText(imgCrop, objectType, { faces[i].x, faces[i].y - 8 }, FONT_HERSHEY_PLAIN, 2, Scalar(0, 255, 0), 2);
	}

	imshow("Image", imgCrop);
	waitKey(0);
	return 0;

}

/// main function ///

int main() {

	FacialRecognition();

}