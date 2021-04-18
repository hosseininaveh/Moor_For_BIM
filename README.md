# Moor_For_BIM
Autonomous six wheels Robot for 3D modelling of a building


This package needs ROS melodic installed on your system. It was successfully run on ubuntu 18.0.4


It can also be used for ROS noetic and ubuntu 20.04. For this version for the word "melodic" in the following commands should be replaced with "noetic" 

-----------------------Installation: 


1) go to the following link and follow the steps mentioned in readme:
https://github.com/hosseininaveh/buildings

2) in case of using Ubuntu 20.04 and ROS noeti, the follwoing steps should be followed:

  sudo add-apt-repository universe

  sudo apt update 

  sudo apt install python2

  curl https://bootstrap.pypa.io/pip/2.7/get-pip.py --output get-pip.py

  sudo python2 get-pip.py
  
  sudo apt install python
 
  python -m pip install --user numpy scipy matplotlib ipython jupyter pandas sympy nose
  
3) the follwoing package should also be installed. In case of using ROS noetic, replace 'melodic' with 'noetic' in the follwoing commands:

 
sudo apt-get install ros-melodic-move-base 

sudo apt-get install ros-melodic-navigation

sudo apt-get install ros-melodic-robot-localization

4) If there is a catkin workspace in the home direcotry named catkin_ws, then 

cd ~/catkin_ws/src 

git clone https://github.com/yujinrobot/yocs_msgs.git

git clone https://github.com/hosseininaveh/Moor_For_BIM 

git clone https://github.com/turtlebot/turtlebot.git

git clone https://github.com/husky/husky.git

cd ~/catkin_ws

rosdep install --from-paths src -i -y

catkin_make

5) make a directory in Desktop using follwoing command:

mkdir ~/Desktop/moor_images

-----------------------Running the repository: 

in terminal 1:

roslaunch mybot_gazebo mybot_world.launch

in terminal 2:

roslaunch yocs_waypoint_provider provider.launch

in terminal 3:

roslaunch moor_navigation moor_amcl_demo.launch

in terminal 4:

rosrun rviz rviz and open file ~/catkin_ws/src/Moor_For_BIM/moor_navigation/rviz/rviz_config.rviz

After running the above commands, the robot should automatically navigate and capture the images from the building.
