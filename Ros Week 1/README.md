# Task 1
## Setting up the SMB Simulation:
Firstly, we need to install some packages in order to run our code :

``` 
sudo apt install -y ros-noetic-hector-gazebo-plugins ros-noetic-velodyne ros-noetic-velodyne-description ros-noetic-velodyne-gazebo-plugins ros-noetic-pointcloud-to-laserscan ros-noetic-twist-mux 
```

This will install hector gazebo plugins, velodyne, pointcloud to laserscan and twist mux

Next,
We download the zip file in the git directory and unzip it.

The task says :Navigate into ~/Workspaces/smb_ws/src and make a symlink.
So we create those directories using:

```
cd Workspace
mkdir -p smb_ws/src/
```

In task 4, we also need teleop_twist_keyboard so we make its directory in Workspace too

```
mkdir -p teleop_twist_keyboard/src/
```

According to task 4, we clone the repo to the folder git

```
cd ..
cd ..
cd git

git clone https://github.com/ros-teleop/teleop_twist_keyboard.git
```

# Now we create the symlink

```
ln -s ~/git/smb_common/* ~/Workspace/smb_ws/src/

ln -s ~/git/teleop_twist_keyboard/ ~/Workspace/teleop_twist_keyboard/src/
```


what we have created right now is basically a shortcut to another file. Or more like a pointer to another file.

# Next we have to Compile the smb_gazebo package with catkin

```
cd ~/Workspace/smb_ws
catkin_make

source devel/setup.bash
```

# Task 2: Launch

```
roslaunch smb_gazebo smb_gazebo.launch
```
 
We open a new window and type in the following

```
rosnode list 
```

This returns the list of all nodes in the ROS network

```
rostopic list
rostopic echo /tf
rostopic hz /tf
```


# Task 3: To command desired velocity 


```
rostopic pub /cmd_vel geometry_msgs/Twist '{linear: {x: 0.5, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 0.1}}'
```


# For Task 4
 ```
 cd Workspace
 cd teleop_twist_keyboard 
 catkin_make

 source devel/setup.bash

 cd ~/Workspace/teleop_twist_keyboard/src/teleop_twist_keyboard

python3 teleop_twist_keyboard.py
rosrun teleop_twist_keyboard teleop_twist_keyboard.py
```


# Task 5: Writing the launch file


```
<?xml version="1.0" encoding="utf-8"?>
<launch>
  <include file="$(find smb_gazebo)/launch/smb_gazebo.launch">
    <arg name="world_file" value="/usr/share/gazebo-11/worlds/worlds/robocup14_spl_field.world"/>
  </include>
     <node name='teleop_twist_keyboard'
   pkg="teleop_twist_keyboard" type='teleop_twist_keyboard.py' 
   output="screen"/> 
</launch> 
```



