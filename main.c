#include <at89c5131.h>  // defines Sfr registers and BIT Registers for AT89C5131
#include "lcd.h"		//Header file with LCD interfacing functions
#include "serial.c"	//C file with UART interfacing functions

sbit LED=P1^7;  // 7 th bit named as led 
sbit LED2=P1^6;
sbit LED3=P1^5;
sbit LED4=P1^4;

//Main function
void main(void)
{
	int i = 0 ;
	int j = 0 ;
	
	int player_1_set = 0 ;   // won sets 
	char player_1_set_1_game = 0 ;   // won game in set
	char player_1_set_2_game = 0 ;   // won game in set
	char player_1_set_3_game = 0 ;   // won game in set
	
	

	int player_1_point = 0 ;
	
	
  int player_2_set = 0 ;   // won sets 
	char player_2_set_1_game = 0 ;   // won game in set
	char player_2_set_2_game = 0 ;   // won game in set
	char player_2_set_3_game = 0 ;   // won game in set
	
	int player_2_game = 0 ;  // dont use this looks confusing 
	int player_2_point = 0 ;
	
	
	unsigned char tie_break = 0;
	
	char dash = '-' ;
	char space = ' ' ;
	unsigned char ch=0;
	int marks[6]={0,15,30,40,50,60};     // 50 is Ad , 60 is win after Ad
	
	//Initialize port P1 for output from P1.7-P1.4
	P1 = 0x0F;
	
	//Call initialization functions
	lcd_init();
	uart_init();
	
	while(1)
	{         			
char adc_ip_data_ascii[3]={0,0,'\0'}   ; 

char adc_ip_data_ascii_1_digit[2]={0,'\0'}   ;

		
			//Receive a character
			ch = receive_char();
			switch(ch)
			{          case '1':   // updating score 
				
					
				if (tie_break == 0)
								{  
								if (j == 4) { j = j-1 ;        //  40 - Ad situation
                             player_2_point = marks[j]	;							}
						 else { i = i+1 ; 
									player_1_point = marks[i] ; }
											 
								}

								
			else 
								{  player_1_point = player_1_point + 1 ; }
								
								 break;
	
				
				case '2':       //  
					
  
				   if (tie_break == 0)
								{  
								if (i == 4) { i = i-1 ; 
								               player_1_point = marks[i]	;			}
								else { j = j+1 ; 
									player_2_point = marks[j] ; }
											 
								}

								
					else 
								{  player_2_point = player_2_point + 1 ; }
				
								 break;
				
			} 			// swith function ends 
				
	/*  DECISION MAKING   */  
			
			

			
 if (tie_break == 0) {
	 
	if ( ((player_1_point == 50) &&  (player_2_point < 40 ) )  || ((player_1_point == 60) &&  (player_2_point == 40 ) ) )
			{   
         if ( player_1_set + player_2_set == 0 ){
					 
					 player_1_set_1_game = player_1_set_1_game + 1 ;
				 
				                         }
				 
						else {
				 
				  if ( player_1_set + player_2_set == 1 ){
					 
					 player_1_set_2_game = player_1_set_2_game + 1 ;
				 
				                         }
					
					if ( player_1_set + player_2_set == 2 ){
					 
					 player_1_set_3_game = player_1_set_3_game + 1 ;      }
					
				                                         }
					
					// Since player 1 wins the game , we will reset the points 
							

							player_1_point = 0 ; 
					    i = 0 ;
              player_2_point = 0 ; 		
              j = 0 ; 					 
																 
        
					
					}	  // player 1 winning non tie break loop ends here 			

else {
			
			if ( ((player_2_point == 50) &&  (player_1_point < 40 ) ) || ((player_2_point == 60) &&  (player_1_point == 40 ) ) )

                                    			// player 2 winning a non tie breaker game loop 
			{   
         if ( player_1_set + player_2_set == 0 ){
					 
					 player_2_set_1_game = player_2_set_1_game + 1 ;     }
				 
    			
else {
					 
		if ( player_1_set + player_2_set == 1 ){
					 
					 player_2_set_2_game = player_2_set_2_game + 1 ;
				 
				                         }
		
							else {
		
					
					if ( player_1_set + player_2_set == 2 ){
					 
					 player_2_set_3_game = player_2_set_3_game + 1 ;
				 
				                         }
															 }  // second else ends
					
																 
															 }  // first else ends 
					
							// Since player 2 wins the game , we will reset the points 
							
             player_1_point = 0 ; 
					    i = 0 ;
              player_2_point = 0 ; 		
              j = 0 ; 	 																 
																 
															 }  // player 2 winning loop ends here 
																 

		     	}  // else loop ends here 	 			
            

    }			// tie break = 0 loop ends 
 
 if (tie_break == 1) {
	 
			if ( (   player_1_point > 6 ) &&  ( player_1_point - player_2_point > 1 )  ) 
				
			{   
         if ( player_1_set + player_2_set == 0 ){
					 
					 player_1_set_1_game = player_1_set_1_game + 1 ;
				 
				                         }
				 
		else {
				  if ( player_1_set + player_2_set == 1 ){
					 
					 player_1_set_2_game = player_1_set_2_game + 1 ;
				 
				                         }
					
					if ( player_1_set + player_2_set == 2 ){
					 
					 player_1_set_3_game = player_1_set_3_game + 1 ;
				 
				                         }
					
															     }  // else loop ends here
					
					tie_break = 0 ; 
					
					// Since player 1 wins the game , we will reset the points 
							

							player_1_point = 0 ; 
					    i = 0 ;
              player_2_point = 0 ; 		
              j = 0 ; 													 
																 
        															 
			}	  // player 1 winning tie break game loop ends here 			

			
			else {
			
			if ( (   player_2_point > 6 ) &&  ( player_2_point - player_1_point > 1 )  ) 

                                    			// player 2 winning a tie breaker game loop 
			{   
         if ( player_1_set + player_2_set == 0 ){
					 
					 player_2_set_1_game = player_2_set_1_game + 1 ;
				 
				                         }
				 
																 
				  if ( player_1_set + player_2_set == 1 ){
					 
					 player_2_set_2_game = player_2_set_2_game + 1 ;
				 
				                         }
					
					if ( player_1_set + player_2_set == 2 ){
					  player_2_set_3_game = player_2_set_3_game + 1 ;      }
					
							tie_break = 0 ; 
					
							// Since player 2 wins the game , we will reset the points 
							player_1_point = 0 ; 
					    i = 0 ;
              player_2_point = 0 ; 		
              j = 0 ; 																 
																 
        						 
																 

			}	  // player 2 winning a tie break game loop ends here 	

		}  // else loop ends here 
			
        }  // tie break = 1 loop ends 
  			
			
			// Add set winning loop here  , also loop to make tie break = 1 
      // Add the tie break  = 1 loop 
				
				
 if ( player_1_set + player_2_set == 0 ){  

	 // 
	if ( (	(	player_1_set_1_game == 6 ) &&  ( player_2_set_1_game < 5  ) )  ||  (	(	player_1_set_1_game == 7 ) && ( player_2_set_1_game == 5  ) )  ||   ((	player_1_set_1_game == 7 ) && ( player_2_set_1_game == 6  ) )  )
                   {     player_1_set = player_1_set + 1 ;   }  
									 
	            if (	(	player_1_set_1_game == 6 ) &&  ( player_2_set_1_game == 6  ) )
                   {    tie_break =  1 ;   } 
									 

									 
	          	if ( (	(	player_2_set_1_game == 6 ) &&  ( player_1_set_1_game < 5  ) ) ||  (	(	player_2_set_1_game == 7 ) && ( player_1_set_1_game == 5  ) )  ||  (	(	player_2_set_1_game == 7 ) &&  ( player_1_set_1_game == 6  ) ) )
                   {     player_2_set = player_2_set + 1 ;   }  


                               	}
 
						// add else 
else {
																																
	  if ( player_1_set + player_2_set == 1 ){             // 
	if ( (	(	player_1_set_2_game == 6 ) &&  ( player_2_set_2_game < 5  ) ) ||  (	(	player_1_set_2_game == 7 ) &&  ( player_2_set_2_game == 5  ) )  ||   (	(	player_1_set_2_game == 7 ) &&  ( player_2_set_2_game == 6  ) ) )
                   {     player_1_set = player_1_set + 1 ;   }  
									 
	            if (	(	player_1_set_2_game == 6 ) &&  ( player_2_set_2_game == 6  ) )
                   {    tie_break =  1 ;   } 

									 
	          	if ( (	(	player_2_set_2_game == 6 ) &&  ( player_1_set_2_game < 5  ) ) ||  (	(	player_2_set_2_game == 7 ) &&  ( player_1_set_2_game == 5  ) )  ||  (	(	player_2_set_2_game == 7 ) &&  ( player_1_set_2_game == 6  ) ) )
                   {     player_2_set = player_2_set + 1 ;   }  


                               	}
		
					else {											
																															
	 if ( player_1_set + player_2_set == 2 ){             //
	if ( (	(	player_1_set_3_game == 6 ) && ( player_2_set_3_game < 5  ) ) ||  (	(	player_1_set_3_game == 7 ) &&  ( player_2_set_3_game == 5  ) )  ||   (	(	player_1_set_3_game == 7 ) &&  ( player_2_set_3_game == 6  ) ) )
                   {     player_1_set = player_1_set + 1 ;   }  
									 
	            if (	(	player_1_set_3_game == 6 ) &&  ( player_2_set_3_game = 6  ) )
                   {    tie_break =  1 ;   } 
									 
	    	if ( (	(	player_2_set_3_game == 6 ) &&  ( player_1_set_3_game < 5  ) ) ||  (	(	player_2_set_3_game == 7 ) &&  ( player_1_set_3_game == 5  ) )  ||   (	(	player_2_set_3_game == 7 ) &&  ( player_1_set_3_game == 6  ) ) )
                   {     player_2_set = player_2_set + 1 ;   }  


                               	}
															}   // second else ends 
	 
															}  // first else ends
																
		
	


                               	
	
		
																 												 
     // add final winning loop here   // cut from below   // If we get a winner 
			
			if (player_1_set == 2 )           // p 1 wins 
			{ 
				    lcd_cmd(0x01);	
					msdelay(100) ;
				lcd_write_string("P1 wins"); 
				msdelay(5000) ;
				break ;           }
			
		else {		
					if (player_2_set == 2 )           // p 2 wins 
			{  lcd_cmd(0x01);	
				msdelay(100) ;
				lcd_write_string("P2 wins"); 
			  msdelay(5000) ;
				
		//		main() ; // code size exceeds 
				
				break ;   }
		     }  // else loop ends here 
			
			// updating lcd display  
			
			
			  lcd_cmd(0x01);	   // UPDATING FIRST LINE 	 
			  lcd_cmd(0x80);		
	      msdelay(100) ;			//Move cursor to first line
			 
			 
		    int_to_string_1_digit(player_1_set_1_game,  adc_ip_data_ascii_1_digit) ; 
				lcd_write_string(adc_ip_data_ascii_1_digit); 	
       lcd_write_string("-");
         msdelay(100) ;				 
				int_to_string_1_digit(player_2_set_1_game,  adc_ip_data_ascii_1_digit) ; //   ? ? 
				lcd_write_string(adc_ip_data_ascii_1_digit);  
				 
				if (player_1_set + player_2_set > 0  ){
				 
				 lcd_write_string(" ");
				
				
		    int_to_string_1_digit(player_1_set_2_game,  adc_ip_data_ascii_1_digit) ; 
				lcd_write_string(adc_ip_data_ascii_1_digit); 	
       lcd_write_string("-"); 	
        msdelay(100) ;		
				
				int_to_string_1_digit(player_2_set_2_game,  adc_ip_data_ascii_1_digit) ; 
				lcd_write_string(adc_ip_data_ascii_1_digit);  
				 
				
				
				if (player_1_set + player_2_set == 2 ){
				
				 lcd_write_string(" ");
				 
				 
		    int_to_string_1_digit(player_1_set_3_game,  adc_ip_data_ascii_1_digit) ; 
				lcd_write_string(adc_ip_data_ascii_1_digit); 	
       lcd_write_string("-"); 		
			 
			 
        msdelay(100) ;			 
				int_to_string_1_digit(player_2_set_3_game,  adc_ip_data_ascii_1_digit) ; 
				lcd_write_string(adc_ip_data_ascii_1_digit); 
				 
				}
			}
				
			
			
			
		// second line of lcd 	
			 lcd_cmd(0xc0);	          // updating second line 
        	msdelay(100) ;                        // it can be 0 , 15 , 30 , 40 ,Ad 
				                        // or 0-99
				
			if (player_1_point == 50){  
				 lcd_write_string("Ad"); }
			else {
				 int_to_string(player_1_point,  adc_ip_data_ascii) ; 
				lcd_write_string(adc_ip_data_ascii);                }
			
			 lcd_write_string("-");  
			
				if (player_2_point == 50){  
				 lcd_write_string("Ad"); }
			else {
				 int_to_string(player_2_point,  adc_ip_data_ascii) ; 
				lcd_write_string(adc_ip_data_ascii);                }
			
			
				
				}       // while(1) loop ends here  
	           }

	
