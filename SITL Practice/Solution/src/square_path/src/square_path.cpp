#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/CommandTOL.h>
#include <math.h>

using namespace std;
using namespace ros;
using namespace geometry_msgs;
using namespace mavros_msgs;

bool isConnected = false, isArmed = false, isGuided = false;
PoseStamped current_position;

_Float64 distance(PoseStamped p1, PoseStamped p2) {
    return pow(pow(p1.pose.position.x-p2.pose.position.x, 2) + pow(p1.pose.position.y-p2.pose.position.y, 2) + pow(p1.pose.position.z-p2.pose.position.z, 2), 0.5);
}
PoseStamped setPose(_Float64 x, _Float64 y, _Float64 z) {
    PoseStamped position;
    position.pose.position.x = x;
    position.pose.position.y = y;
    position.pose.position.z = z;
    return position;
}
void goToPose(PoseStamped target_position, Publisher position_publisher, float tolerance, Rate rate) {
    position_publisher.publish(target_position);
    _Float64 current_distance = distance(target_position, current_position);
    while( ok() && distance(target_position, current_position) > tolerance ) {
        ROS_INFO("Target Position = (%f, %f, %f) Current Position = (%f, %f, %f) Distance = %f", target_position.pose.position.x, target_position.pose.position.y, target_position.pose.position.z, current_position.pose.position.x, current_position.pose.position.y, current_position.pose.position.z, current_distance);
        current_distance = distance(target_position, current_position);
        spinOnce();
        rate.sleep();
    }
}

void getState(State msg) {
    isConnected = msg.connected;
    isArmed = msg.armed;
    if( msg.mode == "GUIDED" )
        isGuided = true;
    else
        isGuided = false;
}
void updatePosition(PoseStamped msg) {
    current_position = msg;
}

int main(int argc, char *argv[]) {
    int rate, queue_size;
    int rounds;
    float altitude, side, tolerance;
    string set_mode_service, arm_service, takeoff_service, land_service;
    string state_subscription, position_subscription;
    string position_publisher;
    string mode;
    SetMode mode_command;
    CommandBool arm_command;
    CommandTOL takeoff_command, land_command;

    init(argc, argv, "square_path_controller");

    NodeHandle node("~");
    node.getParam("rate", rate);
    node.getParam("queue_size", queue_size);
    node.getParam("altitude", altitude);
    node.getParam("side", side);
    node.getParam("rounds", rounds);
    node.getParam("tolerance", tolerance);
    node.getParam("mode", mode);
    node.getParam("set_mode_service", set_mode_service);
    node.getParam("arm_service", arm_service);
    node.getParam("takeoff_service", takeoff_service);
    node.getParam("land_service", land_service);
    node.getParam("state_subscription", state_subscription);
    node.getParam("position_subscription", position_subscription);
    node.getParam("position_publisher", position_publisher);

    PoseStamped initialPosition = setPose(0, 0, altitude);
    PoseStamped startPosition = setPose(0, side/2, altitude);
    vector<PoseStamped> path;
    path.push_back(setPose(-side/2, side/2, altitude));
    path.push_back(setPose(-side/2, -side/2, altitude));
    path.push_back(setPose(side/2, -side/2, altitude));
    path.push_back(setPose(side/2, side/2, altitude));

    ServiceClient set_mode = node.serviceClient<SetMode>(set_mode_service);
    ServiceClient arm = node.serviceClient<CommandBool>(arm_service);
    ServiceClient takeoff = node.serviceClient<CommandTOL>(takeoff_service);
    ServiceClient land = node.serviceClient<CommandTOL>(land_service);

    Subscriber state = node.subscribe(state_subscription, queue_size, getState);
    Subscriber position = node.subscribe(position_subscription, queue_size, updatePosition);

    Publisher target_position = node.advertise<PoseStamped>(position_publisher, queue_size);

    Rate loop_rate(rate);

    ROS_INFO("Connecting to Drone...");
    while(ok() && !isConnected) {
        spinOnce();
        loop_rate.sleep();
    }
    ROS_INFO("Drone Connected!");

    ROS_INFO("Setting Mode to GUIDED...");
    mode_command.request.custom_mode = mode;
    set_mode.call(mode_command);
    while(ok() && !mode_command.response.mode_sent && !isGuided) {
        spinOnce();
        loop_rate.sleep();
    }
    ROS_INFO("Mode set to GUIDED!");

    ROS_INFO("Arming the Drone...");
    arm_command.request.value = true;
    arm.call(arm_command);
    while(ok() && arm_command.response.success && !isArmed) {
        spinOnce();
        loop_rate.sleep();
    }
    ROS_INFO("Armed the Drone!");

    ROS_INFO("Initiating Takeoff...");
    takeoff_command.request.altitude = altitude;
    takeoff.call(takeoff_command);
    while( abs(altitude-current_position.pose.position.z) > tolerance ) {
        spinOnce();
        loop_rate.sleep();
    }
    ROS_INFO("Takeoff Successful! Altitude = %f", altitude);

    ROS_INFO("Following Trajectory of a %f side square", side);
    goToPose(startPosition, target_position, tolerance, loop_rate);
    for(int round = 0; round < rounds; round++) {
        ROS_INFO("Round %d", round+1);
        for(vector<PoseStamped>::iterator vertex = path.begin(); vertex != path.end(); vertex++)
            goToPose(*vertex, target_position, tolerance, loop_rate);
    }
    ROS_INFO("Completed Trajectory of a %f side square %d times", side, rounds);

    ROS_INFO("Going to Initial Position (Position of Takeoff and now Landing)...");
    goToPose(startPosition, target_position, tolerance, loop_rate);
    goToPose(initialPosition, target_position, tolerance, loop_rate);
    ROS_INFO("Reached Initial Position");

    ROS_INFO("Landing...");
    land_command.request.altitude = 0;
    land.call(land_command);
    while( current_position.pose.position.z > tolerance ) {
        spinOnce();
        loop_rate.sleep();
    }
    ROS_INFO("Landing Successful!");

    return 0;
}