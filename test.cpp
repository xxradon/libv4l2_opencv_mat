#include <V4l2Device.h>
#include <V4l2Capture.h>
#include "logger.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

int main(){
    int verbose=0;
    int stop=0;
    const char * in_devname = "/dev/video0";/* V4L2_PIX_FMT_YUYV V4L2_PIX_FMT_MJPEG*/
    /*
     *使用说明，我们读取UVC免驱的摄像头时，应该避免直接使用opencv的videocpature，
     * 因为简单的API使得我们并不知道我们到底获取的时摄像头的哪种图片格式。应该直接使用Qt v4l2 test benchmark软件去获取我们真正需要的
     * 图像帧格式。
     * V4L2_PIX_FMT_MJPEG （MJPEG）
     */
    V4L2DeviceParameters param(in_devname, V4L2_PIX_FMT_MJPEG , 1920, 1080, 30, 0,verbose);
    V4l2Capture* videoCapture = V4l2Capture::create(param, V4l2Access::IOTYPE_MMAP);
    if (videoCapture == NULL)
    {
        LOG(WARN) << "Cannot create V4L2 capture interface for device:" << "/dev/video0";
        return -1;
    }
    timeval tv;
    LOG(NOTICE) << "USB bus:" <<videoCapture->getBusInfo();
    LOG(NOTICE) << "Start Uncompressing " << in_devname ;

    while (!stop)
    {
        tv.tv_sec=1;
        tv.tv_usec=0;
        int ret = videoCapture->isReadable(&tv);
        if (ret == 1)
        {
            cv::Mat v4l2Mat;
            ret =  videoCapture->read(v4l2Mat);

            if (ret != 0)
            {
                LOG(NOTICE) << "stop " ;
                stop=1;
            }
            else
            {
               cv::imwrite("test.jpg",v4l2Mat);
            }
        }
        else if (ret == -1) //返回错误
        {
            LOG(NOTICE) << "stop " << strerror(errno);
            stop=1;
        }else if( ret == 0) // 返回超时
        {

        }
        break;
    }
    delete videoCapture;
    V4L2DeviceParameters mparam(in_devname, V4L2_PIX_FMT_YUYV , 1920, 1080, 5, 0,verbose);
    videoCapture = V4l2Capture::create(mparam, V4l2Access::IOTYPE_MMAP);
    while (!stop)
    {
        tv.tv_sec=1;
        tv.tv_usec=0;
        int ret = videoCapture->isReadable(&tv);
        if (ret == 1)
        {
            cv::Mat v4l2Mat;
            ret =  videoCapture->read(v4l2Mat);

            if (ret != 0)
            {
                LOG(NOTICE) << "stop " ;
                stop=1;
            }
            else
            {
               cv::imwrite("test.jpg",v4l2Mat);
            }
        }
        else if (ret == -1) //返回错误
        {
            LOG(NOTICE) << "stop " << strerror(errno);
            stop=1;
        }else if( ret == 0) // 返回超时
        {

        }
    }
}
