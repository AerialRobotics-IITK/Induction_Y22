---


---

<h1 id="week2">Week2</h1>
<h2 id="downloading-smb_highlevel_controller">Downloading smb_highlevel_controller</h2>
<p>Download via .zip given at the course website, and we extract it to ~/catkin_ws/src.<br>
We can open and inspect the package.xml and CMakeLists.txt via</p>
<pre><code>cd ~/catkin_ws/src/smb_highlevel_controller
nano package.xml
nano CMakeLists.txt
</code></pre>
<h3 id="task-modifying-the-node-and-its-header-file-to-do-the-given-task">Task: Modifying the node, and its header file to do the given task</h3>
<p>First, we modify the header file to make SmbHighLevelController class</p>
<pre><code>#pragma once

#include &lt;ros/ros.h&gt;
#include &lt;geometry_msgs/Twist.h&gt;
#include &lt;sensor_msgs/LaserScan.h&gt;
#include &lt;string.h&gt;

using namespace std;

namespace smb_highlevel_controller {
	class SmbHighlevelController {
		public:
			SmbHighlevelController (ros::NodeHandle&amp; nodeHandle);
			virtual ~SmbHighlevelController();

		private:
			bool readParameters();
			void scanCallback(const sensor_msgs::LaserScan::ConstPtr&amp; msg);

			ros::NodeHandle nodeHandle_;
			ros::Subscriber scanSubscriber_;
			ros::Publisher twistPublisher_;
			string scanTopic_;
			int subscriberQueueSize_;
			string twistTopic_;
			int publisherQueueSize_;
};

} /* namespace */

</code></pre>
<p>once the class is made, we make the changes to SmbHighlevelController.cpp:</p>
<pre class=" language-undefined"><code class="prism language-#include language-undefined">
namespace smb_highlevel_controller {

SmbHighlevelController::SmbHighlevelController(ros::NodeHandle&amp; nodeHandle) :
  nodeHandle_(nodeHandle),
  scanTopic_("/scan"),
  subscriberQueueSize_(10),
  twistTopic_("/twist"),
  publisherQueueSize_(10)
{
	if (!readParameters()){
		ROS_ERROR("CANT READ PARAMETERS");
		ros::requestShutdown;
	}
	scanSubscriber_ = nodeHandle_.subscribe(scanTopic_, subscriberQueueSize_, &amp;SmbHighlevelController::scanCallback, this);
	twistPublisher_ =  nodeHandle_.advertise&lt;geometry_msgs::Twist&gt;(twistTopic_, publisherQueueSize_);
}

SmbHighlevelController::~SmbHighlevelController()
{
}

bool SmbHighlevelController::readParameters() {
	if(!nodeHandle_.getParam("/smb_high level_controller/scan_subscriber_queue_size", subscriberQueueSize_)){
		return false;
	}
	if(!nodeHandle_.getParam("/smb_highlevel_controller/scan_subscriber_topic_name", scanTopic_)) {
		return false;
	}
	if(!nodeHandle_.getParam("/smb_highlevel_controller/twist_publisher_queue_size", publisherQueueSize_)) {
		return false;
	}
	if(!nodeHandle_.getParam("/smb_high level_controller/twist_publisher_topic_name", twistTopic_)){
		return false;
	}
	return true;
} 

void SmbHighlevelController::scanCallback(const sensor_msgs::LaserScan::ConstPtr&amp; msg) {
	float minDistance = 100.0;
	int minDistanceIndex = 0;

	int i = 0;
	float angle = msg-&gt;angle_min;

	while (angle &lt;= msg-&gt;angle_max ) {
		if(msg-&gt;ranges [i]&lt;minDistance) {
			minDistance= msg-&gt;ranges [i];
			minDistanceIndex= i;
		}
		i++;
		angle += msg-&gt;angle_increment;
	}

	ROS_INFO("Min Distance: %f, angle: %f", minDistance, msg-&gt;angle_min+minDistanceIndex*msg-&gt;angle_increment);

}

}/* namespace */
</code></pre>
<p>In this we implement the following:<br>
the while loop is such that it is called whenever a new laser scan message is received. It finds the minimum distance in the laser scan and publishes a twist message that rotates the robot away from that direction.</p>
<p>Finally, the smb_highlevel_Controller_node.cpp is:</p>
<pre><code>#include &lt;ros/ros.h&gt;
#include "smb_highlevel_controller/SmbHighlevelController.hpp"

int main(int argc, char** argv) {
  ros::init(argc, argv, "smb_highlevel_controller");
  ros::NodeHandle nodeHandle("~");

  smb_highlevel_controller::SmbHighlevelController smbHighlevelController(nodeHandle);

  ros::spin();
  return 0;
}
</code></pre>
<p>Now for the parameter file, I used a .yaml file as it was easier to read, and I stored it in a made directory : ~/catkin_ws/src/smb_highlevel_controller/param<br>
the file is as follows :</p>
<pre><code>scan_subscriber_queue_size : 1
scan_subscriber_topic_name : /scan
twist_publisher_queue_size : 1
twist_publisher_topic_name : /scan
</code></pre>
<h2 id="modifying-the-launch-file">Modifying the launch file</h2>
<p>the new launch file is:</p>
<pre><code>&lt;?xml version="1.0" encoding="utf-8"?&gt;
&lt;launch&gt;

 &lt;!-- Laaunch ROS Package Template Node --&gt;
 &lt;node pkg="smb_highlevel_controller" type="smb_highlevel_controller" name="smb_highlevel_controller" output="screen"/&gt;
 	&lt;rosparam file="~/catkin_ws/src/smb_highlevel_controller/param/param.yaml"/&gt;

 &lt;include file="~/Git/smb_common/smb_gazebo/launch/ex1launch.launch"/&gt;

 &lt;node pkg="rviz" type="rviz" name="rviz" output="screen"/&gt; 

&lt;/launch&gt;
</code></pre>
<p>But due to constant error, I could not proceed further</p>

