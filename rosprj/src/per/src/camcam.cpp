#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <nav_msgs/Odometry.h>


void imuCallback(const sensor_msgs::Imu::ConstPtr& msg)
{
    // 打印imu数据
    ROS_INFO("IMU - Orientation: [%f, %f, %f], Angular Velocity: [%f, %f, %f], Linear Acceleration: [%f, %f, %f]",
        msg->orientation.x, msg->orientation.y, msg->orientation.z,
        msg->angular_velocity.x, msg->angular_velocity.y, msg->angular_velocity.z,
        msg->linear_acceleration.x, msg->linear_acceleration.y, msg->linear_acceleration.z);
}


void odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
    // 打印odom数据#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>


    void colorImageCallback(const sensor_msgs::Image::ConstPtr & msg)
    {
        // 将ROS消息转换为OpenCV图像
        cv_bridge::CvImagePtr cv_ptr;
        try
        {
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }

        // 在窗口中显示图像
        cv::imshow("Color Image", cv_ptr->image);
        cv::waitKey(1);
    }



    void depthImageCallback(const sensor_msgs::Image::ConstPtr & msg)
    {
        // 将ROS消息转换为OpenCV图像
        cv::Mat depth_img = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::TYPE_32FC1)->image;

        // 在窗口中显示图像
        cv::imshow("Depth Image", depth_img);
        cv::waitKey(1);
    }



    int main(int argc, char** argv)
    {
        // 初始化ROS节点
        ros::init(argc, argv, "camera_viewer");

        // 创建ROS节点
        ros::NodeHandle nh;

        // 创建订阅器，订阅图像topic
        ros::Subscriber color_image_sub = nh.subscribe("/camera/color/image_raw", 10, colorImageCallback);
        ros::Subscriber depth_image_sub = nh.subscribe("/camera/depth/image_rect_raw", 10, depthImageCallback);

        // 进入ROS循环
        ros::spin();

        return 0;
    }

    ROS_INFO("Odometry - Position: [%f, %f, %f], Orientation: [%f, %f, %f]",
        msg->pose.pose.position.x, msg->pose.pose.position.y, msg->pose.pose.position.z,
        msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z);
}


int main(int argc, char** argv)
{

    ros::init(argc, argv, "topic_subscriber");
    ros::NodeHandle nh;


    // 创建两个订阅器，分别接收imu和odom话题的消息
    ros::Subscriber imuSub = nh.subscribe("/imu/data_raw", 1, imuCallback);
    ros::Subscriber odomSub = nh.subscribe("/odom", 1, odomCallback);


    ros::spin();


    return 0;
}
