/*****************************************************************
*��������ͨ��F340��uart0��PC���д���ͨѶ�����̣�����ʵ��Ϊ��F340��ȡ�⴫����ģ�����ݺ�
*����PC�� ,�˿�ΪRX��P0.5��TX��P0.4
******************************************************************/
#include <c8051f340.h>
#include  <INTRINS.H>
#define uchar unsigned char
#define uint unsigned int

typedef   unsigned char BYTE;
typedef   unsigned short WORD;

#define	  SlaveAddress   0x46 
uchar  BUF[5];
uchar   ge,shi,bai,qian,wan;            //��ʾ����
//****************************************
/************************************************************************************
// ������ȫ�ֱ�������
*************************************************************************************/
#define  IIC_WRITE      0                 // WRITE direction bit
#define  IIC_READ       1                 // READ direction bit

sbit	  SCL=P1^0;      //IICʱ�����Ŷ���
sbit  	  SDA=P1^1;      //IIC�������Ŷ���



//*********************************************************
void conversion(uint temp_data)  //  ����ת���� ����ʮ���٣�ǧ����
{  
    wan=temp_data/10000+0x30 ;
    temp_data=temp_data%10000;   //ȡ������
	qian=temp_data/1000+0x30 ;
    temp_data=temp_data%1000;    //ȡ������
    bai=temp_data/100+0x30   ;
    temp_data=temp_data%100;     //ȡ������
    shi=temp_data/10+0x30    ;
    temp_data=temp_data%10;      //ȡ������
    ge=temp_data+0x30; 	
}
/***********************************************************************************
* Function: Delay_us;
*
* Description: ��ʱ����, ��ʱʱ�䷶Χ: 0~65535us;
*
* Input:  times, ��ʱʱ�����;
*
* Output: none;
*
* Return: none;
*
* Note:   ��ʱʱ�������65535us;
************************************************************************************/
void Delay_us(unsigned int times)
{
    unsigned int i;

	for (i=0; i<times; i++)
	{
		_nop_();	// ����NOP,��ʱ1us
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
        
	    _nop_();	
		_nop_();
	}
}


void Delay_ms(unsigned int times)
{
    unsigned int i;
	
	for (i=0; i<times; i++)	
		Delay_us(1000); 	// ������ʱ����,��ʱ1ms		
}

void Delay_s(unsigned int times)
{
	unsigned int i;
	
	for (i=0; i<times; i++)
		Delay_ms(1000);	   // ������ʱ����,��ʱ1s
}


void Delay5us()
{
    _nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
}

void Delay5ms()
{
    int n = 560;

    while (n--);
}
/**************************************
��ʼ�ź�
**************************************/
void BH1750_Start()
{
    SDA = 1;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 0;                    //�����½���
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
}

/**************************************
ֹͣ�ź�
**************************************/
void BH1750_Stop()
{
    SDA = 0;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 1;                    //����������
    Delay5us();                 //��ʱ
}

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void BH1750_SendACK(bit ack)
{
    SDA = ack;                  //дӦ���ź�
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ
}

/**************************************
����Ӧ���ź�
**************************************/
bit BH1750_RecvACK()
{
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    CY = SDA;                   //��Ӧ���ź�
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ

    return CY;
}

/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void BH1750_SendByte(uchar dat)
{
    uchar i;

    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;              //�Ƴ����ݵ����λ
        SDA = CY;               //�����ݿ�
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
    }
    BH1750_RecvACK();
}

/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
uchar BH1750_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1;                    //ʹ���ڲ�����,׼����ȡ����,
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        dat |= SDA;             //������               
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
    }
    return dat;
}

//*********************************

void Single_Write_BH1750(uchar REG_Address)
{
    BH1750_Start();                  //��ʼ�ź�
    BH1750_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
    BH1750_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf22ҳ 
  //  BH1750_SendByte(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf22ҳ 
    BH1750_Stop();                   //����ֹͣ�ź�
}


//*********************************************************
//
//��������BH1750�ڲ�����
//
//*********************************************************
void Multiple_read_BH1750(void)
{   uchar i;	
    BH1750_Start();                          //��ʼ�ź�
    BH1750_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
	
	 for (i=0; i<3; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
    {
        BUF[i] = BH1750_RecvByte();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 3)
        {

           BH1750_SendACK(1);                //���һ��������Ҫ��NOACK
        }
        else
        {		
          BH1750_SendACK(0);                //��ӦACK
       }
   }

    BH1750_Stop();                          //ֹͣ�ź�
    Delay5ms();
}


//****************************************




/*****************************************************************
*�˿ڳ�ʼ������
*****************************************************************/
void PORT_Init (void)
{
 XBR0      = 0x01;//�˿�I/O���濪�ؼĴ���0��UART TX0, RX0 �����˿����� P0.4 �� P0.5                                          
 XBR1      = 0x40;//�˿�I/O���濪�ؼĴ���1,���濪��ʹ��                   
 P0MDOUT   = 0x10;//P0.4Ϊ���������������Ϊ©����·���
}
/****************************************************************
*UART0��ʼ������
*****************************************************************/
void UART0_Init (void)
{
 SCON0    |= 0x10;                                                            
 CKCON     = 0x01;
 TH1       = 0x64;   //������Ϊ9600
 TL1       = TH1;                         
 TMOD      = 0x20;                     
 TR1       = 1;//P235����ʱ��1���п��ƣ���ʱ��1����                           
 TI0       = 1;//P235���ж�1����ѡ��INT1Ϊ���ش���                           
}

void tx_data(uchar g)  //����8λ����
 {
   SBUF0=g;     
   while(TI0==0);  //����
   TI0=0;
}

/*****************************************************************
*������
*****************************************************************/
void main()
{   
   uint  dis_data;
   float temp;
 PCA0MD    &= ~0x40;//�رտ��Ź�                  
 OSCICN    |= 0x03;//P126                     
 PORT_Init();//�˿ڳ�ʼ��                      
 UART0_Init();//UART0��ʼ��

 while(1)
  {
 
    Single_Write_BH1750(0x01);   // power on
    Single_Write_BH1750(0x10);   // H- resolution mode
    Delay_ms(180);               //��ʱ180ms
    Multiple_Read_BH1750();      //�����������ݣ��洢��BUF��  
	dis_data=BUF[0];
    dis_data=(dis_data<<8)+BUF[1];//�ϳ����� 

	temp=(float)dis_data/1.2;
	conversion(temp);         //�������ݺ���ʾ
	tx_data('L'); 
	tx_data('i'); 
	tx_data('g'); 
	tx_data('h'); 
	tx_data('t'); 
    tx_data(':'); 

    tx_data(wan); //��ʾ����
    tx_data(qian);  
    tx_data(bai); 
    tx_data(shi); 
	tx_data(ge); 

	tx_data('l'); //��ʾ����λ
	tx_data('x');  

	tx_data(0x0d);
    tx_data(0x0a);

  }
}
 