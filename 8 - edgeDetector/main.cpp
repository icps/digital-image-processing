#include <QCoreApplication>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

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


int main( )
{

  Mat src, src_gray;
  src = imread("/home/isadora/Imagens/PDI/Fig1016(a)(building_original).tif", CV_LOAD_IMAGE_COLOR );

  if( !src.data )
  { return -1; }

  //SUAVIZADA
  Mat blurred;
//  GaussianBlur( src, blurred, Size(5,5), 0, 0, BORDER_DEFAULT );
  medianBlur(src, blurred, 5);
  cvtColor( blurred, src_gray, CV_BGR2GRAY );

  Mat grad = resultSobel(src_gray);

  namedWindow("(B)", CV_WINDOW_AUTOSIZE);
  imshow("(B)", grad );


  //NÃO SUAVIZADA
  Mat src_gray1;
  cvtColor( src, src_gray1, CV_BGR2GRAY );

  Mat grad1 = resultSobel(src_gray1);

  namedWindow("(A)", CV_WINDOW_AUTOSIZE );
  imshow("(A)", grad1 );


  waitKey(0);
  return 0;
  }
