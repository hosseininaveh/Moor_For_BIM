/*
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include "nav_msgs/Odometry.h"
#include <tf/transform_broadcaster.h>
#include <fstream>
#include <string>
#include<algorithm>
#include<vector>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <std_msgs/Float32.h>
#include <string>
#include "std_msgs/String.h"
#define EXIT_FILE_ERROR (1)
#define EXIT_UNEXPECTED_EOF (2)
#define EXIT_INVALID_FIRSTLINE (3)
#define MAXLINE (10000)
void input_goals();
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
float x, y, z, or_x, or_y, or_z, or_w, vx, av_z;
void chatterCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
  
  x= msg->pose.pose.position.x;
  y=msg->pose.pose.position.y;

  ROS_INFO ("x=%f, y=%f", x,y);
}
void chatterCallback2(const nav_msgs::Odometry::ConstPtr& msg)
{
  or_x=msg->pose.pose.orientation.x;
  or_y=msg->pose.pose.orientation.y;
  or_z=msg->pose.pose.orientation.z;
  or_w=msg->pose.pose.orientation.w;
}
std::vector< std::vector<float> > targets;
using namespace std;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "simple_navigation_goals");
  ros::NodeHandle n;
  // input goals from file into targets matrix
  input_goals();
 
  // subscribe odom node to have x, y, yaw 
  ros::Subscriber sub = n.subscribe("/odom", 1000,chatterCallback); 
  ros::Subscriber sub2 = n.subscribe("/odom", 1000, chatterCallback2); 
  ros::Publisher pub = n.advertise<std_msgs::String>("capture_image", 1000);
  std_msgs:: String msg1, msg2;
  std::stringstream ss;
  ss<< "0" ;
  msg1.data = ss.str();
  pub.publish(msg1);
  ss.clear();
  ss<< "1" ;
  msg2.data = ss.str();
  tf::Quaternion q(or_x, or_y, or_z, or_w);
  tf::Matrix3x3 m(q);
  double roll, pitch, yaw;
  m.getRPY(roll, pitch, yaw);
 
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;
  for (int j=0; j<targets.size(); j++)
  {
	  float inc_x=targets[j][0] -x;
	  float inc_y=targets[j][1] -y;
	  float angle_to_goal=atan2(inc_y, inc_x);
	  pub.publish(msg1);

	  if (abs(sqrt(pow(inc_x,2)+pow(inc_y,2))) >0.1)
	  {
		  //we'll send a goal to the robot to move 0.1 meter forward
		  goal.target_pose.header.frame_id = "base_link";
		  goal.target_pose.header.stamp = ros::Time::now();
  
		  goal.target_pose.pose.position.x= inc_x;
		  goal.target_pose.pose.position.y= inc_y;
		  goal.target_pose.pose.position.z= 0.0;
		  goal.target_pose.pose.orientation.x= 0.0;
		  goal.target_pose.pose.orientation.y= 0.0;
		  goal.target_pose.pose.orientation.z= 0.0;
		 // goal.target_pose.pose.orientation.w= 1.0;
 		  ROS_INFO("move forward to the goal x=%f, y=%f", inc_x, inc_y);
        	  ac.sendGoal(goal);
	
        	  ac.waitForResult();

		  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
		    {
		    	ROS_INFO("reaching the goal ...");                    	
			 pub.publish(msg2);
			usleep(1000);

        	    }
		  else
		    ROS_INFO("Oh... No ... "); 
  	}
	ROS_INFO ("x=%f, y=%f, th=%f", x,y,yaw);
        sub = n.subscribe("/amcl_pose", 1000, chatterCallback);
  	tf::Quaternion q(or_x, or_y, or_z, or_w);
  	tf::Matrix3x3 m(q);
  	double roll, pitch, yaw;
  	m.getRPY(roll, pitch, yaw);
	ROS_INFO ("x=%f, y=%f, th=%f", x,y,yaw);

	  if (abs(yaw-targets[j][2]) >0.1)
	  {
		  //we'll send a goal to the robot to move 0.1 meter forward
		  goal.target_pose.header.frame_id = "base_link";
		  goal.target_pose.header.stamp = ros::Time::now();
  
		  goal.target_pose.pose.position.x= 0.0;
		  goal.target_pose.pose.position.y= 0.0;
		  goal.target_pose.pose.position.z= 0.0;
		  goal.target_pose.pose.orientation.x= 0.0;
		  goal.target_pose.pose.orientation.y= 0.0;
		  goal.target_pose.pose.orientation.z= 0.0;
		  goal.target_pose.pose.orientation.w= yaw-targets[j][2];
		  ac.sendGoal(goal);

        	  ac.waitForResult();

		  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
		  {
		    	ROS_INFO("ready to go ");
			pub.publish(msg2);
			usleep(1000);
 		  }
		  else
		    ROS_INFO("Oh My God! I cannot rotate"); 
     	   } 
  } 
   ros::spin();
   return 0;
}

void input_goals()
{
FILE *fp;
  string sFileName = "/home/ali/mybot_ws/src/simple_navigation_goals/goals/points.txt";
  ifstream fileStream(sFileName.c_str());
  if (!fileStream.is_open())
  {
	ROS_INFO("Exiting unable to open file" );
	exit(EXIT_FILE_ERROR);
  }
  std::string line;
  while (getline(fileStream, line, '\n')) {
	std::stringstream ss(line);
	std::vector<float> numbers;
	std::string in_line;
	while (getline(ss, in_line, ',')) {
		numbers.push_back(::strtod(in_line.c_str(), 0));
	}
	targets.push_back(numbers);
  }
  fileStream.close();
  if ((fp = fopen(sFileName.c_str(), "r")) == NULL)
  {
	ROS_INFO("Exiting unable to open file");
	exit(EXIT_FILE_ERROR);
  }
}
*/
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }



  move_base_msgs::MoveBaseGoal goal;

  //we'll send a goal to the robot to move 1 meter forward
  goal.target_pose.header.frame_id = "base_link";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = -1.0;
  goal.target_pose.pose.orientation.w = 1;


  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved 1 meter forward");
  else
    ROS_INFO("The base failed to move forward 1 meter for some reason");

  return 0;
}

