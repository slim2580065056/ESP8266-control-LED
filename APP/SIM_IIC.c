/************************************************
*		SCL->PB3
*		SDA->PB4
*		IIC���Զ��庯����ĩβ����SCL_L�������ݱ仯
************************************************/
#include "SIM_IIC.h"

extern u8 length;

void SIM_SCL_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;		//��©�������IIC����������������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
void SIM_SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;		//��©�������IIC����������������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
void SIM_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		//��©�������IIC����������������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
/*	IIC ���߳�ʼ�����ø�����	*/
void SIM_IIC_INIT(void)
{
	SIM_IIC_OUT;
	SIM_SCL_H;
	SIM_SDA_H;
}
/*  IIC ��ʼ�ź�	*/
void SIM_IIC_START(void)
{
	SIM_IIC_OUT;
	SIM_SCL_H;
	SIM_SDA_H;
	Delay_us(5);
	SIM_SDA_L;
	Delay_us(5);
	SIM_SCL_L;			//data allow change,and received first bit
}
/*	IIC��ֹ�ź�	*/
void SIM_IIC_STOP(void)
{
	SIM_IIC_OUT;
	SIM_SCL_H;
	SIM_SDA_L;
	Delay_us(5);
	SIM_SDA_H;
	Delay_us(5);	
}
/*	IICӦ�����	*/
AckStatus SIM_IIC_CHECK_ACK(void)
{
	SIM_IIC_IN;		//��ȡ�ھ�λ״̬
	SIM_SCL_L;		//�����ȡ���ݣ��Զ��庯��ĩβ����
	if(SIM_SDA_R==ACK)
	{
		SIM_SCL_H;		//����ʱ��5us
		Delay_us(1);
		SIM_SCL_L;		//data allow change,and receive next byte first bit
		return ACK;
	}
	else
	{
		SIM_IIC_STOP();
		return NACK;
	}
}
/*	IIC����Ӧ���������Ӧ��	*/
void SIM_IIC_MASTER_ACK(AckStatus flag)
{
	SIM_IIC_OUT;
//	SCL_L;		//�����ȡ���ݣ��Զ��庯��ĩβ����
	(flag==ACK)?SIM_SDA_L:SIM_SDA_H;		//flagΪ0����Ӧ��
	SIM_SCL_H;			//�������ø�
	Delay_us(1);
	SIM_SCL_L;			//data allow change ,and receive next
}
/*	IIC����һ���ֽ����ݣ���MSB��ʼ	*/
void SIM_SEND_BYTE(u8 byte)
{
	u8 i;
	SIM_IIC_OUT;
	SIM_SCL_L;		  //�����һ�����ݱ仯
	/*	ȡbyte�е����λ�����Ϊ1��SDAΪ�ߣ���֮SDAΪ��	*/
	for(i=0;i<8;i++)
	{
		SIM_SCL_L;		//��������仯
		(byte&0x80)==0x80?SIM_SDA_H:SIM_SDA_L;		//�ж�MSB	
		Delay_us(1);
		SIM_SCL_H;		//���ݲ�����仯
		byte<<=1;	//byte����һλ		
	}
	SIM_SCL_L;			//��������仯������Ӧ��λ
}
/*	IIC����һ���ֽ����ݣ���MSB��ʼ	*/
u8 SIM_READ_BYTE(void)
{
	u8 i,byte=0;
	SIM_IIC_IN;
	SIM_SCL_H;
	for(i=0;i<8;i++)
	{
		byte|=(SIM_SDA_R&0x80);	//�����λ�Ƚ�
		SIM_SCL_L;				//��������仯
		Delay_us(1);	//���ݱ仯ʱ�䣬��ֹ����
		byte<<=1;			//��������һλ
		SIM_SCL_H;				//���ݲ�����仯
	}
	SIM_SCL_L;			//��������仯������Ӧ��
	return byte;
}
/*	����һ��ָ��P������Ϊlength���ַ�	*/
void SIM_SEND_DATA(u8 addr,u8 *P)
{
	u8 flag,i;
	i=0;
	SIM_IIC_START(); 									//START
	SIM_SEND_BYTE(Device_addr);				//DEVICE_ADDRESS & WRITE
	flag=SIM_IIC_CHECK_ACK();					//ACK
	SIM_SEND_BYTE(addr);							//WORD_ADDRESS
	flag=SIM_IIC_CHECK_ACK();					//ACK	//	while(length--)
	while(*P!=NULL)
	{
		i++;
		SIM_SEND_BYTE(*P++);							//DATA
		flag=SIM_IIC_CHECK_ACK();				//ACK
	}	
	printf("is %d\r\n",i);
	SIM_IIC_STOP();										//STOP
}
/*	����һ���ַ����������ظ��ַ�����ַ	*/
//u8 *SIM_READ_DATA(u8 addr,u8 length)
//{
//	u8 *p,flag;
//	IIC_START();									//START
//	SEND_BYTE(Device_addr);				//DEVICE_ADDRESS & WRITE
//	flag=IIC_CHECK_ACK();					//ACK
//	SEND_BYTE(addr);							//WORD_ADDRESS n
//	flag=IIC_CHECK_ACK();					//ACK
//	IIC_START();
//	SEND_BYTE(Device_addr | 1);
//	flag=IIC_CHECK_ACK();
//	while(length--)			//��break����
//	{
//		*p++=READ_BYTE();						//DATA n
//		IIC_MASTER_ACK(length!=1?ACK:NACK);				//ACK
//	}
//	return p;
//}
