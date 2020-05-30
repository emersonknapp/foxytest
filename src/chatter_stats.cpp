#include <chrono>
#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

int main(int argc, char ** argv)
{
  using namespace std::chrono_literals;
  rclcpp::init(argc, argv);

  auto node = std::make_shared<rclcpp::Node>("arst");
  rclcpp::SubscriptionOptions options;
  options.topic_stats_options.state = rclcpp::TopicStatisticsState::Enable;
  options.topic_stats_options.publish_topic = "staty";
  options.topic_stats_options.publish_period = 10ms;
  auto sub_ = node->create_subscription<std_msgs::msg::String>(
    "/chatter", rclcpp::QoS(10),
    [](const std_msgs::msg::String::SharedPtr /* msg */) {
      std::cout << "Gotamsg" << std::endl;
    },
    options);
  rclcpp::spin(node);

  return 0;
}
