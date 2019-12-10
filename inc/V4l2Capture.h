/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** V4l2Capture.h
** 
** V4L2 Capture wrapper 
**
** -------------------------------------------------------------------------*/


#ifndef V4L2_CAPTURE
#define V4L2_CAPTURE

#include "V4l2Access.h"
#include "opencv2/core/core.hpp"


// ---------------------------------
// V4L2 Capture
// ---------------------------------
class V4l2Capture : public V4l2Access
{		
	protected:	
		V4l2Capture(V4l2Device* device);
	
	public:
        /**
         * @brief create 创建Capture
         * @param param
             *使用说明，我们读取UVC免驱的摄像头时，应该避免直接使用opencv的videocpature，
             * 因为简单的API使得我们并不知道我们到底获取的时摄像头的哪种图片格式。应该直接使用Qt v4l2 test benchmark软件去获取我们真正需要的
             * 图像帧格式。
             * V4L2_PIX_FMT_MJPEG （MJPEG）
            使用范例 V4L2DeviceParameters param("/dev/video0", V4L2_PIX_FMT_MJPEG , 1920, 1080, 30, 0,verbose);
         * @param iotype
         * @return
         */
		static V4l2Capture* create(const V4L2DeviceParameters & param, IoType iotype = V4l2Access::IOTYPE_MMAP);
		virtual ~V4l2Capture();

        size_t read(char* buffer, size_t bufferSize);
        /**
         * @brief read 读取图像
         * @param readImage 获取的图像
         * @return
         */
        int read(cv::Mat &readImage);
        /**
         * @brief isReadable 判断是都可读取图像
         * @param tv 等待的时间
         *      timeval tv;
                tv.tv_sec=1;
                tv.tv_usec=0;
                int ret = this->isReadable(&tv);
         *
         * @return -1 不可读      0 超时        1 成功
         */
        int isReadable(timeval* tv);
        /**
         * @brief getBusInfo 获取总线的地址，多个摄像头输入设备时便于判断我们现在采集的到底是哪个摄像头
         * @return
         */
        const char * getBusInfo();

};


#endif
