#include <QCoreApplication>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

int morph_operator = 0;
int const max_operator = 3;

int min_threshold = 0;
int max_threshold = 255;

int min_mask = 0;
int max_mask = 10;

char winName[50] = "0 - DILATE, 1 - ERODE, 2 - OPEN, 3 - CLOSE";
Mat frame;
VideoCapture cap(0);

Mat update_mask();


void morphological_operator(int,  void*)
{
    switch (morph_operator) {
    case 0:
        morphologyEx(frame, frame, MorphTypes::MORPH_DILATE, update_mask());
    case 1:
        morphologyEx(frame, frame, MorphTypes::MORPH_ERODE, update_mask());
    case 2:
        morphologyEx(frame, frame, MorphTypes::MORPH_OPEN, update_mask());
    case 3:
        morphologyEx(frame, frame, MorphTypes::MORPH_CLOSE, update_mask());
    }

    imshow(winName, frame);
}

void threshold_adj(int, void*) {

    threshold(frame, frame, min_threshold, max_threshold, ThresholdTypes::THRESH_BINARY);

    imshow(winName, frame);
}

void mask_adj(int, void*) {

    imshow(winName, frame);
}

Mat update_mask() {
    return Mat::ones(min_mask, min_mask, CV_8U);
}

int main(int, char**)
{

    if(!cap.isOpened())  // check if we succeeded
        return -1;

    namedWindow(winName, WINDOW_FULLSCREEN);

     createTrackbar("Operator",
                    winName, &morph_operator, max_operator, morphological_operator);

     createTrackbar("Binary Threshold", winName, &min_threshold, max_threshold, threshold_adj);

     createTrackbar("Mask", winName, &min_mask, max_mask, mask_adj);

    for(;;)
    {
        cap >> frame; // get a new frame from camera

        morphological_operator(morph_operator, 0);
        threshold_adj(min_threshold, 0);
        mask_adj(min_mask, 0);

        waitKey(30);
    }

    cap.release();
    return 0;
}
