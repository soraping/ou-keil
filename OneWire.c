#include <REGX52.H>

sbit OneWire_DQ = P3^3;

unsigned char OneWire_Init(void)
{
    unsigned char AckBit = 0;
    unsigned char i;
    // 总线复位
    OneWire_DQ = 1;
    // 稍微给个5us延时
    i=2;while(--i);
    // 单总线初始化
    OneWire_DQ = 0;
    // 延时 至少480us
    i=247;while(--i);
    // 释放总线
    OneWire_DQ = 1;
    // 延时70us
    i=32;while(--i);
    // 稍做延时后，如果x=0则初始化成功，x=1则初始化失败
    AckBit = OneWire_DQ;
    i=247;while(--i);
    return AckBit;
}

/**
 * @brief 发送1位时序
 * 原本发送1和0是不同的时序，但是可以通过以下方式省略if判断
 * 
 * @param Bit 
 */
void OneWire_SendBit(unsigned char Bit)
{
    unsigned char i;
    OneWire_DQ = 0;
    // 10us
    i=4;while(--i);
    OneWire_DQ = Bit;
    // 50us
    i=24;while(--i);
    OneWire_DQ = 1;
}


/**
 * @brief 读一位
 * 
 * @return unsigned char 
 */
unsigned char OneWire_ReceiveBit(void)
{
    unsigned char i;
    unsigned char Bit;
    OneWire_DQ=0;
    // 5us
    i=2;while(--i);
    OneWire_DQ=1;
    // 5us
    i=2;while(--i);
    Bit = OneWire_DQ;
    // 50us
    i=24;while(--i);
    return Bit;
}


/**
 * @brief 发送一个字节
 * 
 * @param Byte 
 */
void OneWire_SendByte(unsigned char Byte)
{
    unsigned char i;
    for(i=0;i<8;i++){
        // 通过&,将Byte每一位逐个发送
        OneWire_SendBit(Byte&(0x01<<i));
    }
}

/**
 * @brief 接收一个字节
 * 
 */
unsigned char OneWire_ReceiveByte(void)
{
    unsigned char i;
    unsigned char Byte=0x00;
    for(i=0;i<8;i++){
        if(OneWire_ReceiveBit()){
            // 通过或运算，给字节Byte每一位进行赋值
            Byte |= 0x01<<i;
        }
    }
    return Byte;
}