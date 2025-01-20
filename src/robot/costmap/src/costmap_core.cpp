#include "costmap_core.hpp"

namespace robot
{

CostmapCore::CostmapCore(const rclcpp::Logger& logger) : costmap_data_(std::make_shared<nav_msgs::msg::OccupancyGrid>()),  logger_(logger) {
    reset_costmap();
}

void CostmapCore::reset_costmap() {
    costmap_data_->info.width = costmap_width;
    costmap_data_->info.height = costmap_height;
    costmap_data_->data.assign(costmap_width * costmap_height, -1);
}

void CostmapCore::update_costmap(const sensor_msgs::msg::LaserScan::SharedPtr scan) {  
    // grid is 30x30, so ranges values go from -30 to 30

    std::fill(costmap_data_->data.begin(), costmap_data_->data.end(), 0);
    double angle = scan->angle_min;
    for (size_t i = 0; i < scan->ranges.size(); i++) {
    
        // scan square is a 30x30 square centered about the robot
        // coordinates of point relative to the center of the robot
        double scan_x = scan->ranges[i] * std::sin(angle);
        double scan_y = scan->ranges[i] * std::cos(angle); 

        // costmap grid is a 120x120 grid overlaying the scan square 
        // coordinates of point relative to bottom left corner of scan square
        int costmap_x = (scan_x + scan_width / 2) * costmap_width / scan_width;
        int costmap_y = (scan_y + scan_height / 2) * costmap_height / scan_height;

        if (costmap_x >= 0 && costmap_x < costmap_width && costmap_y >= 0 && costmap_y < costmap_height) {
            costmap_data_->data[costmap_y * costmap_height + costmap_x] = 100;
        }
        angle += scan->angle_increment;
    }
}
}