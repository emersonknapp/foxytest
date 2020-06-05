#include <chrono>
#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/header.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"

// typedef std_msgs::msg::String MessageType;
typedef std_msgs::msg::Header MessageType;
// typedef geometry_msgs::msg::PoseStamped MessageType;

int main(int argc, char ** argv)
{
  using namespace std::chrono_literals;
  rclcpp::init(argc, argv);

  auto node = std::make_shared<rclcpp::Node>("topic_stats_test");
  rclcpp::SubscriptionOptions options;
  options.topic_stats_options.state = rclcpp::TopicStatisticsState::Enable;
  options.topic_stats_options.publish_topic = "staty";
  options.topic_stats_options.publish_period = 2s;

  auto sub = node->create_subscription<MessageType>(
    "/chatter", rclcpp::QoS(10),
    [](const MessageType::SharedPtr /* msg */) {
      std::cout << "Got a message" << std::endl;
    },
    options);
  rclcpp::spin(node);

  return 0;
}
