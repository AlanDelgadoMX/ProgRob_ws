#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

#include <functional>

class SubscriberCpp : public rclcpp::Node
{
    public:
    
     SubscriberCpp() : Node("subscriber_cpp")
     {
         subscription_ = this->create_subscription<std_msgs::msg::String>(
             "TraficoZMG", 10, std::bind(&SubscriberCpp::received_message, this, std::placeholders::_1));
     }

     private:

        void received_message(const std_msgs::msg::String::SharedPtr msg) const 
        {
            RCLCPP_INFO(this->get_logger(), "Mensaje Recibido: '%s'", msg->data.c_str());
        }

        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;

};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SubscriberCpp>());
    rclcpp::shutdown();
    return 0;
}