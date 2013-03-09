#ifndef  DEFINE_H
#define DEFINE_H

#define     MOBILE_CFG_MSG            1
#define     MOBILE_LOC_MSG            2
#define     REFERENCE_CFG_MSG     3
#define     REFERENCE_TMP_MSG    4

//Mobile Node ��λ��Ϣ����֡
#define     MOBILE_LOC_MSG_LEN                6
#define     MSG_TYPE                                          0
#define     M_FIXID                                               (MSG_TYPE + 1)
#define     M_ROOM_FLOOR                             (MSG_TYPE + 2)
#define     M_ROOM_NUMBER                         (MSG_TYPE + 3)
#define     M_HELP                                                (MSG_TYPE + 4)
#define     M_XOR                                                  (MSG_TYPE + 5)
#define     M_NETID_HI                                        (MSG_TYPE + 6)
#define     M_NETID_LO                                       (MSG_TYPE + 7)

//Mobile Node ������Ϣ����֡
#define     MOBILE_CFG_MSG_LEN                8
#define     M_FIXID                                  (MSG_TYPE + 1)//ID
#define     M_LOC_MODE                      (MSG_TYPE + 2)//��λģʽ���Զ������ֶ�
#define     M_DST_ADDR_HI                 (MSG_TYPE + 3)//���ն�λ��Ϣ�豸�ĵ�ַ��λ
#define     M_DST_ADDR_LO                (MSG_TYPE + 4)//��λ
#define     M_LOC_PERIOD                    (MSG_TYPE + 5)//�Զ�ģʽ�µĶ�λ����,10Ϊ1�룬20Ϊ2��
#define     M_SELF_ADDR_HI                (MSG_TYPE + 6)//�Լ��ĵ�ַ��λ
#define     M_SELF_ADDR_LO               (MSG_TYPE + 7)//�Լ��ĵ�ַ��λ

//Reference Node ������Ϣ֡
#define     REFERENCE_CFG_MSG_LEN             5
#define     R_NETID_HI                                           (MSG_TYPE + 1)
#define     R_NETID_LO                                          (MSG_TYPE + 2)
#define     R_ROOM_FLOOR                                 (MSG_TYPE + 3)
#define     R_ROOM_NUMBER                             (MSG_TYPE + 4)

//Reference Node �¶���Ϣ֡���洢��referNode���ݱ���
#define     RT_ROOM_FLOOR       (MSG_TYPE + 1) //¥��
#define     RT_ROOM_NUMBER   (MSG_TYPE + 2)//�����
#define     RT_ROOM_TEMP          (MSG_TYPE + 3)//�¶�


#endif // DEFINE_H
