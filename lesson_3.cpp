#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/// course lesson 2 ///

int imageResizing() {
	string path = "Resources/cards.jpg";
	Mat img = imread(path);
	Mat imgResize, imgCrop;

	// cout << img.size() << endl;
	resize(img, imgResize, Size(), 0.5, 0.5);

	Rect roi(200, 100, 300, 300);
	imgCrop = img(roi);

	//imshow("Image", img);
	imshow("Image Resize", imgResize);
	imshow("Image Crop", imgCrop);
	waitKey(0);

	return(0);
}

/// main function ///

int main() {

	imageResizing();

}