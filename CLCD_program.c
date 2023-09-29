/*
 * CLCD_program.c
 *
 *  Created on: 16 Aug 2023
 *      Author: ????
 */


#include"STD_TYPES.h"
#include"BIT_MATH.h"


#include<util/delay.h>
#include"DIO_interface.h"
#include"CLCD_config.h"
#include"CLCD_interface.h"
#include"CLCD_private.h"



void CLCD_voidSendData(u8 Copy_u8Data){
	//high to receive data
DIO_voidSetPinValue(CLCD_CTRLPORT,CLCD_RS_PIN ,DIO_u8HIGH);
    //low to write
DIO_voidSetPinValue(CLCD_CTRLPORT,CLCD_RW_PIN,DIO_u8LOW);
    //data received writing
DIO_VoidSetPortValue(CLCD_DATAPORT,Copy_u8Data);
    //enable
DIO_voidSetPinValue(CLCD_CTRLPORT,CLCD_EN_PIN,DIO_u8HIGH);
_delay_ms(2);
//disable
DIO_voidSetPinValue(CLCD_CTRLPORT,CLCD_EN_PIN,DIO_u8LOW);

}
void CLCD_voidSendCommand(u8 Copy_u8Command){
	//low to receive command
DIO_voidSetPinValue(CLCD_CTRLPORT,CLCD_RS_PIN ,DIO_u8LOW);
    //low to write
DIO_voidSetPinValue(CLCD_CTRLPORT,CLCD_RW_PIN,DIO_u8LOW);
    //data received writing
DIO_VoidSetPortValue(CLCD_DATAPORT,Copy_u8Command);
    //enable
DIO_voidSetPinValue(CLCD_CTRLPORT,CLCD_EN_PIN,DIO_u8HIGH);
_delay_ms(2);
//disable
DIO_voidSetPinValue(CLCD_CTRLPORT,CLCD_EN_PIN,DIO_u8LOW);

}
void CLCD_voidInit(void){
	_delay_ms(39);
	CLCD_voidSendCommand(0b00111000);
    CLCD_voidSendCommand(0b00001111);
    CLCD_voidSendCommand(0b00000001);
}


void CLCD_voidSendString(u8 * Copy_pu8String){
	u8 i=0;
	while(Copy_pu8String[i]!='\0'){
		CLCD_voidSendData(Copy_pu8String[i]);
		i=i+1;
	}
}
void CLCD_voidSetXYPosition(u8 Copy_u8XPosition,u8 Copy_u8YPosition)
{
	u8 Local_u8Address;
	if(Copy_u8YPosition==0){
		Local_u8Address=Copy_u8XPosition;
	}
	else{
		Local_u8Address=Copy_u8XPosition+0x40;
	}
	SET_BIT(Local_u8Address,7);
	CLCD_voidSendCommand(Local_u8Address);
}

void CLCD_voidClearDisplay(void){
	CLCD_voidSendCommand(0b00000001);
}

s32 CLCD_s32AdderPower(u8 Copy_u8Power){
	if(Copy_u8Power==0){
		return 1;
	}
	else{
		s32 result= 10* (CLCD_s32AdderPower(Copy_u8Power-1));
        return result;
	}
}
f32 CLCD_s32AdderNegativePower(u8 Copy_u8NegativePower){
		return(1.0/(CLCD_s32AdderPower(Copy_u8NegativePower)));
}
