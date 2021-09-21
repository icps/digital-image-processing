#include <QCoreApplication>

#include <iostream>
#include <opencv2/opencv.hpp>
#include<sstream>

using namespace std;
using namespace cv;

int main()
{
    // Load the image
    Mat src = imread("/home/alunoic/Downloads/img/sudoku.png", CV_LOAD_IMAGE_GRAYSCALE);

    medianBlur(src, src, 1);

    adaptiveThreshold(src, src, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 15, 5);

    imshow("final", src);


    waitKey(0);
    return 0;
}
