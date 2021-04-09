## 1.install ros1

Setup your computer to accept software from packages.ros.org.

$ sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'

Set up your keys

$ sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key  C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654

### Installation
First, make sure your Debian package index is up-to-date:
$ sudo apt update

Desktop-Full Install: (Recommended) : ROS, rqt, rviz, robot-generic libraries, 2D/3D simulators and 2D/3D perception
$ sudo apt install ros-melodic-desktop-full

### Environment setup
It's convenient if the ROS environment variables are automatically added to your bash session every time a new shell is launched:
$ echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
$ source ~/.bashrc

To install this tool and other dependencies for building ROS packages, run:
$ sudo apt install python-rosdep python-rosinstall python-rosinstall-generator python-wstool build-essential

### Initialize rosdep
$ sudo apt install python-rosdep
$ sudo rosdep init
$ rosdep update

## 2.install autoware

System dependencies for Ubuntu 18.04 / Melodic
$ sudo apt update
$ sudo apt install -y python-catkin-pkg python-rosdep ros-$ROS_DISTRO-catkin
$ sudo apt install -y python3-pip python3-colcon-common-extensions python3-setuptools python3-vcstool
$ pip3 install -U setuptools

Additional system dependencies for CUDA support
For installation instructions for CUDA 10.0, see https://docs.nvidia.com/cuda/archive/10.0/cuda-installation-guide-linux/index.html.

NOTE: To enable CUDA support on Melodic, Eigen is required to be updated.
WARNING: This might break your system, or the compilation of other programs
$ cd && wget http://bitbucket.org/eigen/eigen/get/3.3.7.tar.gz #Download Eigen
$ mkdir eigen && tar --strip-components=1 -xzvf 3.3.7.tar.gz -C eigen #Decompress
$ cd eigen && mkdir build && cd build && cmake .. && make && make install #Build and install
$ cd && rm -rf 3.3.7.tar.gz && rm -rf eigen #Remove downloaded and temporary files
(ncnynl.com/archives/201911/3481.html)

$ mkdir -p autoware.ai/src
$ cd autoware.ai

For the 1.14.0 release:
$ wget -O autoware.ai.repos "https://raw.githubusercontent.com/Autoware-AI/autoware.ai/1.14.0/autoware.ai.repos"

For the master version (bleeding edge):
$ wget -O autoware.ai.repos "https://raw.githubusercontent.com/Autoware-AI/autoware.ai/master/autoware.ai.repos"

Download Autoware.AI into the workspace.
$ vcs import src < autoware.ai.repos

Install dependencies using rosdep.
$ rosdep update
$ rosdep install -y --from-paths src --ignore-src --rosdistro $ROS_DISTRO

修改calibration_publisher/CMakeLists.txt 增加${OpenCV_LIBS}
target_link_libraries(calibration_publisher
        ${catkin_LIBRARIES} 
        ${OpenCV_LIBS}
        ) 
修改calibration_publisher/package.xml 增加<depend>libopencv-dev</depend>
  <depend>cv_bridge</depend>
  <depend>image_transport</depend> 
  <depend>tf</depend> 
  <depend>libopencv-dev</depend>

calibration_publisher.launch 
<param name="calibration_file" type="str" value="$(arg file)"/>
<param name="calibration_file" type="str" value="$(arg calibration_file)"/>

lidar_euclidean_cluster_detect.cpp
_pub_clusters_message = h.advertise<autoware_msgs::CloudClusterArray>("/detection/lidar_detector/cloud_clusters", 1);
_pub_clusters_message = h.advertise<autoware_msgs::CloudClusterArray>("/cloud_clusters", 1);

$ vim /home/nvidia/catkin_ws/src/spinnaker_sdk_camera_driver-master/params/test_params.yaml
modify cam_ids and master_cam

$ vim /home/nvidia/autoware-1.14/src/autoware/utilities/runtime_manager/scripts/sensing.yaml
- name : Robosense RS16
  desc : Launches the driver for the selected RoboSense LiDAR sensor and publishes the pointcloud in rslidar_points.
  run  : roslaunch rslidar_pointcloud rs_cloud_nodelet_16.launch
- name : Robosense RS16
  desc : Launches the driver for the selected RoboSense LiDAR sensor and publishes the pointcloud in rslidar_points.
  run  : roslaunch rslidar_pointcloud rs_lidar_16.launch

$ vim /home/nvidia/catkin_ws/src/lslidar_C16-master/lslidar_c16_decoder/launch/lslidar_c16.launch
delete the last line  <!--node name="rviz" pkg="rviz" type="rviz" args="-d $(find lslidar_c16_decoder)/launch/lslidar_c16.rviz" output="screen"/-->
[roslaunch lslidar_c16_decoder lslidar_c16.launch]

$ vim /home/nvidia/catkin_ws/src/ros_rslidar-master/rslidar_pointcloud/launch/rs_lidar_16.launch
delete the last line  <node name="rviz" pkg="rviz" type="rviz"  args="-d $(find rslidar_pointcloud)/rviz_cfg/rslidar.rviz" />

## 3.$ sudo apt-get install python-catkin-tools

## 4.install spinnaker SDK (Packages/spinnaker-2.0.0.147-arm64-pkg)

## 5.catkin_ws(/src/lslidar_C16-master ros_rslidar-master spinnaker_sdk_camera_driver-master velodyne-master)
https://github.com/tongsky723/lslidar_C16
https://github.com/RoboSense-LiDAR/ros_rslidar
http://wiki.ros.org/spinnaker_sdk_camera_driver
https://github.com/ros-drivers/velodyne

$ mkdir ~/catkin_ws/src
$ cd catkin_ws
$ catkin build

vim /home/nvidia/catkin_ws/src/ros_rslidar-master/rslidar_pointcloud/src/convert.cc
private_nh.param("output_points_topic", output_points_topic, std::string("points_raw"));//rslidar_points

vim /home/nvidia/catkin_ws/src/lslidar_C16-master/lslidar_c16_decoder/src/lslidar_c16_decoder.cpp
point_cloud_pub = nh.advertise<sensor_msgs::PointCloud2>("points_raw", 10);//lslidar_point_cloud

## 6.install Opencv3.4(ncnynl.com/archives/201903/2899.html)

## 7.compile autoware
Compile the workspace With CUDA support
$ AUTOWARE_COMPILE_WITH_CUDA=1 colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release

Compile the workspace Without CUDA Support
$ colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release

## 8.install peak_can driver(peak-system.com/fileadmin/media/linux/index.htm#)
$ vim /home/nvidia/Packages/peak-linux-driver-8.10.1/driver/Makefile
KERNEL_LOCATION =/lib/modules/4.9.108-tegra/build
KERNEL_LOCATION =/lib/modules/4.9.140-tegra/build

## 9.install pcan_basic

## 10.make the tf files for lidars

## 11.nvidia mode check and set
$ sudo nvpmodel -m 0
$ sudo /usr/bin/./jetson_clocks --show
$ sudo nvpmodel -q --verbose

## 12.Mount new disk(blog.csdn.net/DraemSky/article/details/85280522)

sudo apt install qt5-default

$ sudo apt remove libopencv-dev 
$ sudo apt remove libopencv-core3.2
$ sudo apt list --installed | grep opencv
$ sudo apt install ros-melodic-desktop-full
$ sudo apt --fix-broken install
$ sudo dpkg --force-all -i /var/cache/apt/archives/libopencv-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb
$ sudo apt install ros-melodic-desktop-full
/autoware-1.14$ rosdep update
/autoware-1.14$ rosdep install -y --from-paths src --ignore-src --rosdistro $ROS_DISTRO

