cmake_minimum_required(VERSION 3.0.2)
project(learning_image_transport)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
)
catkin_package()
find_package(OpenCV REQUIRED)

include_directories(
  include ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS}
)

link_directories(
  ${catkin_LIB_DIRS} 
  lib
)  
add_executable(detectslot src/detectslot.cpp)  

target_link_libraries(detectslot ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})   

# add the subscriber example  
#add_executable(my_subscriber src/my_subscriber.cpp)  
#target_link_libraries(my_subscriber ${catkin_LIBRARIES} ${OpenCV_LIBRARIES}) 
