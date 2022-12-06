#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//// course tests /////

int imageImportTest() {
	string path = "resources/test.png";
	Mat img = imread(path); // Mat is matrix for image reading
	imshow("Image", img);
	waitKey(0);
	return 0;
}

int videoImportTest() {
	string path = "resources/test_video.mp4";
	VideoCapture cap(path);
	Mat img;

	while (true) {
		cap.read(img);

		imshow("Video", img);
		waitKey(15);
	}
}

int webcamTestImport() {
	VideoCapture cap(0);
	Mat img;

	while (true) {
		cap.read(img);

		imshow("WebCam", img);
		waitKey(1);
	}
}

/// course lesson 1 ///



/// main function ///

int main() {

	webcamTestImport();

}