# Moor_For_BIM
Autonomous six wheels Robot for 3D modelling of a building


This package needs ROS melodic installed on your system. It was successfully run on ubuntu 18.0.4


It can also be used for ROS noetic and ubuntu 20.04. For this version for the word "melodic" in the following commands should be replaced with "noetic" 

-----------------------Installation: 
go to the following link and follow the steps mentioned in readme:
https://github.com/hosseininaveh/buildings



sudo apt-get install ros-melodic-move-base 

sudo apt-get install ros-melodic-navigation

sudo apt-get install ros-melodic-robot-localization

--If there is a catkin workspace in the home direcotry named catkin_ws, then 

cd ~/catkin_ws/src 

git clone https://github.com/yujinrobot/yocs_msgs.git

git clone https://github.com/hosseininaveh/Moor_For_BIM 

git clone https://github.com/turtlebot/turtlebot/tree/melodic

cd ~/catkin_ws

rosdep install --from-paths src -i -y

catkin_make


-----------------------Running the repository: 

in terminal 1:

roslaunch mybot_gazebo mybot_world.launch

in terminal 2:

roslaunch yocs_waypoint_provider provider.launch

in terminal 3:

roslaunch moor_navigation moor_amcl_demo.launch

in terminal 4:

rosrun rviz rviz and open file ~/catkin_ws/src/Moor_For_BIM/moor_navigation/rviz/rviz_config.rviz
