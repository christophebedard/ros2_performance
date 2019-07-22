#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

/*
 * Same as nopub.cc, but with only 1 node.
 */

int main(int argc, char **argv) {
  using namespace std::chrono_literals;
  rclcpp::init(0, nullptr);

  int create = argc > 1 ? std::atoi(argv[1]) : 10;
  std::chrono::milliseconds loop_interval(argc > 2 ? std::atoi(argv[2]) : 20);
  std::cout << "ROS-no publishers create " << create << " timers @ " << loop_interval.count() << "ms"
            << std::endl;

  rclcpp::executors::SingleThreadedExecutor exec;
  std::vector<rclcpp::Node::SharedPtr> node_refs;
  std::vector<rclcpp::TimerBase::SharedPtr> timer_refs;

  auto node = std::make_shared<rclcpp::Node>("node_" + std::to_string(0));
  node_refs.push_back(node);
  exec.add_node(node);
  for (int n = 0; n < create; ++n) {
    auto timer = node->create_wall_timer(loop_interval, [=]() {
      std_msgs::msg::String msg;
      msg.data = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    });
    timer_refs.push_back(timer);
  }

  exec.spin();
  rclcpp::shutdown();
  return 0;
}