nvidia@nvidia-desktop:~$ sudo apt remove libopencv-dev  
[sudo] password for nvidia: 
Reading package lists... Done
Building dependency tree       
Reading state information... Done
The following packages were automatically installed and are no longer required:
  apt-clone archdetect-deb bogl-bterm busybox-static cryptsetup-bin
  dpkg-repack fltk1.3-doc fluid gir1.2-gtk-2.0 gir1.2-timezonemap-1.0
  gir1.2-xkl-1.0 grub-common hddtemp kde-window-manager kinit kio
  kpackagetool5 kwayland-data kwin-common kwin-data kwin-x11 libatk1.0-dev
  libcairo-script-interpreter2 libcairo2-dev libcharls1 libdebian-installer4
  libfltk-cairo1.3 libfltk-forms1.3 libfltk-gl1.3 libfltk-images1.3 libfltk1.3
  libfltk1.3-dev libgdcm2.8 libgdk-pixbuf2.0-dev libgtk2.0-dev
  libkdecorations2-5v5 libkdecorations2private5v5 libkf5activities5
  libkf5attica5 libkf5completion-data libkf5completion5 libkf5declarative-data
  libkf5declarative5 libkf5doctools5 libkf5globalaccel-data libkf5globalaccel5
  libkf5globalaccelprivate5 libkf5idletime5 libkf5jobwidgets-data
  libkf5jobwidgets5 libkf5kcmutils-data libkf5kcmutils5 libkf5kiocore5
  libkf5kiontlm5 libkf5kiowidgets5 libkf5newstuff-data libkf5newstuff5
  libkf5newstuffcore5 libkf5package-data libkf5package5 libkf5plasma5
  libkf5quickaddons5 libkf5solid5 libkf5solid5-data libkf5sonnet5-data
  libkf5sonnetcore5 libkf5sonnetui5 libkf5textwidgets-data libkf5textwidgets5
  libkf5waylandclient5 libkf5waylandserver5 libkf5xmlgui-bin libkf5xmlgui-data
  libkf5xmlgui5 libkscreenlocker5 libkwin4-effect-builtins1 libkwineffects11
  libkwinglutils11 libkwinxrenderutils11 libopencv-calib3d3.2
  libopencv-core3.2 libopencv-features2d3.2 libopencv-flann3.2
  libopencv-highgui3.2 libopencv-imgcodecs3.2 libopencv-imgproc3.2
  libopencv-ml3.2 libopencv-photo3.2 libopencv-videoio3.2 libpango1.0-dev
  libpixman-1-dev libqgsttools-p1 libqt5multimedia5 libqt5multimedia5-plugins
  libqt5multimediaquick-p5 libqt5multimediawidgets5 libsocket++1
  libxcb-composite0 libxcb-cursor0 libxcb-damage0 libxcb-shm0-dev
  libxcomposite-dev libxcursor-dev libxinerama-dev libxml2-utils os-prober
  python-networkx python-opengl python-psutil python-pydot
  python-pyqt5.qtopengl python-pyqt5.qtwebkit python-pywt python-skimage
  python-skimage-lib python3-dbus.mainloop.pyqt5 python3-icu python3-pam
  python3-pyqt5 python3-pyqt5.qtsvg python3-pyqt5.qtwebkit python3-sip
  qml-module-org-kde-kquickcontrolsaddons qml-module-qtmultimedia
  qml-module-qtquick2 rdate ros-melodic-actionlib-tutorials
  ros-melodic-bond-core ros-melodic-bondpy ros-melodic-cmake-modules
  ros-melodic-common-msgs ros-melodic-common-tutorials
  ros-melodic-controller-manager ros-melodic-controller-manager-msgs
  ros-melodic-diagnostic-aggregator ros-melodic-diagnostic-analysis
  ros-melodic-diagnostic-common-diagnostics ros-melodic-diagnostics
  ros-melodic-diff-drive-controller ros-melodic-executive-smach
  ros-melodic-filters ros-melodic-gazebo-ros-control ros-melodic-geometry
  ros-melodic-geometry-tutorials ros-melodic-gl-dependency
  ros-melodic-grid-map-core ros-melodic-image-common
  ros-melodic-interactive-marker-tutorials ros-melodic-joint-limits-interface
  ros-melodic-joint-state-controller ros-melodic-joint-state-publisher
  ros-melodic-jsk-gui-msgs ros-melodic-jsk-hark-msgs
  ros-melodic-kdl-conversions ros-melodic-kdl-parser ros-melodic-kdl-parser-py
  ros-melodic-laser-assembler ros-melodic-laser-filters
  ros-melodic-laser-pipeline ros-melodic-librviz-tutorial ros-melodic-mk
  ros-melodic-nodelet-core ros-melodic-nodelet-tutorial-math
  ros-melodic-people-msgs ros-melodic-perception-pcl
  ros-melodic-pluginlib-tutorials ros-melodic-polled-camera
  ros-melodic-position-controllers ros-melodic-qt-dotgraph ros-melodic-qt-gui
  ros-melodic-qt-gui-cpp ros-melodic-qt-gui-py-common
  ros-melodic-qwt-dependency ros-melodic-robot
  ros-melodic-robot-state-publisher ros-melodic-ros ros-melodic-ros-base
  ros-melodic-ros-comm ros-melodic-ros-core ros-melodic-ros-tutorials
  ros-melodic-rosbash ros-melodic-rosboost-cfg ros-melodic-roscpp-core
  ros-melodic-roscpp-tutorials ros-melodic-roscreate ros-melodic-roslang
  ros-melodic-roslint ros-melodic-roslisp ros-melodic-rosmake
  ros-melodic-rospy-tutorials ros-melodic-rqt-action ros-melodic-rqt-bag
  ros-melodic-rqt-bag-plugins ros-melodic-rqt-console ros-melodic-rqt-dep
  ros-melodic-rqt-graph ros-melodic-rqt-gui ros-melodic-rqt-gui-cpp
  ros-melodic-rqt-gui-py ros-melodic-rqt-launch ros-melodic-rqt-logger-level
  ros-melodic-rqt-moveit ros-melodic-rqt-msg ros-melodic-rqt-nav-view
  ros-melodic-rqt-plot ros-melodic-rqt-pose-view ros-melodic-rqt-publisher
  ros-melodic-rqt-py-common ros-melodic-rqt-py-console
  ros-melodic-rqt-reconfigure ros-melodic-rqt-robot-dashboard
  ros-melodic-rqt-robot-monitor ros-melodic-rqt-robot-plugins
  ros-melodic-rqt-robot-steering ros-melodic-rqt-runtime-monitor
  ros-melodic-rqt-rviz ros-melodic-rqt-service-caller ros-melodic-rqt-shell
  ros-melodic-rqt-srv ros-melodic-rqt-tf-tree ros-melodic-rqt-top
  ros-melodic-rqt-topic ros-melodic-rqt-web ros-melodic-rviz-plugin-tutorials
  ros-melodic-rviz-python-tutorial ros-melodic-self-test
  ros-melodic-shape-msgs ros-melodic-smach ros-melodic-smach-msgs
  ros-melodic-smach-ros ros-melodic-stage ros-melodic-stage-ros
  ros-melodic-stereo-msgs ros-melodic-tf-conversions ros-melodic-tf2-kdl
  ros-melodic-transmission-interface ros-melodic-turtle-actionlib
  ros-melodic-turtle-tf ros-melodic-turtle-tf2 ros-melodic-turtlesim
  ros-melodic-urdf-parser-plugin ros-melodic-urdf-sim-tutorial
  ros-melodic-urdf-tutorial ros-melodic-urdfdom-py
  ros-melodic-view-controller-msgs ros-melodic-visualization-marker-tutorials
  ros-melodic-visualization-tutorials ros-melodic-webkit-dependency sbcl
  tasksel tasksel-data x11proto-composite-dev x11proto-xinerama-dev
Use 'sudo apt autoremove' to remove them.
The following packages will be REMOVED:
  libopencv-dev ros-melodic-camera-calibration
  ros-melodic-compressed-depth-image-transport
  ros-melodic-compressed-image-transport ros-melodic-cv-bridge
  ros-melodic-depth-image-proc ros-melodic-desktop ros-melodic-desktop-full
  ros-melodic-gazebo-plugins ros-melodic-gazebo-ros-pkgs
  ros-melodic-grid-map-cv ros-melodic-grid-map-ros ros-melodic-gscam
  ros-melodic-image-geometry ros-melodic-image-pipeline ros-melodic-image-proc
  ros-melodic-image-publisher ros-melodic-image-rotate
  ros-melodic-image-transport-plugins ros-melodic-image-view
  ros-melodic-image-view2 ros-melodic-jsk-recognition-utils
  ros-melodic-jsk-rviz-plugins ros-melodic-perception
  ros-melodic-posedetection-msgs ros-melodic-rqt-common-plugins
  ros-melodic-rqt-image-view ros-melodic-simulators
  ros-melodic-stereo-image-proc ros-melodic-theora-image-transport
  ros-melodic-vision-opencv ros-melodic-viz
