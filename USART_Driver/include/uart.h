/*
 * uart.h
 *
 *  Created on: Mar 21, 2020
 *      Author: atourkey
 */

#ifndef UART_H_
#define UART_H_


typedef void (* txCbf_t)(void);
typedef void (* rxCbf_t)(void);

extern void uart_init(void);
extern void uart_send(uint8_t * buffer, uint16_t len);
extern void uart_receive(uint8_t * buffer, uint16_t len);
extern void uart_configure(uint32_t baudRate, uint8_t stopBits, uint8_t parity, uint8_t flowControl);
extern void uart_setTxCbf (txCbf_t txCbf);
extern void uart_setRxCbf(rxCbf_t rxCbf);


#endif /* UART_H_ */
