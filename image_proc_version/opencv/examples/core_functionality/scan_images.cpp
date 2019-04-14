//
// Created by wangrl on 19-4-14.
//

/**
 * scan_images <imageNameToUse> <divideWith> [G]
 * G parameter the image is processed in gray scale.
 */

#include <opencv2/core.hpp>
#include <iostream>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

// 使用取整算法

// classic C style operator[] (pointer) access
Mat& scanImageAndReduceC(Mat& I, const uchar* const table) {
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    int channels = I.channels();

    int nRows = I.rows;
    int nCols = I.cols * channels;

    if (I.isContinuous()) {
        nCols *= nRows;
        nRows = 1;
    }

    uchar *p;
    // 通过查表的方式获取像素。
    for (int i = 0; i < nRows; ++i) {
        // basically just acquire a pointer to the start of each row and go through it until it ends.
        p = I.ptr<uchar>(i);
        for (int j = 0; j < nCols; ++j) {
            p[j] = table[p[j]];
        }
    }
    return I;
}

Mat& scanImageAndReduceIterator(Mat& I, const uchar* const table) {
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch (channels) {
        case 1: {
            MatIterator_<uchar> it, end;
            for (it = I.begin<uchar >(), end = I.end<uchar >(); it != end; ++it) {
                *it = table[*it];
            }
        }
        case 3: {
            MatIterator_<Vec3b> it, end;
            for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it) {
                (*it)[0] = table[(*it)[0]];
                (*it)[1] = table[(*it)[1]];
                (*it)[2] = table[(*it)[2]];
            }
        }
    }
    return I;
}

Mat& scanImageAndReduceRandomAccess(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch(channels)
    {
        case 1:
        {
            for( int i = 0; i < I.rows; ++i)
                for( int j = 0; j < I.cols; ++j )
                    I.at<uchar>(i,j) = table[I.at<uchar>(i,j)];
            break;
        }
        case 3:
        {
            Mat_<Vec3b> _I = I;

            for( int i = 0; i < I.rows; ++i)
                for( int j = 0; j < I.cols; ++j )
                {
                    _I(i,j)[0] = table[_I(i,j)[0]];
                    _I(i,j)[1] = table[_I(i,j)[1]];
                    _I(i,j)[2] = table[_I(i,j)[2]];
                }
            I = _I;
            break;
        }
    }

    return I;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "Not enough parameters" << endl;
        return -1;
    }

    Mat I, J;
    if (argc == 4 && !strcmp(argv[3], "G")) {
        I = imread(argv[1], IMREAD_GRAYSCALE);
    } else {
        I = imread(argv[1], IMREAD_COLOR);
    }

    if (I.empty()) {
        cout << "The image" << argv[1] << " could not be loaded." << endl;
        return -1;
    }

    int divideWith = 0;     // convert our input string to number - C++ style
    stringstream s;
    s << argv[2];
    s >> divideWith;

    if (!s || !divideWith) {
        cout << "Invalid number entered for dividing. " << endl;
        return -1;
    }

    uchar table[256];
    for (int i = 0; i < 256; ++i) {
        table[i] = (uchar)(divideWith * (i / divideWith));
    }

    const int times = 100;

    double t = (double)getTickCount();

    for (int i = 0; i < times; ++i) {
        Mat clone_i = I.clone();
        J = scanImageAndReduceC(clone_i, table);
    }

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the C operator [] (averaged for "
         << times << " runs): " << t << " milliseconds."<< endl;

    t = (double)getTickCount();

    for (int i = 0; i < times; ++i)
    {
        cv::Mat clone_i = I.clone();
        J = scanImageAndReduceIterator(clone_i, table);
    }

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the iterator (averaged for "
         << times << " runs): " << t << " milliseconds."<< endl;

    t = (double)getTickCount();

    for (int i = 0; i < times; ++i)
    {
        cv::Mat clone_i = I.clone();
        scanImageAndReduceRandomAccess(clone_i, table);
    }

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the on-the-fly address generation - at function (averaged for "
         << times << " runs): " << t << " milliseconds."<< endl;

    Mat lookUpTable(1, 256, CV_8U);
    uchar *p = lookUpTable.ptr();
    for (int i = 0; i < 256; ++i)
        p[i] = table[i];

    t = (double)getTickCount();

    for (int i = 0; i < times; ++i)
        LUT(I, lookUpTable, J);

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the LUT function (averaged for "
         << times << " runs): " << t << " milliseconds."<< endl;
}
