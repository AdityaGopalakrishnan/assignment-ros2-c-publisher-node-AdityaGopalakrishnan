#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class PublisherNode : public rclcpp::Node
{
public:
  PublisherNode()
  : Node("publisher_node"), count_(0)
  {
    // TODO: Create the publisher here
    // We create a publisher for std_msgs/String on topic "/counter" with a queue size of 10
    publisher_ = this->create_publisher<std_msgs::msg::String>("/counter", 10);

    // TODO: Initialize the timer here
    // We bind the timer_callback function to this timer instance, firing every 500ms
    timer_ = this->create_wall_timer(
      500ms, std::bind(&PublisherNode::timer_callback, this));
  }

private:
  // TODO: Define the timer_callback function here
  void timer_callback()
  {
    auto message = std_msgs::msg::String();
    
    // Format the string and increment the counter
    message.data = "Count: " + std::to_string(count_++);
    
    // Log the output to console
    // .c_str() is required because %s expects a C-style string, not a std::string
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    
    // Publish the message to the topic
    publisher_->publish(message);
  }

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PublisherNode>());
  rclcpp::shutdown();
  return 0;
}
