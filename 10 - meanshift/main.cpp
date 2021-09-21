#include <QCoreApplication>

#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

int main()
{

    //image load
    Mat img = imread("/home/isadora/Imagens/PDI/chipsColoridos.jpg", CV_LOAD_IMAGE_COLOR);
    Mat outImg;

    pyrMeanShiftFiltering(img, outImg, 70, 80, 3);

    //show image
    imshow("origin", img);
    imshow("MeanShift Filter", outImg);


    Mat img2 = imread("/home/isadora/Imagens/PDI/imgNovo.jpg", CV_LOAD_IMAGE_COLOR);
    Mat outImg2;

    pyrMeanShiftFiltering(img2, outImg2, 10, 40, 3);

    //show image
    imshow("origin2", img2);
    imshow("MeanShift Filter2", outImg2);

    waitKey();
    return 0;
}
