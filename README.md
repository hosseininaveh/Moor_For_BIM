# Moor_For_BIM
Autonomous six wheels Robot for 3D modelling of a building

### The main step for installation

1) go to the following link and follow the steps mentioned in readme:
https://github.com/hosseininaveh/buildings

# Installation on ROS noetic: 
you can ignore the next step if you have Ubuntu 22.04 without docker
### Installing using Docker on Ubuntu 22.04 (WSL2)
If you are going to install the packages in Ubuntu 22.04 or later, you can use docker. In this case, please do these extra steps:
```
sudo apt update
sudo apt install docker.io
sudo systemctl start docker
sudo systemctl enable docker
docker pull ros:noetic-robot
sudo apt-get update
sudo apt-get install xauth libx11-xcb1 libx11-6 libxext6 libxrender1 libxmu6 libxi6
```
Make a Dockerfile using sudo gedit Dockerfile and write the following on it:
```
FROM ros:noetic

# Install ROS packages
RUN apt-get update && apt-get install -y \
    ros-noetic-cv-bridge \
    ros-noetic-image-transport \
    ros-noetic-joy \
    ros-noetic-controller-manager \
    ros-noetic-joint-state-controller \
    ros-noetic-joint-state-publisher \
    ros-noetic-gazebo-ros \
    ros-noetic-rviz \
    ros-noetic-move-base \
    ros-noetic-navigation \
    ros-noetic-robot-state-publisher \
    ros-noetic-xacro \
    ros-noetic-robot-localization

# Set up environment variables
ENV ROS_MASTER_URI=http://localhost:11311
ENV ROS_IP=127.0.0.1

# Set up X11 forwarding for GUI applications
RUN apt-get install -y x11-apps
RUN apt-get install -y gedit
# Copy the Gazebo model into the container
COPY ~/.gazebo/models/building /root/.gazebo/models/building
```
Run the following to install all requirements:
```
sudo docker build -t ros-noetic-custom .
```
Now, you have ROS noetic on docker in Ubuntu 22.04. To run the ros noetic commands, run the following code in the first terminal:
```
sudo docker volume create my_ros_data
sudo docker run -it -v my_ros_data:/ros_workspace  --rm  -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v ~/.Xauthority:/root/.Xauthority  ros-noetic-custom
```
and run these commands in the second terminal:
```
sudo docker ps -l
```
Find the name of the container as the ID
```
docker exec -it <the name of the container> bash
source ros_entrypoint.sh
```
The above two commands should be run for every new terminal for running ROS commands



### Go to step 4 if you are using Docker
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
sudo apt-get install ros-noetic-move-base 
sudo apt-get install ros-noetic-navigation
sudo apt-get install ros-noetic-robot-localization
sudo apt-get install ros-noetic-cv-bridge ros-noetic-image-transport ros-noetic-joy ros-noetic-controller-manager ros-noetic-joint-state-controller ros-noetic-gazebo-ros ros-noetic-rviz
```
4) Make a catkin workspace in the home directory and named catkin_ws, then 

```
mkdir -p catkin_ws/src
cd catkin_ws/src 
git clone https://github.com/yujinrobot/yocs_msgs.git
git clone https://github.com/hosseininaveh/Moor_For_BIM 
git clone https://github.com/turtlebot/turtlebot.git
git clone https://github.com/husky/husky.git
cd ..
rosdep install --from-paths src -i -y
catkin_make
```
5) make a directory in Desktop using the follwoing command:
```
mkdir moor_images
```

# Running the repository: 
If you are using Docker use the following commands when opening a new terminal
```
docker exec -it <the name of the container> bash
source ros_entrypoint.sh
```
in terminal 1:
```
roslaunch mybot_gazebo mybot_world.launch
```
It takes time to download the models in .gazebo folder. So, It is time to have a cup of coffee :) 
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

