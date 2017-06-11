
//LCD
sbit LCDRS = P2^7;
sbit LCDEN= P2^6;

//initialize
uchar code Init1[]="Time:00:00 G:00%";	 
uchar code Init2[]="S:000cm Tem:00 C";

//initialize content
uchar code Init3[]="Time:00:00 HG:00";
uchar code Init4[]="HS:000cm   LG:00";

//LCD延时
void LCDdelay(uint z)
{
    uint x,y;
    for(x=z;x>0;x--)
        for(y=10;y>0;y--);
}
//写命令
void w_command(uchar com)
{
  LCDRS=0;
  P0=com;
  LCDdelay(5);
  LCDEN=1;
  LCDdelay(5);
  LCDEN=0;
}
//写数据
void w_data(uchar date)
{
  LCDRS=1;
  P0=date;
  LCDdelay(5);
  LCDEN=1;
  LCDdelay(5);
  LCDEN=0;
}
//1602
void Init1602()
{
  uchar i=0;
  w_command(0x38);
  w_command(0x0C);
  w_command(0x06);
  w_command(0x01);
  w_command(0x80);

  for(i=0;i<16;i++)
  {
		w_data(Init1[i]);
  }
	w_data(0xdf);
	w_data(Init1[14]);

  w_command(0x80+0x40);
  for(i=0;i<16;i++)
  {
		w_data(Init2[i]);
  }
}

//温度 距离显示
void Display_1602(min,sec,W,uint L,uint G_light)
{
	//倒计时时间显示
	w_command(0x80+5);
	w_data('0'+min/10);
	w_data('0'+min%10);
	w_command(0x80+8);
	w_data('0'+sec/10);
	w_data('0'+sec%10);
	//光线值显示
	w_command(0x80+13);
	w_data('0'+G_light/10);
	w_data('0'+G_light%10);
	//温度值显示
	w_command(0x80+0x40+12);
	w_data('0'+W/10);
	w_data('0'+W%10);
	w_data(0xdf);

	//长度值显示
	if(flag1s==1)
	{
		w_command(0x80+0x40+2);//选中第二行第十列
		w_data('0'+L/100);
		w_data('0'+L/10%10);
		w_data('0'+L%10);
	}
	else if(flag1s==0)
	{
		w_command(0x80+0x40+2);
		w_data('-');
		w_data('-');
		w_data('-');
	}
}

//1602初始化最大化最小化调整界面
void Init_MaxMin()
{
	uchar i=0;
	w_command(0x38);//屏幕初始化
	w_command(0x0f);//打开显示 无光标 无光标闪烁
	w_command(0x06);//当读或写一个字符是指针后一一位
	w_command(0x01);//清屏
	w_command(0x80);
	for(i=0;i<16;i++)
	{
		w_data(Init3[i]);
	}
	w_command(0x80+0x40);
	for(i=0;i<16;i++)
	{
		w_data(Init4[i]);
	}

	w_command(0x80+5);
	w_data('0'+min/10);
	w_data('0'+min%10);
	
	w_command(0x80+8);
	w_data('0'+sec/10);
	w_data('0'+sec%10);

	w_command(0x80+14);
	w_data('0'+HG/10);
	w_data('0'+HG%10);

	w_command(0x80+0x40+3);
	w_data('0'+Mini/100);
	w_data('0'+Mini/10%10);
	w_data('0'+Mini%10);

	w_command(0x80+0x40+14);
	w_data('0'+LG/10);
	w_data('0'+LG%10);	
}



