#include <QCoreApplication>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

int Blur = 1;

char winName[20] = "PDI Isadora";
Mat frame;
VideoCapture cap(0);

void onTrackbar_changed(int, void*)
{
    blur(frame, frame, Size(Blur,Blur));

    imshow(winName, frame);
}

int main(int, char**)
{

    if(!cap.isOpened())  // check if we succeeded
        return -1;

    namedWindow(winName);

    createTrackbar("Blur", winName, &Blur, 50, onTrackbar_changed);

    for(;;)
    {
        cap >> frame; // get a new frame from camera
        cvtColor(frame, frame, CV_BGR2GRAY);

        onTrackbar_changed(Blur, 0);

        waitKey(30);
    }

    cap.release();
    return 0;
}
