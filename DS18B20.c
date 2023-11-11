#include <REGX52.H>
#include "OneWire.h"

// 跳过ROM指令
#define DS18B20_SKIP_ROM            0xcc
// 温度变换的功能指令
#define DS18B20_CONVERT_T           0x44
// 读暂存区
#define DS18B20_READ_SCRATCHPAD     0xBE


/**
 * @brief 启动Ds18b20启动转换温度
 * 
 * 起始信号、跳过ROM指令、温度变换指令
 */
void DS18B20_ConvertT(void)
{
    OneWire_Init();
    OneWire_SendByte(DS18B20_SKIP_ROM);
    OneWire_SendByte(DS18B20_CONVERT_T);
}

/**
 * @brief 温度读取
 * 
 * @return float 
 */
float DS18B20_ReadT(void)
{
    float T;
    int Temp;
    unsigned char TLSB, TMSB;
    OneWire_Init();
    OneWire_SendByte(DS18B20_SKIP_ROM);
    OneWire_SendByte(DS18B20_READ_SCRATCHPAD);
    // 低8位
    TLSB = OneWire_ReceiveByte();
    // 高8位
    TMSB = OneWire_ReceiveByte();
    // 在C语言中，两个char类型的变量相加会将它们转换为整数，然后进行加法运算。
    // 这个过程称为类型提升（type promotion）
    // 虽然 TMSB/TLSB原先都是8位数
    // 但是，两个char在做运算之前，就被默认转换传成 int（16位）
    // 高位字节左移8位和低位字节或，拼接成一个完整的温度(16位)
    Temp = (TMSB<<8)|TLSB;
    // 低位字节中有4位是小数，所以要展示小数，
    // 那么假设这个数字原本是2332.4456，但是展示的时候数字左移了4位，没有了小数点
    // 左移一位相当于 *2，左移4位相当于 *16   (2^n)
    // 所以，要还原原来的小数，就是要除以对应的值，浮点数计算，要加上.0
    T = Temp / 16.0;
    return T;
}