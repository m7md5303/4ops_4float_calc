/*
 * KPD_program.c

 *
 *  Created on: 21 Aug 2023
 *      Author: ????
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"


#include"DIO_interface.h"
#include"CLCD_interface.h"


#include <util/delay.h>

#include"KPD_config.h"
#include"KPD_private.h"
#include"KPD_interface.h"

u8 KPD_u8GetPressedKey(void){

u8 arr[4][4]={{1,2,3,4},
		      {5,6,7,8},
			  {9,10,11,12},
			  {13,14,15,16}};
	u8 Local_u8Key=23;
	for(u8 col=0;col<4;col++){
		DIO_voidSetPinValue(KPD_PORT,col,DIO_u8LOW);
		for(u8 row=0;row<4;row++){
			if((DIO_u8GetPinValue(KPD_PORT,row+4)==DIO_u8LOW)){
				Local_u8Key=arr[row][col];
				_delay_ms(2);
				while(DIO_u8GetPinValue(KPD_PORT,row+4)==DIO_u8LOW){

				}
			}
		}
		DIO_voidSetPinValue(KPD_PORT,col,DIO_u8HIGH);
	}
return Local_u8Key-1;

}

