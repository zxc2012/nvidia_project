# generated from catkin/cmake/template/pkgConfig.cmake.in

# append elements to a list and remove existing duplicates from the list
# copied from catkin/cmake/list_append_deduplicate.cmake to keep pkgConfig
# self contained
macro(_list_append_deduplicate listname)
  if(NOT "${ARGN}" STREQUAL "")
    if(${listname})
      list(REMOVE_ITEM ${listname} ${ARGN})
    endif()
    list(APPEND ${listname} ${ARGN})
  endif()
endmacro()

# append elements to a list if they are not already in the list
# copied from catkin/cmake/list_append_unique.cmake to keep pkgConfig
# self contained
macro(_list_append_unique listname)
  foreach(_item ${ARGN})
    list(FIND ${listname} ${_item} _index)
    if(_index EQUAL -1)
      list(APPEND ${listname} ${_item})
    endif()
  endforeach()
endmacro()

# pack a list of libraries with optional build configuration keywords
# copied from catkin/cmake/catkin_libraries.cmake to keep pkgConfig
# self contained
macro(_pack_libraries_with_build_configuration VAR)
  set(${VAR} "")
  set(_argn ${ARGN})
  list(LENGTH _argn _count)
  set(_index 0)
  while(${_index} LESS ${_count})
    list(GET _argn ${_index} lib)
    if("${lib}" MATCHES "^(debug|optimized|general)$")
      math(EXPR _index "${_index} + 1")
      if(${_index} EQUAL ${_count})
        message(FATAL_ERROR "_pack_libraries_with_build_configuration() the list of libraries '${ARGN}' ends with '${lib}' which is a build configuration keyword and must be followed by a library")
      endif()
      list(GET _argn ${_index} library)
      list(APPEND ${VAR} "${lib}${CATKIN_BUILD_CONFIGURATION_KEYWORD_SEPARATOR}${library}")
    else()
      list(APPEND ${VAR} "${lib}")
    endif()
    math(EXPR _index "${_index} + 1")
  endwhile()
endmacro()

# unpack a list of libraries with optional build configuration keyword prefixes
# copied from catkin/cmake/catkin_libraries.cmake to keep pkgConfig
# self contained
macro(_unpack_libraries_with_build_configuration VAR)
  set(${VAR} "")
  foreach(lib ${ARGN})
    string(REGEX REPLACE "^(debug|optimized|general)${CATKIN_BUILD_CONFIGURATION_KEYWORD_SEPARATOR}(.+)$" "\\1;\\2" lib "${lib}")
    list(APPEND ${VAR} "${lib}")
  endforeach()
endmacro()


if(pix_can_CONFIG_INCLUDED)
  return()
endif()
set(pix_can_CONFIG_INCLUDED TRUE)

# set variables for source/devel/install prefixes
if("FALSE" STREQUAL "TRUE")
  set(pix_can_SOURCE_PREFIX /home/nvidia/pixcan/src/pix_can)
  set(pix_can_DEVEL_PREFIX /home/nvidia/pixcan/devel)
  set(pix_can_INSTALL_PREFIX "")
  set(pix_can_PREFIX ${pix_can_DEVEL_PREFIX})
else()
  set(pix_can_SOURCE_PREFIX "")
  set(pix_can_DEVEL_PREFIX "")
  set(pix_can_INSTALL_PREFIX /home/nvidia/pixcan/install)
  set(pix_can_PREFIX ${pix_can_INSTALL_PREFIX})
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "WARNING: package 'pix_can' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  message("${_msg}")
endif()

# flag project as catkin-based to distinguish if a find_package()-ed project is a catkin project
set(pix_can_FOUND_CATKIN_PROJECT TRUE)

