
#define uchar unsigned char 
#define uint unsigned int 
//define interface  定义 DS18B20 接口
sbit DS=P1^4; 
//variable of temperature                      
uint temp=0;
                          
//延时子函数  
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

//发送初始化及复位信号 
void dsreset(void)
{ 
	//DS18B20 初始化
    uint i;                                 
    DS=0; 
    i=103; 
    while(i>0)i--; 
    DS=1; 
    i=4; 
    while(i>0)i--; 
}

//read a bit  读一位
bit tmpreadbit(void)               
{ 
      uint i; 
      bit dat;
	  //i++ for delay    小延时一下  
      DS=0;i++;                    
      DS=1;i++;i++; 
      dat=DS; 
      i=8;while(i>0)i--; 
return (dat); 
}

//read a byte date  读一个字节 
uchar tmpread(void)      
{ 
    uchar i,j,dat; 
    dat=0; 
    for(i=1;i<=8;i++) 
    { 
        j=tmpreadbit(); 
		//读出的数据最低位在最前面，这样刚好
		//一个字节在 dat 里 
        dat=(j<<7)|(dat>>1);      
    } 
	//将一个字节数据返回 
    return(dat);                          
} 

//write a byte to ds18b20 
//写一个字节到 DS18B20 里   
void tmpwritebyte(uchar dat)      
{  
	                                                  
    uint i; 
    uchar j; 
    bit testb; 
    for(j=1;j<=8;j++) 
    { 
        testb=dat&0x01; 
        dat=dat>>1; 
        if(testb)             //write 1       写 1 部分 
        { 
            DS=0; 
            i++;i++; 
            DS=1; 
            i=8;while(i>0)i--; 
        } 
        else 
        { 
            DS=0;              //write 0      写 0 部分 
            i=8;while(i>0)i--; 
            DS=1; 
            i++;i++; 
        } 
  } 
}

//DS18B20 begin change  发送温度转换命令
void tmpchange(void)     
{ 
    dsreset();             //初始化 DS18B20 
    delay(1);              //延时 
    tmpwritebyte(0xcc);    //跳过序列号命令 
    tmpwritebyte(0x44);    //发送温度转换命令 
} 

//get the temperature  获得温度
uint tmp()                               
{ 
    float tt=0; 
    uchar a=0,b=0; 
    dsreset(); 
    delay(1); 
	 //发送读取数据命令
    tmpwritebyte(0xcc); 
    tmpwritebyte(0xbe);
	 //连续读两个字节数据          
    a=tmpread();               
    b=tmpread(); 
	 //two byte    compose a int variable 
	 //两字节合成一个整型变量。
    temp=b; 
    temp<<=8;                          
    temp=temp|a;                 
	 if(b==0xff)
	 {
	   flag=1;
	   temp=~temp+1;
	 }
	 //得到真实十进制温度值，因为 DS18B20	
    tt=temp*0.0625;               
    //可以精确到 0.0625 度，所以读回数据的最低位代表的是 
    //0.0625 度。
	 //放大十倍，这样做的目的将小数点后第一位 
    temp=tt*10+0.5;       
    //也转换为可显示数字，同时进行一个四舍五入操作。 
	 //返回温度值
    return temp;           
}  
   