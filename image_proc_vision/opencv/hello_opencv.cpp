//
// Created by wangrl on 19-4-14.
//

#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("usage: %s <Image_Path>\n", argv[0]);
        return -1;
    }

    Mat image;
    image = imread(argv[1], 1);

    if (!image.data) {
        printf("No image data \n");
        return -1;
    }

    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("DisplayImage", image);
    
    waitKey(0);
    
    return 0;
}