if(NOT "include " STREQUAL " ")
  set(pix_can_INCLUDE_DIRS "")
  set(_include_dirs "include")
  if(NOT " " STREQUAL " ")
    set(_report "Check the issue tracker '' and consider creating a ticket if the problem has not been reported yet.")
  elseif(NOT " " STREQUAL " ")
    set(_report "Check the website '' for information and consider reporting the problem.")
  else()
    set(_report "Report the problem to the maintainer 'wmm <wmm@todo.todo>' and request to fix the problem.")
  endif()
  foreach(idir ${_include_dirs})
    if(IS_ABSOLUTE ${idir} AND IS_DIRECTORY ${idir})
      set(include ${idir})
    elseif("${idir} " STREQUAL "include ")
      get_filename_component(include "${pix_can_DIR}/../../../include" ABSOLUTE)
      if(NOT IS_DIRECTORY ${include})
        message(FATAL_ERROR "Project 'pix_can' specifies '${idir}' as an include dir, which is not found.  It does not exist in '${include}'.  ${_report}")
      endif()
    else()
      message(FATAL_ERROR "Project 'pix_can' specifies '${idir}' as an include dir, which is not found.  It does neither exist as an absolute directory nor in '\${prefix}/${idir}'.  ${_report}")
    endif()
    _list_append_unique(pix_can_INCLUDE_DIRS ${include})
  endforeach()
endif()

