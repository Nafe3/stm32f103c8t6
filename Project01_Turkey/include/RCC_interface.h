#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

//#include "BIT_MATH.h"
#include "STD_TYPES.h"

#define HSI_DIVIDED_BY_TWO_PLL          0x00000000
#define HSE_PLL                         0x00010000
#define HSE_DIVIDED_BY_TWO_PLL          0x00030000

#define PLLx2                           0x00000000
#define PLLx3                           0x00040000
#define PLLx4                           0x00080000
#define PLLx5                           0x000C0000
#define PLLx6                           0x00100000
#define PLLx7                           0x00140000
#define PLLx8                           0x00180000
#define PLLx9                           0x001C0000
#define PLLx10                          0x00200000
#define PLLx11                          0x00240000
#define PLLx12                          0x00280000
#define PLLx13                          0x002C0000
#define PLLx14                          0x00300000
#define PLLx15                          0x00340000
#define PLLx16                          0x00380000

#define MCO_SYSCLK_SELECTED             0x04000000
#define MCO_HSI_SELECTED                0x05000000
#define MCO_HSE_SELECTED                0x06000000
#define MCO_PLL_DIVIDED_BY_TWO_SELECTED 0x07000000

#define IOPA                            0x00000004
#define IOPB                            0x00000008
#define IOPC                            0x00000010
/******************  Bit definition for RCC_APB2ENR register  *****************/
#define  RCC_APB2ENR_USART1EN           ((u32)0x00004000)         /*!< USART1 clock enable */
/*****************  Bit definition for RCC_APB1ENR register  ******************/
#define  RCC_APB1ENR_USART2EN           0x00020000        /*!< USART 2 clock enable */
#define  RCC_APB1ENR_USART3EN           0x00040000        /*!< USART 3 clock enable */

#define HSI_SYSCLK                      0x00000000
#define HSE_SYSCLK                      0x00000001
#define PLL_SYSCLK                      0x00000002

extern ErrorStatus RCC_EnableHSI(void);
extern ErrorStatus RCC_DisableHSI(void);

extern ErrorStatus RCC_EnableHSE(void);
extern ErrorStatus RCC_DisableHSE(void);

extern ErrorStatus RCC_EnablePLL(u8 Copy_u8PLLClockSelected, u8 Copy_u8PLLMUL);
extern ErrorStatus RCC_DisablePLL(void);

extern ErrorStatus RCC_SelectSystemClock(u8 Copy_u8SelectSystemClock);

extern ErrorStatus RCC_MCOConfiguration(u8 Copy_u8MCOCLockSelected);

extern ErrorStatus RCC_EnableAHBPeripheral(u32 Copy_u8PeripheralName);
extern ErrorStatus RCC_DisableAHBPeripheral(u32 Copy_u8PeripheralName);

extern ErrorStatus RCC_EnableAPB2Peripheral(u32 Copy_u8PeripheralName);
extern ErrorStatus RCC_DisableAPB2Peripheral(u32);

extern ErrorStatus RCC_EnableAPB1Peripheral(u32 Copy_u8PeripheralName);
extern ErrorStatus RCC_DisableAPB1Peripheral(u32 Copy_u8PeripheralName);

extern ErrorStatus RCC_GetSysFreq(u32 *Copy_SysFreq);

#endif
