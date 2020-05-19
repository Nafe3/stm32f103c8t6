/****************************************************/
/* Author : Mirna Anis */
/* Date : 30 march 2020 */
/* Version : 1.0 */
/****************************************************/

#ifndef _DMA_REGISTER_H
#define _DMA_REGISTER_H

typedef struct{
  u32 CCR       ;
  u32 CNDTR     ;
  u32 CPAR      ;
  u32 CMAR      ;
  u32 Reserved  ;
}DMA_Channel;

typedef struct{
  u32 ISR                 ;
  u32 IFCR                ;
  DMA_Channel Channel[7]  ; 
}DMA_Type;

#define myDMA     ((volatile DMA_Type*)0x40020000)

#endif
