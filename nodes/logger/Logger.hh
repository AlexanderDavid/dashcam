#include <filesystem>

#include <ros/ros.h>

#include "Serializer.hh"

std::vector<std::string> imageTopics {
    "/camera/image/raw"
}

class Logger
{
public:
    Logger(std::filesystem::path logPath);

    void addTopic(std::string topic);

private:
    std::unordered_map<std::string, std::pair<std::filesystem::path, ros::Subscriber>> topicMap_{};
};
