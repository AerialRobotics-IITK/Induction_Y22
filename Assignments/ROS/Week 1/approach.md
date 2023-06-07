
### Task 1: SMB Workspace

  

- download the zip file form the link mentioned

  

- unzip the file in a created ~/git folder

  

- next create a workspace by the name of smb_ws, create a src folder too 

  

- navigate to the created workspace and use ```catkin build``` . use ``` source devel/setup.bash ``` after building the workspace 
 

- create a symlink as mentioned using the following command from the smb_gazebo src folder  
 ``` ln -s ~git/smb_common/smb_gazebo ```
 - build smb_gazebo using ```catkin build ```
 
 ###  Task 2: Launch simulation
- from the smb_ws directory run ``` roslaunch smb_gazebo smb_gazebo.launch```
- this will launch gazebo. open a fresh terminal and run commands such as  
``` 
rosnode list 
rosnode topic 
rostopic echo [TOPIC] 
rostopic hz [TOPIC] 
rqt_graph
```
### Task 3: Command Velocity using terminal 

- use the topic /cmd_vel and the command `rostopic pub `

- ```rostopic  pub /cmd_vel geometry_msgs/Twist  '[x,y,z]' '[ang.x,ang.y,ang.z]' ``` where x,y,z and ang.x,ang.y,ang.z are float/int values of resp. veocities 

### Task 4: Using teleop_twist_keyboard
- firstly clone the repsoitory onto the local ~/git folder 

- create a symlink between the smb_ws/src file and the git repo 

- build the repo in our smb workspace 

- launch smb_gazebo first, then in a new termianl use the command `rosrun teleop_twist_keyboard telop_twistkeyboard.py` to launch the keyboard.

- use the keyboard as directed in the terminal 

### Task 5: 
- go to the smb_gazebo directory and make a new launch file 
- the file is attached herewith the code 
- launch gazebo using the newly written launch file(this part didnt work correctly for me, still figuring it out ) 
