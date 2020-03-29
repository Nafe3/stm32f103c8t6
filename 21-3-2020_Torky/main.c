

uint8_t txBuffer[1024] ;
uint8_t rxBuffer[1024] ;

int
main(int argc, char* argv[])
{
	uint8_t retries ;

//	----> intr rx byte uart

	uart_setTxCbf(uartTxDone);

//	----> intr rx byte uart

	res = uart_send(txBuffer, 1) ; // res = OK
//	----> intr rx byte uart
	res = uart_receive(rxBuffer, 10) ; // res = busy !!
//	----> intr rx byte uart OKKKKK

	lcd_write()


  while (1)
    {

    }
}

//2000 ms
void app_task(void)
{
	uart_send(txBuffer, 1024);
}

void uartTxDone(void)
{
	res = uart_send(txBuffer, 1024) ; // res = OK

}
