#include <filesystem>
#include <functional>

#include <ros/ros.h>
#include <sensor_msgs/Image.h>

class ImageSerializer
{
public:
    ImageSerializer(ros::NodeHandle &nh, std::string topic, std::filesystem::path path)
    {
        sub_ = nh.subscribe(topic, 1, &ImageSerializer::serialize, this);
    }

    bool serialize(sensor_msgs::Image msg)
    {
        ROS_INFO("Recieved message");
    };

private:
    ros::Subscriber sub_ { };
};
