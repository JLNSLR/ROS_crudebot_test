#include "ros/ros.h"
#include <iostream>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include "crudebot_test_pkg/Demo_actionAction.h"

int main(int argc, char ** argv){

    ros::init(argc,argv, "demo_action_client");

    if(argc !=3){
        ROS_INFO("%d", argc);
        ROS_WARN("Usage: demo:action_client <goal> <time_to_preempt_in_sec>");
        return 1;
    }

    //create the action client
    // true causes the client to spin its own thread

    actionlib::SimpleActionClient<crudebot_test_pkg::Demo_actionAction> ac("demo_action", true);

    ROS_INFO("Waiting for action server to start");

    ac.waitForServer(); //will wait for infinite time;

    ROS_INFO("Action server started, sending goal.");

    // send a goal to the action

    crudebot_test_pkg::Demo_actionGoal goal;
    goal.count = atoi(argv[1]);

    ROS_INFO("Sending Goal [%d] and Preempt time of [%d]", goal.count, atoi(argv[2]));
    ac.sendGoal(goal);


    //wait for the action to return
    bool finished_before_timeout = ac.waitForResult(ros::Duration(atoi(argv[2])));

    if(finished_before_timeout){
        actionlib::SimpleClientGoalState state = ac.getState();
        ROS_INFO("Action finished: %s", state.toString().c_str());
        //Preempting the process
        ac.cancelGoal();
    }else{
        ROS_INFO("Action did not finished before the time out");
    }

    //exit

    return 0;
}



