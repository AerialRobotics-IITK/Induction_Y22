#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"

using namespace std;
using namespace ros;
using namespace sensor_msgs;

void scan_call_back(LaserScan msg) {
    _Float32 minDistance = INFINITY;
    for(int i = 0; i < msg.ranges.size(); i++)
        if( minDistance > msg.ranges[i] )
            minDistance = msg.ranges[i];
    ROS_INFO("Minimum Distance = %f", minDistance);
}

int main(int argc, char *argv[]) {
    init(argc, argv, "smb_highlevel_controller");
    NodeHandle node("~");
    string topic;
    int queue_size;
    node.getParam("topic", topic);
    node.getParam("queue_size", queue_size);
    Subscriber scan = node.subscribe(topic, queue_size, scan_call_back);
    ros::spin();

    return 0;
}