#include <QCoreApplication>

#include <iostream>
#include <opencv2/opencv.hpp>
#include<sstream>

using namespace std;
using namespace cv;

int main()
{
    // Load the image
    Mat src = imread("/home/isadora/Imagens/PDI/001_A-L_24 05 2013.jpg", CV_LOAD_IMAGE_COLOR);

    Mat dst;
    cvtColor(src, dst, COLOR_RGB2GRAY);
    // Check if image is loaded fine
    if(!src.data)
        cerr << "Problem loading image!!!" << endl;
    // Show source image
    namedWindow("src", WINDOW_NORMAL);
    imshow("src", dst);

    Mat bw;
    adaptiveThreshold(dst, bw, 255, CV_ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 17, -10);
    // Show binary image
    namedWindow("binary", WINDOW_NORMAL);
    imshow("binary", bw);

    // Create the images that will use to extract the horizontal and vertical lines
    Mat horizontal = bw.clone();

    // Specify size on horizontal axis
    int horizontalsize = horizontal.cols / 20;
    // Create structure element for extracting horizontal lines through morphology operations
    Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontalsize,1));
    // Apply morphology operations
    morphologyEx(horizontal, horizontal, MORPH_OPEN, horizontalStructure, Point(-1,-1), 2);

    // Show extracted horizontal lines
    namedWindow("horizontal", WINDOW_NORMAL);
    imshow("horizontal", horizontal);

    Mat result;
    result = bw - horizontal;
    bitwise_not(result, result);

    namedWindow("result", WINDOW_NORMAL);
    imshow("result", result);

    Mat img_sobel, img_threshold;
    vector<cv::Rect> boundRect;

    Sobel(result, img_sobel, CV_8U, 1, 0, 3, BORDER_DEFAULT);
    threshold(img_sobel, img_threshold, 0, 255, THRESH_OTSU+CV_THRESH_BINARY);
    Mat element = getStructuringElement(MORPH_RECT, Size(17, 5));
    morphologyEx(img_threshold, img_threshold, MORPH_CLOSE, element, Point(-1,-1), 1);

    vector< vector< cv::Point> > contours;
    findContours(img_threshold, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    vector<vector<Point> > contours_poly( contours.size());

    for( int i = 0; i < contours.size(); i++ )
        if (contours[i].size()>50)
        {
            approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
            Rect appRect( boundingRect( Mat(contours_poly[i]) ));
            if (appRect.width>appRect.height)
                boundRect.push_back(appRect);
        }

    for(int i=0; i< boundRect.size(); i++) {
        rectangle(src,boundRect[i],Scalar(0,255,0),3,8,0);
    }



//    //Create an image for each word
//    for(int i=0; i< boundRect.size(); i++) {
//        Mat cropped = result(Rect(boundRect[i]));

//        string savingName = "/home/isadora/Imagens/PDI/palavras/" + std::to_string(i) + ".jpg";
//        imwrite(savingName, cropped);
//    }


//    namedWindow("result1", WINDOW_NORMAL);
    imshow("result1", src);



    waitKey(0);
    return 0;
}
