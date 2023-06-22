# Excercise 1
---
## SMB Setup
Followed the official guide to setup core smb software on ETHZ website
```bash
mkdir ARIITK #Housing the Workspaces
cd ARIITK
mkdir -p ./smb_ws/src
cd ~/smb_ws/
catkin init
catkin config --extend /opt/ros/noetic #overlaying with ROS
catkin config -DCMAKE_BUILD_TYPE=Release

cd src

# Download the packages
vcs import \
--recursive \
--input https://raw.githubusercontent.com/ETHZ-RobotX/SuperMegaBot/master/smb.repos .
```
Instead of manually installing dependencies like, I used rosdep as indicated in the official guide, nevertheless, I still know how to install them manually

* hector gazebo plugins
* velodyne
* pointcloud to laserscan
* twist mux
```bash
sudo apt-get install python3-rosdep
sudo rosdep init
rosdep update
cd 
cd ARIITK/smb_ws/src
rosdep install --from-paths . --ignore-src --os=ubuntu:focal -r -y
```
Successfully installed all dependencies except gazebo-plugins
```bash
sudo apt install ros-noetic-gazebo-plugins
```
### Build TIme!
```bash
cd
cd ARIITK/smb_ws
catkin build smb_gazebo
```
Sourcing the setup.bash file
```bash
echo "source ~/ARIITK/smb_ws/devel/setup.bash" >> ~/.bashrc
```




