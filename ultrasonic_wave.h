sbit RX=P2^4;
sbit TX=P2^5;

//超声波初始化
void Init_ultrasonic_wave()
{
	 TX=0;			   //关闭发射
	 TMOD=0x11;		   //设T0为方式1，GATE=1；
	 TH0=0;
	 TL0=0; 
	 TH1=0x3c;
	 TL0=0xb0;         
	 ET0=1;           //允许T0中断
	 ET1=1;
	 TR1=1;
	 EA=1;			   //开启总中断	
}

//启动超声波
void StartModule() 	//启动模块
{
	TX=1;			      //启动一次模块
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_();
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_();
	TX=0;
}
//计算不同温度下的速度
void JS_(uchar WD)
{
	//大于-30
	if(WD>=30&&flag==1)
	{
		L_=(time*3.13)/200;     //算出来是CM;		
	}
	//大于-20<-30
	else if(WD>=20&&WD<30&&flag==1)
	{
		L_=(time*3.19)/200;     //算出来是CM;		
	}
	//大于-10<-20
	else if(WD>=10&&WD<20&&flag==1)
	{
		L_=(time*3.25)/200;     //算出来是CM;		
	}
	//大于0<-10
	else if(WD>=0&&WD<10&&flag==1)
	{
		L_=(time*3.23)/200;     //算出来是CM;		
	}

	//大于0<10
	else if(WD<=10&&WD>0&&flag==0)
	{
		L_=(time*3.38)/200;     //算出来是CM;		
	}
	//大于10<20
	else if(WD<=20&&WD>10&&flag==0)
	{
		L_=(time*3.34)/200;     //算出来是CM;		
	}
	//大于20<30
	else if(WD<=30&&WD>20&&flag==0)
	{
		L_=(time*3.49)/200;     //算出来是CM;		
	}
	//大于30
	else if(WD>30&&flag==0)
	{
		L_=(time*3.86)/200;     //算出来是CM;		
	}
}
//距离计算 SD为当时的超声速度
void Conut(uchar WD)
{
	 time=TH0*256+TL0;
	 TH0=0;
	 TL0=0;
	 JS_(WD);

	 //距离大于200或者超时
	 if(L_>500||flags==1)
	 {
		flags=0;
		//无效显示
		flag1s=0;
		L_=500;
		FW=1;	
//		Feng_Start();	
	 }	
	 //距离小于100
	 else if(L_<=500)
	 {
		flag1s=1;
		FW=0;	
//		Feng_Stop();
	 }

}


