#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <chrono>
#include <functional>
#include <memory>

std_msgs::msg::String create_message() {
  auto message = std::make_shared<std_msgs::msg::String>();
  message->data = "Hola Mundo desde C++";
  return *message;
}

class PublisherCpp : public rclcpp::Node {

    public:
    PublisherCpp() : Node("noticias_alan") {
        publisher_ = this->create_publisher<std_msgs::msg::String>("TraficoZMG", 10);

        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&PublisherCpp::publish_message, this)
        );

    }
    
    private:


        void publish_message() {
            auto message = create_message();
            RCLCPP_INFO(this->get_logger(), "hola_eldiablo: '%s'", message.data.c_str());
            publisher_->publish(message);
        }

        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
    };

    int main(int argc, char * argv[]) {
        rclcpp::init(argc, argv);
        rclcpp::spin(std::make_shared<PublisherCpp>());
        rclcpp::shutdown();
        return 0;
    }