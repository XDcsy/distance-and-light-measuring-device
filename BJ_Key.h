
//管脚声明
sbit Feng=P1^0;
sbit K1=P1^1;
sbit K2=P1^2;
sbit K3=P1^3;

//蜂鸣打开
void Feng_Start()
{
	Feng=0;
}

//蜂鸣关闭
void Feng_Stop()
{
	Feng=1;
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
	//功能键按下
	if(K1==0)
	{
		Feng_Start();//蜂鸣器开
		delay_key(); //消抖
		flag_BJS=0;
		flag_BJC=0;
		while(K1==0);//等待松手
		Feng_Stop(); //蜂鸣器关闭
		mode++;      //模式++
		jishi=0;
		if(mode>=6)	 //达到最大限度归为
		{
			mode=0;
			if((min+sec)!=0)
			jishi=1;	
		}	
		k=1;			 //按键标志位
	}
	//+键
	else if(K2==0)
	{
		Feng_Start();//蜂鸣器开
		delay_key(); //消抖
		flag_BJS=0;
		while(K2==0);//等待松手
		Feng_Stop(); //蜂鸣器关闭
		//整
		if(mode==1)  //在最大值调整下
		{
			min++;	 //调整最大值
			if(min>=99)//到达99
			min=99;
		}
		//最小值
		else if(mode==2)//最小模式下调整
		{
			sec++;		//调整最小值
			if(sec>59) //最小值不能大于最大值
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
	//-键
	else if(K3==0)
	{
		Feng_Start();
		delay_key();
		flag_BJS=0;
		while(K3==0);
		Feng_Stop();
		//调整
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
