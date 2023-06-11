#include <smb_highlevel_controller/SmbHighlevelController.hpp>
#include <sensor_msgs/LaserScan.h>

int main(int argc, char** argv){

    ros::init(argc, argv, "Scanner");
    ros::NodeHandle nh;
    smb_highlevel_controller::SmbHighlevelController shc(nh);
    ros::Subscriber scanSub = (nh).subscribe("scan", 10, &smb_highlevel_controller::SmbHighlevelController::scanCallBack,&shc);
    ros::spin();
    return 0;
}

