#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/// course lesson licence plate recognition ///

void FacialRecognition() {

	string objectType = "number plate";

	VideoCapture cap(0);
	Mat img;

	CascadeClassifier plateCascade;
	plateCascade.load("Resources/haarcascade_russian_plate_number.xml");

	if (plateCascade.empty()) { cout << "XML file not found" << endl; }

	vector<Rect> plates;

	while (true) 
	{
		cap.read(img);
		plateCascade.detectMultiScale(img, plates, 1.1, 10); // look up detectMultiScale for more setting options

		for (int i = 0; i < plates.size(); i++) {
			Mat imgCrop = img(plates[i]);
			//imshow(to_string(i), imgCrop);
			imwrite("Resources/plates/" + to_string(i) + ".png", imgCrop);
			rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 3);
			putText(img, objectType, { plates[i].x, plates[i].y - 8 }, FONT_HERSHEY_PLAIN, 2, Scalar(0, 255, 0), 2);
		}

		imshow("Image", img);
		waitKey(1);
	}
}

/// main function ///

int main() {

	FacialRecognition();

}