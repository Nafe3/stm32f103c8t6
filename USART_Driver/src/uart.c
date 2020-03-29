/*
 * uart.c
 *
 *  Created on: Mar 21, 2020
 *      Author: atourkey
 */


typedef struct {

	uint32_t DR;
	uint32_t SR;
	uint32_t ICR;

}uartPeri_t;

static uartPeri_t * uart = 0x000000 ;

typedef enum{
	idle ,
	busy
}bufferState_t;

typedef struct{
	uin8_t * ptr;
	uint32_t position;
	uint32_t size;
	bufferState_t state;
}dataBuffer_t;

static dataBuffer_t txBuffer;
static dataBuffer_t rxBuffer;


typedef void (*appTxNotify_t) (void);
typedef void (*appRxNotify_t) (void);

static appTxNotify_t appTxNotify ;
static appRxNotify_t appRxNotify ;

extern void uart_init(void)
{
	// GPIO configure pins ---> could be move to UART HAL
	// setup default configurations
	// setup interrupts ---> clear pending , enable interrupt

	return error;
}

// 10ms
void USART1_IRQHandler(void)
{
	if(TXE){
		//clear TXE

		if(txBuffer.size != txBuffer.position){
			uart->DR = txBuffer.ptr[txBuffer.position];
			txBuffer.position++;
		} else {
			// transmission Done
			txBuffer.ptr = NULL ;
			txBuffer.size = 0 ;
			txBuffer.position = 0;
			txBuffer.state = idle ;
			appTxNotify();
		}
	}

	if(RXNE){
		// clear RXNE
		if(rxBuffer.state == busy){

			rxBuffer.ptr[rxBuffer.position] = uart->DR ;
			rxBuffer.position++;

			if(rxBuffer.position == rxBuffer.size){

				rxBuffer.ptr = NULL ;
				rxBuffer.size = 0 ;
				rxBuffer.position = 0 ;
				rxBuffer.state = idle ;
				appRxNotify();
			}

		} else {
			return ;
		}
	}
}

extern uint8_t uart_send(uint8_t * buffer, uint16_t bytesCount)
{
	uint8_t res ;
	if(buffer && (bytesCount > 0) ){
		if(txBuffer.state == idle){
			txBuffer.state = busy ;
			txBuffer.ptr = buffer ;
			txBuffer.position = 0 ;
			txBuffer.size = bytesCount ;

			uart->DR = txBuffer.ptr[txBuffer.position];
			txBuffer.position++;

			res = STAT_OK;
		}else {
			res = STAT_BUSY;
		}
	}else {
		res = STAT_ERROR;
	}

	return res;
}

extern void uart_receive(uint8_t * buffer, uint16_t len)
{
	if(rxBuffer.state == idle){
		rxBuffer.ptr = buffer ;
		rxBuffer.size = len;
		rxBuffer.position = 0;
		rxBuffer.state = busy;
		res = STAT_OK ;
	} else {
		res = STAT_BUSY ;
	}
}

typedef struct{
	uint32_t baudrate;
	uint32_t stopBits;
	uint8_t flowControl;
}strUartCFg_t ;

extern void uart_configure( strUartCFg_t * cfg )
{

}

extern void uart_configure(uint32_t baudRate, uint8_t stopBits, uint32_t flowControl)
{

}

extern void uart_setTxCbf (appTxNotify_t txCbf)
{
	if(txCbf){
		appTxNotify = txCbf;
	}
}
extern void uart_setRxCbf(appRxNotify_t rxCbf)
{
	if(rxCbf){
		appRxNotify = rxCbf;
	}
}

