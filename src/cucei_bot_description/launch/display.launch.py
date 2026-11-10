"""Visualize the Xacro robot with movable joints in RViz2."""
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import Command, FindExecutable
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    share = get_package_share_directory('cucei_bot_description')
    model = os.path.join(share, 'urdf', 'cucei_bot.urdf.xacro')
    rviz = os.path.join(share, 'rviz', 'robot.rviz')
    description = {
    'robot_description': ParameterValue(
        Command([FindExecutable(name='xacro'), ' ', model]),
        value_type=str
    )
}
    return LaunchDescription([
        Node(package='robot_state_publisher', executable='robot_state_publisher', parameters=[description], output='screen'),
        Node(package='joint_state_publisher_gui', executable='joint_state_publisher_gui', output='screen'),
        Node(package='rviz2', executable='rviz2', arguments=['-d', rviz], output='screen'),
    ])
