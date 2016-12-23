#include <intrins.h>
#include "NRF24L01.H"


u8 code TX_ADDRESS[6][TX_ADR_WIDTH]={//本地地址
{0x34,0x43,0x10,0x10,0x01},
{0x34,0x43,0x10,0x10,0x02},
{0x34,0x43,0x10,0x10,0x03},
{0x34,0x43,0x10,0x10,0x04},
{0x34,0x43,0x10,0x10,0x05},
{0x34,0x43,0x10,0x10,0x06}
};

u8 code  RX_ADDRESS[6][RX_ADR_WIDTH]={//本地地址
{0x34,0x43,0x10,0x10,0x01},
{0x34,0x43,0x10,0x10,0x02},
{0x34,0x43,0x10,0x10,0x03},
{0x34,0x43,0x10,0x10,0x04},
{0x34,0x43,0x10,0x10,0x05},
{0x34,0x43,0x10,0x10,0x06}
};
//                       0 1  2  3  4  5  6  7  8   9
u8 code Channel_fre[10]={0,15,30,45,55,65,75,90,105,115};

//****************************************************************************************
/*NRF24L01初始化
//***************************************************************************************/
void init_NRF24L01(void)
{
     CE=0;    // chip enable
 	CSN=1;   // Spi  disable 
}

uchar SPI_RW(uchar dat)
{
  uchar xdata i;
   for (i = 0; i < 8; i++) // output 8-bit
   {
      //发送1位数据
      if (dat & 0x80)         // output 'uchar', MSB to MOSI
      {
         MOSI = 1;
      }
      else
      {
         MOSI = 0;
      }

      dat <<= 1;           // shift next bit into MSB..
      
      //读取1位数据
      SCK = 1;                      // Set SCK high..

      if (MISO)
      {
         dat |= 1;
      }             // capture current MISO bit
      else
      {
         dat &= 0xFE;
      }
      SCK = 0;                    // ..then set SCK low again
   }
   
   return(dat);                  // return read uchar
}

/*u8 SPI_RW(u8 dat)
{
		return(SPItransfer(dat));

}*/
/****************************************************************************************************
/*函数：uchar SPI_Read(uchar reg)
/*功能：NRF24L01读寄存器函数，向寄存器reg写一个字节，同时返回状态字节
/****************************************************************************************************/

u8 SPI_Read(u8 reg)
{
	u8 xdata reg_val;
	
	CSN = 0;                // CSN low, initialize SPI communication...
	
	SPI_RW(reg);            // Select register to read from..
	reg_val = SPI_RW(0xff);    // ..then read registervalue
	CSN = 1;                // CSN high, terminate SPI communication	
	
	return(reg_val);        // return register value
}

/****************************************************************************************************/
/*功能：NRF24L01写寄存器函数，向寄存器reg写一个字节，同时返回状态字节
/****************************************************************************************************/
u8 SPI_RW_Reg(u8 reg, u8 value)
{
	u8 xdata status;
	CSN = 0;                   // CSN low, init SPI transaction
	status = SPI_RW(reg);      // select register
	SPI_RW(value);             // ..and write value to it..
	CSN = 1;                   // CSN high again
	return(status);            // return nRF24L01 status
}
/****************************************************************************************************/
/*函数：u8 SPI_Read_Buf(u8 reg, u8 *pBuf, u8 uchars)
/*功能: 用于读数据，reg：为寄存器地址，pBuf：为待读出数据地址，uchars：读出数据的个数
/****************************************************************************************************/
u8 SPI_Read_Buf(u8 reg, u8 *pBuf, u8 uchars)
{
	u8 xdata status,uchar_ctr;
	
	CSN = 0;                    		// Set CSN low, init SPI tranaction
	status = SPI_RW(reg);       		// Select register to write to and read status
	
	for(uchar_ctr=0; uchar_ctr<uchars; uchar_ctr++)
		pBuf[uchar_ctr] = SPI_RW(0);    // 
	
	CSN = 1;                           
	
	return(status);                    // return nRF24L01 status
}

/*********************************************************************************************************
/*函数：u8 SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)
/*功能: 用于写数据：为寄存器地址，pBuf：为待写入数据地址，uchars：写入数据的个数
/*********************************************************************************************************/
u8 SPI_Write_Buf(u8 reg, u8 *pBuf, u8 uchars)
{
	u8 xdata status,uchar_ctr;
	
	CSN = 0;            //SPI使能       
	status = SPI_RW(reg);   
	//最多只能发送32字节
	if(uchars>TX_PLOAD_WIDTH)
      uchars=TX_PLOAD_WIDTH;
	
	for(uchar_ctr=0; uchar_ctr<uchars; uchar_ctr++) //
	   SPI_RW(*pBuf++);
	CSN = 1;           //关闭SPI
	return(status);    // 
}

