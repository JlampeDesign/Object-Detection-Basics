#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/// course lesson 1 ///
int colorManipulation() {
	string path = "resources/cards.jpg";
	Mat img = imread(path);
	Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
	
	// image modifications
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur, Size(7,7),5,0);
	Canny(imgBlur, imgCanny, 25, 75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);
	erode(imgDil, imgErode, kernel);

	imshow("GrayImage", imgGray);
	imshow("BlurImage", imgBlur);
	imshow("CannyImage", imgCanny);
	imshow("dilationImage", imgDil);
	imshow("ErodeImage", imgErode);

	waitKey(0);
	return(0);
}


/// main function ///

int main() {

	colorManipulation();

}