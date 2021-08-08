#include <chrono>
#include <ctime>
#include <vector>

#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv/cv.hpp>
#include <ros/ros.h>

std::vector<std::string> imageTopics = { "/camera/raw" }

int main(int argc, char** argv)
{
  ros::init(argc, argv, "logger");
  ros::NodeHandle nh{};
  image_transport::ImageTransport it{nh};

  std::unordered_map < std::string, std::path
}
