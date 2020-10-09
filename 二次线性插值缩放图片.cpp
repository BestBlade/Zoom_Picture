#include <iostream>
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include"opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace std;
using namespace cv;

Mat zoomPic(Mat img, Size res_size)
{
	int rows = img.rows - 1;
	int cols = img.cols - 1;

	int newrows = res_size.height;
	int newcols = res_size.width;

	Mat res(res_size, img.type());
	for (int i = 0; i < newrows; i++) {
		for (int j = 0; j < newcols; j++) {
			float x = i * rows / float(newrows);
			float y = j * cols / float(newcols);

			int x1 = x;
			int x2 = x1 + 1;
			int y1 = y;
			int y2 = y1 + 1;
			if (img.channels() == 1) {
				float f1 = (img.at<uchar>(x1, y2) - img.at<uchar>(x1, y1)) * float(y - y1) + img.at<uchar>(x1, y1);
				float f2 = (img.at<uchar>(x2, y2) - img.at<uchar>(x2, y1)) * float(y - y1) + img.at<uchar>(x2, y1);
				float fxy = (f2 - f1) * (x - x1) + f1;

				res.at<uchar>(i, j) = fxy;
			}
			else {
				for (int c = 0; c < img.channels(); c++) {
					float f1 = (img.at<Vec3b>(x1, y2)[c] - img.at<Vec3b>(x1, y1)[c]) * float(y - y1) + img.at<Vec3b>(x1, y1)[c];
					float f2 = (img.at<Vec3b>(x2, y2)[c] - img.at<Vec3b>(x2, y1)[c]) * float(y - y1) + img.at<Vec3b>(x2, y1)[c];
					float fxy = (f2 - f1) * (x - x1) + f1;

					res.at<Vec3b>(i, j)[c] = fxy;
				}
			}
		}
	}
	return res;
}

int main()
{
	Mat img = imread("C://Users//Chrysanthemum//Desktop//1.png");
	Size res_size(192*5, 108*3);				/*	先列再行	*/

	Mat res = zoomPic(img, res_size);

	imshow("origin pic", img);
	imshow("result pic", res);
	waitKey();

}