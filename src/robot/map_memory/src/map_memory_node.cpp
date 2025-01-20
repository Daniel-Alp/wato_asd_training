#include <memory>
#include "map_memory_node.hpp"

MapMemoryNode::MapMemoryNode() : Node("map_memory"), map_memory_(robot::MapMemoryCore(this->get_logger())) {
  odom_sub_ = this->create_subscription< nav_msgs::msg::Odometry>(
      "/odom/filtered", 10, 
      std::bind(
        &MapMemoryNode::odom_topic_callback, this, 
        std::placeholders::_1));

  local_costmap_sub_ = this->create_subscription<nav_msgs::msg::OccupancyGrid>(
      "/costmap", 10, 
      std::bind(
        &MapMemoryNode::local_costmap_topic_callback, this, 
        std::placeholders::_1));

  RCLCPP_INFO(this->get_logger(), "Initialized Memory Map Node");
}

void MapMemoryNode::odom_topic_callback(const nav_msgs::msg::Odometry::SharedPtr msg) {
    RCLCPP_INFO(this->get_logger(), "Received odom msg");
}

void MapMemoryNode::local_costmap_topic_callback(const nav_msgs::msg::OccupancyGrid::SharedPtr msg) {
    RCLCPP_INFO(this->get_logger(), "Received local costmap msg");
}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MapMemoryNode>());
  rclcpp::shutdown();
  return 0;
}
