cmake_minimum_required(VERSION 2.8.3)
project(pix_can)

find_package(PCL REQUIRED)

set(autoware_build_flags_DIR /home/wmm/autoware-1.13.0/build/autoware_build_flags/catkin_generated/installspace/autoware_build_flagsConfig.cmake )

#find_package(autoware_build_flags REQUIRED)

set(autoware_msgs_DIR /home/wmm/autoware-1.13.0/build/autoware_msgs/catkin_generated/installspace/autoware_msgsConfig.cmake )

#find_package(autoware_msgs REQUIRED)

set(autoware_config_msgs_DIR /home/wmm/autoware-1.13.0/build/autoware_config_msgs/catkin_generated/installspace/autoware_config_msgsConfig.cmake)

#find_package(autoware_config_msgs REQUIRED)

set(tablet_socket_msgs_DIR /home/wmm/autoware-1.13.0/build/tablet_socket_msgs/catkin_generated/installspace/tablet_socket_msgsConfig.cmake)

#find_package(tablet_socket_msgs REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  message_generation
  std_msgs
  tf
  tf2
  geometry_msgs
  pcl_ros
  pcl_conversions
  sensor_msgs
  autoware_msgs
  autoware_can_msgs
  autoware_config_msgs
  amathutils_lib
  tablet_socket_msgs
#  autoware_health_checker
  rostest
  rosunit
  libwaypoint_follower
#  astar_search
)

## Generate messages in the 'msg' folder
add_message_files(
  DIRECTORY msg
  FILES
    CANTestInfo.msg
)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
        INCLUDE_DIRS include
#        LIBRARIES libwaypoint_follower
        CATKIN_DEPENDS roscpp
        message_runtime
        std_msgs
        tf
        tf2
        geometry_msgs
        autoware_msgs
        autoware_can_msgs
        autoware_config_msgs
        amathutils_lib
        pcl_ros
        pcl_conversions
        sensor_msgs
        tablet_socket_msgs
        autoware_health_checker
        gazebo_msgs
        libwaypoint_follower
        astar_search
)

###########
## Build ##
###########

SET(CMAKE_CXX_FLAGS "-O2 -g -Wall ${CMAKE_CXX_FLAGS}")

include_directories(
        include
        /usr/include
        ${autoware_config_msgs_INCLUDE_DIRS}
        ${autoware_msgs_INCLUDE_DIRS}
        ${autoware_can_msgs_INCLUDE_DIRS}
        ${tablet_socket_msgs_INCLUDE_DIRS}
        ${catkin_INCLUDE_DIRS}
)

#add_executable(pix_can 
#  nodes/pcaneventwrite.cpp nodes/libpcanbasic.c nodes/pcaninfo.c nodes/pcanlog.c nodes/pcbtrace.c nodes/pcblog.c nodes/pcbcore.c  nodes/libpcan.c nodes/libpcanfd.c
#)

add_executable(pix_can_write 
  nodes/pix_can_write.cpp
  nodes/vehicle_speed_control.cpp
)

target_link_libraries(pix_can_write ${catkin_LIBRARIES} /usr/lib/libpcanbasic.so)
add_dependencies(pix_can_write
        ${catkin_EXPORTED_TARGETS})


add_executable(pix_can_read 
  nodes/pix_can_read.cpp
  nodes/vehicle_speed_control.cpp
)

target_link_libraries(pix_can_read ${catkin_LIBRARIES} /usr/lib/libpcanbasic.so)
add_dependencies(pix_can_read
        ${catkin_EXPORTED_TARGETS})



#############
## Install ##
#############

install(TARGETS pix_can_write pix_can_read
        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY launch/
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
        PATTERN ".svn" EXCLUDE
)

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_executables.html
# install(TARGETS ${PROJECT_NAME}_node
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark libraries for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_libraries.html
# install(TARGETS ${PROJECT_NAME}
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_docking.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
