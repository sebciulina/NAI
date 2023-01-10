#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/aruco/dictionary.hpp>
#include <opencv2/aruco.hpp>

using namespace std;
using namespace cv;

int main()
{

    VideoCapture camera(1);
    if (!camera.isOpened())
    {
        cerr << "Failed to open the camera!" << endl;
        return 1;
    }

    Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_6X6_250);
    Ptr<aruco::DetectorParameters> detectorParams = aruco::DetectorParameters::create();

    Mat frame;
    while (true)
    {

        camera >> frame;
        if (frame.empty())
            break;

        vector<int> ids;
        vector<vector<Point2f>> corners;
        aruco::detectMarkers(frame, dictionary, corners, ids, detectorParams);

        if (ids.size() >= 2) {
            Point2f p1 = corners[0][0];
            Point2f p2 = corners[1][0];

            float distance = norm(p1 - p2);
            string distance_str = "Distance: " + to_string(distance);
            putText(frame, distance_str, Point(20, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);
        }

        aruco::drawDetectedMarkers(frame, corners, ids);

        imshow("Camera", frame);

        int key = waitKey(1);
        if (key == 27) //Esc
            break;
    }
    camera.release();
    destroyAllWindows();
    return 0;
}