0 upgraded, 0 newly installed, 32 to remove and 344 not upgraded.
After this operation, 34.5 MB disk space will be freed.
Do you want to continue? [Y/n] y
(Reading database ... 210051 files and directories currently installed.)
Removing ros-melodic-desktop-full (1.4.1-0bionic.20200823.044522) ...
Removing ros-melodic-perception (1.4.1-0bionic.20200823.002734) ...
Removing ros-melodic-vision-opencv (1.13.0-0bionic.20200822.083322) ...
Removing ros-melodic-image-pipeline (1.15.0-1bionic.20200822.201702) ...
Removing ros-melodic-stereo-image-proc (1.15.0-1bionic.20200822.070442) ...
Removing ros-melodic-image-view2 (2.2.10-0bionic.20200822.222657) ...
Removing ros-melodic-image-view (1.15.0-1bionic.20200822.051301) ...
Removing ros-melodic-camera-calibration (1.15.0-1bionic.20200822.055930) ...
Removing ros-melodic-image-transport-plugins (1.9.5-0bionic.20200822.084327) ...
Removing ros-melodic-compressed-depth-image-transport (1.9.5-0bionic.20200822.035126) ...
Removing ros-melodic-compressed-image-transport (1.9.5-0bionic.20200822.035123) ...
Removing ros-melodic-depth-image-proc (1.15.0-1bionic.20200822.162410) ...
Removing ros-melodic-desktop (1.4.1-0bionic.20200823.044216) ...
Removing ros-melodic-simulators (1.4.1-0bionic.20200823.043020) ...
Removing ros-melodic-gazebo-ros-pkgs (2.8.7-1bionic.20200822.211607) ...
Removing ros-melodic-gazebo-plugins (2.8.7-1bionic.20200822.185105) ...
Removing ros-melodic-grid-map-ros (1.6.2-1bionic.20200822.183029) ...
Removing ros-melodic-grid-map-cv (1.6.2-1bionic.20200822.034324) ...
Removing ros-melodic-gscam (1.0.1-0bionic.20200822.032136) ...
Removing ros-melodic-image-proc (1.15.0-1bionic.20200822.051219) ...
Removing ros-melodic-jsk-rviz-plugins (2.1.6-1bionic.20200823.040355) ...
Removing ros-melodic-image-publisher (1.15.0-1bionic.20200822.032038) ...
Removing ros-melodic-image-rotate (1.15.0-1bionic.20200822.181832) ...
Removing ros-melodic-jsk-recognition-utils (1.2.10-0bionic.20200823.021509) ...
Removing ros-melodic-posedetection-msgs (4.3.1-0bionic.20200822.032314) ...
Removing ros-melodic-viz (1.4.1-0bionic.20200823.042931) ...
Removing ros-melodic-rqt-common-plugins (0.4.8-0bionic.20200822.220029) ...
Removing ros-melodic-rqt-image-view (0.4.16-1bionic.20200822.034436) ...
Removing ros-melodic-theora-image-transport (1.9.5-0bionic.20200822.034457) ...
Removing ros-melodic-image-geometry (1.13.0-0bionic.20200822.044213) ...
Removing ros-melodic-cv-bridge (1.13.0-0bionic.20200822.025653) ...
Removing libopencv-dev (3.3.1-2-g31ccdfe11) ...
nvidia@nvidia-desktop:~$ sudo apt remove libopencv-core3.2
Reading package lists... Done
Building dependency tree       
Reading state information... Done
The following packages were automatically installed and are no longer required:
  apt-clone archdetect-deb bogl-bterm busybox-static cryptsetup-bin
  dpkg-repack fltk1.3-doc fluid gir1.2-gtk-2.0 gir1.2-timezonemap-1.0
  gir1.2-xkl-1.0 grub-common hddtemp kde-window-manager kinit kio
  kpackagetool5 kwayland-data kwin-common kwin-data kwin-x11 libatk1.0-dev
  libcairo-script-interpreter2 libcairo2-dev libcharls1 libdebian-installer4
  libfltk-cairo1.3 libfltk-forms1.3 libfltk-gl1.3 libfltk-images1.3 libfltk1.3
  libfltk1.3-dev libgdcm2.8 libgdk-pixbuf2.0-dev libgtk2.0-dev
  libkdecorations2-5v5 libkdecorations2private5v5 libkf5activities5
  libkf5attica5 libkf5completion-data libkf5completion5 libkf5declarative-data
  libkf5declarative5 libkf5doctools5 libkf5globalaccel-data libkf5globalaccel5
  libkf5globalaccelprivate5 libkf5idletime5 libkf5jobwidgets-data
  libkf5jobwidgets5 libkf5kcmutils-data libkf5kcmutils5 libkf5kiocore5
  libkf5kiontlm5 libkf5kiowidgets5 libkf5newstuff-data libkf5newstuff5
  libkf5newstuffcore5 libkf5package-data libkf5package5 libkf5plasma5
  libkf5quickaddons5 libkf5solid5 libkf5solid5-data libkf5sonnet5-data
  libkf5sonnetcore5 libkf5sonnetui5 libkf5textwidgets-data libkf5textwidgets5
  libkf5waylandclient5 libkf5waylandserver5 libkf5xmlgui-bin libkf5xmlgui-data
  libkf5xmlgui5 libkscreenlocker5 libkwin4-effect-builtins1 libkwineffects11
  libkwinglutils11 libkwinxrenderutils11 libpango1.0-dev libpixman-1-dev
  libqgsttools-p1 libqt5multimedia5 libqt5multimedia5-plugins
  libqt5multimediaquick-p5 libqt5multimediawidgets5 libsocket++1
  libxcb-composite0 libxcb-cursor0 libxcb-damage0 libxcb-shm0-dev
  libxcomposite-dev libxcursor-dev libxinerama-dev libxml2-utils os-prober
  python-networkx python-opengl python-psutil python-pydot
  python-pyqt5.qtopengl python-pyqt5.qtwebkit python-pywt python-skimage
  python-skimage-lib python3-dbus.mainloop.pyqt5 python3-icu python3-pam
  python3-pyqt5 python3-pyqt5.qtsvg python3-pyqt5.qtwebkit python3-sip
  qml-module-org-kde-kquickcontrolsaddons qml-module-qtmultimedia
  qml-module-qtquick2 rdate ros-melodic-actionlib-tutorials
  ros-melodic-bond-core ros-melodic-bondpy ros-melodic-cmake-modules
  ros-melodic-common-msgs ros-melodic-common-tutorials
  ros-melodic-controller-manager ros-melodic-controller-manager-msgs
  ros-melodic-diagnostic-aggregator ros-melodic-diagnostic-analysis
  ros-melodic-diagnostic-common-diagnostics ros-melodic-diagnostics
  ros-melodic-diff-drive-controller ros-melodic-executive-smach
  ros-melodic-filters ros-melodic-gazebo-ros-control ros-melodic-geometry
  ros-melodic-geometry-tutorials ros-melodic-gl-dependency
  ros-melodic-grid-map-core ros-melodic-image-common
  ros-melodic-interactive-marker-tutorials ros-melodic-joint-limits-interface
  ros-melodic-joint-state-controller ros-melodic-joint-state-publisher
  ros-melodic-jsk-gui-msgs ros-melodic-jsk-hark-msgs
  ros-melodic-kdl-conversions ros-melodic-kdl-parser ros-melodic-kdl-parser-py
  ros-melodic-laser-assembler ros-melodic-laser-filters
  ros-melodic-laser-pipeline ros-melodic-librviz-tutorial ros-melodic-mk
  ros-melodic-nodelet-core ros-melodic-nodelet-tutorial-math
  ros-melodic-people-msgs ros-melodic-perception-pcl
  ros-melodic-pluginlib-tutorials ros-melodic-polled-camera
  ros-melodic-position-controllers ros-melodic-qt-dotgraph ros-melodic-qt-gui
  ros-melodic-qt-gui-cpp ros-melodic-qt-gui-py-common
  ros-melodic-qwt-dependency ros-melodic-robot
  ros-melodic-robot-state-publisher ros-melodic-ros ros-melodic-ros-base
  ros-melodic-ros-comm ros-melodic-ros-core ros-melodic-ros-tutorials
  ros-melodic-rosbash ros-melodic-rosboost-cfg ros-melodic-roscpp-core
  ros-melodic-roscpp-tutorials ros-melodic-roscreate ros-melodic-roslang
  ros-melodic-roslint ros-melodic-roslisp ros-melodic-rosmake
  ros-melodic-rospy-tutorials ros-melodic-rqt-action ros-melodic-rqt-bag
  ros-melodic-rqt-bag-plugins ros-melodic-rqt-console ros-melodic-rqt-dep
  ros-melodic-rqt-graph ros-melodic-rqt-gui ros-melodic-rqt-gui-cpp
  ros-melodic-rqt-gui-py ros-melodic-rqt-launch ros-melodic-rqt-logger-level
  ros-melodic-rqt-moveit ros-melodic-rqt-msg ros-melodic-rqt-nav-view
  ros-melodic-rqt-plot ros-melodic-rqt-pose-view ros-melodic-rqt-publisher
  ros-melodic-rqt-py-common ros-melodic-rqt-py-console
  ros-melodic-rqt-reconfigure ros-melodic-rqt-robot-dashboard
  ros-melodic-rqt-robot-monitor ros-melodic-rqt-robot-plugins
  ros-melodic-rqt-robot-steering ros-melodic-rqt-runtime-monitor
  ros-melodic-rqt-rviz ros-melodic-rqt-service-caller ros-melodic-rqt-shell
  ros-melodic-rqt-srv ros-melodic-rqt-tf-tree ros-melodic-rqt-top
  ros-melodic-rqt-topic ros-melodic-rqt-web ros-melodic-rviz-plugin-tutorials
  ros-melodic-rviz-python-tutorial ros-melodic-self-test
  ros-melodic-shape-msgs ros-melodic-smach ros-melodic-smach-msgs
  ros-melodic-smach-ros ros-melodic-stage ros-melodic-stage-ros
  ros-melodic-stereo-msgs ros-melodic-tf-conversions ros-melodic-tf2-kdl
  ros-melodic-transmission-interface ros-melodic-turtle-actionlib
  ros-melodic-turtle-tf ros-melodic-turtle-tf2 ros-melodic-turtlesim
  ros-melodic-urdf-parser-plugin ros-melodic-urdf-sim-tutorial
  ros-melodic-urdf-tutorial ros-melodic-urdfdom-py
  ros-melodic-view-controller-msgs ros-melodic-visualization-marker-tutorials
  ros-melodic-visualization-tutorials ros-melodic-webkit-dependency sbcl
  tasksel tasksel-data x11proto-composite-dev x11proto-xinerama-dev
Use 'sudo apt autoremove' to remove them.
The following packages will be REMOVED:
  libopencv-calib3d3.2 libopencv-core3.2 libopencv-features2d3.2
  libopencv-flann3.2 libopencv-highgui3.2 libopencv-imgcodecs3.2
  libopencv-imgproc3.2 libopencv-ml3.2 libopencv-photo3.2 libopencv-videoio3.2
0 upgraded, 0 newly installed, 10 to remove and 344 not upgraded.
After this operation, 8,323 kB disk space will be freed.
Do you want to continue? [Y/n] y
(Reading database ... 208437 files and directories currently installed.)
Removing libopencv-calib3d3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Removing libopencv-features2d3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Removing libopencv-highgui3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Removing libopencv-videoio3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Removing libopencv-photo3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Removing libopencv-flann3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Removing libopencv-imgcodecs3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Removing libopencv-imgproc3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Removing libopencv-ml3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Removing libopencv-core3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Processing triggers for libc-bin (2.27-3ubuntu1) ...
nvidia@nvidia-desktop:~$ sudo apt list --installed | grep opencv  

WARNING: apt does not have a stable CLI interface. Use with caution in scripts.

libopencv/now 3.3.1-2-g31ccdfe11 arm64 [installed,local]
libopencv-python/now 3.3.1-2-g31ccdfe11 arm64 [installed,local]
libopencv-samples/now 3.3.1-2-g31ccdfe11 arm64 [installed,local]
nvidia@nvidia-desktop:~$ sudo apt install ros-melodic-desktop-full
Reading package lists... Done
Building dependency tree       
Reading state information... Done
The following packages were automatically installed and are no longer required:
  apt-clone archdetect-deb bogl-bterm busybox-static cryptsetup-bin
  dpkg-repack gir1.2-timezonemap-1.0 gir1.2-xkl-1.0 grub-common
  kde-window-manager kinit kio kpackagetool5 kwayland-data kwin-common
  kwin-data kwin-x11 libdebian-installer4 libkdecorations2-5v5
  libkdecorations2private5v5 libkf5activities5 libkf5attica5
  libkf5completion-data libkf5completion5 libkf5declarative-data
  libkf5declarative5 libkf5doctools5 libkf5globalaccel-data libkf5globalaccel5
  libkf5globalaccelprivate5 libkf5idletime5 libkf5jobwidgets-data
  libkf5jobwidgets5 libkf5kcmutils-data libkf5kcmutils5 libkf5kiocore5
  libkf5kiontlm5 libkf5kiowidgets5 libkf5newstuff-data libkf5newstuff5
  libkf5newstuffcore5 libkf5package-data libkf5package5 libkf5plasma5
  libkf5quickaddons5 libkf5solid5 libkf5solid5-data libkf5sonnet5-data
  libkf5sonnetcore5 libkf5sonnetui5 libkf5textwidgets-data libkf5textwidgets5
  libkf5waylandclient5 libkf5waylandserver5 libkf5xmlgui-bin libkf5xmlgui-data
  libkf5xmlgui5 libkscreenlocker5 libkwin4-effect-builtins1 libkwineffects11
  libkwinglutils11 libkwinxrenderutils11 libqgsttools-p1 libqt5multimedia5
  libqt5multimedia5-plugins libqt5multimediaquick-p5 libqt5multimediawidgets5
  libxcb-composite0 libxcb-cursor0 libxcb-damage0 os-prober python-networkx
  python-pywt python-skimage python-skimage-lib python3-dbus.mainloop.pyqt5
  python3-icu python3-pam python3-pyqt5 python3-pyqt5.qtsvg
  python3-pyqt5.qtwebkit python3-sip qml-module-org-kde-kquickcontrolsaddons
  qml-module-qtmultimedia qml-module-qtquick2 rdate ros-melodic-grid-map-core
  ros-melodic-jsk-gui-msgs ros-melodic-jsk-hark-msgs ros-melodic-people-msgs
  ros-melodic-view-controller-msgs tasksel tasksel-data
