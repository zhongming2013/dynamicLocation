#ifndef  DEFINE_H
#define DEFINE_H

#define     MOBILE_CFG_MSG            1
#define     MOBILE_LOC_MSG            2
#define     REFER_CFG_MSG                3
#define     REFER_TMP_MSG               4

//Mobile Node 定位信息数据帧
#define     MOBILE_LOC_MSG_LEN                7
#define     MSG_TYPE                                          0
#define     M_FIXID                                               (MSG_TYPE + 1)
#define     M_ROOM_FLOOR                             (MSG_TYPE + 2)
#define     M_ROOM_NUMBER                         (MSG_TYPE + 3)
#define     M_HELP                                                (MSG_TYPE + 4)
#define     M_NETID_HI                                        (MSG_TYPE + 5)
#define     M_NETID_LO                                       (MSG_TYPE + 6)

//Mobile Node 配置信息数据帧
#define     MOBILE_CFG_MSG_LEN                8
#define     M_FIXID                                  (MSG_TYPE + 1)//ID
#define     M_LOC_MODE                      (MSG_TYPE + 2)//定位模式，自动或者手动
#define     M_DST_ADDR_HI                 (MSG_TYPE + 3)//接收定位信息设备的地址高位
#define     M_DST_ADDR_LO                (MSG_TYPE + 4)//低位
#define     M_LOC_PERIOD                    (MSG_TYPE + 5)//自动模式下的定位周期,10为1秒，20为2秒
#define     M_SELF_ADDR_HI                (MSG_TYPE + 6)//自己的地址高位
#define     M_SELF_ADDR_LO               (MSG_TYPE + 7)//自己的地址低位

//Reference Node 配置信息帧
#define     REFER_CFG_MSG_LEN             6
#define     R_NETID_HI                                           (MSG_TYPE + 1)
#define     R_NETID_LO                                          (MSG_TYPE + 2)
#define     R_ROOM_FLOOR                                 (MSG_TYPE + 3)
#define     R_ROOM_NUMBER                             (MSG_TYPE + 4)
#define     R_TEMP_PERIOD                                  (MSG_TYPE + 5)//1代表的时间为1秒

//Reference Node 温度信息帧，存储在referNode数据表里
#define		REFER_TMP_MSG_LEN				  5
#define     RT_ROOM_FLOOR       (MSG_TYPE + 1) //楼层
#define     RT_ROOM_NUMBER   (MSG_TYPE + 2)//房间号
#define     RT_ROOM_TEMP          (MSG_TYPE + 3)//温度
#define     RT_ROOM_VOLTAGE   (MSG_TYPE + 4)//电池电压


#endif // DEFINE_H
