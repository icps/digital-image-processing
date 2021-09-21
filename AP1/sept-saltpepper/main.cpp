#include <QCoreApplication>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat imagem = imread("/home/isadora/Downloads/pdi/septagon.tif", CV_LOAD_IMAGE_GRAYSCALE);

    //additive gaussian node
//    Mat gaussian_noise = img.clone();
//    randn(gaussian_noise,128,30);

    Mat saltpepper_noise = Mat::zeros(imagem.rows, imagem.cols,CV_8U);
    randu(saltpepper_noise,0,255);

    Mat black = saltpepper_noise < 30;
    Mat white = saltpepper_noise > 225;

    Mat saltpepper_imagem = imagem.clone();
    saltpepper_imagem.setTo(255,white);
    saltpepper_imagem.setTo(0,black);

    imshow("img", saltpepper_imagem);

    waitKey();
    return 0;

}
