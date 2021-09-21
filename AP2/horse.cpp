#include <QCoreApplication>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

Mat thinning(Mat image, vector<Mat> elements) {
  Mat output, last, current = image.clone();

  Mat comp;
  bitwise_not(current, current);

  do {
    current.copyTo(last);
    for (Mat element : elements) {
      morphologyEx(current, output, MORPH_HITMISS, element);

      bitwise_not(output, output);
      bitwise_and(current, output, current);

    }
    compare(current, last, comp, CMP_NE);
  } while(countNonZero(comp));

  return current;
}

int main() {

    Mat image = imread("/home/alunoic/Downloads/img/horse.png", CV_LOAD_IMAGE_GRAYSCALE);

    Mat elem1 = (Mat_<int>(3, 3) << -1, -1, -1, 0, 1, 0, 1, 1, 1);
    Mat elem2 = (Mat_<int>(3, 3) << 0, -1, -1, 1, 1, -1, 1, 1, 0);
    Mat elem3 = (Mat_<int>(3, 3) << 1, 0, -1, 1, 1, -1, 1, 0, -1);
    Mat elem4 = (Mat_<int>(3, 3) << 1, 1, 0, 1, 1, -1, 0, -1, -1);
    Mat elem5 = (Mat_<int>(3, 3) << 1, 1, 1, 0, 1, 0, - 1, -1, -1);
    Mat elem6 = (Mat_<int>(3, 3) << 0, 1, 1, -1, 1, 1, -1, -1, 0);
    Mat elem7 = (Mat_<int>(3, 3) << -1, 0, 1, -1, 1, 1, -1, 0, 1);
    Mat elem8 = (Mat_<int>(3, 3) << -1, -1, 0, -1, 1, 1, 0, 1, 1);

    vector<Mat> elements = {move(elem1), move(elem2), move(elem3), move(elem4), move(elem5), move(elem6), move(elem7), move(elem8)};

    Mat output = thinning(image, elements);
    imshow("output", output);

    waitKey(0);
    return 0;

}
