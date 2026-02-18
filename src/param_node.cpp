#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

/*
 * TODO: Create a Class named 'ParamNode' that inherits from rclcpp::Node.
 * Requirements:
 * 1. The constructor should name the node "param_node".
 * 2. Declare these parameters with default values:
 * - "robot_name" (string): default "ROS2Bot"
 * - "max_speed" (double): default 1.5
 * - "enabled" (bool): default true
 * 3. Create a timer that triggers every 2000ms.
 * 4. In timer callback, read parameters and log:
 * "Robot: <name>, Max Speed: <speed>, Enabled: <enabled>"
 */

class ParamNode : public rclcpp::Node
{
public:
    ParamNode()
        : Node("param_node")
    {
        // 1. Declare parameters with default values
        // Syntax: declare_parameter("name", default_value);
        this->declare_parameter("robot_name", "ROS2Bot");
        this->declare_parameter("max_speed", 1.5);
        this->declare_parameter("enabled", true);

        // 2. Create timer (2000ms)
        timer_ = this->create_wall_timer(
            2000ms,
            std::bind(&ParamNode::timer_callback, this));
    }

private:
    // 3. Define timer_callback function
    void timer_callback()
    {
        // Get the current values of the parameters
        // We fetch them every time so the log updates if params are changed externally
        std::string name = this->get_parameter("robot_name").as_string();
        double speed = this->get_parameter("max_speed").as_double();
        bool enabled = this->get_parameter("enabled").as_bool();

        // Log the output
        // Use ternary operator (condition ? true_val : false_val) to print "true/false" text
        RCLCPP_INFO(this->get_logger(), 
            "Robot: %s, Max Speed: %.2f, Enabled: %s", 
            name.c_str(), 
            speed, 
            enabled ? "true" : "false");
    }

    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ParamNode>());
    rclcpp::shutdown();
    return 0;
}
