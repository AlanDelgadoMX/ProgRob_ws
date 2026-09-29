#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/srv/add_two_ints.hpp>


class ServiceClientCpp : public rclcpp::Node
{
 private:
    std::vector<std::thread> threads_;

 public:
    ServiceClientCpp() : Node("service_client_cpp")
    {
        threads_.push_back(std::thread(&ServiceClientCpp::callAddTwoIntsService, this, 1, 2));
        threads_.push_back(std::thread(&ServiceClientCpp::callAddTwoIntsService, this, 3, 4));
        threads_.push_back(std::thread(&ServiceClientCpp::callAddTwoIntsService, this, 5, 6));
        threads_.push_back(std::thread(&ServiceClientCpp::callAddTwoIntsService, this, 7, 8));
}

 void callAddTwoIntsService(int a, int b)
    {
        auto client = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
        while(!client->wait_for_service(std::chrono::seconds(1)))
        {
            RCLCPP_WARN(this->get_logger(), "Esperando al servidor");
        }
        auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        request->a = a;
        request->b = b;

        auto future = client->async_send_request(request);

        if(rclcpp::spin_until_future_complete(this->shared_from_this(), future) == rclcpp::FutureReturnCode::SUCCESS)
        {
            RCLCPP_INFO(this->get_logger(), "%d + %d = %d", (int) request->a, (int) request->b, (int) future.get()->sum);
        }
        else
        {
            RCLCPP_ERROR(this->get_logger(), "Error al conectar con el servicio");  
        }
 
        try 
        {
            auto response = future.get();
            RCLCPP_INFO(this->get_logger(), "Resultado: %d", response->sum);
        }

        catch (const std::exception &e)
        {
            RCLCPP_ERROR(this->get_logger(), "No se ha podido encontrar el servicio: %s", e.what());    
        }
    }

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ServiceClientCpp>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}