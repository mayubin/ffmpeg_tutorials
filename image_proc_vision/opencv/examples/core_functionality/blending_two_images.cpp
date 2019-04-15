//
// Created by wangrl on 19-4-14.
//

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// Simple Linear Blender

int main(int argc, char *argv[]) {

    double alpha = 0.5; double beta; double input;

    Mat src1, src2, dst;
    cout << " Enter alpha [0.0-1.0]: ";
    cin >> input;
    if (input >= 0 && input <= 1)
        alpha = input;

    src1 = imread("../../../res/window.jpg");
    src2 = imread("../../../res/linux.jpg");

    if( src1.empty() ) { cout << "Error loading src1" << endl; return -1; }
    if( src2.empty() ) { cout << "Error loading src2" << endl; return -1; }

    beta = (1.0 - alpha);

    // 图片尺寸必须是相同大小
    addWeighted(src1, alpha, src2, beta, 0.0, dst);

    imshow("Linear Blend", dst);
    waitKey(0);

    return 0;
}

