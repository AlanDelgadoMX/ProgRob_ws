#include "rclcpp/rclcpp.hpp"
#include <example_interfaces/srv/add_two_ints.hpp>
#include <functional>

using std::placeholders::_1;
using std::placeholders::_2;

class ServiceServerCpp : public rclcpp::Node
{
 private:
   rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr server_;
   void callbackAddTwoInts(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
                        std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response)
   {
       response->sum = request->a + request->b;
       RCLCPP_INFO(this->get_logger(), "Recibido: %ld + %ld = %ld", (long int) request->a, (long int) request->b, (long int) response->sum);
       
   }

   public:
    ServiceServerCpp() : Node("add_two_ints_server")
    {
        server_ = this->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints", std::bind(
            &ServiceServerCpp::callbackAddTwoInts, this, _1, _2));
    }

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ServiceServerCpp>();
    RCLCPP_INFO(node->get_logger(), "Servidor de Suma Iniciado");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}