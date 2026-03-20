#include <xc.h>
#define _XTAL_FREQ 20000000  
#define baud_rate  9600
void string(char *s);
void mychar(char d);
void SPI_Slave_Init(void);
void uart_initiate(void);
unsigned char receivedData,transmitData;

int i;
void main(void)
{
    TRISD=0x00;
    SPI_Slave_Init();
    uart_initiate();
  
    while(1)
    {
            transmitData = '0'+i++;
            SSPIF = 0;
            SSPBUF = transmitData;
            while(!SSPIF);   
            RD0=1;
            receivedData = SSPBUF; 
     
            string("received character:");
            mychar(receivedData);
            string("\r\n");
            __delay_ms(1000);
            RD0=0;
            
          
                
    }
  }

void SPI_Slave_Init(void)
{
    TRISC = 0x98;

    SSPSTAT = 0x00;    
    SSPCON1 = 0x24;    
    PIR1bits.SSPIF = 0;
}
void uart_initiate(){
  TXSTA = 0X24;
  RCSTA = 0X90;
  SPBRG = (((_XTAL_FREQ/baud_rate)/16)-1);
}

void string(char *s){
    while(*s){
        TXREG = *s++;
        while(!PIR1bits.TXIF);
        PIR1bits.TXIF = 0;
    }
}
void mychar(char d){
    TXREG = d;
    while(!PIR1bits.TXIF);
    PIR1bits.TXIF = 0;
}
