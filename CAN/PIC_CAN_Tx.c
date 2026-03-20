//CAN Communication using PIC MCU 


#include<xc.h>

void delay(int  a)
{
    int i,j;
    for(i=0;i<a;i++)
    {for(j=0;j<500;j++);}
}
void txd(char a)
{
    while(TXIF==0);
    TXREG=a;
    TXIF=0;

}
void cantx(char a)
{

    TXB0SIDH=0;
    TXB0SIDL=0xE0;        //ID=7
    TXB0DLC=0x02;
    TXB0D0=a;
    TXB0CON=0x08;
    txd('r');
    txd(' ');
    while((TXB0CON&0x08)==0x08);
    txd('n');
    txd(' ');
}

void main()
{
    TXSTA=0x24;
    RCSTA=0x90;
    SPBRG=129;
    TRISB=0x08;
    TRISC=0x80;
    LATB3=0;
    
    CANCONbits.REQOP2=1;             //Configuration mode
    while(CANSTATbits.OPMODE2==0);
    CANCONbits.ABAT=1;                //to clear(abort) pending transmission
    
    MDSEL1=0;
    MDSEL0=0;

    BRGCON1=0x04;
    BRGCON2=0xa4;
    BRGCON3=0x04;

    LATB3=0;

    ENDRHI=1;
    CANCONbits.REQOP2=0;                //Normal mode
    while(CANSTATbits.OPMODE2==1);

    while(1){
        while(RCIF==0);
    
        txd('I');
        txd(' ');
        cantx(RCREG);
        
        delay(100);
        RCIF=0;    
    }
}
