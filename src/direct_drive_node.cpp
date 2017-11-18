#include "ros/ros.h"
#include "cmg_msgs/GimbalTarget.h"
#include "sensor_msgs/Imu.h"

class Controller {
	private:
		ros::NodeHandle n;
		ros::Publisher gimbal_pub;
		ros::Subscriber imu_sub;
	public:
		Controller() : n("~") {
			gimbal_pub = n.advertise<cmg_msgs::GimbalTarget>("/gimbal/cmd", 1);
			imu_sub = n.subscribe("/imu/filtre", 1, &Controller::imu_cb, this);
		}
		void imu_cb(const sensor_msgs::Imu::ConstPtr & msg) {
			double vit = msg->angular_velocity.x;
			cmg_msgs::GimbalTarget gc;
			gc.mode = 1;
			for (int i = 0; i < 6; i++) {
				gc.positions.push_back(vit);
			}
			gimbal_pub.publish(gc);
		}
};

int main(int argc, char * argv[]) {
	ros::init(argc, argv, "direct_drive");
	Controller c;	
	ros::spin();
}
