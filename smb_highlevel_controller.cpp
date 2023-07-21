#include <iostream>
#include <ros/ros.h>
// #include <smb_highlevel_controller/SmbHighlevelController.hpp>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <visualization_msgs/Marker.h>
#include <boost/shared_ptr.hpp>
// #include <ros/rosconsole.h>
#include <bits/stdc++.h>
#include <vector>
#include <limits>
#include <math.h>

class SmbHighlevelController{

    private:
        ros::NodeHandle nh;
        ros::Publisher pub_angular;
        ros::Publisher pub_marker;

    public:

        SmbHighlevelController(){
            
            ros::Subscriber scanSub = (nh).subscribe<sensor_msgs::LaserScan>("scan", 5, &SmbHighlevelController::scanCallBack,this);
            ros::Publisher pub_angular = (nh).advertise<geometry_msgs::Twist>("cmd_vel",5,this);
            ros::Publisher pub_marker = (nh).advertise<visualization_msgs::Marker>("visualization_marker",0,this);
            
        }


        void scanCallBack(const sensor_msgs::LaserScan::ConstPtr& msg){

                std::vector<float> range = msg->ranges;
                float Min_dist = std::numeric_limits<float>::max();
                int angle_count = 0;
                float target;
                for(auto& itr : range){
                        if(itr < Min_dist) {
                            Min_dist = itr;
                            target = angle_count;
                        }
                        // ROS_INFO("Range =  %.2f\n", itr);
                        angle_count++;
                        // ROS_INFO("angle_count = %d", angle_count);
                }
                // ROS_INFO("increment = %.2f", msg->angle_increment);
                // ROS_INFO("target = %.2f\n", (target)*(msg->angle_increment));
                float Target_Angle = (target)*(msg->angle_increment)+(msg->angle_min);   
                ROS_INFO("target = %.2f", target);
                // ROS_INFO("Minimum distance = %.2f Target_Angle = %.2f", Min_dist, Target_Angle);
                float p_gain_angular;
                float p_gain_linear;
                ros::param::get("~p_gain_angular", p_gain_angular);
                ros::param::get("~p_gain_linear", p_gain_linear);
                ROS_INFO("%f",p_gain_angular);
                geometry_msgs::Twist msg_rotate;
                ROS_INFO("Target angle = %f  Min dist = %.2f", Target_Angle, Min_dist);
                // ROS_INFO("%f", (Target_Angle)*(p_gain_angular));
                float ang_vel = (Target_Angle)*p_gain_angular;
                float lin_vel = Min_dist*p_gain_linear;
                ROS_INFO("ang = %f lin = %f",ang_vel, lin_vel);
                ros::param::set("~Min_dist", Min_dist);
                ros::param::set("~Target_Angle", Target_Angle);

                // visualization_msgs::Marker marker;
                // marker.header.frame_id = "rslidar";
                // marker.header.stamp = ros::Time::now();
                // marker.ns = "pillar";
                // marker.id = 0;
                // marker.type = visualization_msgs::Marker::CYLINDER;
                // marker.action = 0;
                // ROS_INFO("x = %f y = %f",Min_dist*cos(Target_Angle), Min_dist*sin(Target_Angle));
                // marker.pose.position.x = Min_dist*cos(Target_Angle);
                // marker.pose.position.y = Min_dist*sin(Target_Angle);
                // marker.pose.position.z = 0.0;
                // marker.pose.orientation.x = 0.0;
                // marker.pose.orientation.y = 0.0;
                // marker.pose.orientation.z = 0.0;
                // marker.pose.orientation.w = 1.0;
                // marker.scale.x = 1.0;  
                // marker.scale.y = 1.0;
                // marker.scale.z = 1.0;
                // marker.color.r = 1.0;   
                // marker.color.g = 0.0;
                // marker.color.b = 0.0;
                // marker.color.a = 1.0;
                // marker.lifetime = ros::Duration();

                // pub_marker.publish(marker);

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
                    if(Target_Angle < 0.7 && Target_Angle > -0.7){
                    
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
            }

};

int main(int argc, char** argv){

    ros::init(argc,argv,"Scanner");
    SmbHighlevelController smb();

    ros::Rate rate(100);
    ros::spin();
    return 0;
}
