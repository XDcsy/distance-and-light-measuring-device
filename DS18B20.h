#define uchar unsigned char
#define uint unsigned int

sbit DS=P1^4;

uint temp=0;

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

void reset(void)
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

//read a bit
bit tmpreadbit(void)
{
    uint i;
    bit data;
    DS=0;i++;
    DS=1;i++;i++;
    data=DS;
    i=8;while(i>0)i--;
    return (data);
}

uchar tmpread(void)
{
    uchar i,j,data;
    data=0;
    for(i=1;i<=8;i++)
    {
        j=tmpreadbit();
        data=(j<<7)|(data>>1);
    }
    return(data);
}

//write a byte to ds18b20
void tmpwritebyte(uchar data)
{
    uint i;
    uchar j;
    bit testb;
    for(j=1;j<=8;j++)
    {
        testb=data&0x01;
        data=data>>1;
        if(testb)             //write 1
        {
            DS=0;
            i++;i++;
            DS=1;
            i=8;while(i>0)i--;
        }
        else
        {
            DS=0;              //write 0
            i=8;while(i>0)i--;
            DS=1;
            i++;i++;
        }
  }
}

//DS18B20 begin change
void tmpchange(void)
{
    reset();             //初始化 DS18B20
    delay(1);              //延时
    tmpwritebyte(0xcc);    //跳过序列号命令
    tmpwritebyte(0x44);    //发送温度转换命令
}

//get the temperature  获得温度
uint tmp()
{
    float tt=0;
    uchar a=0,b=0;
    reset();
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
	//得到十进制温度值
    tt=temp*0.0625;
    //读回数据的最低位代表的是 0.0625 度。
    temp=tt*10+0.5;
    return temp;
}
