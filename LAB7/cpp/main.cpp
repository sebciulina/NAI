#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <vector>
#include <chrono>
// g++ pkg-config --cflags opencv4 cv2.cpp pkg-config --libs opencv4
using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    using Clock = std::chrono::steady_clock;
    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> now;
    std::chrono::milliseconds duration;

    cv::Mat input_grey, blur_img, thresh_img;
    cv::Size kernel(3, 3);

    VideoCapture vc(1);
    vc.open(1, CAP_DSHOW);
    if (!vc.isOpened())
        return 1;
    cv::Mat frame;

    int i = 0;
    while (waitKey(10) != 27)
    {
        vc >> frame;
        start = Clock::now();
        flip(frame, frame, 1);

        cv::cvtColor(frame, input_grey, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(input_grey, blur_img, kernel, 0);
        cv::threshold(blur_img, thresh_img, 150, 255, cv::THRESH_BINARY);

        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;

        cv::findContours(thresh_img, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

        cv::Scalar green(0, 255, 0);
        cv::drawContours(frame, contours, -1, green, 2);

        int largest_area = 0;
        int largest_contour_index = 0;
        Rect bounding_rect;
        for (size_t i = 0; i < contours.size(); i++) // iterate through each contour.
        {
            double area = contourArea(contours[i]); //  Find the area of contour

            if (area > largest_area)
            {
                largest_area = area;
                largest_contour_index = i;                 // Store the index of largest contour
                bounding_rect = boundingRect(contours[i]); // Find the bounding rectangle for biggest contour
            }
        }
        now = Clock::now();
        cv::rectangle(frame, bounding_rect, Scalar(255, 0, 0), 2);

        cv::imshow("Contours", frame);
    }
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
    std::cout << "Time: " << duration.count() << " ms." << endl;

    vc.release();
    cv::destroyAllWindows();
    return 0;
}