#include <QCoreApplication>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

float Brightness;
float Contrast ;

int B;
int C;

char winName[20]="PDI Isadora";
Mat frame;
VideoCapture cap(0);

void onTrackbar_changed(int, void*)
{
     Brightness = float(B)/100;
     Contrast   = float(C)/100;

    cap.set(CAP_PROP_BRIGHTNESS,Brightness);
    cap.set(CAP_PROP_CONTRAST, Contrast);
}

int main(int, char**)
{

    if(!cap.isOpened())  // check if we succeeded
        return -1;

    cout<<"Press 's' to save snapshot"<<endl;
    namedWindow(winName);

    Brightness = cap.get(CAP_PROP_BRIGHTNESS);
    Contrast   = cap.get(CAP_PROP_CONTRAST);

      B = int(Brightness*100);
      C = int(Contrast*100);

      createTrackbar("Brightness", winName, &B, 100, onTrackbar_changed);
      createTrackbar("Contrast", winName, &C, 100, onTrackbar_changed);

      int i = 0;
      char name[10];
      for(;;)
      {

           cap >> frame; // get a new frame from camera
           imshow(winName, frame);
           char c = waitKey(30);

           if(c=='s') {
            sprintf(name,"%d.jpg",i++);
            imwrite(name,frame);
            }

            if( c == 'e')
               break;


       }
       return 0;
}
