#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"

using namespace std;
using namespace ros;
using namespace sensor_msgs;
using namespace geometry_msgs;

class PID {
    private:
        float kp, kd, ki, dt, setPoint, integral = 0, prevError;
        bool firstValue = true;
    public:
        PID(float KP, float KD, float KI, float DT, float SETPOINT) {
            kp = KP;
            kd = KD;
            ki = KI;
            dt = DT;
            setPoint = SETPOINT;
        }
        float value(float valuePoint) {
            float p, d, i, error;
            error = setPoint - valuePoint;
            p = kp * error;
            if( firstValue ) {
                firstValue = false;
                prevError = error;
            } else {
                d = kd * (error-prevError) / dt;
                prevError = error;
            }
            i = ki * error * dt;
            integral += i;
            return p + d + integral;
        }
};

int angle = 0;
_Float32 minimum_distance = INFINITY;

void scan_call_back(LaserScan msg) {
    _Float32 minDistance = INFINITY;
    for(int i = 0; i < msg.ranges.size(); i++)
        if( minDistance > msg.ranges[i] ) {
            minDistance = msg.ranges[i];
            minimum_distance = minDistance;
            angle = i;
        }
}

int main(int argc, char *argv[]) {
    int rate, desired_angle, desired_distance, publisher_queue_size, subscirber_queue_size, angle_error;
    float angle_kp, angle_kd, angle_ki, velocity_kp, velocity_kd, velocity_ki;
    string publisher_topic, subscriber_topic;
    init(argc, argv, "smb_highlevel_controller");
    NodeHandle node("~");
    node.getParam("publisher_topic", publisher_topic);
    node.getParam("subscriber_topic", subscriber_topic);
    node.getParam("publisher_queue_size", publisher_queue_size);
    node.getParam("subscriber_queue_size", subscirber_queue_size);
    node.getParam("rate", rate);
    node.getParam("desired_angle", desired_angle);
    node.getParam("desired_distance", desired_distance);
    node.getParam("angle_kp", angle_kp);
    node.getParam("angle_kd", angle_kd);
    node.getParam("angle_ki", angle_ki);
    node.getParam("velocity_kp", velocity_kp);
    node.getParam("velocity_kd", velocity_kd);
    node.getParam("velocity_ki", velocity_ki);
    node.getParam("angle_error", angle_error);
    float dt = (float) 1 / rate;
    Publisher cmd_vel = node.advertise<Twist>(publisher_topic, publisher_queue_size);
    Subscriber scan = node.subscribe(subscriber_topic, subscirber_queue_size, scan_call_back);
    Rate loop_rate(rate);

    PID angleController(angle_kp, angle_kd, angle_ki, dt, (float) desired_angle);
    PID velocityController(velocity_kp, velocity_kd, velocity_ki, dt, (float) desired_distance);

    while(ok()) {
        Twist velocity;
        velocity.linear.x = 0;
        velocity.linear.y = 0;
        velocity.linear.z = 0;
        velocity.angular.x = 0;
        velocity.angular.y = 0;
        velocity.angular.z = (_Float64) angleController.value(angle) * -1;
        if( abs(desired_angle - angle) <= angle_error )
            velocity.linear.x = (_Float64) velocityController.value(minimum_distance) * -1;
        else
            velocity.linear.x = 0;
        cmd_vel.publish(velocity);
        ROS_INFO("Distance = %f Angle = %d Linear Velocity = %f Angular Velocity = %f", minimum_distance, angle, (float) velocity.linear.x, (float) velocity.angular.z);
        spinOnce();
        loop_rate.sleep();
    }

    return 0;
}