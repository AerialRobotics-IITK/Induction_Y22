#include<ros/ros.h>
#include<std_msgs/Int32.h>
#include<sensor_msgs/LaserScan.h>

using namespace std;
void scanCallback(sensor_msgs::LaserScan scan){       
    float min = scan.ranges[0];
    auto minElement = std::min_element(scan.ranges.begin(), scan.ranges.end());

    if (minElement != scan.ranges.end()) {
        min = *minElement;
    }
    ROS_INFO("Min Distance is: %f ",min);
}

int main(int argc, char **argv){
    ros::init(argc, argv,"min_dist");
    ros::NodeHandle nodehandle("~");
    string topicname;
    int quesize;
    nodehandle.getParam("quesize",quesize);
    nodehandle.getParam("topicname", topicname);
    ros::Subscriber subscribe_to_scan = nodehandle.subscribe(topicname , quesize , scanCallback);
    ros::spin();
    return 0;



}