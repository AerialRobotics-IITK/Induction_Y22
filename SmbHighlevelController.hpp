#pragma once

#include <ros/ros.h>
#include <iostream>
#include <bits/stdc++.h>
#include "sensor_msgs/LaserScan.h"
#include <vector>

namespace smb_highlevel_controller {

/*!
 * Class containing the Husky Highlevel Controller
 */
class SmbHighlevelController {
public:
	/*!
	 * Constructor.
	 */
	SmbHighlevelController(ros::NodeHandle& nodeHandle){
		nodeHandle_= nodeHandle;
	}

	/*!
	 * Destructor.
	 */
	// virtual ~SmbHighlevelController();
	void scanCallBack(const sensor_msgs::LaserScan::ConstPtr& scanMsg){
		
		std::vector<float> range = scanMsg->ranges;
		std::vector<float>::iterator itr;
		itr = range.begin();

		float temp = *(itr);
		for(itr = range.begin(); itr != range.end() ;itr++){
			if( *(itr) < temp) temp = *(itr);
		}
		ROS_INFO("test");
		// ROS_INFO("Least range: %f", temp);
		}



private:
	ros::NodeHandle nodeHandle_;

}; 
}/* namespace */
