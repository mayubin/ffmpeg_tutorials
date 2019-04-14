//
// Created by wangrl on 19-4-14.
//

#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char *argv[]) {

    const char *filename = "../../../res/lena.jpg";

    const char *outname = "out.jpg";

    // Input/Output
    Mat img = imread(filename);

    Mat img_gray = imread(filename, IMREAD_GRAYSCALE);

    // 保存到文件中
    imwrite(outname, img);


    // 先row, 然后col
    int y = 5, x = 5;
    Vec3b intensity = img.at<Vec3b>(y, x);
    uchar blue = intensity.val[0];
    uchar green = intensity.val[1];
    uchar red = intensity.val[2];

    img.at<uchar>(y, x) = 128;

    Mat dst;
    img.convertTo(dst, CV_32F);

    // Visualizing images
    Mat lena = imread("../../../res/lena.jpg");
    namedWindow("image", WINDOW_AUTOSIZE);
    imshow("image", img);
    waitKey();

    Mat grey;
    cvtColor(lena, grey, COLOR_BGR2GRAY);
    Mat sobelx;
    Sobel(grey, sobelx, CV_32F, 1, 0);
    double minVal, maxVal;
    minMaxLoc(sobelx, &minVal, &maxVal);        // find minimum and maximum intensities
    Mat draw;
    sobelx.convertTo(draw, CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));
    namedWindow("image", WINDOW_AUTOSIZE);
    imshow("image", WINDOW_AUTOSIZE);
    imshow("image", draw);
    waitKey();

    return 0;
}

