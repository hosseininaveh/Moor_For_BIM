#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "yocs_waypoint_provider/waypoint_provider.hpp"
#include "yocs_waypoint_provider/yaml_parser.hpp"
#include <yocs_msgs/WaypointList.h>
#include <iostream>
#include "std_msgs/String.h"
using namespace std;
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
void move_base_waypoints(ros::NodeHandle& n, const yocs_msgs::WaypointList& wps);
move_base_msgs::MoveBaseGoal buildGoal(const yocs_msgs::Waypoint& wp);
int main(int argc, char** argv)
{
  ros::init(argc, argv, "waypoint_provider");
  ros::NodeHandle priv_n("~");
  ros::NodeHandle n;
  yocs::WaypointProvider* wm;
  yocs_msgs::WaypointList wps;
  yocs_msgs::TrajectoryList trajs;
  std::string filename;

  if(!priv_n.getParam("filename", filename)) {
    ROS_ERROR("Waypoint Provider : filename argument is not set");
    return -1;
  }

  if(!yocs::loadWaypointsAndTrajectoriesFromYaml(filename, wps, trajs))
  {
    ROS_ERROR("Waypoint Provider : Failed to parse yaml[%s]",filename.c_str());
    return -1;
  }
  ros::Rate loop_rate(10);
 while (ros::ok())
  {
    wm = new yocs::WaypointProvider(n, wps, trajs);
    ROS_INFO("Waypoint Provider : Initialized");

    move_base_waypoints(n, wps);
    wm->spin();
    ROS_INFO("Waypoint Provider : Bye Bye");

    delete wm;
    loop_rate.sleep();
  }
  return 0;
}

 void move_base_waypoints(ros::NodeHandle& n, const yocs_msgs::WaypointList& wps)
{
  MoveBaseClient ac("move_base", true);
  std_msgs::String msg;
  char command;
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("IfCapture", 1);
  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  for(int i = 0; i < wps.waypoints.size(); i++)
    {
      yocs_msgs::Waypoint wp;
      wp.pose.position.x=wps.waypoints[i].pose.position.x;
      wp.pose.position.y=wps.waypoints[i].pose.position.y;
      wp.pose.position.z=wps.waypoints[i].pose.position.z;
      wp.pose.orientation.x=wps.waypoints[i].pose.orientation.x;
      wp.pose.orientation.y=wps.waypoints[i].pose.orientation.y;
      wp.pose.orientation.z=wps.waypoints[i].pose.orientation.z;
      wp.pose.orientation.w=wps.waypoints[i].pose.orientation.w;
      move_base_msgs::MoveBaseGoal goal = buildGoal(wp); //initiate a move_base_msg called goal

      ac.sendGoal(goal);
      ac.waitForResult();
     
      if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      {
         ROS_INFO("Hooray, the goal is reached");
         command='p';
         msg.data =command ;
         chatter_pub.publish(msg);
         ros::Duration(1).sleep();
         ROS_INFO("an image is captured");
      }
      else
         ROS_INFO("The base failed to move the the goal for some reasons");
      command=' ';
      msg.data =command ;
      chatter_pub.publish(msg);
    }
}
move_base_msgs::MoveBaseGoal buildGoal(const yocs_msgs::Waypoint& wp)
{
    move_base_msgs::MoveBaseGoal goal;

    //Specify what frame we want the goal to be published in
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

    // Specify x and y goal
    goal.target_pose.pose.position.x = wp.pose.position.x; //specify x goal
    goal.target_pose.pose.position.y = wp.pose.position.y; //specify y goal
    goal.target_pose.pose.orientation.x = wp.pose.orientation.x;   // don't care about heading because we aren't actually acheiving our goal
    goal.target_pose.pose.orientation.y = wp.pose.orientation.y;   // don't care about heading because we aren't actually acheiving our goal
    goal.target_pose.pose.orientation.z = wp.pose.orientation.z;   // don't care about heading because we aren't actually acheiving our goal
    goal.target_pose.pose.orientation.w = wp.pose.orientation.w;   // don't care about heading because we aren't actually acheiving our goal
cout<<"Executing move_base goal to position x:" << goal.target_pose.pose.position.x << "  y:" <<goal.target_pose.pose.position.y<<"  z: "<<goal.target_pose.pose.position.z;
    ROS_INFO("Sending goal");
    return goal;
}

