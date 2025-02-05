#ifndef COSTMAP_CORE_HPP_
#define COSTMAP_CORE_HPP_

#include <array>
#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/occupancy_grid.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"

namespace robot
{

class CostmapCore {
  public:
    nav_msgs::msg::OccupancyGrid::SharedPtr costmap_data_; 

    // Constructor, we pass in the node's RCLCPP logger to enable logging to terminal
    explicit CostmapCore(const rclcpp::Logger& logger);

    void reset_costmap();  // set entire map to value of 0

    void update_costmap(const sensor_msgs::msg::LaserScan::SharedPtr scan); 

    void inflate_gridcell(int costmap_x, int costmap_y);

  private:
    rclcpp::Logger logger_;


    int costmap_width = 90;
    int costmap_height = 90;

    int scan_width = 30;
    int scan_height = 30;
    double inflation_radius = 10;
};
}  

#endif  