Use 'sudo apt autoremove' to remove them.
The following additional packages will be installed:
  libdc1394-22-dev libexif-dev libexif-doc libexif12 libgdcm2-dev
  libgphoto2-dev libilmbase-dev liblept5 libopencv-calib3d-dev
  libopencv-calib3d3.2 libopencv-contrib-dev libopencv-contrib3.2
  libopencv-core-dev libopencv-core3.2 libopencv-dev libopencv-features2d-dev
  libopencv-features2d3.2 libopencv-flann-dev libopencv-flann3.2
  libopencv-highgui-dev libopencv-highgui3.2 libopencv-imgcodecs-dev
  libopencv-imgcodecs3.2 libopencv-imgproc-dev libopencv-imgproc3.2
  libopencv-ml-dev libopencv-ml3.2 libopencv-objdetect-dev
  libopencv-objdetect3.2 libopencv-photo-dev libopencv-photo3.2
  libopencv-shape-dev libopencv-shape3.2 libopencv-stitching-dev
  libopencv-stitching3.2 libopencv-superres-dev libopencv-superres3.2
  libopencv-ts-dev libopencv-video-dev libopencv-video3.2
  libopencv-videoio-dev libopencv-videoio3.2 libopencv-videostab-dev
  libopencv-videostab3.2 libopencv-viz-dev libopencv-viz3.2 libopencv3.2-java
  libopencv3.2-jni libopenexr-dev libopenexr22 libraw1394-dev libraw1394-tools
  libtesseract4 ros-melodic-camera-calibration
  ros-melodic-compressed-depth-image-transport
  ros-melodic-compressed-image-transport ros-melodic-cv-bridge
  ros-melodic-depth-image-proc ros-melodic-desktop ros-melodic-gazebo-plugins
  ros-melodic-gazebo-ros-pkgs ros-melodic-image-geometry
  ros-melodic-image-pipeline ros-melodic-image-proc
  ros-melodic-image-publisher ros-melodic-image-rotate
  ros-melodic-image-transport-plugins ros-melodic-image-view
  ros-melodic-perception ros-melodic-rqt-common-plugins
  ros-melodic-rqt-image-view ros-melodic-simulators
  ros-melodic-stereo-image-proc ros-melodic-theora-image-transport
  ros-melodic-vision-opencv ros-melodic-viz
Suggested packages:
  opencv-doc libraw1394-doc
The following NEW packages will be installed:
  libdc1394-22-dev libexif-dev libexif-doc libgdcm2-dev libgphoto2-dev
  libilmbase-dev liblept5 libopencv-calib3d-dev libopencv-calib3d3.2
  libopencv-contrib-dev libopencv-contrib3.2 libopencv-core-dev
  libopencv-core3.2 libopencv-dev libopencv-features2d-dev
  libopencv-features2d3.2 libopencv-flann-dev libopencv-flann3.2
  libopencv-highgui-dev libopencv-highgui3.2 libopencv-imgcodecs-dev
  libopencv-imgcodecs3.2 libopencv-imgproc-dev libopencv-imgproc3.2
  libopencv-ml-dev libopencv-ml3.2 libopencv-objdetect-dev
  libopencv-objdetect3.2 libopencv-photo-dev libopencv-photo3.2
  libopencv-shape-dev libopencv-shape3.2 libopencv-stitching-dev
  libopencv-stitching3.2 libopencv-superres-dev libopencv-superres3.2
  libopencv-ts-dev libopencv-video-dev libopencv-video3.2
  libopencv-videoio-dev libopencv-videoio3.2 libopencv-videostab-dev
  libopencv-videostab3.2 libopencv-viz-dev libopencv-viz3.2 libopencv3.2-java
  libopencv3.2-jni libopenexr-dev libraw1394-dev libraw1394-tools
  libtesseract4 ros-melodic-camera-calibration
  ros-melodic-compressed-depth-image-transport
  ros-melodic-compressed-image-transport ros-melodic-cv-bridge
  ros-melodic-depth-image-proc ros-melodic-desktop ros-melodic-desktop-full
  ros-melodic-gazebo-plugins ros-melodic-gazebo-ros-pkgs
  ros-melodic-image-geometry ros-melodic-image-pipeline ros-melodic-image-proc
  ros-melodic-image-publisher ros-melodic-image-rotate
  ros-melodic-image-transport-plugins ros-melodic-image-view
  ros-melodic-perception ros-melodic-rqt-common-plugins
  ros-melodic-rqt-image-view ros-melodic-simulators
  ros-melodic-stereo-image-proc ros-melodic-theora-image-transport
  ros-melodic-vision-opencv ros-melodic-viz
The following packages will be upgraded:
  libexif12 libopenexr22
