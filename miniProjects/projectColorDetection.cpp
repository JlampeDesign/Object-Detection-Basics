#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//// webcam recognition /////

Mat img;
vector<vector<int>> newPoint; // { {x,y,0}, {x,y,1}, {} }

// vectors
vector<vector<int>> Colors{
	{124,48,117,143,170,255},	// purple
	{68,72,156,102,126,255},	// green
	{0,62,0,35,255,255} };		// orange

vector<Scalar> ColorValues{
	{255,0,255},
	{0,255,0},
	{51,153,255} };

String colorNames[3] = {
	{"Purple"},
	{"Green"},
	{"Orange"} };

// functions

 Point getContours(Mat imgDil) {

	vector<vector<Point>> contours; 
	vector<Vec4i> hierarchy;

	Point myPoint(0, 0);

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(0, 0, 0), 2);

	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++) {

		int area = contourArea(contours[i]);
		string objectType;

		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);

			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;

			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
			//putText(img, objectType, { boundRect[i].x,boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 1.2);
		}
	}
	return myPoint;
}

 vector<vector<int>> findColor(Mat img)
{
	Mat imgHSV, mask;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	for (int i = 0; i < Colors.size(); i++)
	{
		Scalar lower(Colors[i][0], Colors[i][1], Colors[i][2]);
		Scalar upper(Colors[i][3], Colors[i][4], Colors[i][5]);
		inRange(imgHSV, lower, upper, mask);
		//imshow(colorNames[i], mask);

		Point myPoint = getContours(mask);

		if (myPoint.x != 0 && myPoint.y != 0) {
			newPoint.push_back({ myPoint.x, myPoint.y,i });
		}
	}
	return newPoint;
}

void canvasDraw(vector<vector<int>> drawPoint, vector<Scalar> colorPatterns) 
{
	for (int i = 0; i < drawPoint.size(); i++) {
		circle(img, (Point(drawPoint[i][0], drawPoint[i][1])), 10, colorPatterns[drawPoint[i][2]], FILLED);
	}
}

int webcamTestImport() {
	VideoCapture cap(0);

	while (true) {
		cap.read(img);

		newPoint = findColor(img);
		canvasDraw(newPoint, ColorValues);

		imshow("WebCam", img);
		waitKey(1);
	}
}

/// main function ///

int main() {

	webcamTestImport();

}