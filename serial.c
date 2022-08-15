#include <at89c5131.h>

bit tx_complete = 0,rx_complete = 0;    //Bit flags for interrupts  // compliment of ti and ri 

/**********************************************************
   uart_init(): 
	Initialization function to be completed
	Initializes UART peripheral for 8-bit transfer, 
	1 start and 1 stop bits. 
	
	Please write TH1 value for required baud rate
***********************************************************/	

                    // timer automatically re-loaded from TH when it overflows
										// 256 -  24 M / (384 * baud rate)  , cc = 204 
										// without the parity bit, clear SM0 , set SM1. , set REN to enable data reception
void uart_init(void)
{
	  TMOD = (TMOD | 0x20 ) & 0x2F  ;//TMOD=0x__;			//Configure Timer 1 in Mode 2 // xdon't affect T0
	  TH1 = 0xCC  ;          //TH1=__;	// 	51 			//Load TH1 to obtain require Baudrate (Refer Serial.pdf for calculations)
	  SCON = 0x50  ;       //SCON=0x__;	  		//Configure UART peripheral for 8-bit data transfer 
	  TR1 = 1      ;  //								//Start Timer 1
		ES = 1					;			//Enable Serial Interrupt
		EA = 1						;		//Enable Global Interrupt
	
	                     
}


/**********************************************************
   transmit_char(<unsigned char ch>): 
	Transmits a character using UART
***********************************************************/
/*
void transmit_char(unsigned char ch)
{
	SBUF=ch;				//Load data in SBUF
	while(!tx_complete); 			//Wait for tx_complete flag (interrupt to complete)
	tx_complete = 0;		//Clear tx_complete flag 
}
*/

/**********************************************************
   transmit_string(<String pointer>): 
	Transmit a string using UART
***********************************************************/	
/*
void transmit_string(unsigned char *s)
{
	while(*s != 0)
	{
			transmit_char(*s++);
	}
}
*/

/**********************************************************
   receive_char(): 
	Receives a character through UART. Returns a 
	character.
***********************************************************/		
unsigned char receive_char(void)
{
	unsigned char ch = 0;
	while(!rx_complete);				//Wait for rx_complete(interrupt to complete)
	rx_complete = 0;       // sets the flag RI. This is an invitation to the processor to read Sbuf
	ch = SBUF;					//Read data from SBUF
	return ch;					//Return read character
}

/*
When a complete frame has been shifted in,
the data is transferred to the receive sbuf
register and a flag (RI) is set to inform the
processor that serial data is available for
reading at Sbuf.
*/



/**********************************************************
   Serial_ISR(): 
	Interrupt service routine for UART interrupt.
	Determines whether it is a transmit or receive
	interrupt and raise corresponding flag.
	Transmit or receive functions (defined above) monitor
	for these flags to check if data transfer is done.
***********************************************************/	
void serial_ISR(void) interrupt 4    // 4	SERIAL PORT     ; 5 internal interr total 
{
		if(TI==1)			//check whether TI is set  TI is set, inviting the program to write fresh data to Sbuf
		{
			TI = 0;			//Clear TI flag
			tx_complete = 1;	//Set tx_complete flag indicating interrupt completion  
		}
		else if(RI==1)			//check whether RI is set
		{
			RI = 0;			//Clear RI flag RI is set to inform the processor that serial data is available for reading at Sbuf.
			rx_complete = 1;	//Set rx_complete flag indicating interrupt completion
		}
}
