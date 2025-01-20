#ifndef COSTMAP_CORE_HPP_
#define COSTMAP_CORE_HPP_

#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/occupancy_grid.hpp"
// #include "sensor_msgs/msg/laser_scan.hpp"

// GET OUT!

namespace robot
{

class CostmapCore {
  public:
    // Constructor, we pass in the node's RCLCPP logger to enable logging to terminal
    explicit CostmapCore(const rclcpp::Logger& logger);

  private:
    // nav_msgs::msg::OccupancyGrid costmap_msg_; 
    rclcpp::Logger logger_;

};

}  

#endif  