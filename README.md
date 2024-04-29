# Moor_For_BIM
Autonomous six wheels Robot for 3D modelling of a building

# Installation on ROS noetic: 
If you are going to install the packages in Ubuntu 22.04 or later, you can use docker. In this case, please do these extra steps:
```
sudo apt update
sudo apt install docker.io
sudo systemctl start docker
sudo systemctl enable docker
docker pull ros:noetic-robot
```
Now, you will have ROS noetic on docker in Ubuntu 22.04. To run the docker run the following code in every terminal:
```
docker run -it ros:noetic-robot
```

1) go to the following link and follow the steps mentioned in readme:
https://github.com/hosseininaveh/buildings



2) in the case of using Ubuntu 20.04 and ROS noetic, the following steps should be followed:

```
  sudo add-apt-repository universe
  sudo apt update 
  sudo apt install python2
  curl https://bootstrap.pypa.io/pip/2.7/get-pip.py --output get-pip.py
  sudo python2 get-pip.py
  sudo apt install python
  python -m pip install --user numpy scipy matplotlib ipython jupyter pandas sympy nose
```  
3) the following packages should also be installed. 

 ```
sudo apt-get install ros-melodic-move-base 
sudo apt-get install ros-melodic-navigation
sudo apt-get install ros-melodic-robot-localization
```
4) If there is a catkin workspace in the home directory named catkin_ws, then 

```
cd ~/catkin_ws/src 
git clone https://github.com/yujinrobot/yocs_msgs.git
git clone https://github.com/hosseininaveh/Moor_For_BIM 
git clone https://github.com/turtlebot/turtlebot.git
git clone https://github.com/husky/husky.git

sudo apt-get install ros-noetic-cv-bridge ros-noetic-image-transport ros-noetic-joy ros-noetic-controller-manager ros-noetic-joint-state-controller ros-noetic-gazebo-ros

cd ~/catkin_ws
rosdep install --from-paths src -i -y
catkin_make
```
5) make a directory in Desktop using follwoing command:
```
mkdir ~/Desktop/moor_images
```

# Running the repository: 

in terminal 1:
```
roslaunch mybot_gazebo mybot_world.launch
```
in terminal 2:
```
roslaunch yocs_waypoint_provider provider.launch
```
in terminal 3:
```
roslaunch moor_navigation moor_amcl_demo.launch
```
in terminal 4:
```
rosrun rviz rviz and open file ~/catkin_ws/src/Moor_For_BIM/moor_navigation/rviz/rviz_config.rviz
```
After running the above commands, the robot should automatically navigate and capture the images from the building.


Citation:


Hosseininaveh, Ali, and Fabio Remondino. "An Imaging Network Design for UGV-Based 3D Reconstruction of Buildings." Remote Sensing 13, no. 10 (2021): 1923.
https://www.mdpi.com/2072-4292/13/10/1923

