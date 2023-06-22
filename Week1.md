---


---

<h1 id="week1">WEEK1</h1>
<p>We have to launch a simulation and then command a robot to move with a commanded velocity, and use keyboard to control it</p>
<h2 id="create-workspace">Create Workspace</h2>
<p>This folder will contain all ROS packages and will contain 2 sub-folders:<br>
smb_ws and teleop_twist_keyboard</p>
<pre><code>mkdir Workspaces
cd Workspaces
mkdir -p smb_ws/src/
mkdir -p teleop_twist_keyboard/src/
</code></pre>
<p>Following the instructions of the exercise, to install and unzip the folder.</p>
<pre><code>mkdir Git
cd Git
wget https://ethz.ch/content/dam/ethz/special-interest/mavt/robotics-n-intelligent-systems/rsl-dam/ROS2021/lec1/smb_common.zip
unzip smb_common.zip 
</code></pre>
<p>Creating the symlink</p>
<pre><code>ln -s ~/Git/smb_common/* ~/Workspaces/smb_ws/src/
</code></pre>
<p>Compiling via catkin</p>
<pre><code>cd ~/Workspaces/smb_ws/
catkin build
source devel/setup.bash
</code></pre>
<p>Launching Simulations</p>
<pre><code>roslaunch smb_gazebo smb_gazebo.launch
</code></pre>
<p>This launches the simulation<br>
<img src="https://i.imgur.com/ZRYKXrE.png" alt="enter image description here"><br>
Inspecting the Nodes, lists, their information and rates can be inspected via the commands given in the exercise page<br>
rosnode list<br>
rostopic list<br>
rostopic echo /Topic</p>
<p>Whole graph can be seen via</p>
<pre><code>rqt_graph
</code></pre>
<p>which gives<br>
<img src="https://i.imgur.com/DjuL1To.png" alt="enter image description here"></p>
<h1 id="commanding-the-bot">Commanding the bot</h1>
<p>rostopic pub [TOPIC] [TYPE] [DATA] is to be used</p>
<pre><code>rostopic pub -r 10 /cmd_vel geometry_msgs/Twist  '{linear:  {x: 0.1, y: 0.0, z: 0.0}, angular: {x: 0.0,y: 0.0,z: 0.0}}'
</code></pre>
<h1 id="setup-teleop_twist_keyboard-to-control-using-the-keyboard.">setup teleop_twist_keyboard to control using the keyboard.</h1>
<pre><code>cd ~/Git/
git clone https://github.com/ros-teleop/teleop_twist_keyboard.git
cd ~/Workspaces/teleop_twist_keyboard/
catkin build
source devel/setup.bash
</code></pre>
<p>running teleop_twist_keyboard</p>
<pre><code>cd ~/Workspaces/teleop_twist_keyboard/src/teleop_twist_keyboard
python teleop_twist_keyboard.py
</code></pre>
<p>then we can control the smb via keyboard<br>
<img src="https://i.imgur.com/qW3gWg9.png" alt="enter image description here"></p>
<h1 id="the-launch-file">The Launch File</h1>
<p>We write the launch file in xml</p>
<pre><code>&lt;?xml version="1.0" encoding="utf-8"?&gt;
&lt;launch&gt;
    &lt;arg name="world_name" default="big_map_summer_school" /&gt;
    &lt;include file="~/Git/smb_common/smb_gazebo/launch/smb_gazebo.launch"&gt;
    	&lt;arg name="world" value="~/Git/smb_common/smb_gazebo/worlds/big_map_summer_school.world" /&gt;
    &lt;/include&gt;
    &lt;node name="teleop_twist_keyboard" pkg="teleop_twist_keyboard" type="teleop_twist_keyboard.py" /&gt;
&lt;/launch&gt;
</code></pre>
<p>moving this file into ~/Workspaces/smb_ws/src/smb_gazebo/launch and</p>
<pre><code>	cd ~/Workspaces/smb_ws/src/smb_gazebo/launch
	roslaunch ex1launch.launch
</code></pre>
<p>launches the required simulation</p>

