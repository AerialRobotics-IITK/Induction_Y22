cmake_minimum_required(VERSION 3.0.2)
project(square_path)
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  mavros_msgs
  roscpp
)
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES square_path
  CATKIN_DEPENDS geometry_msgs mavros_msgs roscpp
  DEPENDS system_lib
)
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)
add_executable(
  ${PROJECT_NAME} 
    src/square_path.cpp
)
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
install(FILES
  ${PROJECT_NAME}
    launch/square_path.launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)