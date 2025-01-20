#include <chrono>
#include <memory>
 
#include "costmap_node.hpp"

using std::placeholders::_1;
 
CostmapNode::CostmapNode() : Node("costmap"), costmap_(robot::CostmapCore(this->get_logger())) {
   lidar_sub_ = this->create_subscription<std_msgs::msg::String>(
      "/lidar", 10, std::bind(&CostmapNode::lidar_topic_callback, this, _1));

  // Initialize the constructs and their parameters
  // string_pub_ = this->create_publisher<std_msgs::msg::String>("/test_topic", 10);
  // timer_ = this->create_wall_timer(std::chrono::milliseconds(500), std::bind(&CostmapNode::publishMessage, this));
}
 
// Define the timer to publish a message every 500ms
// void CostmapNode::publishMessage() {
//   auto message = std_msgs::msg::String();
//   message.data = "Hello, ROS 2!";
//   RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
//   string_pub_->publish(message);
// }

void CostmapNode::lidar_topic_callback(const std_msgs::msg::String::SharedPtr msg) const {
  RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
}
 
int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CostmapNode>());
  rclcpp::shutdown();
  return 0;
}