//
// Created by wangrl on 19-4-14.
//

#include <opencv2/opencv.hpp>

/**
 * This program shows how to filter images with mask: the write it yourself and the
 * filter2d way.
 */

using namespace cv;
using namespace std;

void sharpen(const Mat& myImage, Mat& result) {
    CV_Assert(myImage.depth() == CV_8U);
    const int nChannels = myImage.channels();
    result.create(myImage.size(), myImage.type());

    for (int j = 1; j < myImage.rows - 1; ++j) {
        const uchar *previous = myImage.ptr<uchar >(j - 1);
        const uchar *current = myImage.ptr<uchar>(j);
        const uchar *next = myImage.ptr<uchar>(j + 1);

        uchar *output = result.ptr<uchar>(j);

        for (int i = nChannels; i < nChannels * (myImage.cols - 1); ++i) {
            *output++ = saturate_cast<uchar>(5*current[i]
                                             -current[i-nChannels] - current[i+nChannels] - previous[i] - next[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    const char *filename = argv[1];

    cv::Mat src, dst0, dst1;

    if (argc >= 3 && !strcmp("G", argv[2]))
        src = imread(filename, IMREAD_GRAYSCALE);
    else
        src = imread(filename, IMREAD_COLOR);

    if (src.empty()) {
        cerr << "Can't open image ["  << filename << "]" << endl;
        return -1;
    }

    namedWindow("Input", WINDOW_AUTOSIZE);
    namedWindow("Output", WINDOW_AUTOSIZE);

    imshow("Input", src);

    double t = (double)getTickCount();

    sharpen(src, dst0);

    t = ((double)getTickCount() - t) / getTickFrequency();
    cout << "Hand written function time passed in seconds: " << t << endl;

    imshow("Output", dst0);
    waitKey();

    Mat kernel = (Mat_<char>(3, 3) << 0, -1,  0,
            -1,  5, -1,
            0, -1,  0);

    t = (double)getTickCount();
    filter2D(src, dst1, src.depth(), kernel);

    t = ((double)getTickCount() - t) / getTickFrequency();
    cout << "Built-in filter2D time passed in seconds: " << t << endl;

    imshow("Output", dst1);

    waitKey();

    return 0;
}

