#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    cv::Mat myImage;
    cv::namedWindow("Video Player");
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "No video stream detected" << std::endl;
        system("pause");
        return -1;
    }
    while (true) {
        cap >> myImage;
        if (myImage.empty())
            break;
        imshow("Video Player", myImage);
        char c = (char)cv::waitKey(25);
        if (c == 27)
            break;
    }
    cap.release();
    return 0;
}