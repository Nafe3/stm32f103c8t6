/*
 *
 *
 *
 *
 * id: 0x01 --> Set counter value
 *
 * data{
 * D0:D3 -> counter
 * D4:D7 -> res
 * }
 *
 * id: 0x02 ->
 *
 * data{
 * D0: sw00 status
 * D1: sw01 status
 * D2: sw02 status
 * D3: sw03 status
 *
 * D4:D7->reserved
 * }
 *
 * */
typedef enum{

}frameID_t;



typedef struct{
	u8 	sf;
	u8 	id;
	u16 len;
}tProtocolHeader_t;

typedef struct{
	tProtocolHeader_t 	header;
	u8					data[8];
	u8					ef;
}tProtocol_t;

typedef struct{
	u8  swStatus[4];
	u32 res;
}switchStatus;

typedef struct{
	tProtocolHeader_t ;

};


static u8 txRawDataBuffer[100];
static u8 rxRawDataBuffer[100];

int main (void)
{
	tProtocol_t* frame = (tProtocol_t*) txRawDataBuffer;

	frame->header.sf = 0x55;
	//frame->header.id = 0x01;
	frame->header.id = id_setCounterValue;
	frame->header.len= 200;

	frame->data[0] = 0xFF;
	frame->ef      = 0xC0;

	uart_recv(rxRawDataBuffer);
	uart_sendBuffer(txRawDataBuffer, sizeof(tProtocol_t));
}
