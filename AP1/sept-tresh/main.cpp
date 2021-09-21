#include <QCoreApplication>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat imagem = imread("/home/isadora/Downloads/pdi/septagon.tif", CV_LOAD_IMAGE_COLOR);

    cvtColor(imagem, imagem, CV_BGR2GRAY);

    threshold(imagem, imagem, 100, 255, THRESH_BINARY);

    imshow("img", imagem);

    waitKey();
    return 0;

}
