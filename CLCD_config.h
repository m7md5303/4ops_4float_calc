/*
 * CLCD_config.h
 *
 *  Created on: 16 Aug 2023
 *      Author: ????
 */

#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_
/*Options:
 *        1)DIO_u8PORTA
 *        2)DIO_u8PORTB
 *        3)DIO_u8PORTC
 *        4)DIO_u8PORTD
 **/
#define CLCD_DATAPORT       DIO_u8PORTB
#define CLCD_CTRLPORT       DIO_u8PORTA

#define CLCD_RS_PIN             0
#define CLCD_RW_PIN             1
#define CLCD_EN_PIN             2
#endif /* CLCD_CONFIG_H_ */
