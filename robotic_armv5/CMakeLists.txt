cmake_minimum_required(VERSION 2.8.3)

project(robotic_armv5)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  control_msgs
  controller_manager
  message_generation
  roscpp
  rospy
  std_msgs
  std_srvs
  trajectory_msgs
  visualization_msgs
  geometry_msgs
  urdf
  xacro
  message_generation
)

add_service_files(
   FILES
   Floats_array.srv
#   Service2.srv
)

generate_messages(
   DEPENDENCIES
   std_msgs #   control_msgs#     trajectory_msgs#   visualization_msgs
)

catkin_package(CATKIN_DEPENDS
  actionlib
  control_msgs
  controller_manager
  geometry_msgs
  roscpp
  rospy
  std_msgs
  std_srvs
  trajectory_msgs
  visualization_msgs
  message_runtime
)

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

find_package(roslaunch)

foreach(dir config launch meshes urdf)
	install(DIRECTORY ${dir}/
		DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach(dir)
