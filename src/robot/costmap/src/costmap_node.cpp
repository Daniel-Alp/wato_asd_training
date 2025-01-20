#include <chrono>
#include <memory>
 
#include "costmap_node.hpp"
 
CostmapNode::CostmapNode() : Node("costmap"), costmap_(robot::CostmapCore(this->get_logger())) {
    lidar_sub_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
      "/lidar", 10, 
      std::bind(
        &CostmapNode::lidar_topic_callback, this, 
        std::placeholders::_1));

    occupancy_grid_pub_ = this->create_publisher<nav_msgs::msg::OccupancyGrid>("/costmap", 10);

    RCLCPP_INFO(this->get_logger(), "Initialized Costmap Node");
} 

void CostmapNode::lidar_topic_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg) const {
  RCLCPP_INFO(this->get_logger(), "Hello, ROS");
}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CostmapNode>());
  rclcpp::shutdown();
  return 0;
}