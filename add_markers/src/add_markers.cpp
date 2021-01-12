#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <math.h>


float pickup[2] = {5.0, 6.0};
float dropoff[2] = {2.0, -3.0};
float thresh = 0.5f;
bool move = false;
bool dropped = false;
float current[2] = {pickup[0], pickup[1]};

visualization_msgs::Marker marker;
ros::Publisher marker_pub;

//map correction odom
float odom_pick[2] = {-6.0, 5.0};
float odom_drop[2] = {3.0, 2.0};

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
   float x = msg->pose.pose.position.x;
   float y = msg->pose.pose.position.y;

   //before pickup
   if(!move)
   {  
      marker.pose.position.x = current[0];
      marker.pose.position.y = current[1];
      marker_pub.publish(marker);
   }

   if(fabs(x - odom_pick[0]) <= thresh && fabs(y - odom_pick[1]) <= thresh)
   {
      marker.action = visualization_msgs::Marker::DELETE;
      marker_pub.publish(marker);
      ROS_INFO("Robot picked up object");
      move = true;
   }
   else if(fabs(x - odom_drop[0]) <= thresh && fabs(y - odom_drop[1]) <= thresh)
   {
      // current[0] = dropoff[0];
      // current[1] = dropoff[1];
      marker.pose.position.x = dropoff[0];
      marker.pose.position.y = dropoff[1];
      marker.action = visualization_msgs::Marker::ADD;
      marker_pub.publish(marker);
      ROS_INFO("Robot drpped the object");
      dropped = true;
   }

}

// void goalCallback(const geometry_msgs::Pose& pos)
// {
//    current[0] = pose.pose.position.x;
//    current[1] = pose.pose.position.y;
// }

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber odom_sub = n.subscribe("/odom", 10, odomCallback);
  //ros::Subscriber target_sub = n.subscribe("/target", 10, goalCallback);
   // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  while (ros::ok())
  {
      marker.header.frame_id = "map";
      marker.header.stamp = ros::Time::now();

      // Set the namespace and id for this marker.  This serves to create a unique ID
      // Any marker sent with the same namespace and id will overwrite the old one
      marker.ns = "add_markers";
      marker.id = 0;

      // Set the marker type as CUBE
      marker.type = visualization_msgs::Marker::CYLINDER;

      // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the heade
      
      // Set the scale of the marker
      marker.scale.x = 0.25;
      marker.scale.y = 0.25;
      marker.scale.z = 0.25;

      // Set the color 
      marker.color.r = 0.0f;
      marker.color.g = 0.0f;
      marker.color.b = 1.0f;
      marker.color.a = 1.0;
      marker.lifetime = ros::Duration();
      //marker_pub.publish(marker);
      ros::spinOnce();   
      r.sleep();
  }
}