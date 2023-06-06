# download the files in ~/Git folder
unzip smb_common
rm smb_common.zip (optional)
ln -s ~/Git/smb_common ~/Workspaces/smb_ws/src (it is possible that the directories workspace or src dont exist then just create them using mkdir)
#symlink created
#compilation
cd ~/Workspaces
catkin build
# catkin build if used without any further arguments just builds all the packages present in the directory
# here it is possible that the build fails showing an error of missing hector_plugins in that case
sudo apt-get install ros-noetic-hector-gazebo-plugins
# this should make it work

roslaunch smb_gazebo smb_gazebo.launch
# this should start the simulation in gazebo if not, check if the error shows of a missing velodyne_description file if yes
sudo apt-get install ros-noetic-velodyne-description
# this should do the trick
# now that our simulation is set-up

# we move on the other tasks
#open a new terminal and just run these, not a big deal.
rosnode list
rostopic list
rostopic echo [TOPIC]
rostopic hz [TOPIC]
rqt_graph

# now publishing to the ropic can be a bit confusing as the names of some topics are similar
rostopic pub /cmd_vel geometry_msgs/Twist '[0.5,0,0]' '[0,0,0]'
# this will publish the values in square brackets as separate velocity parameters along different axes
# here I did not read the source part and directly installed teleop 
rosrun teleop_twist_keyboard teleop_twist_keyboard.py
# launch file has been uploaded as a PR the file spawns robocup 14 field as a world
