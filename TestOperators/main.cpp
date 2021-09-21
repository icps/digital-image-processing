#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    Mat image;
//    Mat image1 = imread("/home/alunoic/workspaces/qt/TestOperatorsOpenCV/preto-branco-cronica.png", 0);
//    Mat image2 = imread("/home/alunoic/workspaces/qt/TestOperatorsOpenCV/Mcdonalds-preto-e-branco.png", 0);

//    resize(image1, image1, Size(480, 340));
//    resize(image2, image2, Size(480, 340));

//    threshold(image1, image1, 128, 255, ThresholdTypes::THRESH_BINARY);
//    threshold(image2, image2, 128, 255, ThresholdTypes::THRESH_BINARY);

    image = imread("/home/alunoic/Downloads/Fig0908(a)(wirebond-mask).tif", 0);

    // Rectangular mask
 //   morphologyEx(image, image, MorphTypes::MORPH_OPEN, Mat::ones(5, 5, CV_8U));

    Mat mask = Mat::ones(5, 5, CV_8U); // all 1
    mask[1] = 0;
    cout << mask;
    morphologyEx(image, image, MorphTypes::MORPH_OPEN, Mat::ones(5, 5, CV_8U));

//    morphologyEx(image2, image, MorphTypes::MORPH_ERODE, Mat::ones(5, 5, CV_8U));
//    bitwise_not(image1, image);

//    imshow("Test1", image1);
//    imshow("Test2", image2);
    imshow("Test3", image);

    waitKey();
    return 0;
}
