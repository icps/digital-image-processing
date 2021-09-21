#include <QCoreApplication>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <math.h>

using namespace cv;
using namespace std;

void fourier(Mat I)
{
    Mat padded;                            //expand input image to optimal size
    int m = getOptimalDFTSize( I.rows );
    int n = getOptimalDFTSize( I.cols ); // on the border add zero values
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

    dft(complexI, complexI, DFT_INVERSE);            // this way the result may fit in the source matrix

    // compute the magnitude and switch to logarithmic scale
    // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    Mat magI = planes[0];

    magI += Scalar::all(1);                    // switch to logarithmic scale
    log(magI, magI);

    // crop the spectrum, if it has an odd number of rows or columns
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = magI.cols/2;
    int cy = magI.rows/2;

    Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
                                            // viewable image form (float between values 0 and 1).
    imshow("spectrum magnitude", magI);
}

int main(int argc, char *argv[])
{
    Mat imagem = Mat::zeros( 512, 512, CV_32FC1 );
    circle(imagem, Point(3,30), 1, Scalar(255,255,255), 1, LINE_AA);
    circle(imagem, Point(512-3,512-30), 1, Scalar(255,255,255), 1, LINE_AA);

    fourier(imagem);

//    // VIGNETTE
//    Mat imagem = imread("/home/alunoic/RV1/lena.png", CV_LOAD_IMAGE_GRAYSCALE);

//    Mat kernel_X = getGaussianKernel(imagem.cols, 100);
//    Mat kernel_Y = getGaussianKernel(imagem.rows, 100);
//    Mat kernel_X_transpose;
//    transpose(kernel_X, kernel_X_transpose);
//    Mat kernel = kernel_Y * kernel_X_transpose;

//    Mat mask_v, proc_img;
//    normalize(kernel, mask_v, 0, 1, NORM_MINMAX);
//    imagem.convertTo(proc_img, CV_64F);
//    multiply(mask_v, proc_img, proc_img);
//    convertScaleAbs(proc_img, proc_img);
//    imshow ("lena_vignette_isadora", proc_img);

//    // TARGET
//    Mat imagem = Mat::zeros( 512, 512, CV_8UC3 );

//    circle(imagem, Point(512/2,512/2), 110, Scalar(40,40,40), 240, LINE_AA);
//    circle(imagem, Point(512/2,512/2), 90, Scalar(80,80,80), 200, LINE_AA);
//    circle(imagem, Point(512/2,512/2), 70, Scalar(120,120,120), 160, LINE_AA);
//    circle(imagem, Point(512/2,512/2), 50, Scalar(160,160,160), 120, LINE_AA);
//    circle(imagem, Point(512/2,512/2), 30, Scalar(200,200,200), 60, LINE_AA);
//    circle(imagem, Point(512/2,512/2), 10, Scalar(240,240,240), 20, LINE_AA);

//    // SAL E PIMENTA
//    Mat imagem = imread("/home/alunoic/RV1/lena.png", CV_LOAD_IMAGE_GRAYSCALE);

//    Mat saltpepper_noise = Mat::zeros(imagem.rows, imagem.cols,CV_8U);
//    randu(saltpepper_noise,0,255);

//    Mat black = saltpepper_noise < 30;
//    Mat white = saltpepper_noise > 225;

//    Mat saltpepper_imagem = imagem.clone();
//    saltpepper_imagem.setTo(255,white);
//    saltpepper_imagem.setTo(0,black);

//    imshow("lena_sp_isadora", saltpepper_imagem);
    imshow("img", imagem);



     waitKey();
     return 0;
}
