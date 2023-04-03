/*
 ******************************************************************************************
 * @file      multiple.h
 * @author    GowinSemiconductor
 * @device    Gowin_EMPU(GW1NS-4C)
 * @brief     Multiple driver.
 ******************************************************************************************
 */

#ifndef MULTIPLE_H
#define MULTIPLE_H

/* Includes ------------------------------------------------------------------*/
#include "gw1ns4c.h"

/* Definitions ------------------------------------------------------------------*/
//type definition
typedef struct
{
  __IO   uint32_t  MULTIPLIER;        /* Offset: 0x000 (R/W) [7:0] */
  __IO   uint32_t  MULTIPLICAND;      /* Offset: 0x004 (R/W) [7:0] */
  __IO   uint32_t  CMD;               /* Offset: 0x008 (R/W) [1:0] */
  __I    uint32_t  RESULT;            /* Offset: 0x00C (R/ ) [15:0] */
}MULTIPLE_TypeDef;

//base address
#define MULTIPLE_BASE   (AHB2PERIPH_BASE + 0x0000)

//mapping
#define MULTIPLE        ((MULTIPLE_TypeDef   *) MULTIPLE_BASE)

//bit definition
#define MUL_MULTIPLIER		((uint32_t) 0x000000FF)
#define MUL_MULTIPLICAND	((uint32_t) 0x000000FF)
#define CMD_START					((uint32_t) 0x00000001)
#define STATUS_FINISHED		((uint32_t) 0x00000010)
#define MUL_RESULT				((uint32_t) 0x0000FFFF)

typedef enum
{
	FINISHED_STATUS = 0x0,
	NO_FINISHED_STATUS = 0x1
}STATUS;

/* Declarations ------------------------------------------------------------------*/
void setMultiplier(uint32_t multi);
uint32_t getMultiplier(void);
void setMultiplicand(uint32_t multi);
uint32_t getMultiplicand(void);
uint32_t getMultipleResult(void);
void startMultiple(void);
void finishMultiple(void);
STATUS getFinishStatus(void);
uint32_t getMultipleCmd(void);

#endif