set(libraries "")
foreach(library ${libraries})
  # keep build configuration keywords, target names and absolute libraries as-is
  if("${library}" MATCHES "^(debug|optimized|general)$")
    list(APPEND pix_can_LIBRARIES ${library})
  elseif(${library} MATCHES "^-l")
    list(APPEND pix_can_LIBRARIES ${library})
  elseif(${library} MATCHES "^-")
    # This is a linker flag/option (like -pthread)
    # There's no standard variable for these, so create an interface library to hold it
    if(NOT pix_can_NUM_DUMMY_TARGETS)
      set(pix_can_NUM_DUMMY_TARGETS 0)
    endif()
    # Make sure the target name is unique
    set(interface_target_name "catkin::pix_can::wrapped-linker-option${pix_can_NUM_DUMMY_TARGETS}")
    while(TARGET "${interface_target_name}")
      math(EXPR pix_can_NUM_DUMMY_TARGETS "${pix_can_NUM_DUMMY_TARGETS}+1")
      set(interface_target_name "catkin::pix_can::wrapped-linker-option${pix_can_NUM_DUMMY_TARGETS}")
    endwhile()
    add_library("${interface_target_name}" INTERFACE IMPORTED)
    if("${CMAKE_VERSION}" VERSION_LESS "3.13.0")
      set_property(
        TARGET
        "${interface_target_name}"
        APPEND PROPERTY
        INTERFACE_LINK_LIBRARIES "${library}")
    else()
      target_link_options("${interface_target_name}" INTERFACE "${library}")
    endif()
    list(APPEND pix_can_LIBRARIES "${interface_target_name}")
  elseif(TARGET ${library})
    list(APPEND pix_can_LIBRARIES ${library})
  elseif(IS_ABSOLUTE ${library})
    list(APPEND pix_can_LIBRARIES ${library})
  else()
    set(lib_path "")
    set(lib "${library}-NOTFOUND")
    # since the path where the library is found is returned we have to iterate over the paths manually
    foreach(path /home/nvidia/pixcan/install/lib;/home/nvidia/autoware-bleeding/install/ymc/lib;/home/nvidia/autoware-bleeding/install/xsens_driver/lib;/home/nvidia/autoware-bleeding/install/wf_simulator/lib;/home/nvidia/autoware-bleeding/install/lattice_planner/lib;/home/nvidia/autoware-bleeding/install/waypoint_planner/lib;/home/nvidia/autoware-bleeding/install/waypoint_maker/lib;/home/nvidia/autoware-bleeding/install/way_planner/lib;/home/nvidia/autoware-bleeding/install/vlg22c_cam/lib;/home/nvidia/autoware-bleeding/install/vision_ssd_detect/lib;/home/nvidia/autoware-bleeding/install/vision_segment_enet_detect/lib;/home/nvidia/autoware-bleeding/install/vision_lane_detect/lib;/home/nvidia/autoware-bleeding/install/vision_darknet_detect/lib;/home/nvidia/autoware-bleeding/install/vision_beyond_track/lib;/home/nvidia/autoware-bleeding/install/vel_pose_diff_checker/lib;/home/nvidia/autoware-bleeding/install/vehicle_socket/lib;/home/nvidia/autoware-bleeding/install/vehicle_sim_model/lib;/home/nvidia/autoware-bleeding/install/vehicle_model/lib;/home/nvidia/autoware-bleeding/install/vehicle_gazebo_simulation_launcher/lib;/home/nvidia/autoware-bleeding/install/vehicle_gazebo_simulation_interface/lib;/home/nvidia/autoware-bleeding/install/vehicle_engage_panel/lib;/home/nvidia/autoware-bleeding/install/vehicle_description/lib;/home/nvidia/autoware-bleeding/install/trafficlight_recognizer/lib;/home/nvidia/autoware-bleeding/install/op_utilities/lib;/home/nvidia/autoware-bleeding/install/op_simulation_package/lib;/home/nvidia/autoware-bleeding/install/op_local_planner/lib;/home/nvidia/autoware-bleeding/install/op_global_planner/lib;/home/nvidia/autoware-bleeding/install/lidar_kf_contour_track/lib;/home/nvidia/autoware-bleeding/install/op_ros_helpers/lib;/home/nvidia/autoware-bleeding/install/ff_waypoint_follower/lib;/home/nvidia/autoware-bleeding/install/dp_planner/lib;/home/nvidia/autoware-bleeding/install/op_simu/lib;/home/nvidia/autoware-bleeding/install/op_planner/lib;/home/nvidia/autoware-bleeding/install/op_utility/lib;/home/nvidia/autoware-bleeding/install/lidar_euclidean_cluster_detect/lib;/home/nvidia/autoware-bleeding/install/vector_map_server/lib;/home/nvidia/autoware-bleeding/install/road_occupancy_processor/lib;/home/nvidia/autoware-bleeding/install/costmap_generator/lib;/home/nvidia/autoware-bleeding/install/object_map/lib;/home/nvidia/autoware-bleeding/install/naive_motion_predict/lib;/home/nvidia/autoware-bleeding/install/lanelet_aisan_converter/lib;/home/nvidia/autoware-bleeding/install/map_file/lib;/home/nvidia/autoware-bleeding/install/libvectormap/lib;/home/nvidia/autoware-bleeding/install/lane_planner/lib;/home/nvidia/autoware-bleeding/install/imm_ukf_pda_track/lib;/home/nvidia/autoware-bleeding/install/decision_maker/lib;/home/nvidia/autoware-bleeding/install/vector_map/lib;/home/nvidia/autoware-bleeding/install/vector_map_msgs/lib;/home/nvidia/autoware-bleeding/install/vectacam/lib;/home/nvidia/autoware-bleeding/install/udon_socket/lib;/home/nvidia/autoware-bleeding/install/twist_generator/lib;/home/nvidia/autoware-bleeding/install/twist_gate/lib;/home/nvidia/autoware-bleeding/install/twist_filter/lib;/home/nvidia/autoware-bleeding/install/twist2odom/lib;/home/nvidia/autoware-bleeding/install/tablet_socket/lib;/home/nvidia/autoware-bleeding/install/runtime_manager/lib;/home/nvidia/autoware-bleeding/install/mqtt_socket/lib;/home/nvidia/autoware-bleeding/install/tablet_socket_msgs/lib;/home/nvidia/autoware-bleeding/install/state_machine_lib/lib;/home/nvidia/autoware-bleeding/install/sound_player/lib;/home/nvidia/autoware-bleeding/install/sick_lms5xx/lib;/home/nvidia/autoware-bleeding/install/sick_ldmrs_tools/lib;/home/nvidia/autoware-bleeding/install/sick_ldmrs_driver/lib;/home/nvidia/autoware-bleeding/install/sick_ldmrs_msgs/lib;/home/nvidia/autoware-bleeding/install/sick_ldmrs_description/lib;/home/nvidia/autoware-bleeding/install/points2image/lib;/home/nvidia/autoware-bleeding/install/rosinterface/lib;/home/nvidia/autoware-bleeding/install/rosbag_controller/lib;/home/nvidia/autoware-bleeding/install/pure_pursuit/lib;/home/nvidia/autoware-bleeding/install/points_preprocessor/lib;/home/nvidia/autoware-bleeding/install/mpc_follower/lib;/home/nvidia/autoware-bleeding/install/lidar_localizer/lib;/home/nvidia/autoware-bleeding/install/emergency_handler/lib;/home/nvidia/autoware-bleeding/install/autoware_health_checker/lib;/home/nvidia/autoware-bleeding/install/as/lib;/home/nvidia/autoware-bleeding/install/ros_observer/lib;/home/nvidia/autoware-bleeding/install/roi_object_filter/lib;/home/nvidia/autoware-bleeding/install/range_vision_fusion/lib;/home/nvidia/autoware-bleeding/install/pos_db/lib;/home/nvidia/autoware-bleeding/install/points_downsampler/lib;/home/nvidia/autoware-bleeding/install/pixel_cloud_fusion/lib;/home/nvidia/autoware-bleeding/install/pcl_omp_registration/lib;/home/nvidia/autoware-bleeding/install/pc2_downsampler/lib;/home/nvidia/autoware-bleeding/install/oculus_socket/lib;/home/nvidia/autoware-bleeding/install/obj_db/lib;/home/nvidia/autoware-bleeding/install/nmea_navsat/lib;/home/nvidia/autoware-bleeding/install/ndt_tku/lib;/home/nvidia/autoware-bleeding/install/ndt_gpu/lib;/home/nvidia/autoware-bleeding/install/ndt_cpu/lib;/home/nvidia/autoware-bleeding/install/multi_lidar_calibrator/lib;/home/nvidia/autoware-bleeding/install/mrt_cmake_modules/lib;/home/nvidia/autoware-bleeding/install/microstrain_driver/lib;/home/nvidia/autoware-bleeding/install/memsic_imu/lib;/home/nvidia/autoware-bleeding/install/marker_downsampler/lib;/home/nvidia/autoware-bleeding/install/map_tools/lib;/home/nvidia/autoware-bleeding/install/map_tf_generator/lib;/home/nvidia/autoware-bleeding/install/log_tools/lib;/home/nvidia/autoware-bleeding/install/lidar_shape_estimation/lib;/home/nvidia/autoware-bleeding/install/lidar_point_pillars/lib;/home/nvidia/autoware-bleeding/install/lidar_naive_l_shape_detect/lib;/home/nvidia/autoware-bleeding/install/lidar_fake_perception/lib;/home/nvidia/autoware-bleeding/install/lidar_apollo_cnn_seg_detect/lib;/home/nvidia/autoware-bleeding/install/libwaypoint_follower/lib;/home/nvidia/autoware-bleeding/install/lgsvl_simulator_bridge/lib;/home/nvidia/autoware-bleeding/install/lanelet2_extension/lib;/home/nvidia/autoware-bleeding/install/lanelet2_validation/lib;/home/nvidia/autoware-bleeding/install/lanelet2_examples/lib;/home/nvidia/autoware-bleeding/install/lanelet2_python/lib;/home/nvidia/autoware-bleeding/install/lanelet2_routing/lib;/home/nvidia/autoware-bleeding/install/lanelet2_traffic_rules/lib;/home/nvidia/autoware-bleeding/install/lanelet2_projection/lib;/home/nvidia/autoware-bleeding/install/lanelet2_maps/lib;/home/nvidia/autoware-bleeding/install/lanelet2_io/lib;/home/nvidia/autoware-bleeding/install/lanelet2_core/lib;/home/nvidia/autoware-bleeding/install/kvaser/lib;/home/nvidia/autoware-bleeding/install/kitti_launch/lib;/home/nvidia/autoware-bleeding/install/kitti_player/lib;/home/nvidia/autoware-bleeding/install/kitti_box_publisher/lib;/home/nvidia/autoware-bleeding/install/javad_navsat_driver/lib;/home/nvidia/autoware-bleeding/install/integrated_viewer/lib;/home/nvidia/autoware-bleeding/install/image_processor/lib;/home/nvidia/autoware-bleeding/install/hokuyo/lib;/home/nvidia/autoware-bleeding/install/graph_tools/lib;/home/nvidia/autoware-bleeding/install/gnss_localizer/lib;/home/nvidia/autoware-bleeding/install/gnss/lib;/home/nvidia/autoware-bleeding/install/glviewer/lib;/home/nvidia/autoware-bleeding/install/gazebo_world_description/lib;/home/nvidia/autoware-bleeding/install/gazebo_imu_description/lib;/home/nvidia/autoware-bleeding/install/gazebo_camera_description/lib;/home/nvidia/autoware-bleeding/install/garmin/lib;/home/nvidia/autoware-bleeding/install/freespace_planner/lib;/home/nvidia/autoware-bleeding/install/fastvirtualscan/lib;/home/nvidia/autoware-bleeding/install/ekf_localizer/lib;/home/nvidia/autoware-bleeding/install/ds4_msgs/lib;/home/nvidia/autoware-bleeding/install/ds4_driver/lib;/home/nvidia/autoware-bleeding/install/detected_objects_visualizer/lib;/home/nvidia/autoware-bleeding/install/decision_maker_panel/lib;/home/nvidia/autoware-bleeding/install/data_preprocessor/lib;/home/nvidia/autoware-bleeding/install/custom_msgs/lib;/home/nvidia/autoware-bleeding/install/carla_autoware_bridge/lib;/home/nvidia/autoware-bleeding/install/calibration_publisher/lib;/home/nvidia/autoware-bleeding/install/autoware_system_msgs/lib;/home/nvidia/autoware-bleeding/install/autoware_rviz_plugins/lib;/home/nvidia/autoware-bleeding/install/autoware_quickstart_examples/lib;/home/nvidia/autoware-bleeding/install/autoware_pointgrey_drivers/lib;/home/nvidia/autoware-bleeding/install/autoware_driveworks_interface/lib;/home/nvidia/autoware-bleeding/install/autoware_connector/lib;/home/nvidia/autoware-bleeding/install/autoware_camera_lidar_calibrator/lib;/home/nvidia/autoware-bleeding/install/astar_search/lib;/home/nvidia/autoware-bleeding/install/amathutils_lib/lib;/home/nvidia/autoware-bleeding/install/autoware_msgs/lib;/home/nvidia/autoware-bleeding/install/autoware_map_msgs/lib;/home/nvidia/autoware-bleeding/install/autoware_launcher_rviz/lib;/home/nvidia/autoware-bleeding/install/autoware_launcher/lib;/home/nvidia/autoware-bleeding/install/autoware_lanelet2_msgs/lib;/home/nvidia/autoware-bleeding/install/autoware_external_msgs/lib;/home/nvidia/autoware-bleeding/install/autoware_driveworks_gmsl_interface/lib;/home/nvidia/autoware-bleeding/install/autoware_config_msgs/lib;/home/nvidia/autoware-bleeding/install/autoware_can_msgs/lib;/home/nvidia/autoware-bleeding/install/autoware_build_flags/lib;/home/nvidia/autoware-bleeding/install/autoware_bag_tools/lib;/home/nvidia/autoware-bleeding/install/adi_driver/lib;/home/nvidia/autoware-1.14/install/ymc/lib;/home/nvidia/autoware-1.14/install/xsens_driver/lib;/home/nvidia/autoware-1.14/install/wf_simulator/lib;/home/nvidia/autoware-1.14/install/lattice_planner/lib;/home/nvidia/autoware-1.14/install/waypoint_planner/lib;/home/nvidia/autoware-1.14/install/waypoint_maker/lib;/home/nvidia/autoware-1.14/install/way_planner/lib;/home/nvidia/autoware-1.14/install/vlg22c_cam/lib;/home/nvidia/autoware-1.14/install/vision_ssd_detect/lib;/home/nvidia/autoware-1.14/install/vision_segment_enet_detect/lib;/home/nvidia/autoware-1.14/install/vision_lane_detect/lib;/home/nvidia/autoware-1.14/install/vision_darknet_detect/lib;/home/nvidia/autoware-1.14/install/vision_beyond_track/lib;/home/nvidia/autoware-1.14/install/vel_pose_diff_checker/lib;/home/nvidia/autoware-1.14/install/vehicle_socket/lib;/home/nvidia/autoware-1.14/install/vehicle_model/lib;/home/nvidia/autoware-1.14/install/vehicle_gazebo_simulation_launcher/lib;/home/nvidia/autoware-1.14/install/vehicle_gazebo_simulation_interface/lib;/home/nvidia/autoware-1.14/install/vehicle_engage_panel/lib;/home/nvidia/autoware-1.14/install/vehicle_description/lib;/home/nvidia/autoware-1.14/install/trafficlight_recognizer/lib;/home/nvidia/autoware-1.14/install/op_utilities/lib;/home/nvidia/autoware-1.14/install/op_simulation_package/lib;/home/nvidia/autoware-1.14/install/op_local_planner/lib;/home/nvidia/autoware-1.14/install/op_global_planner/lib;/home/nvidia/autoware-1.14/install/lidar_kf_contour_track/lib;/home/nvidia/autoware-1.14/install/op_ros_helpers/lib;/home/nvidia/autoware-1.14/install/ff_waypoint_follower/lib;/home/nvidia/autoware-1.14/install/dp_planner/lib;/home/nvidia/autoware-1.14/install/op_simu/lib;/home/nvidia/autoware-1.14/install/op_planner/lib;/home/nvidia/autoware-1.14/install/op_utility/lib;/home/nvidia/autoware-1.14/install/lidar_euclidean_cluster_detect/lib;/home/nvidia/autoware-1.14/install/vector_map_server/lib;/home/nvidia/autoware-1.14/install/road_occupancy_processor/lib;/home/nvidia/autoware-1.14/install/costmap_generator/lib;/home/nvidia/autoware-1.14/install/object_map/lib;/home/nvidia/autoware-1.14/install/naive_motion_predict/lib;/home/nvidia/autoware-1.14/install/lanelet_aisan_converter/lib;/home/nvidia/autoware-1.14/install/map_file/lib;/home/nvidia/autoware-1.14/install/libvectormap/lib;/home/nvidia/autoware-1.14/install/lane_planner/lib;/home/nvidia/autoware-1.14/install/imm_ukf_pda_track/lib;/home/nvidia/autoware-1.14/install/decision_maker/lib;/home/nvidia/autoware-1.14/install/vector_map/lib;/home/nvidia/autoware-1.14/install/vector_map_msgs/lib;/home/nvidia/autoware-1.14/install/vectacam/lib;/home/nvidia/autoware-1.14/install/udon_socket/lib;/home/nvidia/autoware-1.14/install/twist_generator/lib;/home/nvidia/autoware-1.14/install/twist_gate/lib;/home/nvidia/autoware-1.14/install/twist_filter/lib;/home/nvidia/autoware-1.14/install/twist2odom/lib;/home/nvidia/autoware-1.14/install/tablet_socket/lib;/home/nvidia/autoware-1.14/install/runtime_manager/lib;/home/nvidia/autoware-1.14/install/mqtt_socket/lib;/home/nvidia/autoware-1.14/install/tablet_socket_msgs/lib;/home/nvidia/autoware-1.14/install/state_machine_lib/lib;/home/nvidia/autoware-1.14/install/sound_player/lib;/home/nvidia/autoware-1.14/install/sick_lms5xx/lib;/home/nvidia/autoware-1.14/install/sick_ldmrs_tools/lib;/home/nvidia/autoware-1.14/install/sick_ldmrs_driver/lib;/home/nvidia/autoware-1.14/install/sick_ldmrs_msgs/lib;/home/nvidia/autoware-1.14/install/sick_ldmrs_description/lib;/home/nvidia/autoware-1.14/install/points2image/lib;/home/nvidia/autoware-1.14/install/rosinterface/lib;/home/nvidia/autoware-1.14/install/rosbag_controller/lib;/home/nvidia/autoware-1.14/install/pure_pursuit/lib;/home/nvidia/autoware-1.14/install/points_preprocessor/lib;/home/nvidia/autoware-1.14/install/mpc_follower/lib;/home/nvidia/autoware-1.14/install/lidar_localizer/lib;/home/nvidia/autoware-1.14/install/emergency_handler/lib;/home/nvidia/autoware-1.14/install/autoware_health_checker/lib;/home/nvidia/autoware-1.14/install/as/lib;/home/nvidia/autoware-1.14/install/ros_observer/lib;/home/nvidia/autoware-1.14/install/roi_object_filter/lib;/home/nvidia/autoware-1.14/install/range_vision_fusion/lib;/home/nvidia/autoware-1.14/install/pos_db/lib;/home/nvidia/autoware-1.14/install/points_downsampler/lib;/home/nvidia/autoware-1.14/install/pixel_cloud_fusion/lib;/home/nvidia/autoware-1.14/install/pcl_omp_registration/lib;/home/nvidia/autoware-1.14/install/pc2_downsampler/lib;/home/nvidia/autoware-1.14/install/oculus_socket/lib;/home/nvidia/autoware-1.14/install/obj_db/lib;/home/nvidia/autoware-1.14/install/nmea_navsat/lib;/home/nvidia/autoware-1.14/install/ndt_tku/lib;/home/nvidia/autoware-1.14/install/ndt_cpu/lib;/home/nvidia/autoware-1.14/install/multi_lidar_calibrator/lib;/home/nvidia/autoware-1.14/install/microstrain_driver/lib;/home/nvidia/autoware-1.14/install/memsic_imu/lib;/home/nvidia/autoware-1.14/install/marker_downsampler/lib;/home/nvidia/autoware-1.14/install/map_tools/lib;/home/nvidia/autoware-1.14/install/map_tf_generator/lib;/home/nvidia/autoware-1.14/install/log_tools/lib;/home/nvidia/autoware-1.14/install/lidar_shape_estimation/lib;/home/nvidia/autoware-1.14/install/lidar_point_pillars/lib;/home/nvidia/autoware-1.14/install/lidar_naive_l_shape_detect/lib;/home/nvidia/autoware-1.14/install/lidar_fake_perception/lib;/home/nvidia/autoware-1.14/install/lidar_apollo_cnn_seg_detect/lib;/home/nvidia/autoware-1.14/install/libwaypoint_follower/lib;/home/nvidia/autoware-1.14/install/lgsvl_simulator_bridge/lib;/home/nvidia/autoware-1.14/install/lanelet2_extension/lib;/home/nvidia/autoware-1.14/install/kvaser/lib;/home/nvidia/autoware-1.14/install/kitti_launch/lib;/home/nvidia/autoware-1.14/install/kitti_player/lib;/home/nvidia/autoware-1.14/install/kitti_box_publisher/lib;/home/nvidia/autoware-1.14/install/javad_navsat_driver/lib;/home/nvidia/autoware-1.14/install/integrated_viewer/lib;/home/nvidia/autoware-1.14/install/image_processor/lib;/home/nvidia/autoware-1.14/install/hokuyo/lib;/home/nvidia/autoware-1.14/install/graph_tools/lib;/home/nvidia/autoware-1.14/install/gnss_localizer/lib;/home/nvidia/autoware-1.14/install/gnss/lib;/home/nvidia/autoware-1.14/install/glviewer/lib;/home/nvidia/autoware-1.14/install/gazebo_world_description/lib;/home/nvidia/autoware-1.14/install/gazebo_imu_description/lib;/home/nvidia/autoware-1.14/install/gazebo_camera_description/lib;/home/nvidia/autoware-1.14/install/garmin/lib;/home/nvidia/autoware-1.14/install/freespace_planner/lib;/home/nvidia/autoware-1.14/install/fastvirtualscan/lib;/home/nvidia/autoware-1.14/install/ekf_localizer/lib;/home/nvidia/autoware-1.14/install/ds4_msgs/lib;/home/nvidia/autoware-1.14/install/ds4_driver/lib;/home/nvidia/autoware-1.14/install/detected_objects_visualizer/lib;/home/nvidia/autoware-1.14/install/decision_maker_panel/lib;/home/nvidia/autoware-1.14/install/data_preprocessor/lib;/home/nvidia/autoware-1.14/install/custom_msgs/lib;/home/nvidia/autoware-1.14/install/calibration_publisher/lib;/home/nvidia/autoware-1.14/install/autoware_system_msgs/lib;/home/nvidia/autoware-1.14/install/autoware_rviz_plugins/lib;/home/nvidia/autoware-1.14/install/autoware_quickstart_examples/lib;/home/nvidia/autoware-1.14/install/autoware_pointgrey_drivers/lib;/home/nvidia/autoware-1.14/install/autoware_driveworks_interface/lib;/home/nvidia/autoware-1.14/install/autoware_connector/lib;/home/nvidia/autoware-1.14/install/autoware_camera_lidar_calibrator/lib;/home/nvidia/autoware-1.14/install/astar_search/lib;/home/nvidia/autoware-1.14/install/amathutils_lib/lib;/home/nvidia/autoware-1.14/install/autoware_msgs/lib;/home/nvidia/autoware-1.14/install/autoware_map_msgs/lib;/home/nvidia/autoware-1.14/install/autoware_launcher_rviz/lib;/home/nvidia/autoware-1.14/install/autoware_launcher/lib;/home/nvidia/autoware-1.14/install/autoware_lanelet2_msgs/lib;/home/nvidia/autoware-1.14/install/autoware_external_msgs/lib;/home/nvidia/autoware-1.14/install/autoware_driveworks_gmsl_interface/lib;/home/nvidia/autoware-1.14/install/autoware_config_msgs/lib;/home/nvidia/autoware-1.14/install/autoware_can_msgs/lib;/home/nvidia/autoware-1.14/install/autoware_build_flags/lib;/home/nvidia/autoware-1.14/install/autoware_bag_tools/lib;/home/nvidia/autoware-1.14/install/adi_driver/lib;/home/nvidia/catkin_ws/devel/lib;/opt/ros/melodic/lib)
      find_library(lib ${library}
        PATHS ${path}
        NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
      if(lib)
        set(lib_path ${path})
        break()
      endif()
    endforeach()
    if(lib)
      _list_append_unique(pix_can_LIBRARY_DIRS ${lib_path})
      list(APPEND pix_can_LIBRARIES ${lib})
    else()
      # as a fall back for non-catkin libraries try to search globally
      find_library(lib ${library})
      if(NOT lib)
        message(FATAL_ERROR "Project '${PROJECT_NAME}' tried to find library '${library}'.  The library is neither a target nor built/installed properly.  Did you compile project 'pix_can'?  Did you find_package() it before the subdirectory containing its code is included?")
      endif()
      list(APPEND pix_can_LIBRARIES ${lib})
    endif()
  endif()
endforeach()

set(pix_can_EXPORTED_TARGETS "pix_can_generate_messages_cpp;pix_can_generate_messages_eus;pix_can_generate_messages_lisp;pix_can_generate_messages_nodejs;pix_can_generate_messages_py")
# create dummy targets for exported code generation targets to make life of users easier
foreach(t ${pix_can_EXPORTED_TARGETS})
  if(NOT TARGET ${t})
    add_custom_target(${t})
  endif()
endforeach()

set(depends "roscpp;message_runtime;std_msgs;tf;tf2;geometry_msgs;autoware_msgs;autoware_can_msgs;autoware_config_msgs;amathutils_lib;pcl_ros;pcl_conversions;sensor_msgs;tablet_socket_msgs;autoware_health_checker;gazebo_msgs;libwaypoint_follower;astar_search")
foreach(depend ${depends})
  string(REPLACE " " ";" depend_list ${depend})
  # the package name of the dependency must be kept in a unique variable so that it is not overwritten in recursive calls
  list(GET depend_list 0 pix_can_dep)
  list(LENGTH depend_list count)
  if(${count} EQUAL 1)
    # simple dependencies must only be find_package()-ed once
    if(NOT ${pix_can_dep}_FOUND)
      find_package(${pix_can_dep} REQUIRED NO_MODULE)
    endif()
  else()
    # dependencies with components must be find_package()-ed again
    list(REMOVE_AT depend_list 0)
    find_package(${pix_can_dep} REQUIRED NO_MODULE ${depend_list})
  endif()
  _list_append_unique(pix_can_INCLUDE_DIRS ${${pix_can_dep}_INCLUDE_DIRS})

  # merge build configuration keywords with library names to correctly deduplicate
  _pack_libraries_with_build_configuration(pix_can_LIBRARIES ${pix_can_LIBRARIES})
  _pack_libraries_with_build_configuration(_libraries ${${pix_can_dep}_LIBRARIES})
  _list_append_deduplicate(pix_can_LIBRARIES ${_libraries})
  # undo build configuration keyword merging after deduplication
  _unpack_libraries_with_build_configuration(pix_can_LIBRARIES ${pix_can_LIBRARIES})

  _list_append_unique(pix_can_LIBRARY_DIRS ${${pix_can_dep}_LIBRARY_DIRS})
  list(APPEND pix_can_EXPORTED_TARGETS ${${pix_can_dep}_EXPORTED_TARGETS})
endforeach()

set(pkg_cfg_extras "pix_can-msg-extras.cmake")
foreach(extra ${pkg_cfg_extras})
  if(NOT IS_ABSOLUTE ${extra})
    set(extra ${pix_can_DIR}/${extra})
  endif()
  include(${extra})
endforeach()
