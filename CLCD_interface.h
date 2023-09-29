/*
 * CLCD_interface.h
 *
 *  Created on: 16 Aug 2023
 *      Author: ????
 */

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

void CLCD_voidSendData(u8 Copy_u8Data);
void CLCD_voidSendCommand(u8 Copy_u8Command);
void CLCD_voidInit(void);

void CLCD_voidSendString(u8 * Copy_pu8String);
void CLCD_voidSetXYPosition(u8 Copy_u8XPosition,u8 Copy_u8YPosition);
void CLCD_voidClearDisplay(void);
s32 CLCD_s32AdderPower(u8 Copy_u8Power);
f32 CLCD_s32AdderNegativePower(u8 Copy_u8NegativePower);
#endif /* CLCD_INTERFACE_H_ */
