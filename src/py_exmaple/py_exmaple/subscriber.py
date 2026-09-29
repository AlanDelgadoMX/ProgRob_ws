import rclpy
from rclpy.node import Node
from std_msgs.msg import String


class SubscriberPython(Node):

    def __init__(self):
        super().__init__('subscriber_python')

        self.subscription = self.create_subscription(
            String,
            'TraficoZMG',
            self.recibir_mensaje,
            10
        )

    def recibir_mensaje(self, msg):
        self.get_logger().info(
            f'Recibido: "{msg.data}"'
        )


def main(args=None):
    rclpy.init(args=args)

    nodo = SubscriberPython()

    rclpy.spin(nodo)

    nodo.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()