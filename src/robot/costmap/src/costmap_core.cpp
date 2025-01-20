#include "costmap_core.hpp"

namespace robot
{

CostmapCore::CostmapCore(const rclcpp::Logger& logger) : costmap_data_(std::make_shared<nav_msgs::msg::OccupancyGrid>()),  logger_(logger) {
    reset_costmap();
}

void CostmapCore::reset_costmap() {
    costmap_data_->info.resolution = (double)scan_width/costmap_width;
    // grid is 30x30, offset by -15
    costmap_data_->info.origin.position.x = -15; 
    costmap_data_->info.origin.position.y = -15;
    costmap_data_->info.origin.position.z = 0;
    
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
        double scan_x = scan->ranges[i] * std::cos(angle);
        double scan_y = scan->ranges[i] * std::sin(angle); 

        // costmap grid is a 90x90 grid overlaying the scan square 
        // coordinates of point relative to bottom left corner of scan square
        int costmap_x = scan_x * costmap_width / scan_width + costmap_width / 2;
        int costmap_y = scan_y * costmap_height / scan_height + costmap_height / 2;

        if (costmap_x >= 0 && costmap_x < costmap_width && costmap_y >= 0 && costmap_y < costmap_height) {
            costmap_data_->data[costmap_y * costmap_height + costmap_x] = 100;
            inflate_gridcell(costmap_x, costmap_y);
        }
        angle += scan->angle_increment;
    }
}

void CostmapCore::inflate_gridcell(int costmap_x, int costmap_y) {
    int inflate_width = 9;
    int inflate_height = 9;
    for (int y = costmap_y - inflate_height/2; y < costmap_y + inflate_height/2; y++) {
        for (int x = costmap_x - inflate_width/2; x < costmap_x + inflate_width/2; x++) {
            if (x < 0 || x >= costmap_width || y < 0 || y >= costmap_height) {
                continue;
            }
            double distance = std::hypot(x - costmap_x, y - costmap_y) * (double)costmap_width/scan_width;
            double score = 100 * (1 - distance/inflation_radius);
            if (score > costmap_data_->data[y * costmap_height + x]) {
                costmap_data_->data[y * costmap_height + x] = score;
            }
        }
    }
}
}