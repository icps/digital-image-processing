#include <QCoreApplication>

#include <iostream>
#include <opencv2/opencv.hpp>
#include<sstream>

using namespace std;
using namespace cv;

int main()
{
    // Load the image
    Mat src = imread("/home/isadora/Imagens/PDI/Fig0930(a)(calculator).tif", CV_LOAD_IMAGE_COLOR);

    Mat dst;
    cvtColor(src, dst, COLOR_RGB2GRAY);
    // Check if image is loaded fine
    if(!src.data)
        cerr << "Problem loading image!!!" << endl;
    // Show source image
    namedWindow("src", WINDOW_GUI_NORMAL);
    imshow("src", dst);

    Mat bw;
    threshold(dst, bw, 150, 255, THRESH_BINARY);
    // Show binary image
    namedWindow("binary", WINDOW_GUI_NORMAL);
    imshow("binary", bw);

    // Create the images that will use to extract the horizontal and vertical lines
    Mat horizontal = bw.clone();

    // Specify size on horizontal axis
    int horizontalsize = horizontal.cols / 40;
    // Create structure element for extracting horizontal lines through morphology operations
    Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontalsize,1));
    // Apply morphology operations
    morphologyEx(horizontal, horizontal, MORPH_OPEN, horizontalStructure, Point(-1,-1), 2);

    // Show extracted horizontal lines
    namedWindow("horizontal", WINDOW_NORMAL);
    imshow("horizontal", horizontal);

    Mat result;
    result = bw - horizontal;

    medianBlur(result, result, 7);

    namedWindow("result", WINDOW_AUTOSIZE);
    imshow("result", result);

    waitKey(0);
    return 0;
}
