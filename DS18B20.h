
#define uchar unsigned char 
#define uint unsigned int 
//define interface  ���� DS18B20 �ӿ�
sbit DS=P1^4; 
//variable of temperature                      
uint temp=0;
                          
//��ʱ�Ӻ���  
//sign of the result positive or                                 
void delay(uint count) 
{    
	uint i; 
	while(count) 
    { 
        i=200; 
        while(i>0) 
        i--; 
        count--; 
    } 
}

//���ͳ�ʼ������λ�ź� 
void dsreset(void)
{ 
	//DS18B20 ��ʼ��
    uint i;                                 
    DS=0; 
    i=103; 
    while(i>0)i--; 
    DS=1; 
    i=4; 
    while(i>0)i--; 
}

//read a bit  ��һλ
bit tmpreadbit(void)               
{ 
      uint i; 
      bit dat;
	  //i++ for delay    С��ʱһ��  
      DS=0;i++;                    
      DS=1;i++;i++; 
      dat=DS; 
      i=8;while(i>0)i--; 
return (dat); 
}

//read a byte date  ��һ���ֽ� 
uchar tmpread(void)      
{ 
    uchar i,j,dat; 
    dat=0; 
    for(i=1;i<=8;i++) 
    { 
        j=tmpreadbit(); 
		//�������������λ����ǰ�棬�����պ�
		//һ���ֽ��� dat �� 
        dat=(j<<7)|(dat>>1);      
    } 
	//��һ���ֽ����ݷ��� 
    return(dat);                          
} 

//write a byte to ds18b20 
//дһ���ֽڵ� DS18B20 ��   
void tmpwritebyte(uchar dat)      
{  
	                                                  
    uint i; 
    uchar j; 
    bit testb; 
    for(j=1;j<=8;j++) 
    { 
        testb=dat&0x01; 
        dat=dat>>1; 
        if(testb)             //write 1       д 1 ���� 
        { 
            DS=0; 
            i++;i++; 
            DS=1; 
            i=8;while(i>0)i--; 
        } 
        else 
        { 
            DS=0;              //write 0      д 0 ���� 
            i=8;while(i>0)i--; 
            DS=1; 
            i++;i++; 
        } 
  } 
}

//DS18B20 begin change  �����¶�ת������
void tmpchange(void)     
{ 
    dsreset();             //��ʼ�� DS18B20 
    delay(1);              //��ʱ 
    tmpwritebyte(0xcc);    //�������к����� 
    tmpwritebyte(0x44);    //�����¶�ת������ 
} 

//get the temperature  ����¶�
uint tmp()                               
{ 
    float tt=0; 
    uchar a=0,b=0; 
    dsreset(); 
    delay(1); 
	 //���Ͷ�ȡ��������
    tmpwritebyte(0xcc); 
    tmpwritebyte(0xbe);
	 //�����������ֽ�����          
    a=tmpread();               
    b=tmpread(); 
	 //two byte    compose a int variable 
	 //���ֽںϳ�һ�����ͱ�����
    temp=b; 
    temp<<=8;                          
    temp=temp|a;                 
	 if(b==0xff)
	 {
	   flag=1;
	   temp=~temp+1;
	 }
	 //�õ���ʵʮ�����¶�ֵ����Ϊ DS18B20	
    tt=temp*0.0625;               
    //���Ծ�ȷ�� 0.0625 �ȣ����Զ������ݵ����λ������� 
    //0.0625 �ȡ�
	 //�Ŵ�ʮ������������Ŀ�Ľ�С������һλ 
    temp=tt*10+0.5;       
    //Ҳת��Ϊ����ʾ���֣�ͬʱ����һ��������������� 
	 //�����¶�ֵ
    return temp;           
}  
   