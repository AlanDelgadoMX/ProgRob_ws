"""Spawn robot in Gazebo Classic 11 (ROS 2 Humble gazebo_ros)."""
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, TimerAction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch.substitutions import Command, FindExecutable


def generate_launch_description():
    share = get_package_share_directory('cucei_bot_description')
    model = os.path.join(share, 'urdf', 'cucei_bot.urdf.xacro')
    gazebo_share = get_package_share_directory('gazebo_ros')
    description = {'robot_description': Command([FindExecutable(name='xacro'), ' ', model])}
    return LaunchDescription([
        IncludeLaunchDescription(PythonLaunchDescriptionSource(os.path.join(gazebo_share, 'launch', 'gazebo.launch.py'))),
        Node(package='robot_state_publisher', executable='robot_state_publisher', parameters=[description], output='screen'),
        TimerAction(period=5.0, actions=[Node(package='gazebo_ros', executable='spawn_entity.py', arguments=['-topic', 'robot_description', '-entity', 'cucei_bot'], output='screen')]),
    ])