2 upgraded, 75 newly installed, 0 to remove and 342 not upgraded.
Need to get 14.0 MB/19.0 MB of archives.
After this operation, 97.8 MB of additional disk space will be used.
Do you want to continue? [Y/n] y
Get:1 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/main arm64 libexif12 arm64 0.6.21-4ubuntu0.5 [70.2 kB]
Get:2 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/main arm64 libexif-dev arm64 0.6.21-4ubuntu0.5 [78.1 kB]
Get:3 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/main arm64 libexif-doc all 0.6.21-4ubuntu0.5 [256 kB]
Get:4 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic/universe arm64 libgdcm2-dev arm64 2.8.4-1build2 [252 kB]
Get:5 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic/main arm64 libgphoto2-dev arm64 2.5.16-2 [773 kB]
Get:6 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic/main arm64 libilmbase-dev arm64 2.2.0-11ubuntu2 [71.0 kB]
Get:7 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic/universe arm64 liblept5 arm64 1.75.3-3 [775 kB]
Get:8 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/main arm64 libopenexr22 arm64 2.2.0-11.1ubuntu1.3 [524 kB]
Get:9 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-core-dev arm64 3.2.0+dfsg-4ubuntu0.1 [1,049 kB]
Get:10 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-flann-dev arm64 3.2.0+dfsg-4ubuntu0.1 [157 kB]
Get:11 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic/main arm64 libraw1394-dev arm64 2.1.2-1 [32.8 kB]
Get:12 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic/universe arm64 libdc1394-22-dev arm64 2.2.5-1 [104 kB]
Get:13 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-imgproc-dev arm64 3.2.0+dfsg-4ubuntu0.1 [929 kB]
Get:14 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-imgcodecs-dev arm64 3.2.0+dfsg-4ubuntu0.1 [117 kB]
Get:15 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-videoio-dev arm64 3.2.0+dfsg-4ubuntu0.1 [111 kB]
Get:16 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/main arm64 libopenexr-dev arm64 2.2.0-11.1ubuntu1.3 [673 kB]
Get:17 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-highgui-dev arm64 3.2.0+dfsg-4ubuntu0.1 [30.7 kB]
Get:18 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-ml-dev arm64 3.2.0+dfsg-4ubuntu0.1 [267 kB]
Get:19 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-features2d-dev arm64 3.2.0+dfsg-4ubuntu0.1 [244 kB]
Get:20 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-calib3d-dev arm64 3.2.0+dfsg-4ubuntu0.1 [461 kB]
Get:21 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-objdetect3.2 arm64 3.2.0+dfsg-4ubuntu0.1 [126 kB]
Get:22 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-video3.2 arm64 3.2.0+dfsg-4ubuntu0.1 [105 kB]
Get:23 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-shape3.2 arm64 3.2.0+dfsg-4ubuntu0.1 [50.1 kB]
Get:24 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-stitching3.2 arm64 3.2.0+dfsg-4ubuntu0.1 [148 kB]
Get:25 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-superres3.2 arm64 3.2.0+dfsg-4ubuntu0.1 [37.9 kB]
Get:26 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-videostab3.2 arm64 3.2.0+dfsg-4ubuntu0.1 [86.6 kB]
Get:27 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-viz3.2 arm64 3.2.0+dfsg-4ubuntu0.1 [100 kB]
Get:28 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic/universe arm64 libtesseract4 arm64 4.00~git2288-10f4998a-2 [1,078 kB]
Get:29 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-contrib3.2 arm64 3.2.0+dfsg-4ubuntu0.1 [1,293 kB]
Get:30 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-objdetect-dev arm64 3.2.0+dfsg-4ubuntu0.1 [156 kB]
Get:31 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-photo-dev arm64 3.2.0+dfsg-4ubuntu0.1 [208 kB]
Get:32 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-video-dev arm64 3.2.0+dfsg-4ubuntu0.1 [136 kB]
Get:33 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-shape-dev arm64 3.2.0+dfsg-4ubuntu0.1 [66.7 kB]
Get:34 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-stitching-dev arm64 3.2.0+dfsg-4ubuntu0.1 [197 kB]
Get:35 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-superres-dev arm64 3.2.0+dfsg-4ubuntu0.1 [49.1 kB]
Get:36 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-videostab-dev arm64 3.2.0+dfsg-4ubuntu0.1 [113 kB]
Get:37 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-viz-dev arm64 3.2.0+dfsg-4ubuntu0.1 [147 kB]
Get:38 http://packages.ros.org/ros/ubuntu bionic/main arm64 ros-melodic-compressed-image-transport arm64 1.9.5-0bionic.20200822.035123 [82.2 kB]
Get:39 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-contrib-dev arm64 3.2.0+dfsg-4ubuntu0.1 [1,774 kB]
Get:40 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-ts-dev arm64 3.2.0+dfsg-4ubuntu0.1 [259 kB]
Get:41 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv3.2-jni arm64 3.2.0+dfsg-4ubuntu0.1 [170 kB]
Get:42 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv3.2-java all 3.2.0+dfsg-4ubuntu0.1 [387 kB]
Get:43 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic-updates/universe arm64 libopencv-dev arm64 3.2.0+dfsg-4ubuntu0.1 [200 kB]
Get:44 http://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports bionic/main arm64 libraw1394-tools arm64 2.1.2-1 [15.6 kB]
Fetched 14.0 MB in 26s (532 kB/s)                                                                                                                       
debconf: delaying package configuration, since apt-utils is not installed
(Reading database ... 208387 files and directories currently installed.)
Preparing to unpack .../00-libexif12_0.6.21-4ubuntu0.5_arm64.deb ...
Unpacking libexif12:arm64 (0.6.21-4ubuntu0.5) over (0.6.21-4) ...
Selecting previously unselected package libexif-dev:arm64.
Preparing to unpack .../01-libexif-dev_0.6.21-4ubuntu0.5_arm64.deb ...
Unpacking libexif-dev:arm64 (0.6.21-4ubuntu0.5) ...
Selecting previously unselected package libexif-doc.
Preparing to unpack .../02-libexif-doc_0.6.21-4ubuntu0.5_all.deb ...
Unpacking libexif-doc (0.6.21-4ubuntu0.5) ...
Selecting previously unselected package libgdcm2-dev.
Preparing to unpack .../03-libgdcm2-dev_2.8.4-1build2_arm64.deb ...
Unpacking libgdcm2-dev (2.8.4-1build2) ...
Selecting previously unselected package libgphoto2-dev:arm64.
Preparing to unpack .../04-libgphoto2-dev_2.5.16-2_arm64.deb ...
Unpacking libgphoto2-dev:arm64 (2.5.16-2) ...
Selecting previously unselected package libilmbase-dev.
Preparing to unpack .../05-libilmbase-dev_2.2.0-11ubuntu2_arm64.deb ...
Unpacking libilmbase-dev (2.2.0-11ubuntu2) ...
Selecting previously unselected package liblept5.
Preparing to unpack .../06-liblept5_1.75.3-3_arm64.deb ...
Unpacking liblept5 (1.75.3-3) ...
Selecting previously unselected package libopencv-core3.2:arm64.
Preparing to unpack .../07-libopencv-core3.2_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-core3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-flann3.2:arm64.
Preparing to unpack .../08-libopencv-flann3.2_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-flann3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-imgproc3.2:arm64.
Preparing to unpack .../09-libopencv-imgproc3.2_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-imgproc3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Preparing to unpack .../10-libopenexr22_2.2.0-11.1ubuntu1.3_arm64.deb ...
Unpacking libopenexr22:arm64 (2.2.0-11.1ubuntu1.3) over (2.2.0-11.1ubuntu1) ...
Selecting previously unselected package libopencv-imgcodecs3.2:arm64.
Preparing to unpack .../11-libopencv-imgcodecs3.2_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-imgcodecs3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-videoio3.2:arm64.
Preparing to unpack .../12-libopencv-videoio3.2_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-videoio3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-highgui3.2:arm64.
Preparing to unpack .../13-libopencv-highgui3.2_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-highgui3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-ml3.2:arm64.
Preparing to unpack .../14-libopencv-ml3.2_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-ml3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-features2d3.2:arm64.
Preparing to unpack .../15-libopencv-features2d3.2_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-features2d3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-calib3d3.2:arm64.
Preparing to unpack .../16-libopencv-calib3d3.2_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-calib3d3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-core-dev:arm64.
Preparing to unpack .../17-libopencv-core-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-core-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-flann-dev:arm64.
Preparing to unpack .../18-libopencv-flann-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-flann-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libraw1394-dev:arm64.
Preparing to unpack .../19-libraw1394-dev_2.1.2-1_arm64.deb ...
Unpacking libraw1394-dev:arm64 (2.1.2-1) ...
Selecting previously unselected package libdc1394-22-dev:arm64.
Preparing to unpack .../20-libdc1394-22-dev_2.2.5-1_arm64.deb ...
Unpacking libdc1394-22-dev:arm64 (2.2.5-1) ...
Selecting previously unselected package libopencv-imgproc-dev:arm64.
Preparing to unpack .../21-libopencv-imgproc-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-imgproc-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-imgcodecs-dev:arm64.
Preparing to unpack .../22-libopencv-imgcodecs-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-imgcodecs-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-videoio-dev:arm64.
Preparing to unpack .../23-libopencv-videoio-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-videoio-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopenexr-dev.
Preparing to unpack .../24-libopenexr-dev_2.2.0-11.1ubuntu1.3_arm64.deb ...
Unpacking libopenexr-dev (2.2.0-11.1ubuntu1.3) ...
Selecting previously unselected package libopencv-highgui-dev:arm64.
Preparing to unpack .../25-libopencv-highgui-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-highgui-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-ml-dev:arm64.
Preparing to unpack .../26-libopencv-ml-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-ml-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-features2d-dev:arm64.
Preparing to unpack .../27-libopencv-features2d-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-features2d-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-calib3d-dev:arm64.
Preparing to unpack .../28-libopencv-calib3d-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-calib3d-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-objdetect3.2:arm64.
Preparing to unpack .../29-libopencv-objdetect3.2_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-objdetect3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-photo3.2:arm64.
Preparing to unpack .../30-libopencv-photo3.2_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-photo3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-video3.2:arm64.
Preparing to unpack .../31-libopencv-video3.2_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-video3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-shape3.2:arm64.
Preparing to unpack .../32-libopencv-shape3.2_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-shape3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-stitching3.2:arm64.
Preparing to unpack .../33-libopencv-stitching3.2_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-stitching3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-superres3.2:arm64.
Preparing to unpack .../34-libopencv-superres3.2_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-superres3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-videostab3.2:arm64.
Preparing to unpack .../35-libopencv-videostab3.2_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-videostab3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-viz3.2:arm64.
Preparing to unpack .../36-libopencv-viz3.2_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-viz3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libtesseract4.
Preparing to unpack .../37-libtesseract4_4.00~git2288-10f4998a-2_arm64.deb ...
Unpacking libtesseract4 (4.00~git2288-10f4998a-2) ...
Selecting previously unselected package libopencv-contrib3.2:arm64.
Preparing to unpack .../38-libopencv-contrib3.2_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-contrib3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-objdetect-dev:arm64.
Preparing to unpack .../39-libopencv-objdetect-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-objdetect-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-photo-dev:arm64.
Preparing to unpack .../40-libopencv-photo-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-photo-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-video-dev:arm64.
Preparing to unpack .../41-libopencv-video-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-video-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-shape-dev:arm64.
Preparing to unpack .../42-libopencv-shape-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-shape-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-stitching-dev:arm64.
Preparing to unpack .../43-libopencv-stitching-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-stitching-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-superres-dev:arm64.
Preparing to unpack .../44-libopencv-superres-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-superres-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-videostab-dev:arm64.
Preparing to unpack .../45-libopencv-videostab-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-videostab-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-viz-dev:arm64.
Preparing to unpack .../46-libopencv-viz-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-viz-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-contrib-dev:arm64.
Preparing to unpack .../47-libopencv-contrib-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-contrib-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-ts-dev:arm64.
Preparing to unpack .../48-libopencv-ts-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-ts-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv3.2-jni.
Preparing to unpack .../49-libopencv3.2-jni_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv3.2-jni (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv3.2-java.
Preparing to unpack .../50-libopencv3.2-java_3.2.0+dfsg-4ubuntu0.1_all.deb ...
Unpacking libopencv3.2-java (3.2.0+dfsg-4ubuntu0.1) ...
Selecting previously unselected package libopencv-dev.
Preparing to unpack .../51-libopencv-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-dev (3.2.0+dfsg-4ubuntu0.1) ...
dpkg: error processing archive /tmp/apt-dpkg-install-UmOggN/51-libopencv-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb (--unpack):
 trying to overwrite '/usr/bin/opencv_version', which is also in package libopencv 3.3.1-2-g31ccdfe11
Selecting previously unselected package libraw1394-tools.
Preparing to unpack .../52-libraw1394-tools_2.1.2-1_arm64.deb ...
Unpacking libraw1394-tools (2.1.2-1) ...
Selecting previously unselected package ros-melodic-cv-bridge.
Preparing to unpack .../53-ros-melodic-cv-bridge_1.13.0-0bionic.20200822.025653_arm64.deb ...
Unpacking ros-melodic-cv-bridge (1.13.0-0bionic.20200822.025653) ...
Selecting previously unselected package ros-melodic-image-geometry.
Preparing to unpack .../54-ros-melodic-image-geometry_1.13.0-0bionic.20200822.044213_arm64.deb ...
Unpacking ros-melodic-image-geometry (1.13.0-0bionic.20200822.044213) ...
Selecting previously unselected package ros-melodic-camera-calibration.
Preparing to unpack .../55-ros-melodic-camera-calibration_1.15.0-1bionic.20200822.055930_arm64.deb ...
Unpacking ros-melodic-camera-calibration (1.15.0-1bionic.20200822.055930) ...
Selecting previously unselected package ros-melodic-depth-image-proc.
Preparing to unpack .../56-ros-melodic-depth-image-proc_1.15.0-1bionic.20200822.162410_arm64.deb ...
Unpacking ros-melodic-depth-image-proc (1.15.0-1bionic.20200822.162410) ...
Selecting previously unselected package ros-melodic-gazebo-plugins.
Preparing to unpack .../57-ros-melodic-gazebo-plugins_2.8.7-1bionic.20200822.185105_arm64.deb ...
Unpacking ros-melodic-gazebo-plugins (2.8.7-1bionic.20200822.185105) ...
Selecting previously unselected package ros-melodic-gazebo-ros-pkgs.
Preparing to unpack .../58-ros-melodic-gazebo-ros-pkgs_2.8.7-1bionic.20200822.211607_arm64.deb ...
Unpacking ros-melodic-gazebo-ros-pkgs (2.8.7-1bionic.20200822.211607) ...
Selecting previously unselected package ros-melodic-image-proc.
Preparing to unpack .../59-ros-melodic-image-proc_1.15.0-1bionic.20200822.051219_arm64.deb ...
Unpacking ros-melodic-image-proc (1.15.0-1bionic.20200822.051219) ...
Selecting previously unselected package ros-melodic-image-publisher.
Preparing to unpack .../60-ros-melodic-image-publisher_1.15.0-1bionic.20200822.032038_arm64.deb ...
Unpacking ros-melodic-image-publisher (1.15.0-1bionic.20200822.032038) ...
Selecting previously unselected package ros-melodic-image-rotate.
Preparing to unpack .../61-ros-melodic-image-rotate_1.15.0-1bionic.20200822.181832_arm64.deb ...
Unpacking ros-melodic-image-rotate (1.15.0-1bionic.20200822.181832) ...
Selecting previously unselected package ros-melodic-image-view.
Preparing to unpack .../62-ros-melodic-image-view_1.15.0-1bionic.20200822.051301_arm64.deb ...
Unpacking ros-melodic-image-view (1.15.0-1bionic.20200822.051301) ...
Selecting previously unselected package ros-melodic-stereo-image-proc.
Preparing to unpack .../63-ros-melodic-stereo-image-proc_1.15.0-1bionic.20200822.070442_arm64.deb ...
Unpacking ros-melodic-stereo-image-proc (1.15.0-1bionic.20200822.070442) ...
Selecting previously unselected package ros-melodic-image-pipeline.
Preparing to unpack .../64-ros-melodic-image-pipeline_1.15.0-1bionic.20200822.201702_arm64.deb ...
Unpacking ros-melodic-image-pipeline (1.15.0-1bionic.20200822.201702) ...
Selecting previously unselected package ros-melodic-rqt-image-view.
Preparing to unpack .../65-ros-melodic-rqt-image-view_0.4.16-1bionic.20200822.034436_arm64.deb ...
Unpacking ros-melodic-rqt-image-view (0.4.16-1bionic.20200822.034436) ...
Selecting previously unselected package ros-melodic-compressed-depth-image-transport.
Preparing to unpack .../66-ros-melodic-compressed-depth-image-transport_1.9.5-0bionic.20200822.035126_arm64.deb ...
Unpacking ros-melodic-compressed-depth-image-transport (1.9.5-0bionic.20200822.035126) ...
Selecting previously unselected package ros-melodic-compressed-image-transport.
Preparing to unpack .../67-ros-melodic-compressed-image-transport_1.9.5-0bionic.20200822.035123_arm64.deb ...
Unpacking ros-melodic-compressed-image-transport (1.9.5-0bionic.20200822.035123) ...
Selecting previously unselected package ros-melodic-rqt-common-plugins.
Preparing to unpack .../68-ros-melodic-rqt-common-plugins_0.4.8-0bionic.20200822.220029_arm64.deb ...
Unpacking ros-melodic-rqt-common-plugins (0.4.8-0bionic.20200822.220029) ...
Selecting previously unselected package ros-melodic-viz.
Preparing to unpack .../69-ros-melodic-viz_1.4.1-0bionic.20200823.042931_arm64.deb ...
Unpacking ros-melodic-viz (1.4.1-0bionic.20200823.042931) ...
Selecting previously unselected package ros-melodic-desktop.
Preparing to unpack .../70-ros-melodic-desktop_1.4.1-0bionic.20200823.044216_arm64.deb ...
Unpacking ros-melodic-desktop (1.4.1-0bionic.20200823.044216) ...
Selecting previously unselected package ros-melodic-theora-image-transport.
Preparing to unpack .../71-ros-melodic-theora-image-transport_1.9.5-0bionic.20200822.034457_arm64.deb ...
Unpacking ros-melodic-theora-image-transport (1.9.5-0bionic.20200822.034457) ...
Selecting previously unselected package ros-melodic-image-transport-plugins.
Preparing to unpack .../72-ros-melodic-image-transport-plugins_1.9.5-0bionic.20200822.084327_arm64.deb ...
Unpacking ros-melodic-image-transport-plugins (1.9.5-0bionic.20200822.084327) ...
Selecting previously unselected package ros-melodic-vision-opencv.
Preparing to unpack .../73-ros-melodic-vision-opencv_1.13.0-0bionic.20200822.083322_arm64.deb ...
Unpacking ros-melodic-vision-opencv (1.13.0-0bionic.20200822.083322) ...
Selecting previously unselected package ros-melodic-perception.
Preparing to unpack .../74-ros-melodic-perception_1.4.1-0bionic.20200823.002734_arm64.deb ...
Unpacking ros-melodic-perception (1.4.1-0bionic.20200823.002734) ...
Selecting previously unselected package ros-melodic-simulators.
Preparing to unpack .../75-ros-melodic-simulators_1.4.1-0bionic.20200823.043020_arm64.deb ...
Unpacking ros-melodic-simulators (1.4.1-0bionic.20200823.043020) ...
Selecting previously unselected package ros-melodic-desktop-full.
Preparing to unpack .../76-ros-melodic-desktop-full_1.4.1-0bionic.20200823.044522_arm64.deb ...
Unpacking ros-melodic-desktop-full (1.4.1-0bionic.20200823.044522) ...
Errors were encountered while processing:
 /tmp/apt-dpkg-install-UmOggN/51-libopencv-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb
E: Sub-process /usr/bin/dpkg returned an error code (1)
nvidia@nvidia-desktop:~$ sudo dpkg --force-all -i n/tmp/apt-dpkg-install-UmOggN/51-libopencv-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb
dpkg: error: cannot access archive 'n/tmp/apt-dpkg-install-UmOggN/51-libopencv-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb': No such file or directory
nvidia@nvidia-desktop:~$ sudo dpkg --force-all -i /tmp/apt-dpkg-install-UmOggN/51-libopencv-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb
dpkg: error: cannot access archive '/tmp/apt-dpkg-install-UmOggN/51-libopencv-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb': No such file or directory
nvidia@nvidia-desktop:~$ sudo apt install ros-melodic-desktop-full
Reading package lists... Done
Building dependency tree       
Reading state information... Done
ros-melodic-desktop-full is already the newest version (1.4.1-0bionic.20200823.044522).
You might want to run 'apt --fix-broken install' to correct these.
The following packages have unmet dependencies:
 ros-melodic-cv-bridge : Depends: libopencv-dev but it is not going to be installed
 ros-melodic-image-geometry : Depends: libopencv-dev but it is not going to be installed
E: Unmet dependencies. Try 'apt --fix-broken install' with no packages (or specify a solution).
nvidia@nvidia-desktop:~$ sudo apt --fix-broken install
Reading package lists... Done
Building dependency tree       
Reading state information... Done
Correcting dependencies... Done
The following packages were automatically installed and are no longer required:
  apt-clone archdetect-deb bogl-bterm busybox-static cryptsetup-bin dpkg-repack gir1.2-timezonemap-1.0 gir1.2-xkl-1.0 grub-common kde-window-manager
  kinit kio kpackagetool5 kwayland-data kwin-common kwin-data kwin-x11 libdebian-installer4 libkdecorations2-5v5 libkdecorations2private5v5
  libkf5activities5 libkf5attica5 libkf5completion-data libkf5completion5 libkf5declarative-data libkf5declarative5 libkf5doctools5
  libkf5globalaccel-data libkf5globalaccel5 libkf5globalaccelprivate5 libkf5idletime5 libkf5jobwidgets-data libkf5jobwidgets5 libkf5kcmutils-data
  libkf5kcmutils5 libkf5kiocore5 libkf5kiontlm5 libkf5kiowidgets5 libkf5newstuff-data libkf5newstuff5 libkf5newstuffcore5 libkf5package-data
  libkf5package5 libkf5plasma5 libkf5quickaddons5 libkf5solid5 libkf5solid5-data libkf5sonnet5-data libkf5sonnetcore5 libkf5sonnetui5
  libkf5textwidgets-data libkf5textwidgets5 libkf5waylandclient5 libkf5waylandserver5 libkf5xmlgui-bin libkf5xmlgui-data libkf5xmlgui5
  libkscreenlocker5 libkwin4-effect-builtins1 libkwineffects11 libkwinglutils11 libkwinxrenderutils11 libqgsttools-p1 libqt5multimedia5
  libqt5multimedia5-plugins libqt5multimediaquick-p5 libqt5multimediawidgets5 libxcb-composite0 libxcb-cursor0 libxcb-damage0 os-prober python-networkx
  python-pywt python-skimage python-skimage-lib python3-dbus.mainloop.pyqt5 python3-icu python3-pam python3-pyqt5 python3-pyqt5.qtsvg
  python3-pyqt5.qtwebkit python3-sip qml-module-org-kde-kquickcontrolsaddons qml-module-qtmultimedia qml-module-qtquick2 rdate
  ros-melodic-grid-map-core ros-melodic-jsk-gui-msgs ros-melodic-jsk-hark-msgs ros-melodic-people-msgs ros-melodic-view-controller-msgs tasksel
  tasksel-data
Use 'sudo apt autoremove' to remove them.
The following additional packages will be installed:
  libopencv-dev
Suggested packages:
  opencv-doc
The following NEW packages will be installed:
  libopencv-dev
0 upgraded, 1 newly installed, 0 to remove and 342 not upgraded.
76 not fully installed or removed.
Need to get 0 B/200 kB of archives.
After this operation, 681 kB of additional disk space will be used.
Do you want to continue? [Y/n] y
debconf: delaying package configuration, since apt-utils is not installed
(Reading database ... 210556 files and directories currently installed.)
Preparing to unpack .../libopencv-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-dev (3.2.0+dfsg-4ubuntu0.1) ...
dpkg: error processing archive /var/cache/apt/archives/libopencv-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb (--unpack):
 trying to overwrite '/usr/bin/opencv_version', which is also in package libopencv 3.3.1-2-g31ccdfe11
Errors were encountered while processing:
 /var/cache/apt/archives/libopencv-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb
E: Sub-process /usr/bin/dpkg returned an error code (1)
nvidia@nvidia-desktop:~$ sudo dpkg --force-all -i /var/cache/apt/archives/libopencv-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb
(Reading database ... 210556 files and directories currently installed.)
Preparing to unpack .../libopencv-dev_3.2.0+dfsg-4ubuntu0.1_arm64.deb ...
Unpacking libopencv-dev (3.2.0+dfsg-4ubuntu0.1) ...
dpkg: warning: overriding problem because --force enabled:
dpkg: warning: trying to overwrite '/usr/bin/opencv_version', which is also in package libopencv 3.3.1-2-g31ccdfe11
dpkg: also configuring 'libopencv-calib3d-dev:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-contrib-dev:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-core-dev:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-features2d-dev:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-flann-dev:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-highgui-dev:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-imgcodecs-dev:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-imgproc-dev:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-ml-dev:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-objdetect-dev:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-photo-dev:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-shape-dev:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-stitching-dev:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-superres-dev:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-ts-dev:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-video-dev:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-videoio-dev:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-videostab-dev:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-viz-dev:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv3.2-java' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-calib3d3.2:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-contrib3.2:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-core3.2:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-features2d3.2:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-highgui3.2:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-imgcodecs3.2:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-imgproc3.2:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-videoio3.2:arm64' (required by 'libopencv-dev')
dpkg: also configuring 'libopencv-calib3d3.2:arm64' (required by 'libopencv-calib3d-dev:arm64')
dpkg: also configuring 'libopencv-features2d-dev:arm64' (required by 'libopencv-calib3d-dev:arm64')
dpkg: also configuring 'libopencv-contrib3.2:arm64' (required by 'libopencv-contrib-dev:arm64')
dpkg: also configuring 'libopencv-core-dev:arm64' (required by 'libopencv-contrib-dev:arm64')
dpkg: also configuring 'libopencv-features2d-dev:arm64' (required by 'libopencv-contrib-dev:arm64')
dpkg: also configuring 'libopencv-flann-dev:arm64' (required by 'libopencv-contrib-dev:arm64')
dpkg: also configuring 'libopencv-highgui-dev:arm64' (required by 'libopencv-contrib-dev:arm64')
dpkg: also configuring 'libopencv-imgcodecs-dev:arm64' (required by 'libopencv-contrib-dev:arm64')
dpkg: also configuring 'libopencv-imgproc-dev:arm64' (required by 'libopencv-contrib-dev:arm64')
dpkg: also configuring 'libopencv-ml-dev:arm64' (required by 'libopencv-contrib-dev:arm64')
dpkg: also configuring 'libopencv-objdetect-dev:arm64' (required by 'libopencv-contrib-dev:arm64')
dpkg: also configuring 'libopencv-photo-dev:arm64' (required by 'libopencv-contrib-dev:arm64')
dpkg: also configuring 'libopencv-shape-dev:arm64' (required by 'libopencv-contrib-dev:arm64')
dpkg: also configuring 'libopencv-stitching-dev:arm64' (required by 'libopencv-contrib-dev:arm64')
dpkg: also configuring 'libopencv-superres-dev:arm64' (required by 'libopencv-contrib-dev:arm64')
dpkg: also configuring 'libopencv-video-dev:arm64' (required by 'libopencv-contrib-dev:arm64')
dpkg: also configuring 'libopencv-videoio-dev:arm64' (required by 'libopencv-contrib-dev:arm64')
dpkg: also configuring 'libopencv-videostab-dev:arm64' (required by 'libopencv-contrib-dev:arm64')
dpkg: also configuring 'libopencv-viz-dev:arm64' (required by 'libopencv-contrib-dev:arm64')
dpkg: also configuring 'libopencv-core3.2:arm64' (required by 'libopencv-core-dev:arm64')
dpkg: also configuring 'libopencv-features2d3.2:arm64' (required by 'libopencv-features2d-dev:arm64')
dpkg: also configuring 'libopencv-flann-dev:arm64' (required by 'libopencv-features2d-dev:arm64')
dpkg: also configuring 'libopencv-highgui-dev:arm64' (required by 'libopencv-features2d-dev:arm64')
dpkg: also configuring 'libopencv-ml-dev:arm64' (required by 'libopencv-features2d-dev:arm64')
dpkg: also configuring 'libopencv-flann3.2:arm64' (required by 'libopencv-flann-dev:arm64')
dpkg: also configuring 'libdc1394-22-dev:arm64' (required by 'libopencv-highgui-dev:arm64')
dpkg: also configuring 'libgphoto2-dev:arm64' (required by 'libopencv-highgui-dev:arm64')
dpkg: also configuring 'libopencv-highgui3.2:arm64' (required by 'libopencv-highgui-dev:arm64')
dpkg: also configuring 'libopencv-videoio-dev:arm64' (required by 'libopencv-highgui-dev:arm64')
dpkg: also configuring 'libopenexr-dev' (required by 'libopencv-highgui-dev:arm64')
dpkg: also configuring 'libraw1394-dev:arm64' (required by 'libopencv-highgui-dev:arm64')
dpkg: also configuring 'libgdcm2-dev' (required by 'libopencv-imgcodecs-dev:arm64')
dpkg: also configuring 'libopencv-imgcodecs3.2:arm64' (required by 'libopencv-imgcodecs-dev:arm64')
dpkg: also configuring 'libopencv-imgproc-dev:arm64' (required by 'libopencv-imgcodecs-dev:arm64')
dpkg: also configuring 'libopencv-imgproc3.2:arm64' (required by 'libopencv-imgproc-dev:arm64')
dpkg: also configuring 'libopencv-ml3.2:arm64' (required by 'libopencv-ml-dev:arm64')
dpkg: also configuring 'libopencv-objdetect3.2:arm64' (required by 'libopencv-objdetect-dev:arm64')
dpkg: also configuring 'libopencv-photo3.2:arm64' (required by 'libopencv-photo-dev:arm64')
dpkg: also configuring 'libopencv-shape3.2:arm64' (required by 'libopencv-shape-dev:arm64')
dpkg: also configuring 'libopencv-video-dev:arm64' (required by 'libopencv-shape-dev:arm64')
dpkg: also configuring 'libopencv-stitching3.2:arm64' (required by 'libopencv-stitching-dev:arm64')
dpkg: also configuring 'libopencv-superres3.2:arm64' (required by 'libopencv-superres-dev:arm64')
dpkg: also configuring 'libopencv-video-dev:arm64' (required by 'libopencv-superres-dev:arm64')
dpkg: also configuring 'libopencv-videoio-dev:arm64' (required by 'libopencv-superres-dev:arm64')
dpkg: also configuring 'libopencv-video3.2:arm64' (required by 'libopencv-video-dev:arm64')
dpkg: also configuring 'libgphoto2-dev:arm64' (required by 'libopencv-videoio-dev:arm64')
dpkg: also configuring 'libopencv-videoio3.2:arm64' (required by 'libopencv-videoio-dev:arm64')
dpkg: also configuring 'libopencv-videostab3.2:arm64' (required by 'libopencv-videostab-dev:arm64')
dpkg: also configuring 'libopencv-viz3.2:arm64' (required by 'libopencv-viz-dev:arm64')
dpkg: also configuring 'libopencv3.2-jni' (required by 'libopencv3.2-java')
dpkg: also configuring 'libopencv-features2d3.2:arm64' (required by 'libopencv-calib3d3.2:arm64')
dpkg: also configuring 'libopencv-core3.2:arm64' (required by 'libopencv-calib3d3.2:arm64')
dpkg: also configuring 'libopencv-flann3.2:arm64' (required by 'libopencv-calib3d3.2:arm64')
dpkg: also configuring 'libopencv-imgproc3.2:arm64' (required by 'libopencv-calib3d3.2:arm64')
dpkg: also configuring 'libopencv-core3.2:arm64' (required by 'libopencv-contrib3.2:arm64')
dpkg: also configuring 'libopencv-features2d3.2:arm64' (required by 'libopencv-contrib3.2:arm64')
dpkg: also configuring 'libopencv-flann3.2:arm64' (required by 'libopencv-contrib3.2:arm64')
dpkg: also configuring 'libopencv-highgui3.2:arm64' (required by 'libopencv-contrib3.2:arm64')
dpkg: also configuring 'libopencv-imgcodecs3.2:arm64' (required by 'libopencv-contrib3.2:arm64')
dpkg: also configuring 'libopencv-imgproc3.2:arm64' (required by 'libopencv-contrib3.2:arm64')
dpkg: also configuring 'libopencv-ml3.2:arm64' (required by 'libopencv-contrib3.2:arm64')
dpkg: also configuring 'libopencv-objdetect3.2:arm64' (required by 'libopencv-contrib3.2:arm64')
dpkg: also configuring 'libopencv-photo3.2:arm64' (required by 'libopencv-contrib3.2:arm64')
dpkg: also configuring 'libopencv-shape3.2:arm64' (required by 'libopencv-contrib3.2:arm64')
dpkg: also configuring 'libopencv-stitching3.2:arm64' (required by 'libopencv-contrib3.2:arm64')
dpkg: also configuring 'libopencv-superres3.2:arm64' (required by 'libopencv-contrib3.2:arm64')
dpkg: also configuring 'libopencv-video3.2:arm64' (required by 'libopencv-contrib3.2:arm64')
dpkg: also configuring 'libopencv-videoio3.2:arm64' (required by 'libopencv-contrib3.2:arm64')
dpkg: also configuring 'libopencv-videostab3.2:arm64' (required by 'libopencv-contrib3.2:arm64')
dpkg: also configuring 'libopencv-viz3.2:arm64' (required by 'libopencv-contrib3.2:arm64')
dpkg: also configuring 'libtesseract4' (required by 'libopencv-contrib3.2:arm64')
Setting up libopencv-core3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
dpkg: also configuring 'libopencv-flann3.2:arm64' (required by 'libopencv-features2d3.2:arm64')
dpkg: also configuring 'libopencv-highgui3.2:arm64' (required by 'libopencv-features2d3.2:arm64')
dpkg: also configuring 'libopencv-ml3.2:arm64' (required by 'libopencv-features2d3.2:arm64')
dpkg: also configuring 'libopencv-imgproc3.2:arm64' (required by 'libopencv-features2d3.2:arm64')
dpkg: also configuring 'libopencv-videoio3.2:arm64' (required by 'libopencv-highgui3.2:arm64')
dpkg: also configuring 'libopencv-imgcodecs3.2:arm64' (required by 'libopencv-highgui3.2:arm64')
dpkg: also configuring 'libopencv-imgproc3.2:arm64' (required by 'libopencv-highgui3.2:arm64')
dpkg: also configuring 'libopencv-imgproc3.2:arm64' (required by 'libopencv-imgcodecs3.2:arm64')
dpkg: also configuring 'libopenexr22:arm64' (required by 'libopencv-imgcodecs3.2:arm64')
Setting up libopencv-imgproc3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-core-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-flann3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-flann-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
dpkg: also configuring 'libraw1394-dev:arm64' (required by 'libdc1394-22-dev:arm64')
dpkg: also configuring 'libexif-dev:arm64' (required by 'libgphoto2-dev:arm64')
dpkg: also configuring 'libilmbase-dev' (required by 'libopenexr-dev')
dpkg: also configuring 'libopenexr22:arm64' (required by 'libopenexr-dev')
Setting up libraw1394-dev:arm64 (2.1.2-1) ...
Setting up libgdcm2-dev (2.8.4-1build2) ...
Setting up libopencv-imgproc-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-ml3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-ml-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-photo3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-photo-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
dpkg: also configuring 'libopencv-video3.2:arm64' (required by 'libopencv-shape3.2:arm64')
dpkg: also configuring 'libopencv-video3.2:arm64' (required by 'libopencv-superres3.2:arm64')
Setting up libopencv-ts-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-video3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-video-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-viz3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-viz-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
dpkg: also configuring 'liblept5' (required by 'libtesseract4')
Setting up libopenexr22:arm64 (2.2.0-11.1ubuntu1.3) ...
Setting up libopencv-imgcodecs3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-videoio3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libdc1394-22-dev:arm64 (2.2.5-1) ...
dpkg: also configuring 'libexif12:arm64' (required by 'libexif-dev:arm64')
Setting up libilmbase-dev (2.2.0-11ubuntu2) ...
Setting up libopenexr-dev (2.2.0-11.1ubuntu1.3) ...
Setting up libopencv-imgcodecs-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-shape3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-shape-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-superres3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up liblept5 (1.75.3-3) ...
Setting up libtesseract4 (4.00~git2288-10f4998a-2) ...
Setting up libopencv-highgui3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libexif12:arm64 (0.6.21-4ubuntu0.5) ...
Setting up libexif-dev:arm64 (0.6.21-4ubuntu0.5) ...
Setting up libgphoto2-dev:arm64 (2.5.16-2) ...
Setting up libopencv-objdetect3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-videoio-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-features2d3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-highgui-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-objdetect-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-superres-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-calib3d3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-features2d-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-stitching3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-videostab3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-contrib3.2:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-calib3d-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-stitching-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-videostab-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv3.2-jni (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv3.2-java (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-contrib-dev:arm64 (3.2.0+dfsg-4ubuntu0.1) ...
Setting up libopencv-dev (3.2.0+dfsg-4ubuntu0.1) ...
Processing triggers for man-db (2.8.3-2ubuntu0.1) ...
Processing triggers for libc-bin (2.27-3ubuntu1) ...
nvidia@nvidia-desktop:~$ sudo apt install ros-melodic-desktop-full
Reading package lists... Done
Building dependency tree       
Reading state information... Done
ros-melodic-desktop-full is already the newest version (1.4.1-0bionic.20200823.044522).
The following packages were automatically installed and are no longer required:
  apt-clone archdetect-deb bogl-bterm busybox-static cryptsetup-bin dpkg-repack gir1.2-timezonemap-1.0 gir1.2-xkl-1.0 grub-common kde-window-manager
  kinit kio kpackagetool5 kwayland-data kwin-common kwin-data kwin-x11 libdebian-installer4 libkdecorations2-5v5 libkdecorations2private5v5
  libkf5activities5 libkf5attica5 libkf5completion-data libkf5completion5 libkf5declarative-data libkf5declarative5 libkf5doctools5
  libkf5globalaccel-data libkf5globalaccel5 libkf5globalaccelprivate5 libkf5idletime5 libkf5jobwidgets-data libkf5jobwidgets5 libkf5kcmutils-data
  libkf5kcmutils5 libkf5kiocore5 libkf5kiontlm5 libkf5kiowidgets5 libkf5newstuff-data libkf5newstuff5 libkf5newstuffcore5 libkf5package-data
  libkf5package5 libkf5plasma5 libkf5quickaddons5 libkf5solid5 libkf5solid5-data libkf5sonnet5-data libkf5sonnetcore5 libkf5sonnetui5
  libkf5textwidgets-data libkf5textwidgets5 libkf5waylandclient5 libkf5waylandserver5 libkf5xmlgui-bin libkf5xmlgui-data libkf5xmlgui5
  libkscreenlocker5 libkwin4-effect-builtins1 libkwineffects11 libkwinglutils11 libkwinxrenderutils11 libqgsttools-p1 libqt5multimedia5
  libqt5multimedia5-plugins libqt5multimediaquick-p5 libqt5multimediawidgets5 libxcb-composite0 libxcb-cursor0 libxcb-damage0 os-prober python-networkx
  python-pywt python-skimage python-skimage-lib python3-dbus.mainloop.pyqt5 python3-icu python3-pam python3-pyqt5 python3-pyqt5.qtsvg
  python3-pyqt5.qtwebkit python3-sip qml-module-org-kde-kquickcontrolsaddons qml-module-qtmultimedia qml-module-qtquick2 rdate
  ros-melodic-grid-map-core ros-melodic-jsk-gui-msgs ros-melodic-jsk-hark-msgs ros-melodic-people-msgs ros-melodic-view-controller-msgs tasksel
  tasksel-data
Use 'sudo apt autoremove' to remove them.
0 upgraded, 0 newly installed, 0 to remove and 342 not upgraded.
26 not fully installed or removed.
After this operation, 0 B of additional disk space will be used.
Do you want to continue? [Y/n] y
Setting up ros-melodic-image-geometry (1.13.0-0bionic.20200822.044213) ...
Setting up libexif-doc (0.6.21-4ubuntu0.5) ...
Setting up libraw1394-tools (2.1.2-1) ...
Setting up ros-melodic-cv-bridge (1.13.0-0bionic.20200822.025653) ...
Setting up ros-melodic-compressed-image-transport (1.9.5-0bionic.20200822.035123) ...
Setting up ros-melodic-image-proc (1.15.0-1bionic.20200822.051219) ...
Setting up ros-melodic-stereo-image-proc (1.15.0-1bionic.20200822.070442) ...
Setting up ros-melodic-image-view (1.15.0-1bionic.20200822.051301) ...
Setting up ros-melodic-rqt-image-view (0.4.16-1bionic.20200822.034436) ...
Setting up ros-melodic-depth-image-proc (1.15.0-1bionic.20200822.162410) ...
Setting up ros-melodic-rqt-common-plugins (0.4.8-0bionic.20200822.220029) ...
Setting up ros-melodic-image-rotate (1.15.0-1bionic.20200822.181832) ...
Setting up ros-melodic-camera-calibration (1.15.0-1bionic.20200822.055930) ...
Setting up ros-melodic-vision-opencv (1.13.0-0bionic.20200822.083322) ...
Setting up ros-melodic-theora-image-transport (1.9.5-0bionic.20200822.034457) ...
Setting up ros-melodic-image-publisher (1.15.0-1bionic.20200822.032038) ...
Setting up ros-melodic-compressed-depth-image-transport (1.9.5-0bionic.20200822.035126) ...
Setting up ros-melodic-gazebo-plugins (2.8.7-1bionic.20200822.185105) ...
Setting up ros-melodic-viz (1.4.1-0bionic.20200823.042931) ...
Setting up ros-melodic-image-pipeline (1.15.0-1bionic.20200822.201702) ...
Setting up ros-melodic-image-transport-plugins (1.9.5-0bionic.20200822.084327) ...
Setting up ros-melodic-gazebo-ros-pkgs (2.8.7-1bionic.20200822.211607) ...
Setting up ros-melodic-desktop (1.4.1-0bionic.20200823.044216) ...
Setting up ros-melodic-simulators (1.4.1-0bionic.20200823.043020) ...
Setting up ros-melodic-perception (1.4.1-0bionic.20200823.002734) ...
Setting up ros-melodic-desktop-full (1.4.1-0bionic.20200823.044522) ...
nvidia@nvidia-desktop:~/autoware-1.14$ rosdep install -y --from-paths src --ignore-src --rosdistro $ROS_DISTRO




