#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>

//callback that is executed whenever data comes to the /numbers topic
void number_callback(const std_msgs::Int32::ConstPtr& msg){
    ROS_INFO("Received [%d]", msg->data);
}


int main(int argc, char **argv){

    ros::init(argc, argv,"demo_topic_subscriber");
    ros::NodeHandle node_obj;
    ros::Subscriber number_subscriber = node_obj.subscribe("/numbers",10,number_callback); //inits the subscriber with its buffer size

    ros::spin();
    return 0;
};