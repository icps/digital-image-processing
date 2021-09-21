#include <QCoreApplication>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

int main()
{
 Mat src = imread("/home/isadora/Imagens/PDI/Fig1016(a)(building_original).tif", CV_LOAD_IMAGE_GRAYSCALE );
 if(src.empty())
 {
     return -1;
 }

 Mat dst, cdst;
 Canny(src, dst, 250, 300, 3);
 cvtColor(dst, cdst, CV_GRAY2BGR);

  vector<Vec4i> lines;
  HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10 );
  for( size_t i = 0; i < lines.size(); i++ )
  {
    Vec4i l = lines[i];
    line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
  }

 imshow("source", src);
 imshow("detected lines", cdst);

 waitKey();

 return 0;
}
