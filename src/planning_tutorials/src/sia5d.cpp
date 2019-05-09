#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include <moveit_visual_tools/moveit_visual_tools.h>
#include <iostream>


int main(int argc, char** argv)
{
  ros::init(argc, argv, "move_group_interface_tutorial");
  ros::NodeHandle node_handle;
  ros::AsyncSpinner spinner(1);
  spinner.start();

  static const std::string PLANNING_GROUP = "sia5";

  moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);

  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;

  moveit::planning_interface::MoveGroupInterface::Plan my_plan;

  namespace rvt = rviz_visual_tools;
  
  moveit_visual_tools::MoveItVisualTools visual_tools("base_link");

  Eigen::Affine3d text_pose = Eigen::Affine3d::Identity();
  text_pose.translation().z() = 1;	

  ROS_INFO_NAMED("tutorial", "Reference frame: %s", move_group.getPlanningFrame().c_str());

  ROS_INFO_NAMED("tutorial", "End effector link: %s", move_group.getEndEffectorLink().c_str());

  // Start the demo
  // ^^^^^^^^^^^^^^^^^^^^^^^^^


  geometry_msgs::Pose target_pose1 = move_group.getCurrentPose().pose;

  std::vector<geometry_msgs::Pose> waypoints;
  waypoints.push_back(target_pose1);

  target_pose1.position.z -= 0.2;
  waypoints.push_back(target_pose1);  // down
  move_group.setStartStateToCurrentState();

  target_pose1.position.y -= 0.2;
  waypoints.push_back(target_pose1);  // right
  
  target_pose1.position.z += 0.2;
  target_pose1.position.y += 0.2;

  waypoints.push_back(target_pose1);  // up and left
  
  move_group.setMaxVelocityScalingFactor(0.1);

  moveit_msgs::RobotTrajectory trajectory;
  const double jump_threshold = 0.0;
  const double eef_step = 0.01;

  double fraction = move_group.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);

  ROS_INFO_NAMED("tutorial", "Visualizing plan 4 (Cartesian path) (%.2f%% acheived)", fraction * 100.0);

  visual_tools.publishText(text_pose, "Motoman sia5d", rvt::RED, rvt::XLARGE);
  visual_tools.publishPath(waypoints, rvt::LIME_GREEN, rvt::SMALL);
  for (std::size_t i = 0; i < waypoints.size(); ++i)
    visual_tools.publishAxisLabeled(waypoints[i], "pt" + std::to_string(i), rvt::SMALL);
  move_group.move();
  visual_tools.trigger();

  my_plan.trajectory_=trajectory;
  move_group.execute(my_plan);

  ros::shutdown();
  return 0;
}
