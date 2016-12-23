#ifndef _INFRARED_EMISSION_H_
#define _INFRARED_EMISSION_H_

#include "common.h"


void SendIRdata_BYTE(unsigned char irdata);
void SendIRdata(unsigned char g_iraddr1,unsigned char p_irdata);
void Multiple_sendIRdata(u8 count,u8 ir_adress,u8 dat);
    
#endif