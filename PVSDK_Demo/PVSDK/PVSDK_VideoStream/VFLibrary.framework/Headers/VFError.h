//
// Created by 张圣辉 on 2016/12/12.
//

#ifndef PROJECT_VFERROR_H
#define PROJECT_VFERROR_H

#define VF_Success             		1       //成功
#define VF_Failed              		0       //未知失败
#define VF_InvalidFile         		-1      //无效文件或无效文件路径
#define VF_NoVideo             		-2      //无视频正在播放
#define VF_HasVideo            		-3      //已有视频正在播放
#define VF_BrokenFrame         		-4      //视频帧不完整
#define VF_RecvTimeout         		-5      //接收超时
#define VF_FuncUnimplement     		-6      //缺少函数实现
#define VF_UnsupportNalType   		-7      //不支持的NAL类型
#define VF_RtspClosed          		-8      //RTSP连接已关闭
#define VF_SkipFrame           		-9      //视频帧不完整被跳过
#define VF_LostFrame           		-10     //丢失帧数达到指定值
#define VF_NoRecording         		-11     //尚未开始录像
#define VF_HardwareBusy				-12		//硬件处于忙碌状态
#define VF_NoDataSource				-13		//尚未设置数据源
#define VF_ConnectTimeout			-14		//连接超时
#define VF_StreamNotFound			-15		//找不到视频流
#define VF_DecoderNotFound			-16		//找不到解码器
#define VF_DeocderOpenFailed		-17		//解码器打开失败
#define VF_SurfaceInvalid			-18		//渲染视频的Surface不可用
#define VF_UnsupportFileType		-19		//不支持的文件类型
#define VF_VideSizeInvalid			-20		//视频大小异常
#define VF_DeocdeTimeout            -21     //超时时间内未成功解码一帧图像
#define VF_YuvToRgbFailed			-22		//YUV转RGB失败
#define VF_FrameInvalid             -23     //视频帧数据不可用

#endif //PROJECT_VFERROR_H
