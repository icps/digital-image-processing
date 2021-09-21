#include <QCoreApplication>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

int scale = 1;
int delta = 0;
int ddepth = CV_16S;

Mat resultSobel(Mat src_gray) {

    /// Generate grad_x and grad_y
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    Mat grad;

    /// Gradient X
    Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x, abs_grad_x );

    /// Gradient Y
    Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );

    /// Total Gradient (approximate)
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

    return grad;
}

int main() {

  Mat image = imread("/home/alunoic/Downloads/img/pears.png", CV_LOAD_IMAGE_COLOR);
  Mat image2 = image.clone();

  Mat src_gray;
  cvtColor(image, src_gray, CV_BGR2GRAY);
  imshow("pt", src_gray);

  Mat grad = resultSobel(src_gray);

  Mat imgLaplacian;
  Laplacian(grad, imgLaplacian, CV_8U, 7, 6, 0, BORDER_DEFAULT);

  threshold(grad, grad, 40, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
  bitwise_not(grad, grad);

  Mat dist;
  distanceTransform(grad, dist, CV_DIST_L2, 3);
  normalize(dist, dist, 0, 1., NORM_MINMAX);
  imshow("dist", dist);

  threshold(dist, dist, .4, 1, CV_THRESH_BINARY);
  morphologyEx(dist, dist, MORPH_DILATE, Mat::ones(3,3, CV_8UC1));
  imshow("peaks", dist);

  Mat dist_8u;
  dist.convertTo(dist_8u, CV_8U);

  vector<vector<Point>> contours;
  findContours(dist_8u, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
  Mat markers = Mat::zeros(dist.size(), CV_32SC1);

  for (std::size_t i = 0; i < contours.size(); ++i) {
    drawContours(markers, contours, i, Scalar::all(i+1), -1);
  }

  circle(markers, Point(5,5), 3, CV_RGB(255,255,255), -1);

  watershed(image2, markers);
  Mat mark = Mat::zeros(markers.size(), CV_8UC1);
  markers.convertTo(mark, CV_8UC1);
  bitwise_not(mark, mark);

  threshold(mark, mark, 253, 255, THRESH_BINARY);
  imshow("mark", mark);

  waitKey(0);
  return 0;
}
