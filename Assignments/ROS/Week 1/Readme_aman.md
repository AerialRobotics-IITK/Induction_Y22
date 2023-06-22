# Exercise 1
## Prerequisite
### Installing Required Packages
Setting up the Following ROS Noetic Packages using apt command that are required to run the simulator:
* hector gazebo plugins
* velodyne
* pointcloud to laserscan
* twist mux
```bash
sudo apt install -y ros-noetic-hector-gazebo-plugins ros-noetic-velodyne ros-noetic-velodyne-description ros-noetic-velodyne-gazebo-plugins ros-noetic-pointcloud-to-laserscan ros-noetic-twist-mux
```
### Creating Folders
Making the following folders in *home* directory:
* **Git** : For cloning/downloading required files
* **Workspace** : The ROS Workspaces for the Exercises that contains all the Packages
```bash
cd ~
mkdir Git Workspace
```
Let's make the *smb_workspace* and *teleop_twist_keyboard_workspace* folder in **Workspaces** as **smb_ws** and **teleop_twist_keyboard** with **src** folder
```bash
cd Workspace
mkdir -p smb_ws/src/
mkdir -p teleop_twist_keyboard/src/
```
### Downloading the required File
We download the [smb_common.zip](https://ethz.ch/content/dam/ethz/special-interest/mavt/robotics-n-intelligent-systems/rsl-dam/ROS2021/lec1/smb_common.zip) file with the help of *wget* command and clone [teleop_twist_keyboard](https://github.com/ros-teleop/teleop_twist_keyboard.git) with the *git* command into the **Git** Folder
```bash
cd ~/Git/
wget https://ethz.ch/content/dam/ethz/special-interest/mavt/robotics-n-intelligent-systems/rsl-dam/ROS2021/lec1/smb_common.zip
git clone https://github.com/ros-teleop/teleop_twist_keyboard.git
```
### Extracting the ZIP File
We extract the zip file using the *unzip* command
```bash
unzip smb_common.zip
```
Now, we don't need the **smb_common.zip** file, because we already have the folder. So let's delete **smb_common.zip** using the *rm* command
```bash
rm smb_common.zip
```
Let's checkout the folder using *ls* command with long listing (*-l*) argument
```bash
[kaptaan@PEACOCK]-[~/Git]$ ls -l
total 8
-rw-rw-r-- 1 kaptaan kaptaan   94 Apr 10 00:14 Push_Token.txt
drwxr-xr-x 5 kaptaan kaptaan 4096 Feb 17  2021 smb_common
```
Here, we see the **smb_common** folder. And that's the required file
### Linking Folders
We then create a ***symlink*** between the **smb_commond** folder in **Git** folder and **src** in **Workspaces/smb_ws** using the *ln* command.<br />
Also, create a ***symlink*** between the **teleop_twist_keyboard** folder in **Git** folder  and **src** in **Workspaces/teleop_twist_keyboard** using the *ln* command
```bash
ln -s ~/Git/smb_common/* ~/Workspaces/smb_ws/src/
ln -s ~/Git/teleop_twist_keyboard/ ~/Workspaces/teleop_twist_keyboard/src/
```
Let's checkout the **src** folder
```bash
[kaptaan@PEACOCK]-[~/Workspaces/smb_ws]$ cd src/
[kaptaan@PEACOCK]-[~/Workspaces/smb_ws/src]$ ls -l
total 0
lrwxrwxrwx 1 kaptaan kaptaan 38 Jun  4 19:50 README.md -> /home/kaptaan/Git/smb_common/README.md
lrwxrwxrwx 1 kaptaan kaptaan 40 Jun  4 19:50 smb_control -> /home/kaptaan/Git/smb_common/smb_control
lrwxrwxrwx 1 kaptaan kaptaan 44 Jun  4 19:50 smb_description -> /home/kaptaan/Git/smb_common/smb_description
lrwxrwxrwx 1 kaptaan kaptaan 39 Jun  4 19:50 smb_gazebo -> /home/kaptaan/Git/smb_common/smb_gazebo
```
```bash
[kaptaan@PEACOCK]-[~/Workspaces/teleop_twist_keyboard]$ cd src
[kaptaan@PEACOCK]-[~/Workspaces/teleop_twist_keyboard/src]$ ls -l
total 0
lrwxrwxrwx 1 kaptaan kaptaan 40 Jun  4 22:45 teleop_twist_keyboard -> /home/kaptaan/Git/teleop_twist_keyboard/
```
Here, the *->* symbol tells the File/Directory is linked to another file/directory with its path given.
## Setting up the SMB Simulation
Let's build the packages using the *catkin build* command.
```bash
cd ~/Workspace/smb_common/
catkin build
```
If no errors are shown, then we've successfully build the following packages:
* smb_control
* smb_description
* smb_gazebo
<!-- -->
Let's source the **setup.bash** file located in the **devel** folder.
```bash
source devel/setup.bash
```
## Launching the Simulation
Let's launch the **smb_gazebo** using *roslaunch* command.
```bash
roslaunch smb_gazebo smb_gazebo.launch
```
Here, we see the simulator running
![SMB Gazebo Simulation](https://raw.githubusercontent.com/Gill-Singh-A/Induction_Y22/Gill/Assignments/ROS/Exercise_1/assets/images/simulation.png)
Let's see the nodes using the *rosnode list* command.
```bash
[kaptaan@PEACOCK]-[~/Workspaces/smb_ws]$ rosnode list
/base_controller_spawner
/gazebo
/gazebo_gui
/pointcloud_to_laserscan
/rosout
/smb_robot_state_publisher
/twist_mux
```
Let's see the topics using the *rostopic list* command.
```bash
[kaptaan@PEACOCK]-[~/Workspaces/smb_ws]$ rostopic list
/clock
/cmd_vel
/diagnostics
/e_stop
/gazebo/link_states
/gazebo/model_states
/gazebo/parameter_descriptions
/gazebo/parameter_updates
/gazebo/performance_metrics
/gazebo/set_link_state
/gazebo/set_model_state
/gazebo_ros_control/pid_gains/LF_WHEEL_JOINT/parameter_descriptions
/gazebo_ros_control/pid_gains/LF_WHEEL_JOINT/parameter_updates
/gazebo_ros_control/pid_gains/LH_WHEEL_JOINT/parameter_descriptions
/gazebo_ros_control/pid_gains/LH_WHEEL_JOINT/parameter_updates
/gazebo_ros_control/pid_gains/RF_WHEEL_JOINT/parameter_descriptions
/gazebo_ros_control/pid_gains/RF_WHEEL_JOINT/parameter_updates
/gazebo_ros_control/pid_gains/RH_WHEEL_JOINT/parameter_descriptions
/gazebo_ros_control/pid_gains/RH_WHEEL_JOINT/parameter_updates
/imu0
/imu0/accel/parameter_descriptions
/imu0/accel/parameter_updates
/imu0/bias
/imu0/rate/parameter_descriptions
/imu0/rate/parameter_updates
/imu0/yaw/parameter_descriptions
/imu0/yaw/parameter_updates
/joint_states
/joy_teleop/cmd_vel
/odom
/rosout
/rosout_agg
/rslidar_points
/scan
/smb_velocity_controller/cmd_vel
/smb_velocity_controller/odom
/smb_velocity_controller/parameter_descriptions
/smb_velocity_controller/parameter_updates
/tf
/tf_static
/twist_marker_server/cmd_vel
```
The Information of these Topics obtained by running *rotopic info* command is stored in **Topic Information.md**<br />
By executing *rostopic info* command we can see the information of a rostopic. For example ***/tf*** Topic:
```bash
[kaptaan@PEACOCK]-[~/Workspaces/smb_ws]$ rostopic echo /tf
transforms: 
  - 
    header: 
      seq: 0
      stamp: 
        secs: 3375
        nsecs: 743000000
      frame_id: "odom"
    child_frame_id: "base_link"
    transform: 
      translation: 
        x: 0.013231121695972783
        y: 0.00010271608521839856
        z: 0.0
      rotation: 
        x: 0.0
        y: 0.0
        z: 0.007768063744236716
        w: 0.9999698281376621
---
transforms: 
  - 
    header: 
      seq: 0
      stamp: 
        secs: 3375
        nsecs: 743000000
      frame_id: "base_link"
    child_frame_id: "LF_WHEEL"
    transform: 
      translation: 
        x: 0.2159
        y: 0.285
        z: -0.018500000000000003
      rotation: 
        x: -0.7063410574918964
        y: 0.03289848782587708
        z: 0.03289848782587708
        w: 0.7063410574918966
  - 
    header: 
      seq: 0
      stamp: 
        secs: 3375
        nsecs: 743000000
      frame_id: "base_link"
    child_frame_id: "LH_WHEEL"
    transform: 
      translation: 
        x: -0.2159
        y: 0.285
        z: -0.018500000000000003
      rotation: 
        x: -0.7071067661200044
        y: -0.0001459702340116569
        z: -0.00014597023401165694
        w: 0.7071067661200046
  - 
    header: 
      seq: 0
      stamp: 
        secs: 3375
        nsecs: 743000000
      frame_id: "base_link"
    child_frame_id: "RF_WHEEL"
    transform: 
      translation: 
        x: 0.2159
        y: -0.285
        z: -0.018500000000000003
      rotation: 
        x: -0.7063433504901598
        y: 0.03284921944788349
        z: 0.0328492194478835
        w: 0.70634335049016
  - 
    header: 
      seq: 0
      stamp: 
        secs: 3375
        nsecs: 743000000
      frame_id: "base_link"
    child_frame_id: "RH_WHEEL"
    transform: 
      translation: 
        x: -0.2159
        y: -0.285
        z: -0.018500000000000003
      rotation: 
        x: -0.7063433625801808
        y: 0.03284895948006698
        z: 0.03284895948006699
        w: 0.706343362580181
---
```
We can also check the rate of a topic using the *topic hz* command
```bash
[kaptaan@PEACOCK]-[~/Workspaces/smb_ws]$ rostopic hz /tf
subscribed to [/tf]
WARNING: may be using simulated time
average rate: 100.917
	min: 0.001s max: 0.019s std dev: 0.00900s window: 100
average rate: 100.454
	min: 0.001s max: 0.019s std dev: 0.00900s window: 200
average rate: 100.302
	min: 0.000s max: 0.020s std dev: 0.00898s window: 300
average rate: 100.226
	min: 0.000s max: 0.020s std dev: 0.00899s window: 400
average rate: 100.181
	min: 0.000s max: 0.020s std dev: 0.00899s window: 500
average rate: 100.150
	min: 0.000s max: 0.020s std dev: 0.00898s window: 600
average rate: 100.129
	min: 0.000s max: 0.020s std dev: 0.00899s window: 700
```
## Command a desired velocity to the robot from the terminal
We can give the robot a desired velocity by publishing to the topic with the help of *rostopic pub [TOPIC] [TYPE] [DATA]*
```bash
[kaptaan@PEACOCK]-[~/Workspaces/teleop_twist_keyboard/src/teleop_twist_keyboard]$ rostopic pub -r 1000 /cmd_vel geometry_msgs/Twist "linear:
  x: 0.0
  y: 0.0
  z: 0.0
angular:
  x: 0.0
  y: 0.0
  z: 1.0" 
publishing and latching message. Press ctrl-C to terminate
```
## Setting up teleop_twist_keyboard
Let's setup teleop_twist_keyboard to control your robot using the keyboard.
```bash
cd ~/Workspaces/teleop_twist_keyboard/
catkin build
source devel/setup.bash
```
Let's run the teleop_twist_keyboard
```bash
[kaptaan@PEACOCK]-[~]$ cd ~/Workspaces/teleop_twist_keyboard/src/teleop_twist_keyboard
[kaptaan@PEACOCK]-[~/Workspaces/teleop_twist_keyboard/src/teleop_twist_keyboard]$ python teleop_twist_keyboard.py 
Reading from the keyboard  and Publishing to Twist!
---------------------------
Moving around:
   u    i    o
   j    k    l
   m    ,    .
For Holonomic mode (strafing), hold down the shift key:
---------------------------
   U    I    O
   J    K    L
   M    <    >
t : up (+z)
b : down (-z)
anything else : stop
q/z : increase/decrease max speeds by 10%
w/x : increase/decrease only linear speed by 10%
e/c : increase/decrease only angular speed by 10%
CTRL-C to quit
```
## Making the Launch File
In the launch file, the argument *world* of the **smb_gazebo** launch file is set to *big_map_summer_school* and it loads that world.
```xml
<?xml version="1.0" encoding="utf-8"?>
<launch>
  <arg name="world_name" default="big_map_summer_school" />
  <include file="$(find smb_gazebo)/launch/smb_gazebo.launch">
    <arg name="world" value="$(arg world_name)" />
  </include>
  <node name="teleop_twist_keyboard" pkg="teleop_twist_keyboard" type="teleop_twist_keyboard.py" />
</launch>
```
Move the *exercise_1.launch* file to **src/launch** of **smb_gazebo** Package, to execute it with *roslaunch* command after sourcing the **setup.bash** file
```bash
roslaunch smb_gazebo exercise_1.launch
```
Else, we can also run the launch file by specifying the path to it
```bash
roslaunch [PATH to launch file]
```
For example, if the *exercise_1.launch* is in the same directory, then:
```bash
roslaunch exercise_1.launch
```
After running this launch file, we should see something like this.
![SMB Gazebo Simulation](https://raw.githubusercontent.com/Gill-Singh-A/Induction_Y22/Gill/Assignments/ROS/Exercise_1/assets/images/simulation_with_world.png)
# setup.bash
To do the setup for all this, just run the **setup.bash** file
```bash
chmod +x setup.bash
./setup.bash
```
To run the simulation, just run the **run.sh** file:
```bash
chmod +x run.sh
./run.sh
```