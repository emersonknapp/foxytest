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

  rclcpp::QoS qos_offer{10};

  auto node = std::make_shared<rclcpp::Node>("topic_stats_test");
  auto pub = node->create_publisher<MessageType>("/chatter", qos_offer);
  auto clock = node->get_clock();
  auto timer = node->create_wall_timer(1s, [pub, clock]() {
    MessageType message;

    message.stamp = clock->now();
    // message.header.stamp = clock->now();

    pub->publish(message);
  });

  rclcpp::spin(node);

  return 0;
}
