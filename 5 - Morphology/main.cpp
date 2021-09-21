#include <QCoreApplication>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat image1 = imread("/home/isadora/Imagens/PDI/morfologia-opLogicas/original1.jpg", 0);
    Mat image2 = imread("/home/isadora/Imagens/PDI/morfologia-opLogicas/original2.jpg", 0);

    resize(image1, image1, Size(480, 340));
    resize(image2, image2, Size(480, 340));

    threshold(image1, image1, 128, 255, ThresholdTypes::THRESH_BINARY);
    threshold(image2, image2, 128, 255, ThresholdTypes::THRESH_BINARY);

    imshow("Image1", image1);
    imshow("Image2", image2);

    // NOT A e NOT B
    Mat notA, notB;
    bitwise_not(image1, notA);
    bitwise_not(image2, notB);
    imshow("Result1", notA);
    imshow("Result2", notB);

    // A AND B
    Mat andAB;
    bitwise_and(image1, image2, andAB);
    imshow("Result3", andAB);

    // A OR B
    Mat orAB;
    bitwise_or(image1, image2, orAB);
    imshow("Result4", orAB);

    // A XOR B
    Mat xorAB;
    bitwise_xor(image1, image2, xorAB);
    imshow("Result5", xorAB);

    // A XNOR B
    Mat xnorAB;
    bitwise_not(xorAB, xnorAB);
    imshow("Result6", xnorAB);

    // A - B
    Mat result;
    result = image1 - image2;
    imshow("Result7", result);

    //B - A
    Mat result1;
    result1 = image2 - image1;
    imshow("Result8", result1);

    waitKey();
    return 0;
}
