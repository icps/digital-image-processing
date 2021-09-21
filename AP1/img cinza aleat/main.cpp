#include <QCoreApplication>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <math.h>
#include <float.h>

using namespace cv;
using namespace std;

double uniform() { return (rand()/(float)0x7fff)-0.5; }

IplImage* GenerateNoise(IplImage* img, float amount=255) {
    CvSize imgSize = cvGetSize(img);
    IplImage* imgTemp = cvCloneImage(img); // This will hold the noisy image

    // Go through each pixel
    for(int y=0;y<imgSize.height;y++) {
        for(int x=0;x<imgSize.width;x++) {
            int randomValue = (char)((uniform())*amount);
            int pixelValue = cvGetReal2D(imgTemp, y, x)+randomValue;
            cvSetReal2D(imgTemp, y, x, pixelValue);
        }
    }
    return imgTemp;
    // - See more at: http://www.aishack.in/tutorials/generating-uniform-noise/#sthash.D99Dl1Yh.dpuf
}



int main(int argc, char *argv[])
{
    Mat imagem = Mat::zeros( 640, 480, CV_8UC3 );
    imwrite("noise_tester.jpg", imagem);

    // Load the image with no noise
    IplImage* img = cvLoadImage("noise_tester.jpg", 0);
    IplImage* imgTemp;

    // Initialize the window systems
    int trackPos = 20;
    cvNamedWindow("Image");
    cvCreateTrackbar("amount", "Image", &trackPos, 255, NULL);
    while(true) {
        imgTemp = GenerateNoise(img, trackPos); // Display it all
        cvShowImage("Image", imgTemp);
        cvReleaseImage(&imgTemp);

        char keyPress = cvWaitKey(10);
        if(keyPress!=-1) break;
    }

    cvReleaseImage(&img);
    return 0;

}
