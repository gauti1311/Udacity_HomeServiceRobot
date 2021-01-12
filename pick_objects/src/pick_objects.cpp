#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;


float pickup[3] = {5.0, 6.0, 1.0};
float dropoff[3] = {2.0, -3.0, 1.0};

int main(int argc, char** argv)
{
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;
  
  //ros::Publisher goal_pub = n.advertise<geometry_msgs::Pose>("/target",20);

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal pickup_goal;

  // set up the frame parameters
  pickup_goal.target_pose.header.frame_id = "/map";
  pickup_goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  pickup_goal.target_pose.pose.position.x = pickup[0];
  pickup_goal.target_pose.pose.position.y = pickup[1];
  pickup_goal.target_pose.pose.orientation.w = pickup[2];

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pick-up goal");
  ac.sendGoal(pickup_goal);
  
  geometry_msgs::Pose pick_msg;
  pick_msg.position.x =pickup[0];
  pick_msg.position.y = pickup[1];
  pick_msg.position.z = 0.0;
  pick_msg.orientation.x = 0.0;
  pick_msg.orientation.y = 0.0;
  pick_msg.orientation.z = 0.0;
  pick_msg.orientation.w = pickup[2];
  //goal_pub.publish(pick_msg);
  ROS_INFO("Publishing goal for pickup location x:%f, y:%f, w:%f",  pick_msg.position.x, pick_msg.position.y, pick_msg.orientation.w );

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    ROS_INFO("Hooray, the robot reached to Pick-up location");
    ros::Duration(5.0).sleep();
    
    move_base_msgs::MoveBaseGoal dropoff_goal;

  // set up the frame parameters
  	dropoff_goal.target_pose.header.frame_id = "map";
  	dropoff_goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
    dropoff_goal.target_pose.pose.position.x = dropoff[0];
    dropoff_goal.target_pose.pose.position.y = dropoff[1];
    dropoff_goal.target_pose.pose.orientation.w = dropoff[2];

    ROS_INFO("Sending pick-up goal");
    ac.sendGoal(dropoff_goal);

    geometry_msgs::Pose drop_msg;
    drop_msg.position.x = dropoff[0];
    drop_msg.position.y = dropoff[1];
    drop_msg.position.z = 0.0;
    drop_msg.orientation.x = 0.0;
    drop_msg.orientation.y = 0.0;
    drop_msg.orientation.z = 0.0;
    drop_msg.orientation.w = dropoff[2];
    //goal_pub.publish(drop_msg);
    ROS_INFO("Publishing goal for drop-off location x:%f, y:%f, w:%f", drop_msg.position.x, drop_msg.position.y, drop_msg.orientation.w );

    // Wait an infinite time for the results
    ac.waitForResult();

    // Check if the robot reached its goal
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("Hooray, the robot reached to Drop-off location");
    else
      ROS_INFO("The robot failed to move to Drop-off location for some reason");
   }
  else
    ROS_INFO("The robot failed to move to Pick-up location for some reason");
  
 return 0;
}