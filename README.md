# Moor_For_BIM
Autonomous six wheels Robot for 3D modelling of a building


This package needs ROS melodic installed on your system. It was successfully run on ubuntu 18.0.4

-----------------------Installation: 

sudo apt-get install ros-melodic-move-base 
sudo apt-get install ros-melodic-navigation

--If there is a catkin workspace in the home direcotry named catkin_ws, then 

cd ~/catkin_ws/src 
git clone https://github.com/yujinrobot/yocs_msgs.git
git clone https://github.com/hosseininaveh/Moor_For_BIM 
git clone https://github.com/turtlebot/turtlebot/tree/melodic

cd ~/catkin_ws
rosdep install --from-paths src -i -y
catkin_make

-----------------------Running the repository: 
--terminal 1: roslaunch mybot_gazebo mybot_world.launch

--Terminal 2: roslaunch moor_navigation moor_amcl_demo.launch

--Terminal 3: rosrun rviz rviz and open file /home/ali/mybot_ws/src/moor_navigation/rviz/rviz_config.rviz
