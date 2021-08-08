#include <chrono>
#include <ctime>

#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv/cv.hpp>
#include <ros/ros.h>

using Clock = std::chrono::system_clock;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "video_publisher");
    ros::NodeHandle nh {};
    image_transport::ImageTransport it { nh };
    image_transport::Publisher stampedPub = it.advertise("camera/stamped", 1);
    image_transport::Publisher rawPub = it.advertise("camera/raw", 1);

    auto cap = cv::VideoCapture(0);
    auto font = cv::FONT_HERSHEY_SIMPLEX;

    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1920 / 4);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 1080 / 4);
    cap.set(cv::CAP_PROP_FPS, 30);

    if (!cap.isOpened())
    {
        ROS_ERROR("Couldn't open video capture device");
        return 1;
    }

    ros::Rate rate { 30 };

    while (nh.ok())
    {
        cv::Mat image {};
        if (!cap.read(image))
        {
            ROS_ERROR("Failed to read frame");
            return 1;
        }

        sensor_msgs::ImagePtr rawMsg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", std::move(image))
                                           .toImageMsg();
        rawPub.publish(rawMsg);

        auto now = Clock::to_time_t(Clock::now());
        cv::putText(image, std::ctime(&now), { 20, 40 }, font, 1, { 0, 0, 0 }, 8,
            false);
        cv::putText(image, std::ctime(&now), { 20, 40 }, font, 1, { 255, 255, 255 }, 4,
            false);

        sensor_msgs::ImagePtr stampedMsg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", std::move(image))
                                               .toImageMsg();
        stampedPub.publish(stampedMsg);

        ros::spinOnce();
        rate.sleep();
    }
}
