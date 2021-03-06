
#ifndef __PID_H__
#define __PID_H__

#include "Global.h"

typedef struct PID			//定义数法核心数据
{
    s32 vi_Ref;		//速度PID，速度设定值
    s32 vi_FeedBack;		//速度PID，速度反馈值


    s32 vi_PreError;	  	//速度PID，前一次，速度误差,,vi_Ref - vi_FeedBack
    s32 vi_PreDerror;	//速度PID，前一次，速度误差之差，d_error-PreDerror;

    u32 v_Kp;		//速度PID，Ka = Kp
    u32 v_Ki;		//速度PID，Kb = Kp * ( T / Ti )
    u32 v_Kd;		//速度PID，

    s32 vl_PreU;  //控制输出
    s32 motor_PreU;

} PID;

extern PID   L_PID;
extern PID   R_PID;
extern PID 	 POSE_PID;
extern PID 	 TURN_PID;
extern s32 V_PIDCalc(PID *pp);
extern s32 TURN_PIDCalc( PID *pp);
extern s32 POSE_PIDCalc( PID *pp);
extern void V_PIDInit(void);

#endif