/****************************************************************************************************/
/*函数：void SetRX_Mode(void)
/*功能：数据接收配置 
/****************************************************************************************************/
void SetRX_Mode(void)
{
	CE=0;
	SPI_RW_Reg(WRITE_REG + CONFIG2, 0x0f);   		// IRQ收发完成中断响应，16位CRC	，主接收
	CE = 1; 
}


//该函数初始化NRF24L01到RX模式
//设置RX地址,写RX数据宽度,选择RF频道,波特率和LNA HCURR
//当CE变高后,即进入RX模式,并可以接收数据了		   
void NRF24L01_RX_Mode(uchar chn,uchar num)
{
	CE=0;	
	SPI_Write_Buf(WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS[num],RX_ADR_WIDTH);//写RX节点地址
    SPI_RW_Reg(WRITE_REG+EN_AA,0x01);    	//使能通道0的自动应答    
  	SPI_RW_Reg(WRITE_REG+EN_RXADDR,0x01);	//使能通道0的接收地址  	 
   	SPI_RW_Reg(WRITE_REG+RF_CH,Channel_fre[chn]);	    	//设置RF通信频率		  
    SPI_RW_Reg(WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//选择通道0的有效数据宽度 	    
    SPI_RW_Reg(WRITE_REG+RF_SETUP,0x0f);	//设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
  	SPI_RW_Reg(WRITE_REG+CONFIG2, 0x0f);		//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
  	CE = 1; //CE为高,进入接收模式
	
}

//该函数初始化NRF24L01到TX模式
//设置TX地址,写TX数据宽度,设置RX自动应答的地址,填充TX发送数据,选择RF频道,波特率和LNA HCURR
//PWR_UP,CRC使能
//当CE变高后,即进入RX模式,并可以接收数据了		   
//CE为高大于10us,则启动发送.	 

void NRF24L01_TX_Mode(uchar chn,uchar num)
{														 
	CE=0;	    
  	SPI_Write_Buf(WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS[num],TX_ADR_WIDTH);//写TX节点地址 
  	SPI_Write_Buf(WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS[num],RX_ADR_WIDTH); //设置TX节点地址,主要为了使能ACK	  
  	SPI_RW_Reg(WRITE_REG+EN_AA,0x01);     //使能通道0的自动应答    
  	SPI_RW_Reg(WRITE_REG+EN_RXADDR,0x01); //使能通道0的接收地址  
  	SPI_RW_Reg(WRITE_REG+SETUP_RETR,0x1f);//设置自动重发间隔时间:750us + 86us;最大自动重发次数:1次
  	SPI_RW_Reg(WRITE_REG+RF_CH,Channel_fre[chn]);       //设置RF通道为40
    SPI_RW_Reg(WRITE_REG+RF_SETUP,0x0f);  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
    SPI_RW_Reg(WRITE_REG+CONFIG2,0x0e);    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断
	CE=1;//CE为高,10us后启动发送
}
 
/******************************************************************************************************/
/*函数：u8 nRF24L01_RxPacket(u8* rx_buf)
/*功能：数据读取后放如rx_buf接收缓冲区中
/******************************************************************************************************/

u8 NRF24L01_RxPacket(u8* rx_buf)
{
	u8 xdata revale=0,sta;
	sta=SPI_Read(STATUS);	// 读取状态寄存其来判断数据接收状况

	CE=0;
	SPI_RW_Reg(WRITE_REG+STATUS,sta);   //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标志
	if(sta&RX_OK)				// 判断是否接收到数据
	{  
		SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);// read receive payload from RX_FIFO buffer
		revale =1;			//读取数据完成标志
	}
	SPI_RW_Reg(0xE2,0xff);//清楚RX FIFO的数据  
	CE=1;
	return revale;
}


u8 NRF24L01_TxPacket(u8 *txbuf)
{
	u8 xdata sta;   
	CE=0;
  	SPI_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//写数据到24L01 5个字节
 	CE=1;//启动发送	  
	while(IRQ!=0);//等待发送完成
	sta=SPI_Read(STATUS);  //读取状态寄存器的值	 
 	SPI_RW_Reg(WRITE_REG+STATUS,sta); 
	if(sta&MAX_TX)//达到最大重发次数
	{
	SPI_RW_Reg(FLUSH_TX,0xff);//清除TX FIFO寄存器 
		return MAX_TX; 
	}
	if(sta&TX_OK)//发送完成
	{
		return TX_OK;
	} 
	return 0xff;//其他原因发送失败
}

   //检测24L01是否存在
//返回值:0，成功;1，失败	
u8 NRF24L01_Check(void)
{
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 xdata i;
    SPI_Write_Buf(WRITE_REG+TX_ADDR,buf,5);//写入5个字节的地址.	
    SPI_Read_Buf(TX_ADDR,buf,5); //读出写入的地址  
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;//检测24L01错误	
	return 0;		 //检测到24L01
}	

