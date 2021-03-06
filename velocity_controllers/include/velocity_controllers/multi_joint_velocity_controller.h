/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2008, Willow Garage, Inc.
 *  Copyright (c) 2012, hiDOF, Inc.
 *  Copyright (c) 2013, Johns Hopkins University
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

#ifndef VELOCITY_CONTROLLERS_MULTI_JOINT_VELOCITY_CONTROLLER_H
#define VELOCITY_CONTROLLERS_MULTI_JOINT_VELOCITY_CONTROLLER_H

/**
   @class velocity_controllers:MultiJointVelocityController
   @brief Joint Velocity Controller (torque or force)

   This class passes the commanded effort down to the joint

   @section ROS interface

   @param type Must be "MultiJointVelocityController"
   @param joint Name of the joint to control.

   Subscribes to:
   - @b command (std_msgs::Float64) : The joint effort to apply
*/

#include <boost/thread/condition.hpp>
#include <ros/node_handle.h>
// Urdf
#include <urdf/model.h>
#include <hardware_interface/joint_command_interface.h>
#include <controller_interface/controller.h>
#include <std_msgs/Float64MultiArray.h>
// State Publishing   
#include <controllers_msgs/JointControllerState.h>
#include <boost/scoped_ptr.hpp>
#include <boost/thread/condition.hpp>
#include <realtime_tools/realtime_publisher.h>


namespace velocity_controllers
{

class MultiJointVelocityController: public controller_interface::Controller<hardware_interface::VelocityJointInterface>
{
public:
  MultiJointVelocityController();
  ~MultiJointVelocityController();
  bool init(hardware_interface::VelocityJointInterface *robot, ros::NodeHandle &n);
  void starting(const ros::Time& time){}
  void update(const ros::Time& time, const ros::Duration& period);
  void stopping(const ros::Time& time);
  // Members
  unsigned int num_joints_;
  std::vector<double> joint_vel_limits_;
  std::vector<double> joint_upper_position_limits_;
  std::vector<double> joint_lower_position_limits_;

  std::vector<std::string> joint_names_;
  std::vector<hardware_interface::JointHandle> joints_;
  std::vector< boost::shared_ptr<const urdf::Joint> > joint_urdf_;
  std::vector<double> command_;
private:
  ros::Subscriber sub_command_;
  void commandCB(const std_msgs::Float64MultiArrayConstPtr& msg);
};

}

#endif
