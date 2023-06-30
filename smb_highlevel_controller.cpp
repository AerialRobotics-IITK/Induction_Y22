#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <visualization_msgs/Marker.h>
#include <bits/stdc++.h>
#include <vector>
#include <limits>    
#include <math.h>
   
ros::Publisher pub_angular;

void scanCallBack(const sensor_msgs::LaserScan::ConstPtr& msg){

    ros::NodeHandle nh_;
    std::vector<float> range = msg->ranges;
    float Min_dist = std::numeric_limits<float>::max();
    int angle_count = 0;
    float target;
    for(auto& itr : range){
            if(itr < Min_dist) {
                Min_dist = itr;
                target = angle_count;
            }
            angle_count++;
    }
    
    float Target_Angle = (target)*(msg->angle_increment)+(msg->angle_min);
    float p_gain_angular;
    float p_gain_linear;
    ros::param::get("~p_gain_angular", p_gain_angular);
    ros::param::get("~p_gain_linear", p_gain_linear);
    ROS_INFO("p_gain_angular: %f p_gain_linear: %f",p_gain_angular,p_gain_linear);
    geometry_msgs::Twist msg_rotate;
    pub_angular = (nh_).advertise<geometry_msgs::Twist>("cmd_vel",5);
    ROS_INFO("Target angle = %f  Min dist = %.2f", Target_Angle, Min_dist);
    float ang_vel = (Target_Angle)*p_gain_angular;
    float lin_vel = Min_dist*p_gain_linear;
    ros::param::set("~Min_dist", Min_dist);
    ros::param::set("~Target_Angle", Target_Angle);

    ros::Publisher pub_marker = (nh_).advertise<visualization_msgs::Marker>("visualization_marker",5);
    visualization_msgs::Marker marker;
    marker.header.frame_id = "rslidar";
    marker.header.stamp = ros::Time();
    marker.ns = "pillar";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::CYLINDER;
    marker.action = 0;
    marker.pose.position.x = Min_dist*cos(Target_Angle);
    marker.pose.position.y = Min_dist*sin(Target_Angle);
    marker.pose.position.z = 0.0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
    marker.scale.x = 1.0;  
    marker.scale.y = 1.0;
    marker.scale.z = 1.0;
    marker.color.r = 1.0; 
    marker.color.g = 0.0;
    marker.color.b = 0.0;
    marker.color.a = 1.0;
    marker.lifetime = ros::Duration();

    pub_marker.publish(marker);

    if(Min_dist > 1.0){
        if(Target_Angle < 0.5 && Target_Angle > -0.5){
        
        msg_rotate.angular.x = 0.00;
        msg_rotate.angular.y = 0.00;
        msg_rotate.angular.z = 0.0;
        msg_rotate.linear.y = 0.0;
        msg_rotate.linear.x = lin_vel;  
        msg_rotate.linear.z = 0.0;
        pub_angular.publish(msg_rotate);

            }
        else{

        msg_rotate.angular.x = 0.00;
        msg_rotate.angular.y = 0.00;
        msg_rotate.angular.z = ang_vel;
        msg_rotate.linear.x = 0.00;
        msg_rotate.linear.y = 0.00;
        msg_rotate.linear.z = 0.00;
        pub_angular.publish(msg_rotate);

        }
    }
    else{
        if(Target_Angle < 0.65 && Target_Angle > -0.65){
        
        msg_rotate.angular.x = 0.00;
        msg_rotate.angular.y = 0.00;
        msg_rotate.angular.z = 0.0;
        msg_rotate.linear.y = 0.0;
        msg_rotate.linear.x = lin_vel;
        msg_rotate.linear.z = 0.0;
        pub_angular.publish(msg_rotate);

            }
        else{

        msg_rotate.angular.x = 0.00;
        msg_rotate.angular.y = 0.00;
        msg_rotate.angular.z = ang_vel;
        msg_rotate.linear.x = 0.00;
        msg_rotate.linear.y = 0.00;
        msg_rotate.linear.z = 0.00;
        pub_angular.publish(msg_rotate);

        

        }
    }

    ros::spin();
}

int main(int argc, char** argv){

    ros::init(argc, argv, "Scanner");
    ros::NodeHandle nh;
    ros::Subscriber scanSub = (nh).subscribe<sensor_msgs::LaserScan>("scan", 5, &scanCallBack);

    ros::Rate rate(100);
    ros::spin();
    return 0;
}
