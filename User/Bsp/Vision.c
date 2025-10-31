#include "Vision.h"

int8_t Vision_Rx_Data(uint8_t* buffer, VisionRxDataUnion *VisionRx)
{
    VisionTemp Union_temp;
    uint8_t i = 0;
    //获取头帧
    VisionRx->Head_frame = buffer[i++];
    if (VisionRx->Head_frame != 0xCD)
    {
        return -1;
    }
    //获取Pitch角度
    Union_temp.Data[0] = buffer[i++];
    Union_temp.Data[1] = buffer[i++];
    Union_temp.Data[2] = buffer[i++];
    Union_temp.Data[3] = buffer[i++];
    VisionRx->PitchAngle = Union_temp.Data_f;
    //获取Yaw角度
    Union_temp.Data[0] = buffer[i++];
    Union_temp.Data[1] = buffer[i++];
    Union_temp.Data[2] = buffer[i++];
    Union_temp.Data[3] = buffer[i++];
    VisionRx->YawAngle = Union_temp.Data_f;

    VisionRx->VisionState = buffer[i] & 0x07;
    VisionRx->ShootBool = (buffer[i] & 0x08)>>3;
    VisionRx->Target = (buffer[i] & 0x10)>>4;
    i++;
    //if(VisionRxData.PitchAngle>=0)VisionRxData.Target=0;
    //获取VisionTime
    Union_temp.Data[0] = buffer[i++];
    Union_temp.Data[1] = buffer[i++];
    Union_temp.Data[2] = buffer[i++];
    Union_temp.Data[3] = buffer[i++];
    VisionRx->VisionTime = Union_temp.Data_u32;

    VisionRx->End_frame = buffer[i];


    //  VisionRxData.PitchAngle_kal =0;//kalmanFilter(&kfp_visionPitch,VisionRxData.PitchAngle);
    //  VisionRxData.YawAngle_kal =0;//kalmanFilter(&kfp_visionYaw,VisionRxData.YawAngle);


    if (VisionRx->End_frame != 0xDC)
    {
        return -2;
    }
    return 0;
}

void Vision_Tx_Data(float PitchAngle, float YawAngle, uint32_t Time, uint8_t State, uint8_t Rate_of_fire)
{
    VisionTemp Union_temp;
    VisionTxDataUnion VisionTxData;
    uint8_t i = 0;

    VisionTxData.Head_frame = 0xCD;
    VisionTxData.PitchAngle = PitchAngle;
    VisionTxData.YawAngle = YawAngle;
    VisionTxData.VisionTime = Time;
    VisionTxData.VisionState = State;
    VisionTxData.Rate_of_fire = Rate_of_fire;
    VisionTxData.End_frame = 0xDC;


    VisionTxData.data[i++] = VisionTxData.Head_frame;
    Union_temp.Data_f = VisionTxData.PitchAngle;
    VisionTxData.data[i++] = Union_temp.Data[0];
    VisionTxData.data[i++] = Union_temp.Data[1];
    VisionTxData.data[i++] = Union_temp.Data[2];
    VisionTxData.data[i++] = Union_temp.Data[3];

    Union_temp.Data_f = VisionTxData.YawAngle;
    VisionTxData.data[i++] = Union_temp.Data[0];
    VisionTxData.data[i++] = Union_temp.Data[1];
    VisionTxData.data[i++] = Union_temp.Data[2];
    VisionTxData.data[i++] = Union_temp.Data[3];

    VisionTxData.data[i++] &= VisionTxData.VisionState;

    Union_temp.Data_u32 = VisionTxData.VisionTime;
    VisionTxData.data[i++] = Union_temp.Data[0];
    VisionTxData.data[i++] = Union_temp.Data[1];
    VisionTxData.data[i++] = Union_temp.Data[2];
    VisionTxData.data[i++] = Union_temp.Data[3];

    VisionTxData.data[i++] = VisionTxData.Rate_of_fire;

    VisionTxData.data[i++] = VisionTxData.End_frame;

    CDC_Transmit_FS(VisionTxData.data, sizeof(VisionTxData.data));
}
