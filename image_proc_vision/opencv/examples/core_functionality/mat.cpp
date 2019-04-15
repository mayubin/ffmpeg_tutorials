//
// Created by wangrl on 19-4-14.
//
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char *argv[]) {

    /**
     * Mat object has its own header, however the matrix may be shared between
     * two instance of them by having their matrix pointers point to the same
     * address.
     */
    Mat A, C;       // creates just the header parts
    A = imread(argv[1], IMREAD_COLOR);      // here we'll know the method used (allocate matrix)

    Mat B(A);       // Use the copy constructor

    C = A;          // Assignment operator

    // All the above object, in the end, point to the same single data matrix.

    // region of interest (ROI)
    Mat D(A, Rect(10, 10, 100, 100));       // using a rectangle

    Mat E = A(Range::all(), Range(1, 3));   // using row and column boundaries

    // copy the matrix itself.
    // Modify F or G will not affect the matrix pointed by the Mat header.
    Mat F = A.clone();
    Mat G;
    A.copyTo(G);

    // 常见描述颜色信息的格式。
    // RGB
    // HSV
    // YCrCb

    Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));
    std::cout << "M = " << std::endl << " " << M << std::endl;

    // CV_[The number of bits per item][Signed or Unsigned][Type Prefix]C[The channel number]

    // 多维矩阵
    int sz[3] = {2, 2, 2};
    Mat L(3, sz, CV_8UC(1), Scalar::all(0));

    M.create(4, 4, CV_8UC(2));
    std::cout << "M = " << std::endl << " " << M << std::endl;

    // MATLAB style initializer
    Mat O = Mat::eye(4, 4, CV_64F);
    std::cout << "O = " << std::endl << " " << O << std::endl;
    Mat P = Mat::ones(2, 2, CV_32F);
    std::cout << "P = " << std::endl << " " << P << std::endl;
    Mat Q = Mat::zeros(3, 3, CV_8UC1);
    std::cout << "Z = " << std::endl << " " << Q << std::endl;

    Mat R = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    std::cout << "R = " << std::endl << " " << R << std::endl;

    Mat S = (Mat_<double>({0, -1, 0, -1, 5, -1, 0, -1, 0})).reshape(3);
    std::cout << "S = " << std::endl << " " << S << std::endl;

    Mat rowClone = O.row(1).clone();
    std::cout << "rowClone = " << std::endl << " " << rowClone << std::endl;

    std::cout << "R (default) = " << std::endl << R << std::endl;

    std::cout << "R (python) = " << std::endl << format(R, Formatter::FMT_PYTHON) << std::endl;

    std::cout << "R (csv) = " << std::endl << format(R, Formatter::FMT_CSV) << std::endl;

    std::cout << "R (numpy) = " << std::endl << format(R, Formatter::FMT_NUMPY) << std::endl;

    std::cout << "R (c) = " << std::endl << format(R, Formatter::FMT_C) << std::endl;

    // 2D Point
    Point2f Pt(5, 1);
    std::cout << "Point (2D) = " << P << std::endl;

    // 3D Point
    Point3f P3f(2, 6, 7);
    std::cout << "Point (3D) = " << P3f << std::endl;

    std::vector<float> v;
    v.push_back((float)CV_PI);
    v.push_back(2);
    v.push_back(3.01f);

    std::cout << "Vector of floats via Mat = " << Mat(v) << std::endl;

    std::vector<Point2f> vPoints(20);
    for (size_t i = 0; i < vPoints.size(); ++i) {
        vPoints[i] = Point2f((float)(i * 5), (float)(i % 7));
    }
    std::cout << "A vector of 2D Points = " << vPoints << std::endl;
}
