#include "Camera_Wrapper.h"

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/mat.hpp>

void Camera_Wrapper::takePicture()
{
    cv::VideoCapture cap(0); // 0 = default camera

    if (!cap.isOpened())
    {
        return;
    }

    cv::Mat frame;

    while (true)
    {
        cap >> frame;
        if (frame.empty())
            break;

        cv::imshow("Camera Preview", frame);

        int key = cv::waitKey(1);
        if (key == 27) // ESC = exit
            break;
        else if (key == 'c') // 'c' = capture
        {
            cv::imwrite("capture.png", frame);
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
}
