#include <iostream>
#include <venc.h>
#include <memory>

int main(int argc, char *argv[])
{
    VENC_Init();

    VENC_CMD venc_cmd;

    venc_cmd.src_fmt    = E_ECN_FMT_YUV420SP;
    venc_cmd.src_width  = 1920;
    venc_cmd.src_height = 1080;
    venc_cmd.enc_type   = E_ECN_TYPE_H265;
    venc_cmd.fps        = 30;
    venc_cmd.bitrate    = 4000000;
    venc_cmd.gop        = 1;
    venc_cmd.rc_mode    = 1;

    VENC_HANDLE enc_handle = VENC_CreateEncHandle(&venc_cmd);

    T_VENC_DATA data;
    
    data.iFd   = -1;
    data.iLen  = 1920 * 1080 * 3 / 2;
    data.pAddr = NULL;
    data.pAddr = (char *)malloc(data.iLen);

    FILE *input_file  = fopen("test.yuv", "rb");
    FILE *output_file = fopen("test.265", "ab+");

    fread(data.pAddr, 1, data.iLen, input_file);
    T_VENC_STREAM stream;
    for (size_t i = 0; i < 1000U; ++i)
    {
	    VENC_EncodeDataSync(enc_handle, &data, &stream, NULL);
        if (stream.iLen)
        {
            fwrite(stream.pAddr, 1, stream.iLen, output_file);
          	VENC_ReleaseStream(enc_handle, &stream);
        }
    }

    if(data.pAddr)
    {
    	free(data.pAddr);
    }
    
    fclose(output_file);

    return 0;
}
