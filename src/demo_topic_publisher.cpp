#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>
int main(int argc, char **argv){
    /* initializes the rose node, the ros node should be unique*/
    ros::init(argc,argv,"demo_topic_publisher");
    /* creates a NodeHandle obj which is used to communicate with the ROS system */
    ros::NodeHandle node_obj;
    /* creates a topic publisher with the topic name /numbers with the message type
    <std_msgs::Int32>, the second is the buffer size -> number of messages to be put in a buffer
    before sending. Should be high for high data rates */
    ros::Publisher number_Publisher = node_obj.advertise<std_msgs::Int32>("/numbers",10);  
    ros::Rate loop_rate(10); //sets the frequency of the data


    int number_count = 0;

    while(ros::ok()){ // infinite while loop quits when roscore quits or CTRL+C
        std_msgs::Int32 msg; //creates ros message
        msg.data = number_count; //fills message
        ROS_INFO("%d", msg.data); //prints the message data, can be used for logging
        number_Publisher.publish(msg); // publishes the message to the topics /numbers
        ros::spinOnce(); // reads & updates the ROS topics, node will not publish without a spin() or spinOnce() function
        loop_rate.sleep();
        ++number_count;
    }  

    return 0;
};