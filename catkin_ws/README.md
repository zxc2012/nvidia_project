## velodyne:
roslaunch velodyne_pointcloud VLP16_points.launch

## imu:
roslaunch imu_launch imu_msg.launch

rostopic echo /imu_data

## MVS:
rosrun mvs_camera mvs_camera

