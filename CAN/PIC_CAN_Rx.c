//CAN receiver Code
//PIC MCU is used

#include<xc.h>
void delay(int a)
{
int i,j;
for(i=0;i<a;i++)
{for(j=0;j<500;j++);}
}

void main()
{

char a;
TXSTA=0x24;
RCSTA=0x90;
SPBRG=129;
TRISB=0x08;
TRISC=0x80;
LATB3=0;
while(TXIF==0);
TXREG='R';
TXIF=0;
CANCONbits.REQOP2=1;
while(CANSTATbits.OPMODE2==0);
CANCONbits.ABAT=1;
MDSEL1=0;
MDSEL0=0;
BRGCON1=0x04;

BRGCON2=0xa4;
BRGCON3=0x04;
ENDRHI=1;
CANCONbits.REQOP2=0;
while(CANSTATbits.OPMODE2==1);


while(1)
{
RXB0CON=0x60;
while((RXB0CON&0x80) ==0x00);
TXIF=0;
while(TXIF==0);
TXREG=RXB0D0;

TXIF=0;
while(TXIF==0);
TXREG='\n';
//delay(20);


}
}
