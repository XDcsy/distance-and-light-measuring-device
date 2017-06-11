sbit RX=P2^4;
sbit TX=P2^5;

//��������ʼ��
void Init_ultrasonic_wave()
{
	 TX=0;			   //�رշ���
	 TMOD=0x11;		   //��T0Ϊ��ʽ1��GATE=1��
	 TH0=0;
	 TL0=0; 
	 TH1=0x3c;
	 TL0=0xb0;         
	 ET0=1;           //����T0�ж�
	 ET1=1;
	 TR1=1;
	 EA=1;			   //�������ж�	
}

//����������
void StartModule() 	//����ģ��
{
	TX=1;			      //����һ��ģ��
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
//���㲻ͬ�¶��µ��ٶ�
void JS_(uchar WD)
{
	//����-30
	if(WD>=30&&flag==1)
	{
		L_=(time*3.13)/200;     //�������CM;		
	}
	//����-20<-30
	else if(WD>=20&&WD<30&&flag==1)
	{
		L_=(time*3.19)/200;     //�������CM;		
	}
	//����-10<-20
	else if(WD>=10&&WD<20&&flag==1)
	{
		L_=(time*3.25)/200;     //�������CM;		
	}
	//����0<-10
	else if(WD>=0&&WD<10&&flag==1)
	{
		L_=(time*3.23)/200;     //�������CM;		
	}

	//����0<10
	else if(WD<=10&&WD>0&&flag==0)
	{
		L_=(time*3.38)/200;     //�������CM;		
	}
	//����10<20
	else if(WD<=20&&WD>10&&flag==0)
	{
		L_=(time*3.34)/200;     //�������CM;		
	}
	//����20<30
	else if(WD<=30&&WD>20&&flag==0)
	{
		L_=(time*3.49)/200;     //�������CM;		
	}
	//����30
	else if(WD>30&&flag==0)
	{
		L_=(time*3.86)/200;     //�������CM;		
	}
}
//������� SDΪ��ʱ�ĳ����ٶ�
void Conut(uchar WD)
{
	 time=TH0*256+TL0;
	 TH0=0;
	 TL0=0;
	 JS_(WD);

	 //�������200���߳�ʱ
	 if(L_>500||flags==1)
	 {
		flags=0;
		//��Ч��ʾ
		flag1s=0;
		L_=500;
		FW=1;	
//		Feng_Start();	
	 }	
	 //����С��100
	 else if(L_<=500)
	 {
		flag1s=1;
		FW=0;	
//		Feng_Stop();
	 }

}


