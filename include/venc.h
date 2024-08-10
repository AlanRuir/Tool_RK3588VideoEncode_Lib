#ifndef _VENC_H_H
#define _VENC_H_H
#ifdef __cplusplus
extern "C"
{
#endif
typedef void* VENC_HANDLE;
enum{
    E_ECN_TYPE_UNKNOW = -1,
    E_ECN_TYPE_H264,
    E_ECN_TYPE_H265,
};
enum{
    E_ECN_FMT_YUV420SP = 0,
    E_ECN_FMT_YUV420P = 4,

    E_ECN_FMT_RGB888 = 6,
    E_ECN_FMT_BGR888,
    E_ECN_FMT_RGB101010,
    E_ECN_FMT_BGR101010,
    E_ECN_FMT_ARGB8888,
    E_ECN_FMT_ABGR8888,
    E_ECN_FMT_BGRA8888,
    E_ECN_FMT_RGBA8888,
};

typedef struct  _VENC_CMD
{
    int src_fmt;        // [ 输入数据格式，0:YUV420SP(NV12), 6:RGB888 ]
    int src_width;      // [ 宽，16字节对齐 ]
    int src_height;     // [ 高，16字节对齐 ]
    
    int enc_type;       // [ 0:H264, 1:H265 ]
    int fps;            // [ 帧率 ]
    int bitrate;        // [ 码率 ]
    int gop;            // [ I帧间隔 ]
    int rc_mode;        // 0: ENC_RC_MODE_VBR, 1: ENC_RC_MODE_CBR
    
}VENC_CMD, *PVENC_CMD;

/* VENC data struct */
typedef struct _T_VENC_DATA
{ 
    int  iFd;          /* File descriptor of dma          */
    int  iLen;         /* data length              */
    char *pAddr;       /* data buffer address      */
    void* pUser;
}T_VENC_DATA;

/* VENC stream data struct */
typedef struct _T_VENC_STREAM 
{ 
    int  iLen;         /* Encode data length              */
    char *pAddr;       /* Encode data buffer address      */
    int  iFrameType;   /* 帧类型,0: P帧, 1: I帧            */ 
    void* pUser;
}T_VENC_STREAM;

/*
函数: VENC_Init
功能：初始化编码器环境
参数:
    无
返回:
    成功返回0，失败-1      
*/
int VENC_Init();

/*
函数: VENC_Uninit
功能：卸载初始化编码器分配的资源
参数:
    无
返回:
    成功返回0，失败-1      
*/
int VENC_Uninit();

/*
函数: VENC_Version
功能：显示编码库版本
参数:
    无
返回:
    成功返回0，失败-1      
*/
int VENC_Version(char *buf);

/*
函数: VENC_CreateEncHandle
功能：创建编码句柄
参数:
    penc_cmd:结构体指针
返回:
    参数无效或创建失败，返回NULL    
*/
VENC_HANDLE VENC_CreateEncHandle(PVENC_CMD penc_cmd);

/*
函数: VENC_DestroyEncHandle
功能：销毁编码句柄
参数:
    enc_handle:[ 编码句柄 ]
返回:
    成功返回0，失败-1      
*/
int VENC_DestroyEncHandle(VENC_HANDLE enc_handle);

/*
函数: VENC_StartEnc
功能：开始编码
参数:
    enc_handle:[ 编码句柄 ]
返回:
    成功返回0，失败-1      
*/
int VENC_StartEnc(VENC_HANDLE enc_handle);

/*
函数: VENC_StopEnc
功能：停止编码
参数:
    enc_handle:[ 编码句柄 ]
返回:
    成功返回0，失败-1      
*/
int VENC_StopEnc(VENC_HANDLE enc_handle);

/*
函数: VENC_SendPic
功能：输入编码图片数据
参数:
    enc_handle      :编码器句柄
    data_buf        :输入数据缓存区
    data_buf_size   :输入数据缓存区大小
返回:
    成功返回0，失败-1   
备注: 缓存区最大存放100帧个数据，异步编码，线程安全
*/
int  VENC_SendPic(VENC_HANDLE enc_handle, char *data_buf, int data_buf_size);


/*
函数: VENC_SendVEncData
功能：输入编码数据
参数:
    enc_handle      :编码器句柄
    pEncData        :输入数据
返回:
    成功返回0，失败-1   
备注: 缓存区最大存放100帧个数据，异步编码，线程安全
*/
int  VENC_SendVEncData(VENC_HANDLE enc_handle, T_VENC_DATA *pEncData);

/*
函数: VENC_SetEncNextIFrame
功能：设置编码下一帧为I帧
参数:
    enc_handle      :编码器句柄
返回:
    成功返回0，失败-1    
*/
int  VENC_SetEncNextIFrame(VENC_HANDLE enc_handle);

/*
函数: VENC_GetStream
功能：获取编码流数据
参数:
    enc_handle      :编码器句柄
    pStream         :数据流结构
    iBlockFlag      :阻塞标志
返回:
    成功返回0，失败-1    
*/
int  VENC_GetStream(VENC_HANDLE enc_handle, T_VENC_STREAM *pStream, int iBlockFlag);

/*
函数: VENC_ReleaseStream
功能：释放流数据资源
参数:
    enc_handle      :编码器句柄
    pStream         :数据流结构
返回:
    成功返回0，失败-1    
*/
int VENC_ReleaseStream(VENC_HANDLE enc_handle, T_VENC_STREAM *pStream);


/*
函数: VENC_EncodeDataSync
功能：同步获取编码的数据
参数:
    enc_handle      :编码器句柄
    pEncData        :输入数据
    pStream[out]         :数据流结构
返回:
    成功返回0，失败-1    
*/
int VENC_EncodeDataSync(VENC_HANDLE enc_handle, T_VENC_DATA *pEncData, T_VENC_STREAM *pStream, void *ptFrameBuf);
#ifdef __cplusplus
}
#endif
#endif	// _VENC_H_H
