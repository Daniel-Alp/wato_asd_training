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

void CostmapNode::lidar_topic_callback(const sensor_msgs::msg::LaserScan::SharedPtr scan) {
  // RCLCPP_INFO(this->get_logger(), "Received lidar msg");

  costmap_.update_costmap(scan);
  nav_msgs::msg::OccupancyGrid costmap_msg = *(costmap_.costmap_data_);
  costmap_msg.header = scan->header;
  occupancy_grid_pub_->publish(costmap_msg);
}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CostmapNode>());
  rclcpp::shutdown();
  return 0;
}