#include<ros/ros.h>
#include<std_msgs/Int32.h>
#include<sensor_msgs/LaserScan.h>
#include<geometry_msgs/Twist.h>

using namespace std;
using namespace ros;

float p_gain_linear;
float p_gain_angular;
string topicname; 
int quesize;

class ros_setup{
    
    
public:
    ros_setup(){
    string topicname; 
    int quesize;
    nodehandle.getParam("quesize",quesize);
    nodehandle.getParam("topicname", topicname);
    nodehandle.getParam("p_gain_linear",p_gain_linear);
    nodehandle.getParam("p_gain_angular",p_gain_angular);
    subscribe_to_scan = nodehandle.subscribe("/scan" , 10 , &ros_setup::scanCallback,this);
    angle_pub = nodehandle.advertise<geometry_msgs::Twist>("/cmd_vel",1,this);
    };

    void scanCallback(sensor_msgs::LaserScan scan){       
    ros::Rate loopRate(10);  
    double hitpoint = scan.range_min;
    float min = scan.ranges[0];
    auto minElement = std::min_element(scan.ranges.begin(), scan.ranges.end()); 
    if (minElement != scan.ranges.end()) {
        min = *minElement;
    }
    int angle_pos = std::distance(scan.ranges.begin(),minElement) -(scan.ranges.size())/2;
    ROS_INFO("Min Distance is: %f ",min);
    
    
     
    geometry_msgs::Twist angle_rotate_drive;

    if(min>hitpoint){
        angle_rotate_drive.linear.x = min*(0.5);
    }
    else{
        angle_rotate_drive.linear.x = 0;
    }
    if(angle_pos>5 || angle_pos<-5)
        
        angle_rotate_drive.angular.z= angle_pos*(0.1);
        ROS_INFO("Angle Pos is: %d", angle_pos);
        angle_pub.publish(angle_rotate_drive);
        ros::spinOnce;
        loopRate.sleep();
    

}

private:
    ros::NodeHandle nodehandle;
    ros::Subscriber subscribe_to_scan;
    ros::Publisher angle_pub;
    


    
};



int main(int argc, char **argv){
    ros::init(argc, argv,"pillar");
    ros_setup start;
    ros::spin();
    return 0;



}