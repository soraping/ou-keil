void Delay1MS()
{
    unsigned char i, j;
 
    i = 2;
    j = 239;
    do
    {
        while (--j);
    } while (--i);
}

void DelayXMS(unsigned char x)
{
    while (x--)
    {
        Delay1MS();
    }
}

void DelayXUs(unsigned char x)
{
    while(--x);
}