#ifndef MAP_MEMORY_CORE_HPP_
#define MAP_MEMORY_CORE_HPP_

#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/occupancy_grid.hpp"
#include "nav_msgs/msg/odometry.hpp"

namespace robot
{

class MapMemoryCore {
  public:
    nav_msgs::msg::OccupancyGrid::SharedPtr global_costmap_data_; 

    explicit MapMemoryCore(const rclcpp::Logger& logger);

    void reset_costmap();

    void fuse_local_costmap(const nav_msgs::msg::OccupancyGrid::SharedPtr costmap_data);

  private:
    rclcpp::Logger logger_;

    int scan_width = 30; // this really does not belong here and the code can be improved but I want to get this working :-)

    int costmap_width = 90;
    int costmap_height = 90;

    double x;
    double y;
};
}  

#endif  
