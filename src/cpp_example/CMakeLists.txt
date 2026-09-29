cmake_minimum_required(VERSION 3.8)
project(cpp_example)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(example_interfaces REQUIRED)
#find_package(robx7_interfaces REQUIRED)

#rosidl_generate_interfaces(${PROJECT_NAME}
#  "msg/Hardware_Status.msg"
#)

#Test Node
add_executable(test_node src/test_node.cpp)
ament_target_dependencies(test_node rclcpp)

#Publisher C++

add_executable(publisher_cpp src/example_publisher.cpp)
ament_target_dependencies(publisher_cpp rclcpp std_msgs)


#Subscriber C++

add_executable(subscriber_cpp src/example_subscriber.cpp)
ament_target_dependencies(subscriber_cpp rclcpp std_msgs)

#Server C++

add_executable(server_cpp src/example_service_server.cpp)
ament_target_dependencies(server_cpp rclcpp example_interfaces)


#Client 1

add_executable(client_cpp src/example_client.cpp)
ament_target_dependencies(client_cpp rclcpp example_interfaces)

#Client 2

add_executable(client2_cpp src/example_service_client.cpp)
ament_target_dependencies(client2_cpp rclcpp example_interfaces)



install(TARGETS
  test_node
  publisher_cpp
  subscriber_cpp
  server_cpp
  client_cpp
  client2_cpp
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
