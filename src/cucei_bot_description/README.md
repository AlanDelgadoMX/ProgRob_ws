# CUCEI-BOT V1 | Actividad 4

Modelo didáctico de cuatro articulaciones revolutas, pinza fija y propiedades visuales, de colisión e inerciales. Pensado para ROS 2 Humble + Gazebo Classic 11.

## Dependencias (Ubuntu con ROS 2 Humble instalado)

```bash
sudo apt update
sudo apt install ros-humble-xacro ros-humble-robot-state-publisher ros-humble-joint-state-publisher-gui ros-humble-rviz2 ros-humble-gazebo-ros-pkgs ros-humble-tf2-tools
```

Gazebo Classic 11 es software legado; confirmar que los paquetes estén disponibles en la instalación del compañero.

## Instalar y ejecutar

Copiar la carpeta `cucei_bot_description` a `~/ros2_ws/src/` y ejecutar:

```bash
source /opt/ros/humble/setup.bash
cd ~/ros2_ws
colcon build --symlink-install --packages-select cucei_bot_description
source install/setup.bash
ros2 launch cucei_bot_description display.launch.py
```

En otra terminal, para Gazebo:

```bash
source /opt/ros/humble/setup.bash
source ~/ros2_ws/install/setup.bash
ros2 launch cucei_bot_description gazebo.launch.py
```

## Validaciones

```bash
ros2 topic echo /joint_states
ros2 topic echo /robot_description --once
ros2 run tf2_tools view_frames
ros2 run tf2_ros tf2_echo base_link wrist_link
```

El `view_frames` genera un PDF del árbol TF. Guardar capturas de RobotModel, TF, distintas posiciones del GUI y robot en Gazebo. En RViz2, los paneles RobotModel y TF muestran la cinemática; para inspeccionar colisiones e inercias puede requerirse cambiar opciones del display o herramientas adicionales.

## Nota de simulación

Las cuatro articulaciones son pasivas en Gazebo: no se incluye un controlador de posición. Gazebo puede moverlas por gravedad; la base se conecta al marco `world` mediante un joint fijo, cuya interpretación en Gazebo Classic debe comprobarse. Si el spawn falla, revisar primero logs, URDF convertido (`xacro urdf/cucei_bot.urdf.xacro`) y dependencias. No se ha ejecutado ni validado este paquete en Ubuntu desde este entorno.

## Entrega Git

```bash
git add .
git commit -m "Actividad 4: modelo URDF y launch RViz Gazebo"
git tag actividad_4/urdf-gazebo
git push origin HEAD --tags
```
