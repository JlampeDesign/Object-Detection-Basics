#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/// course lesson 3 --- shapes and text ///

int boxShapes() {
	
	// blank box
	Mat box(512, 512, CV_8UC3, Scalar(255, 255, 255));

	circle(box,Point(256, 256),40,Scalar(255,0,255),FILLED);
	rectangle(box, Point(156, 156), Point(356, 356), Scalar(0, 70, 240), 10);
	line(box, Point(50, 400), Point(450, 400), Scalar(0, 0, 0), 10);

	putText(box, "test text", Point(100,390), FONT_HERSHEY_COMPLEX,2, Scalar(0, 0, 0),2);


	imshow("Box", box);
	waitKey(0);

	return(0);
}

/// main function ///

int main() {

	boxShapes();

}