#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/// document scanner project ///

Mat originalImage,imgThre, imgGray, imgCanny, imgBlur, imgDil, imgWarp, smallDil;
vector<Point> initialPoints, finalPoints;

float w = 420, h = 596;

Mat preProcessing(Mat img) 
{
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur, Size(7, 7), 5, 0);
	Canny(imgBlur, imgCanny, 25, 75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
	dilate(imgCanny, imgDil, kernel);
	//erode(imgDil, imgErode, kernel);
	return imgDil;
}

vector<Point> getContours(Mat imgDil) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	vector<Point> biggest;
	int maxArea = 0;

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

			if (area > maxArea && conPoly[i].size()==4) {

				biggest = { conPoly[i][0],conPoly[i][1], conPoly[i][2], conPoly[i][3] };
				maxArea = area;
				//drawContours(originalImage, conPoly, i, Scalar(255, 0, 255), 3);
			}

			//rectangle(originalImage, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
			//putText(img, objectType, { boundRect[i].x,boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 1.2);
		}
	}
	return biggest;
}

void drawPoints(vector<Point> points, Scalar color) 
{

	for (int i = 0; i < points.size(); i++) 
	{
		circle(originalImage, points[i], 10, color, FILLED);
		putText(originalImage, to_string(i), { points[i].x + 10,points[i].y }, FONT_HERSHEY_PLAIN, 5, color, 5);
	}

}

vector<Point> reorder(vector<Point> points) 
{
	vector<Point>	newPoints;
	vector<int>		sumPoint, SubPoints;

	for (int i = 0; i < 4; i++) {
		sumPoint.push_back(points[i].x + points[i].y);
		SubPoints.push_back(points[i].x - points[i].y);
	}

	newPoints.push_back(points[min_element(sumPoint.begin(), sumPoint.end()) - sumPoint.begin()]);
	newPoints.push_back(points[max_element(SubPoints.begin(), SubPoints.end()) - SubPoints.begin()]);
	newPoints.push_back(points[min_element(SubPoints.begin(), SubPoints.end()) - SubPoints.begin()]);
	newPoints.push_back(points[max_element(sumPoint.begin(), sumPoint.end()) - sumPoint.begin()]);

	return newPoints;
}

Mat getWarp(Mat img, vector<Point> points, float w, float h) {

	Point2f src[4] = { points[0], points[1], points[2], points[3] };
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

	Mat matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));

	return imgWarp;
}

void documentImport() {

	string path = "resources/paper.jpg";
	Mat originalImage = imread(path); // Mat is matrix for image reading
	resize(originalImage, originalImage, Size(), 0.6, 0.6);

	//		processing

	imgThre = preProcessing(originalImage);

	//		get contours - biggest

	initialPoints = getContours(imgThre);
	//drawPoints(initialPoints,Scalar(0,0,255));
	finalPoints = reorder(initialPoints);
	//drawPoints(finalPoints, Scalar(0, 255, 0));

	//		warp image

	imgWarp = getWarp(originalImage, finalPoints, w, h);
	
	//		showing image
	
	imshow("Image", originalImage);
	//imshow("Image Dilation", imgThre);
	imshow("Image Warp", imgWarp);

	waitKey(0);
}

/// main function ///
int main() {

	documentImport();

}