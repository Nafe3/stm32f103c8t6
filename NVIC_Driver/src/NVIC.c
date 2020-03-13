//Registers addresses
#include "NVIC.h"

#define NVIC_BASE_ADDRESS 		0xE000E100
#define NVIC_PTR				(void*)NVIC_BASE_ADDRESS

#define  SCB_BASE_ADDRESS       0xE000E008
#define  SCB_AIRCR              *((volatile u32*)(SCB_BASE_ADDRESS+0x0C))
#define SCB_AIRCR_VECTKEY		0x05FA0000	/*SCB_AIRCR Password*/


/*Used to enable writing to STIR*/
#define NVIC_CCR				0xE000ED14
#define USERSETMPEND            0x2


typedef struct
{
  volatile u32 ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
           u32 RESERVED0[24U];
  volatile u32 ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
           u32 RSERVED1[24U];
  volatile u32 ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
           u32 RESERVED2[24U];
  volatile u32 ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
           u32 RESERVED3[24U];
  volatile u32 IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
           u32 RESERVED4[56U];
  volatile u8  IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
  	  	   u32 RESERVED5[644U];
  volatile u32 STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}NVIC_Type;



///////////////////////////////////////////////////////
STD_ERR u8EnableEXTI(u8 inum)
{
	STD_ERR err_status = STD_TYPES_ERROR_OK;
	NVIC_Type* ptr = (NVIC_Type*)NVIC_PTR;
	if(inum > 240)
	{
		err_status = STD_TYPES_ERROR_NOK;
	}
	else
	{
		ptr->ISER[inum>>5U]=( 1 << (inum & 0b11111) );
	}
	return err_status;
}


/////////////////////////////////////////////////////////
STD_ERR u8DisableEXTI(u8 inum)
{
		STD_ERR err_status = STD_TYPES_ERROR_OK;
		NVIC_Type* ptr = (NVIC_Type*)NVIC_PTR;
		if(inum > 240)
		{
			err_status = STD_TYPES_ERROR_NOK;
		}
		else
		{
			ptr->ICER[inum>>5U]=( 1 << (inum & 0b11111) );
		}
		return err_status;
}

////////////////////////////////////////////////////////////
STD_ERR u8SetPendFlag(u8 inum)
{
		STD_ERR err_status = STD_TYPES_ERROR_OK;
		NVIC_Type* ptr = (NVIC_Type*)NVIC_PTR;
		if(inum > 240)
		{
			err_status = STD_TYPES_ERROR_NOK;
		}
		else
		{
			ptr->ISPR[inum>>5U]=( 1 << (inum & 0b11111) );
		}
		return err_status;
}

////////////////////////////////////////////////////////////
STD_ERR u8ClrPendFlag(u8 inum)
{
		STD_ERR err_status = STD_TYPES_ERROR_OK;
		NVIC_Type* ptr = (NVIC_Type*)NVIC_PTR;
		if(inum > 240)
		{
			err_status = STD_TYPES_ERROR_NOK;
		}
		else
		{
			ptr->ICPR[inum>>5U]=( 1 << (inum & 0b11111) );
		}
		return err_status;
}

//////////////////////////////////////////////////////////////
STD_ERR u8IsActive(u8 inum,u8* state)
{
		STD_ERR err_status = STD_TYPES_ERROR_OK;
		NVIC_Type* ptr = (NVIC_Type*)NVIC_PTR;
		if(inum > 240)
		{
			err_status = STD_TYPES_ERROR_NOK;
		}
		else
		{
			//       go to the required register
			//       right shift it with the value of the require bit position
			//		 ANDing it with one to get the state
			*state = ((ptr->IABR[inum>>5U] >> (1U << inum & 0b11111 ) )&1U);
		}
		return err_status;
}

//////////////////////////////////////////////////////////////////
STD_ERR u8SetPriority		()
{
	STD_ERR err_status = STD_TYPES_ERROR_OK;
	NVIC_Type* ptr = (NVIC_Type*)NVIC_PTR;



	return err_status;
}

///////////////////////////////////////////////////////////////////
STD_ERR u8GetPriority		()
{
	STD_ERR err_status = STD_TYPES_ERROR_OK;
	NVIC_Type* ptr = (NVIC_Type*)NVIC_PTR;


	return err_status;
}

///////////////////////////////////////////////////////////////////
STD_ERR u8SetGrpBits 		(u8 PRIGROUP_MASK)
{
	STD_ERR err_status = STD_TYPES_ERROR_OK;
	NVIC_Type* ptr = (NVIC_Type*)NVIC_PTR;


	return err_status;
}

///////////////////////////////////////////////////////////////////
STD_ERR u8EnableAllEXTI		(void)
{
	STD_ERR err_status = STD_TYPES_ERROR_OK;
	NVIC_Type* ptr = (NVIC_Type*)NVIC_PTR;


	return err_status;
}

///////////////////////////////////////////////////////////////////
STD_ERR u8DisableAllEXTI 	(void)
{
	STD_ERR err_status = STD_TYPES_ERROR_OK;
	NVIC_Type* ptr = (NVIC_Type*)NVIC_PTR;


	return err_status;
}

///////////////////////////////////////////////////////////////////
STD_ERR u8EnableAllFaults	(void)
{
	STD_ERR err_status = STD_TYPES_ERROR_OK;
	NVIC_Type* ptr = (NVIC_Type*)NVIC_PTR;


	return err_status;
}

///////////////////////////////////////////////////////////////////
STD_ERR u8DisableAllFaults	(void)
{
	STD_ERR err_status = STD_TYPES_ERROR_OK;
	NVIC_Type* ptr = (NVIC_Type*)NVIC_PTR;


	return err_status;
}

///////////////////////////////////////////////////////////////////
STD_ERR u8DisableEXTI_From	()
{
	STD_ERR err_status = STD_TYPES_ERROR_OK;
	NVIC_Type* ptr = (NVIC_Type*)NVIC_PTR;


	return err_status;
}

///////////////////////////////////////////////////////////////////
STD_ERR u8GenerateSWI		(u8 inum)
{
	STD_ERR err_status = STD_TYPES_ERROR_OK;
	NVIC_Type* ptr = (NVIC_Type*)NVIC_PTR;


	return err_status;
}
