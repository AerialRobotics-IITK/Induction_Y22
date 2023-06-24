cmake_minimum_required(VERSION 3.0.2)
project(smb_highlevel_controller)
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  sensor_msgs
  std_msgs
)
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS geometry_msgs roscpp rospy sensor_msgs std_msgs
)
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)
add_executable(
  ${PROJECT_NAME}
    src/smb_highlevel_controller.cpp
)
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
install(FILES
  ${PROJECT_NAME}
    launch/smb_highlevel_controller.launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)