---
##Installing and Setting up *teleop_twist_keyboard* package
Made the **git** folder for downloading the teleop_twist_keyboard package
```bash
mkdir Git
cd Git
git clone https://github.com/ros-teleop/teleop_twist_keyboard.git
```
Creating a **symlink** between the teleop pacakge and smb_ws/src
```bash
ln -s ~/Git/teleop_twist_keyboard/ ~/ARIITK/teleop_twist_keyboard/src/
```
Setting up ***teleop_twist_keyboard*** package and sourcing it to **.bashrc**
```bash
cd ~/ARIITK/teleop_twist_keyboard/
catkin build
echo "source ~/ARIITK/teleop_twist_keyboard/source/devel/setup.bash" >> ~/.bashrc
```
---
# Running a Simulation with given world
As given in the official documentation, the following command loads RViz, Gazebo in a predefined world that came with the package.
```bash
 roslaunch smb_gazebo sim.launch launch_gazebo_gui:=true world:=WaA
```
![Basic Simulation](https://github.com/AnIVIol/anmol_d/blob/b3d41a07153e94d26dc716b15945bf5f72dc8d56/Assignments/ROS/solution_1/Images/sim.launch.png?raw=true)


## Listing the nodes 
```bash
anmoldeep@anmoldeep-ASUS-TUF-Gaming-F15-FX507ZM-FX577ZM:~/ARIITK/smb_ws$ rosnode list
/control/controller_spawner
/control/smb_robot_state_publisher
/gazebo
/gazebo_gui
/joy_teleop/joy_e_stop_node
/joy_teleop/joy_node
/joy_teleop/teleop_twist_joy
/rosout
/rviz
/tracking_camera_odometry_conversion
/twist_mux


```
## Listing the topics
```bash
anmoldeep@anmoldeep-ASUS-TUF-Gaming-F15-FX507ZM-FX577ZM:~/ARIITK/smb_ws$ rostopic list
/base_odom
/blackfly_right_cam/parameter_descriptions
/blackfly_right_cam/parameter_updates
/camera/odom/sample
/clicked_point
/clock
/command_twist_stamped
/control/base_battery_state
/control/gazebo_ros_control/pid_gains/LF_WHEEL_JOINT/parameter_descriptions
/control/gazebo_ros_control/pid_gains/LF_WHEEL_JOINT/parameter_updates
/control/gazebo_ros_control/pid_gains/LH_WHEEL_JOINT/parameter_descriptions
/control/gazebo_ros_control/pid_gains/LH_WHEEL_JOINT/parameter_updates
/control/gazebo_ros_control/pid_gains/RF_WHEEL_JOINT/parameter_descriptions
/control/gazebo_ros_control/pid_gains/RF_WHEEL_JOINT/parameter_updates
/control/gazebo_ros_control/pid_gains/RH_WHEEL_JOINT/parameter_descriptions
/control/gazebo_ros_control/pid_gains/RH_WHEEL_JOINT/parameter_updates
/control/joint_states
/control/smb_diff_drive/cmd_vel
/control/smb_diff_drive/odom
/control/smb_diff_drive/parameter_descriptions
/control/smb_diff_drive/parameter_updates
/diagnostics
/gazebo/link_states
/gazebo/model_states
/gazebo/parameter_descriptions
/gazebo/parameter_updates
/gazebo/performance_metrics
/gazebo/set_link_state
/gazebo/set_model_state
/imu0
/imu0/accel/parameter_descriptions
/imu0/accel/parameter_updates
/imu0/bias
/imu0/rate/parameter_descriptions
/imu0/rate/parameter_updates
/imu0/yaw/parameter_descriptions
/imu0/yaw/parameter_updates
/initialpose
/joy_teleop/cmd_vel
/joy_teleop/e_stop
/joy_teleop/joy
/joy_teleop/joy/set_feedback
/keyboard_teleop/cmd_vel
/move_base/OmplPlanner/plan
/move_base/TebLocalPlannerROS/teb_poses
/move_base/cancel
/move_base/global_costmap/costmap
/move_base/global_costmap/costmap_updates
/move_base_simple/goal
/mpc_trajectory_standalone
/opc/cmd_vel
/opc/e_stop
/optimal_path
/rc_twist
/rosout
/rosout_agg
/rslidar_ground_truth
/rslidar_points
/smb_mpc/command_twist
/smb_powerstatus/payload
/teb_planner_twist
/tf
/tf_static
/versavis/cam0/slow/camera_info
/versavis/cam0/slow/image_raw
/versavis/cam0/slow/image_raw/compressed
/versavis/cam0/slow/image_raw/compressed/parameter_descriptions
/versavis/cam0/slow/image_raw/compressed/parameter_updates
/versavis/cam0/slow/image_raw/compressedDepth
/versavis/cam0/slow/image_raw/compressedDepth/parameter_descriptions
/versavis/cam0/slow/image_raw/compressedDepth/parameter_updates
/versavis/cam0/slow/image_raw/theora
/versavis/cam0/slow/image_raw/theora/parameter_descriptions
/versavis/cam0/slow/image_raw/theora/parameter_updates
```

## Checking rate of publishing to base_odom
```bash
average rate: 60.325
	min: 0.000s max: 0.049s std dev: 0.02009s window: 53
average rate: 56.793
	min: 0.000s max: 0.049s std dev: 0.02031s window: 103
average rate: 58.148
	min: 0.000s max: 0.049s std dev: 0.02010s window: 158
average rate: 57.847
	min: 0.000s max: 0.049s std dev: 0.02022s window: 210
average rate: 57.086
	min: 0.000s max: 0.049s std dev: 0.02027s window: 260
^Caverage rate: 57.037
	min: 0.000s max: 0.049s std dev: 0.02029s window: 277

```
## Publishing to /opc/cmd_vel
Due to my renowned skills of complicating things, using the core package files has resulted in /cmd_vel not starting as a topic when simulating, instead /opc/cmd_vel is to be used to publish velocity commands

```bash
rostopic pub -r 10 /opc/cmd_vel geometry_msgs/Twist "linear:
  x: 0.0
  y: 0.0
  z: 0.0
angular:
  x: 0.0
  y: 0.0
  z: 1.0"
```
This starts publishing at 10 Hz to /opc/cmd_vel and robot starts rotating like a shwarma rotisserie

---
# Launch File setup 

Again due to my skills, custom launch file was a pain as smb core package had a some attributes that weren't handled by my launch file. So I ended by duplicating launch file and just changing ***world_file*** path to run the predefined worlds in ***/usr/share/gazebo-11/worlds/***

I chose: ***everything.world***

```xml
<?xml version="1.0" encoding="utf-8"?>
<launch>

  <!-- ROBOT ARGUMENTS -->
  <!-- Name of the robot description parameter -->
  <arg name="description_name"            default="smb_description"/>
  <arg name="enable_ekf"                  default="false"/>
  <arg name="robot_namespace"             default=""/>
  <arg name="control_namespace"           default="control"/>
  <arg name="launch_rviz"                 default="true"/>
  <arg name="launch_gazebo_gui"           default="false"/>
  <arg name="mpc"                         default="false"/>
  <arg name="keyboard_teleop"             default="false"/>
  <arg name="world"                       default="WaA"/>


  <include file="$(find smb_control)/launch/smb_control.launch">
    <arg name="control_namespace"       value="$(arg control_namespace)"/>
    <arg name="robot_namespace"         value="$(arg robot_namespace)"/>
    <arg name="description_name"        value="$(arg description_name)"/>
    <arg name="enable_ekf"              value="$(arg enable_ekf)" />
    <arg name="simulation"              value="true"/>
    <arg name="mpc"                     value="$(arg mpc)"/>
    <arg name="keyboard_teleop"         value="$(arg keyboard_teleop)"/>
  </include>

  <include file="$(find smb_gazebo)/launch/smb_gazebo.launch">
    <arg name="description_name"    value="$(arg description_name)"/>
    <arg name="control_namespace"   value="$(arg control_namespace)"/>
    <arg name="run_gui"             value="$(arg launch_gazebo_gui)"/>
    <arg name="world_file"               value="/usr/share/gazebo-11/worlds/everything.world"/>
  </include>

  <include file="$(find smb_opc)/launch/opc.launch" if="$(arg launch_rviz)"/>

</launch>

```
![Changed World](https://github.com/AnIVIol/anmol_d/blob/b3d41a07153e94d26dc716b15945bf5f72dc8d56/Assignments/ROS/solution_1/Images/sim2.launch.png?raw=true)
