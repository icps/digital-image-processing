#include <QCoreApplication>

#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <string>
#include <vector>


using namespace cv;
using namespace std;



int main() {

    // Load input image
    Mat bgr_image = imread("/home/alunoic/Downloads/img/chips.png", CV_LOAD_IMAGE_COLOR);

    imshow("src", bgr_image);

    medianBlur(bgr_image, bgr_image, 3);

    // Convert input image to HSV
    Mat hsv_image;
    cvtColor(bgr_image, hsv_image, COLOR_BGR2HSV);

    // Threshold the HSV image, keep only the red pixels

    // RED
    Mat red_hue_image;
    inRange(hsv_image, Scalar(160, 100, 100), Scalar(179, 255, 255), red_hue_image);

    GaussianBlur(red_hue_image, red_hue_image, Size(9, 9), 2, 2);

    Mat red;
    bitwise_and(hsv_image, hsv_image, red, red_hue_image);
    cvtColor(red, red, COLOR_HSV2BGR);
    imshow("vermelho", red);

    Mat red1;
    bitwise_not(red_hue_image, red1);
    imshow("vermelho[pt]", red1);

    //ORANGE
    Mat orange_hue_image;
    inRange(hsv_image, Scalar(0, 180, 180), Scalar(10, 255, 255), orange_hue_image);

    GaussianBlur(orange_hue_image, orange_hue_image, Size(9, 9), 2, 2);

    Mat orange;
    bitwise_and(hsv_image, hsv_image, orange, orange_hue_image);
    cvtColor(orange, orange, COLOR_HSV2BGR);
    imshow("laranja", orange);

    Mat orange1;
    bitwise_not(orange_hue_image, orange1);
    imshow("laranja[pt]", orange1);

    //YELLOW
    Mat yellow_hue_image;
    inRange(hsv_image, Scalar(20, 100, 100), Scalar(30, 255, 255), yellow_hue_image);

    GaussianBlur(yellow_hue_image, yellow_hue_image, Size(9, 9), 2, 2);

    Mat yellow;
    bitwise_and(hsv_image, hsv_image, yellow, yellow_hue_image);
    cvtColor(yellow, yellow, COLOR_HSV2BGR);
    imshow("amarelo", yellow);

    Mat yellow1;
    bitwise_not(yellow_hue_image, yellow1);
    imshow("amarelo[pt]", yellow1);

    //BLUE
    Mat blue_hue_image;
    inRange(hsv_image, Scalar(110,50,50), Scalar(130, 255, 255), blue_hue_image);

    GaussianBlur(blue_hue_image, blue_hue_image, Size(9, 9), 2, 2);

    Mat blue;
    bitwise_and(hsv_image, hsv_image, blue, blue_hue_image);
    cvtColor(blue, blue, COLOR_HSV2BGR);
    imshow("azul", blue);

    Mat blue1;
    bitwise_not(blue_hue_image, blue1);
    imshow("azul[pt]", blue1);

    //GREEN
    Mat green_hue_image;
    inRange(hsv_image, Scalar(72, 100, 120), Scalar(100, 255, 255), green_hue_image);

    GaussianBlur(green_hue_image, green_hue_image, Size(9, 9), 2, 2);

    Mat green;
    bitwise_and(hsv_image, hsv_image, green, green_hue_image);
    cvtColor(green, green, COLOR_HSV2BGR);
    imshow("verde", green);

    Mat green1;
    bitwise_not(green_hue_image, green1);
    imshow("verde[pt]", green1);

    waitKey(0);
    return 0;
}
