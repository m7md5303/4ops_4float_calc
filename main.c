/*
 * main.c
 *
 *  Created on: 27 Aug 2023
 *      Author: ????
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_register.h"
#include "DIO_private.h"
#include "DIO_interface.h"
#include "DIO_config.h"
#include "CLCD_private.h"
#include "CLCD_interface.h"
#include "CLCD_config.h"
#include "KPD_private.h"
#include "KPD_interface.h"
#include "KPD_config.h"
#include <util/delay.h>

int main(void){
DIO_VoidSetPortDirection(DIO_u8PORTD,0b00001111);
DIO_VoidSetPortValue(DIO_u8PORTD,0b11111111);
DIO_VoidSetPortDirection(DIO_u8PORTB,0b11111111);
DIO_VoidSetPortDirection(DIO_u8PORTA,0b11111111);

CLCD_voidInit();
u8 neg_flag=0,err_flag=0;
f32 sum=0,sum_tmp=0;
s32 int_sum=0,dec_sum=0,int_sum_tmp=0,dec_sum_tmp=0;
u8 i,digit_count,float_count,operation=0;
f32 operand=0;
u8 foperand=0;
u8 press=0;
u8 operandarr[16]={0},floatarr[16]={0};
u8 printed_data [16]={'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
u8 fprinted_data [4]={'0','0','0','0'};
u8 float_state=0;
    digit_count=0;
    float_count=0;
    for(u8 j =0;j<16;j++){
            	CLCD_voidSendData(printed_data[j]);
            }
    while(1){//choosing the operation
    while((operation!=13)&&(operation!=12)&&(operation!=14)&&(operation!=15)){
    	operation=KPD_u8GetPressedKey();
    }
    CLCD_voidClearDisplay();
    switch (operation) {
		case 15:
			CLCD_voidSendString("PLUS");
			break;
		case 14:
			CLCD_voidSendString("MINUS");
			break;
		case 13:
			CLCD_voidSendString("MULTIPLY");
			break;
		case 12:
		    CLCD_voidSendString("DIVIDE");
		    break;
	}
    _delay_ms(500);
    CLCD_voidClearDisplay();
    while(press!=11){//getting the operand from the user
    press=KPD_u8GetPressedKey();
    if(press==14&&(!(neg_flag))){
    	CLCD_voidSendData('-');
    	neg_flag=1;
    }
    if(press==10){//getting the float part
    	CLCD_voidSendData('.');
    	float_state++;
    }
    if(float_state==1){
    	  if((press!=11)&&(press>=0)&&(press<10)&&(press!=10)){
    	    floatarr[float_count]=press;
    	    CLCD_voidSendData(press+48);
    	    float_count++;}
    }

    else{    //getting the integer part

    if((press!=11)&&(press>=0)&&(press<10)&&(press!=12)){
    operandarr[digit_count]=press;
    CLCD_voidSendData(press+48);
    digit_count++;}}}
    u8 counter=0;//storing the integer part
    while(digit_count!=0){
    	operand=operand+(operandarr[counter]*CLCD_s32AdderPower(digit_count-1));
    	counter++;
    	digit_count--;
    }
    counter=0;

    while(float_count!=0){//storing the decimal part
        	operand=operand+(floatarr[counter]*CLCD_s32AdderNegativePower(counter+1));
        	counter++;
        	float_count--;

        }
    if((operand==0)&&(operation==12)){
    	CLCD_voidSendString("MATH ERROR");
    	err_flag=1;
    }

if(neg_flag){
	operand=operand*-1;
} if(!(err_flag)){
    //operating the operand
    switch (operation) {
		case 15:
		sum_tmp+=operand;
			break;
		case 14:
		sum_tmp-=operand;
		    break;
		case 13:
		sum_tmp*=operand;
		    break;
		case 12:
		sum_tmp/=operand;
		    break;
	}
}
    //giving the proper sign for the printed value
    if(sum_tmp>=0){
    	sum=sum_tmp;
    }
    else{
    	sum=(-1*sum_tmp);
    }
    //getting the integer part and the floating part each alone

    int_sum_tmp=sum;
    dec_sum_tmp=((sum-int_sum_tmp)*CLCD_s32AdderPower(4));
    int_sum=int_sum_tmp;
    dec_sum=dec_sum_tmp;





    //storing the printed data
    i=0;
    digit_count=0,float_count=0;
    while((int_sum/10)!=0){
    	printed_data[15-i]=((int_sum%10)+48);
    	int_sum=int_sum/10;
    	i++;
    	digit_count++;
    }
		printed_data[15-digit_count]=((int_sum%10)+48);


	i=0;
	while((dec_sum/10)!=0){
	    	fprinted_data[3-i]=((dec_sum%10)+48);
	    	dec_sum=dec_sum/10;
	    	i++;
	    	float_count++;
	    }
			fprinted_data[3-float_count]=((dec_sum%10)+48);

			 if((fprinted_data[3]=='0')&&(fprinted_data[2]=='0')&&(fprinted_data[1]=='0')&&(fprinted_data[0]=='0')){
						  			 				  fprinted_data[3]=' ';
						  			 				  fprinted_data[2]=' ';
						  			 				  fprinted_data[1]=' ';
						  			 				  fprinted_data[0]=' ';
						  			 			      foperand=3;
						  }

			 if((fprinted_data[3]=='0')&&(fprinted_data[2]=='0')&&(fprinted_data[1]=='0')){
						 				  fprinted_data[3]=' ';
						 				  fprinted_data[2]=' ';
						 				  fprinted_data[1]=' ';foperand=1;
						 			  }

			 if((fprinted_data[3]=='0')&&(fprinted_data[2]=='0')){
							  fprinted_data[3]=' ';
							  fprinted_data[2]=' ';foperand=1;
						  }

			 if(fprinted_data[3]=='0'){
			   fprinted_data[3]=' ';foperand=1;
			       	}





		CLCD_voidClearDisplay();
		if(sum_tmp<0){
			CLCD_voidSendData('-');
		}
    for(i=(15-digit_count);i<=15;i++){
        	CLCD_voidSendData(printed_data[i]);
        	printed_data[i]='0';
        }
   if(((foperand!=3)))
    CLCD_voidSendData('.');

    for(i=0;i<=3;i++){
    	if(fprinted_data[i]!=' ')
            	CLCD_voidSendData(fprinted_data[i]);
            	fprinted_data[i]='0';
            }


    press=0;
    operand=0;
    foperand=0;
    operation=0;
    digit_count=0;
    float_count=0;
    float_state=0;
    neg_flag=0;}




}

