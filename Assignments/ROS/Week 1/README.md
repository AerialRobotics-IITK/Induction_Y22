## Week 1 Assignment
- <a href="https://ethz.ch/content/dam/ethz/special-interest/mavt/robotics-n-intelligent-systems/rsl-dam/ROS2021/lec1/Exercise%20Session%201.pdf">Description</a>
- <a href="https://www.youtube.com/watch?v=aL7zLnaEdAg">Lecture Video</a>
- <a href="https://ethz.ch/content/dam/ethz/special-interest/mavt/robotics-n-intelligent-systems/rsl-dam/ROS2021/lec1/ROS%20Course%20Slides%20Course%201.pdf">Lecture Slides</a>
- Most details are commented in setup.bash but here we go
- first we download the exercise file from the site in ~/Git 
- then we unzip it right there using


- '''bash
-       unzip smb_common.zip
- '''
- create a symlink between the unzipped folder and ~/Workspaces/smb_ws/src 
- 
-'''bash
        ln -s ~/Git/smb_common ~/Workspaces/smb_common/src
 '''
- compile the package by
- 
-  '''bash
-     catkin build
-  '''
-  this builds all the packages present in the directory
-  if the build fails it is possible that hector plugins are missing install them using
-  
-  '''bash
-       sudo apt-get install ros-noetic-hector-gazebo-plugins
-  '''
-  run the package using
-  
-  '''bash
-         roslaunch smb_gazebo smb_gazebo.launch
-  '''
-  complete the other tasks using
-  
-  '''bash
-        rosnode list
        rostopic list
        rostopic echo [TOPIC]
        rostopic hz [TOPIC]
        rqt_graph
-  '''
-
-   publish to a topic directly using "pub"
-   '''bash
-         rostopic pub /cmd_vel geometry_msgs/Twist '[0.5,0,0]' '[0,0,0]'
-   '''
-   here the syntax goes like rostopic pub [TOPIC] [DATA TYPE] [DATA]
-   
-   
-   for the next part I kinda messed up the compile from source part and installed it directly so i am unable to describe that process
-   teleop runs by--
-   '''bash
-                rosrun teleop_twist_keyboard teleop_twist_keyboard.py
-   '''
-   final launch file has been uploaded along with the screenshot
