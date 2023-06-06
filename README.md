# ROS_Exercise_1
## 1.Setup the SMB workspace:  
open terminal
make a directory named git in home directory for cloned git repositories  
After downloading smb_common zipped folder  

```
mkdir -p ~/git 
unzip ~/Downloads/smb_common.zip ~git/
```  

Now, make a ROS workspace for smb  

```
mkdir -p ~/smb_ws/src
cd smb_ws
catkin build
source devel/setup.bash
cd src
ln -s ~/git/smb_common/smb_gazebo
ln -s ~/git/smb_common/smb_control
ln -s ~/git/smb_common/smb_description
cd ..
catkin build smb_gazebo
source devel/setup.bash
```  

smb_control and smb_description are dependencies for smb_gazebo so you have to create symlinks for all three  
and when you compile smb_gazebo, all three get compiled  
Now, we will specifically launch smb_gazebo nodes  

## 2.Running the simulation and seeking info  

`roslaunch smb_gazebo smb_gazebo.launch`  

This should open up a gazebo simulation window with a bot in the middle  
To list out nodes, topics and info, open a new terminal window  

```
rosnode list
rostopic list
rostopic echo [TOPIC]
rostopic hz [TOPIC]
rqt_graph
'''  

## 3.Command a velocity  
To command a desired velocity to the robot in the simulation, we directly publish a message with the velocity command to the topic "/cmd_vel",  

```  
rostopic pub /cmd_vel geometry_msgs/Twist '[<linear.x>, <linear.y>, <linear.z>]' '[<angular.x>, <angular.y>, <angular.z>]'  
```  

This should make the robot move as per you commands  

## 4.Using teleop_twist_keyboard controller  
Now, to setup the controller get the resources by cloning repo  

'git clone https://github.com/ros-teleop/teleop_twist_keyboard.git'  

To build the repo in our smb workspace, open terminal 

'''
cd smb_ws/src  
ln -s ~/git/teleop_twist_keyboard  
cd ..
catkin build
source devel/setup.bash  
'''  

to use the controller, seperately launch smb_gazebo and run teleop_twist_keyboard nodes in different terminal windows  
here smb_gazebo is run using launch files as it has multiple nodes and configurations, but teleop has just one so it is to be run differently,  

'''
roslaunch smb_gazebo smb_gazebo.launch
''' 

in a new window,  

`rosrun teleop_twist_keyboard teleop_twist_keyboard.py`    

now, you should foolow instructions on terminal  

## 5.Make a new launch file to change arguments and integrate controller  

To make a new launch file as per given commands,  

```  
cd ~/smb_ws/src/smb_gazebo/launch
touch smb_gazebo_add.launch
code smb_gazebo_add.launch  
```  

in your code editor write the following,  

```  
<?xml version="1.0" encoding="utf-8"?>
<launch>
    <include file="$(find smb_gazebo) smb_gazebo.launch">
        <arg name='world_file' value="/usr/share/gazebo-11/worlds/robocup14_spl_field.world"/>
    </include>
    <node name='teleop_twist_keyboard' pkg="teleop_twist_keyboard" type='teleop_twist_keyboard.py' output="screen"/> # select "screen" for console
</launch>  
```  

now launch the smb_gazebo package with new launch file  smb_gazebo_add.launch
you will see a new world and will be abble to control the robot using teleop













