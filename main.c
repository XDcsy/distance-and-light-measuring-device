#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int
#define ULint unsigned long int

char flag=0;

char flags=0;

char flag1s=0;

uint time=0;

ULint L_=0;

uint t_=0;

uchar mode=0;

char min=45;
char sec=0;
char Mini=30;
char HG=70;
char LG=30;
//������־
uchar k=0;
//��ֵ����
uchar FW=0;
uint light=0;

sbit CS   = P2^3;
sbit Clk = P2^0;
sbit DATI = P2^1;
sbit DATO = P2^1;

unsigned char dat = 0x00;
unsigned char CH=0;

bit bdata flag_BJS=0,flag_BJC=0,flag_BJG=0,jishi=1;
#include "key.h"
#include "display.h"
#include "ultrasonic_wave.h"
#include "DS18B20.h"



void delayms(uint ms);


unsigned char adc0832(unsigned char CH)
{
    unsigned char i,test,adval;
    adval = 0x00;
    test = 0x00;
    Clk = 0;
    DATI = 1;
    _nop_();
    CS = 0;
    _nop_();
    Clk = 1;
   _nop_();


   if ( CH == 0x00 )
   {
        Clk = 0;
        DATI = 1;
        _nop_();
        Clk = 1;
        _nop_();
        Clk = 0;
        DATI = 0;
        _nop_();
        Clk = 1;
        _nop_();
    }
    else
    {
        Clk = 0;
        DATI = 1;
        _nop_();
        Clk = 1;
        _nop_();
        Clk = 0;
        DATI = 1;
        _nop_();
        Clk = 1;
        _nop_();
   }

        Clk = 0;
        DATI = 1;
    for( i = 0;i < 8;i++ )
    {
        _nop_();
        adval <<= 1;
        Clk = 1;
        _nop_();
        Clk = 0;
        if (DATO)
            adval |= 0x01;
        else
            adval |= 0x00;
    }
    for (i = 0; i < 8; i++)
    {
        test >>= 1;
        if (DATO)
            test |= 0x80;
        else
            test |= 0x00;
            _nop_();
            Clk = 1;
            _nop_();
            Clk = 0;
      }
    if (adval == test)
        dat = test;
    nop_();
    CS = 1;
    DATO = 1;
    Clk = 1;
    return dat;
}
void work()
{
    light=adc0832(CH)*100/255;
}

void main()
{
    Init_ultrasonic_wave();
    //��Ļ��ʼ��
    Init1602();
    //�¶ȳ�ʼ��
    tmpchange();
    t_=tmp();
    tmpchange();
    t_=tmp();
    tmpchange();
    t_=tmp();

    //ѭ����ʾ
    while(1)
    {
        Key();
        //������ʾ
        if(mode==0)
        {
            StartModule();//����������
            while(!RX);   //��RXΪ��ʱ�ȴ�
            TR0=1;        //��������
            while(RX);    //��RXΪ1�������ȴ�
            TR0=0;        //�رռ���

            delayms(20);  //20MS
            tmpchange();  //�¶�ת��
            t_=tmp();     //���¶�

            work();
            if(light<LG||light>HG)
            {
                flag_BJG=1;
            }
            else
            {
                flag_BJG=0;
            }
            Conut(t_/10); //�������
            if(L_<Mini)
            {
                flag_BJC=1;
            }
            else
            {
                flag_BJC=0;
            }
            if(flag_BJC==0&&flag_BJS==0&&flag_BJG==0)
            f=1;
            Display_1602(min,sec,t_/10,L_,light);
        }
        //������ʾ
        else if(mode!=0)
        {
            flag_BJC=0;
            flag_BJS=0;
            flag_BJG=0;
            f=1;
            //�����Сֵ
            Init_MaxMin();
            while(mode!=0)
            {
                Key();
                if(k==1&&mode==1)
                {
                    Init_MaxMin();
                    w_command(0x80+6);
                }
                else if(k==1&&mode==2)
                {
                    Init_MaxMin();
                    w_command(0x80+9);
                }
                else if(k==1&&mode==3)
                {
                    Init_MaxMin();
                    w_command(0x80+0x40+5);
                }
                else if(k==1&&mode==4)
                {
                    Init_MaxMin();
                    w_command(0x80+15);
                }
                else if(k==1&&mode==5)
                {
                    Init_MaxMin();
                    w_command(0x80+0x40+15);
                }
                k=0;
            }
            //�����ʼ��
            Init1602();
        }
    }
}

void delayms(uint ms)
{
    uchar i=100,j;
    for(;ms;ms--)
    {
        while(--i)
        {
            j=10;
            while(--j);
        }
    }
}
//T0�ж��������������,������෶Χ
void CJ_T0() interrupt 1
{
    flags=1;
}

void time1() interrupt 3
{
    uchar m;
    TH1=0x3c;
    TL1=0xb0;
    m++;
    if((m==10||m==20)&&(flag_BJS==1||flag_BJC==1||flag_BJG==1))//500ms������ȡ��
    {
        f=!f;
    }
    if(m>=20)
    {
        m=0;
        if(jishi==1)
        {
            sec--; 
            if(sec<0)
            {
                sec=59;
                min--;
                if(min<0)
                {
                    sec=0;
                    min=0;
                    jishi=0;
                    flag_BJS=1;
                }
            }
        }
    }
}



