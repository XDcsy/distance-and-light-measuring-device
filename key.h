sbit f=P1^0;
sbit K1=P1^1;
sbit K2=P1^2;
sbit K3=P1^3;


void alarm_start()
{
	f=0;
}

//蜂鸣关闭
void alarm_stop()
{
	f=1;
}  

//等待
void delay_key()
{
	uchar i,j;
	for(i=0;i<200;i++)
	for(j=0;j<200;j++);
}
//按键检测
void Key()
{
	if(K1==0)
	{
		alarm_start();
		delay_key(); //消抖
		flag_BJS=0;
		flag_BJC=0;
		while(K1==0);
		alarm_stop();
		mode++;
		jishi=0;
		if(mode>=6)
		{
			mode=0;
			if((min+sec)!=0)
			jishi=1;	
		}	
		k=1;
	}
	//+键
	else if(K2==0)
	{
		alarm_start();
		delay_key(); //消抖
		flag_BJS=0;
		while(K2==0);//等待松手
		alarm_stop();
		if(mode==1)
		{
			min++;
			if(min>=99)
			min=99;
		}
		//最小值
		else if(mode==2)
		{
			sec++;
			if(sec>59)
			sec=0;		
		}
		else if(mode==3)
		{
			Mini++;
			if(Mini>=100)
			Mini=99;
		}
		else if(mode==4)
		{
			HG++;
			if(HG>=100)
			HG=99;
		}
		else if(mode==5)
		{
			LG++;
			if(LG>=HG-1)
			LG=HG-1;
		}
		k=1;
	}
	else if(K3==0)
	{
		alarm_start();
		delay_key();
		flag_BJS=0;
		while(K3==0);
		alarm_stop();
		if(mode==1)
		{
			min--;
			if(min<0)
			min=0;
		}
		else if(mode==2)
		{
			sec--;
			if(sec<0)
			sec=59;				
		}
		else if(mode==3)
		{
			Mini--;
			if(Mini<0)
			Mini=0;		
		}
		else if(mode==4)
		{
			HG--;
			if(HG<=LG+1)
			HG=LG+1;
		}
		else if(mode==5)
		{
			LG--;
			if(LG<0)
			LG=0;
		}
		k=1;
	}
}
