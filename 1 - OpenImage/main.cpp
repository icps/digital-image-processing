//#include <QCoreApplication>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, const char** argv )
{
     Mat img = imread("lena.bmp", CV_LOAD_IMAGE_UNCHANGED);

     if (img.empty()) //check whether the image is loaded or not
     {
          cout << "Error : Image cannot be loaded..!!" << endl;
          return -1;
     }

     Mat gray_image;
     cvtColor(img, gray_image, COLOR_BGR2GRAY);
     imwrite("Gray_Image.jpg", gray_image);

     namedWindow("Display Image", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
     namedWindow( "Gray image", WINDOW_AUTOSIZE);

     imshow("Display Image", img); //display the image which is stored in the 'img' in the "MyWindow" window
     imshow("Gray image", gray_image);

     waitKey(0); //wait infinite time for a keypress

     destroyWindow("MyWindow"); //destroy the window with the name, "MyWindow"

     return 0;
}
