#include "map_memory_core.hpp"

namespace robot
{

MapMemoryCore::MapMemoryCore(const rclcpp::Logger& logger) : global_costmap_data_(std::make_shared<nav_msgs::msg::OccupancyGrid>()),  logger_(logger){
  reset_costmap();
}

void MapMemoryCore::reset_costmap() {
    global_costmap_data_->info.resolution = (double)scan_width/costmap_width;
    // grid is 30x30, offset by -15
    global_costmap_data_->info.origin.position.x = -15; 
    global_costmap_data_->info.origin.position.y = -15;
    global_costmap_data_->info.origin.position.z = 0;
    
    global_costmap_data_->info.width = costmap_width;
    global_costmap_data_->info.height = costmap_height;
    global_costmap_data_->data.assign(costmap_width * costmap_height, -1);
    std::fill(global_costmap_data_->data.begin(), global_costmap_data_->data.end(), 0);
}

void MapMemoryCore::fuse_local_costmap(const nav_msgs::msg::OccupancyGrid::SharedPtr costmap_data) {
  for (int y = 0; y < costmap_height; y++) {
    for(int x = 0; x < costmap_width; x++) {
      int index = y * costmap_height + x;
      if (costmap_data->data[index] > global_costmap_data_->data[index]) {
        global_costmap_data_->data[index] = costmap_data->data[index];
      }
    }
  }
}
} 

