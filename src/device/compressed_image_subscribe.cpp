#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>

using namespace cv;

namespace enc = sensor_msgs::image_encodings;

void imageCallback(const sensor_msgs::CompressedImageConstPtr& message)
{

  int imdecode_flag_ = cv::IMREAD_COLOR;
  cv_bridge::CvImagePtr cv_ptr(new cv_bridge::CvImage);

  // Copy message header
  cv_ptr->header = message->header;

  // Decode color/mono image
  try
  {
    cv_ptr->image = cv::imdecode(cv::Mat(message->data), imdecode_flag_);

    // Assign image encoding string
    const size_t split_pos = message->format.find(';');
    if (split_pos==std::string::npos)
    {
      // Older version of compressed_image_transport does not signal image format
      switch (cv_ptr->image.channels())
      {
        case 1:
          cv_ptr->encoding = enc::MONO8;
          break;
        case 3:
          cv_ptr->encoding = enc::BGR8;
          break;
        default:
          ROS_ERROR("Unsupported number of channels: %i", cv_ptr->image.channels());
          break;
      }
    } else
    {
      std::string image_encoding = message->format.substr(0, split_pos);

      cv_ptr->encoding = image_encoding;

      if ( enc::isColor(image_encoding))
      {
        std::string compressed_encoding = message->format.substr(split_pos);
        bool compressed_bgr_image = (compressed_encoding.find("compressed bgr") != std::string::npos);

        // Revert color transformation
        if (compressed_bgr_image)
        {
          // if necessary convert colors from bgr to rgb
          if ((image_encoding == enc::RGB8) || (image_encoding == enc::RGB16))
            cv::cvtColor(cv_ptr->image, cv_ptr->image, CV_BGR2RGB);

          if ((image_encoding == enc::RGBA8) || (image_encoding == enc::RGBA16))
            cv::cvtColor(cv_ptr->image, cv_ptr->image, CV_BGR2RGBA);

          if ((image_encoding == enc::BGRA8) || (image_encoding == enc::BGRA16))
            cv::cvtColor(cv_ptr->image, cv_ptr->image, CV_BGR2BGRA);
        } else
        {
          // if necessary convert colors from rgb to bgr
          if ((image_encoding == enc::BGR8) || (image_encoding == enc::BGR16))
            cv::cvtColor(cv_ptr->image, cv_ptr->image, CV_RGB2BGR);

          if ((image_encoding == enc::BGRA8) || (image_encoding == enc::BGRA16))
            cv::cvtColor(cv_ptr->image, cv_ptr->image, CV_RGB2BGRA);

          if ((image_encoding == enc::RGBA8) || (image_encoding == enc::RGBA16))
            cv::cvtColor(cv_ptr->image, cv_ptr->image, CV_RGB2RGBA);
        }
      }
    }
  }
  catch (cv::Exception& e)
  {
    ROS_ERROR("%s", e.what());
  }

  size_t rows = cv_ptr->image.rows;
  size_t cols = cv_ptr->image.cols;

  if ((rows > 0) && (cols > 0)) {
    cv::imshow("view", cv_bridge::toCvShare(cv_ptr->toImageMsg(), "bgr8")->image);
    cv::waitKey(30);
  }

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "compressed_image_listener_cpp");
  ros::NodeHandle nh;
  cv::namedWindow("view");
  cv::startWindowThread();
//  image_transport::ImageTransport it(nh);
//  image_transport::Subscriber sub = it.subscribe("/camera/rgb/image_raw/compressed", 1, imageCallback);
  ros::Subscriber sub = nh.subscribe("/camera/rgb/image_raw/compressed", 1000, imageCallback);
  ros::spin();
  cv::destroyWindow("view");
}
