/************************************************************
*		SSD1306 SLAVE ADDRESS      0 1 1 1   1 0	SA0   R/W#
*		Control byte			Co	D/C	0	0		0	0	0	0 	ACK
*************************************************************/
#include "OLED.h"
#include "FONT.h"
#include "PIC.h"

/**
	*	@brief	OLED send command
	*	@param	cmd
	*	@retval None
	*/
void OLED_CMD(u8 cmd)
{
	SIM_IIC_START(); 									//START
	SIM_SEND_BYTE(Device_addr);				//DEVICE_ADDRESS & WRITE
	SIM_IIC_CHECK_ACK();							//ACK
	SIM_SEND_BYTE(0x00);							//COMMAND_ADDRESS
	SIM_IIC_CHECK_ACK();							//ACK	//	while(length--)
	SIM_SEND_BYTE(cmd);								//DATA
	SIM_IIC_MASTER_ACK(NACK);					//NACK
	SIM_IIC_STOP();										//STOP
}
/**
	*	@brief  OLED send data to fill the grid
	*	@param  data
	*	@retcal None
	*/
void OLED_DATA(u8 data)
{
	SIM_IIC_START(); 									//START
	SIM_SEND_BYTE(Device_addr);				//DEVICE_ADDRESS & WRITE
	SIM_IIC_CHECK_ACK();							//ACK
	SIM_SEND_BYTE(0x40);							//DATA_ADDRESS
	SIM_IIC_CHECK_ACK();							//ACK	//	while(length--)
	SIM_SEND_BYTE(data);							//DATA
	SIM_IIC_MASTER_ACK(NACK);					//NACK
	SIM_IIC_STOP();										//STOP
}
/**
	*	@brief	OLED Initialized
	*	@param  None
	*	@retval None
	*/
void OLED_Init(void)
{
	Delay_ms(200);
	OLED_CMD(0xAE);				//��ʾ�ر�
	OLED_CMD(0x21);OLED_CMD(0x00);OLED_CMD(0x7F);				//��������ʼ��ַ�ͽ�����ַ	
	OLED_CMD(0x22);OLED_CMD(0x00);OLED_CMD(0x07);				//����ҳ��ʼ��ַ�ͽ�����ַ
	OLED_CMD(0x20);OLED_CMD(0x00);				//�����ڴ�Ѱַģʽ  00->ˮƽѰַ��	01->��ֱѰַ
	OLED_CMD(0x40);				//��λ����ʼ�е�ַΪ0	
	OLED_CMD(0xA1);				//�е�ַ127ӳ�䵽SEG0
	OLED_CMD(0xC8);				//ɨ������ӳ��ģʽ
	OLED_CMD(0xD3);OLED_CMD(0x00);				//����COM�ڴ�ֱ�ƶ�
	OLED_CMD(0xDA);OLED_CMD(0x10);				//����COM��Ϊ��ѡ��COM�����ã�����COM������ӳ��
	OLED_CMD(0xA8);OLED_CMD(0x3F);				//����MUX����
	OLED_CMD(0xDB);OLED_CMD(0x30);				//����VCOMH��ѹ
	OLED_CMD(0x81);OLED_CMD(0xFF);				//���öԱȶ�	
	OLED_CMD(0xA4);				//�ڴ�������ʾ
	OLED_CMD(0xA6);				//������ʾ
	OLED_CMD(0xFF);				//�������	
	OLED_CMD(0x8D);				//��ɱ�����
	OLED_CMD(0x14);				//ʹ�ܵ�ɱ�	
	OLED_CMD(0xAF);				//��ʾ����	
		
/*	����������	*/	
	OLED_Clear();			//�����ʾ
	OLED_PIC(KISS);OLED_CMD(0xA7);Delay_ms(5000);		//������ʾͼƬ//��ʱ5s
	OLED_CMD(0xA6);Delay_ms(5000);		//������ʾ

	OLED_Clear();			//�����ʾ
}
/**
	*	@brief  OLED screen clear
	*	@param  None
	*	@retval None
	*/
