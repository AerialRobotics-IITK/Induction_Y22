#include <iostream>
#include <ros/ros.h>
// #include <smb_highlevel_controller/SmbHighlevelController.hpp>
#include <sensor_msgs/LaserScan.h>
// #include <ros/rosconsole.h>
#include <bits/stdc++.h>
#include <vector>
#include <limits>

void scanCallBack(const sensor_msgs::LaserScan::ConstPtr& msg){

    std::vector<float> range = msg->ranges;
    float temp = std::numeric_limits<float>::max();
    for(auto& itr : range){
            if(itr < temp) temp = itr;
    }
    ROS_INFO("Minimum distance = %.2f", temp);

}

int main(int argc, char** argv){

    ros::init(argc, argv, "Scanner");
    ros::NodeHandle nh;
    ros::Subscriber scanSub = (nh).subscribe("scan", 5,scanCallBack);
    ros::spin();
    return 0;
}

