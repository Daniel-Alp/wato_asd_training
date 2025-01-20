#ifndef COSTMAP_NODE_HPP_
#define COSTMAP_NODE_HPP_
 
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
 
#include "costmap_core.hpp"
 
class CostmapNode : public rclcpp::Node {
  public:
    CostmapNode();
    
    // Place callback function here
    // void publishMessage();

    void lidar_topic_callback(const std_msgs::msg::String::SharedPtr msg) const;
 
  private:
    robot::CostmapCore costmap_;

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr lidar_sub_;

    // Place these constructs here
    // rclcpp::Publisher<std_msgs::msg::String>::SharedPtr string_pub_;
    // rclcpp::TimerBase::SharedPtr timer_;
};
 
#endif 