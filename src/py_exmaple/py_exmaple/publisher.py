import rclpy
from rclpy.node import Node
from std_msgs.msg import String


class PublisherPython(Node):

    def __init__(self):
        super().__init__('publisher_python')

        self.publisher_ = self.create_publisher(
            String,
            'TraficoZMG',
            10
        )

        self.timer = self.create_timer(1.0, self.publicar_mensaje)
        self.contador = 0

    def publicar_mensaje(self):
        msg = String()
        msg.data = f'Dragon Ball Z es mejor que Super: {self.contador}'

        self.publisher_.publish(msg)

        self.get_logger().info(
            f'Publicando: "{msg.data}"'
        )

        self.contador += 1


def main(args=None):
    rclpy.init(args=args)

    nodo = PublisherPython()

    rclpy.spin(nodo)

    nodo.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()