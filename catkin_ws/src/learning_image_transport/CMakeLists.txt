cmake_minimum_required(VERSION 3.0.2)
project(learning_image_transport)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  rospy
  sensor_msgs
  std_msgs
)
catkin_package()
find_package(OpenCV REQUIRED)  
# add the publisher example  
#add_executable(my_publisher src/my_publisher.cpp)  

#target_link_libraries(my_publisher ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})  

# add the subscriber example  
#add_executable(my_subscriber src/my_subscriber.cpp)  
#target_link_libraries(my_subscriber ${catkin_LIBRARIES} ${OpenCV_LIBRARIES}) 