void OLED_Clear(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
		OLED_CMD(0xB0+i);		//ҳ��ַ
		OLED_CMD(0x00);			//��λ����ʼ��ַ
		OLED_CMD(0x10);			//��λ����ʼ��ַ
		for(n=0;n<128;n++)
			OLED_DATA(0x00);
	}
}
/**
	*	@brief  OLED area screen clear(page3 to page 8)
	*	@param  None
	*	@retval None
	*/
void OLED_Area_Clear(void)
{
	u8 i,n;
	for(i=3;i<8;i++)
	{
		OLED_CMD(0xB0+i);		//ҳ��ַ
		OLED_CMD(0x00);			//��λ����ʼ��ַ
		OLED_CMD(0x10);			//��λ����ʼ��ַ
		for(n=0;n<128;n++)
			OLED_DATA(0x00);
	}
}
/**
	*	@brief  OLED Screen Set site
	*	@param  x , y
	*	@retval None
	*/
void OLED_Pos(u8 x,u8 y)
{
	u8 ly,hy,hx;//,lx;
	x>=64?x%=64:x;
	y>=128?y%=128:y;
	ly=y%16;		//����
	hy=y/16;		//��ģ
//	lx=x%8;
	hx=x/8;
	OLED_CMD(0xB0+hx);		//ҳ��ַ
	OLED_CMD(0x00+ly);		//��λ����ʼ��ַ
	OLED_CMD(0x10+hy);		//��λ����ʼ��ַ
//	OLED_DATA(0x01<<lx);		//�������
}
/**
	*	@breif  OLED Write size 6*8 byte
	*	@param  x,y,byte
	*	@retval None
	*/
void OLED_C6X8(u8 x,u8 y,u8 byte)
{
	u8 i;
 	u8 chr=byte-' ';
	OLED_Pos(x,y);
	for(i=0;i<6;i++)
		OLED_DATA(F6X8[chr][i]);
}
/**
	*	@breif  OLED Write size 6*8 String
	*	@param  x,y,byte
	*	@retval None
	*/
void OLED_S6X8(u8 x,u8 y,u8 *string)
{
	u8 len=0;
	OLED_Pos(x,y);
	while(string[len]!='\0')	
	{	
		OLED_C6X8(x,y+6*len,string[len]);
		len++;
	}
}
/**
	*	@breif  OLED fill grid to draw Picture
	*	@param  const Pic
	*	@retval None
	*/
void OLED_PIC(const u8 *Pic)
{
	u8 i,j;
	u16 n=0;
	OLED_Pos(0,0);
	for(i=0;i<8;i++)
	{			
		for(j=0;j<128;j++)	
		{		
			OLED_Pos(i*8,j);
			OLED_DATA(Pic[n++]);
		}
	}	
}
/**
	*	@breif  OLED Write size 8*16 byte
	*	@param  x,y,byte
	*	@retval None
	*/
void OLED_C8X16(u8 x,u8 y,u8 byte)
{
	u8 i,j;
 	u8 chr=byte-' ';
	OLED_Pos(x,y);
	for(i=0;i<2;i++)
	{
		OLED_Pos(x+i*8,y);
		for(j=0;j<8;j++)
			OLED_DATA(F8X16[chr][i*8+j]);
	}
}
/**
	*	@breif  OLED Write size 8*16 string
	*	@param  x,y,byte
	*	@retval None
	*/
void OLED_S8X16(u8 x,u8 y,u8 *string)
{
	u8 len=0;
	while(string[len]!='\0')	
	{	
		OLED_C8X16(x,y+len*8,string[len]);
		len++;
	}
}
/*****************************************************
*		m^n����
*		���أ�m^n�η�
******************************************************/
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
/*****************************************************
*	x,y :�������	 
*	len :���ֵ�λ��
*	mode:ģʽ	0,���ģʽ(��0ʡ��);1,����ģʽ(��0���)
*	num:��ֵ(0~4294967295)	 
*****************************************************/
void OLED_S6X8Num(u8 x,u8 y,u32 num,u8 len,u8 mode)
{         	
	u8 t,temp;					   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(mode==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_C6X8(x,y+6*t,' ');//�ո��ASCII��ƫ��ֵΪ32
				continue;
			}
			else mode=1; 		 	 
		}
		OLED_C6X8(x,y+6*t,temp+'0'); //���ո�
	}
} 




