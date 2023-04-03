/*
 ******************************************************************************************
 * @file      multiple.c
 * @author    GowinSemiconductor
 * @device    Gowin_EMPU(GW1NS-4C)
 * @brief     Multiple driver.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "multiple.h"

/* Functions ------------------------------------------------------------------*/
void setMultiplier(uint32_t multi)
{
	MULTIPLE->MULTIPLIER = multi & MUL_MULTIPLIER;
}

uint32_t getMultiplier(void)
{
	return MULTIPLE->MULTIPLIER & MUL_MULTIPLIER;
}

void setMultiplicand(uint32_t multi)
{
	MULTIPLE->MULTIPLICAND = multi & MUL_MULTIPLICAND;
}

uint32_t getMultiplicand(void)
{
	return MULTIPLE->MULTIPLICAND & MUL_MULTIPLICAND;
}

uint32_t getMultipleResult(void)
{
	return MULTIPLE->RESULT & MUL_RESULT;
}

void startMultiple(void)
{
	MULTIPLE->CMD |= CMD_START;
}

void finishMultiple(void)
{
	MULTIPLE->CMD = 0;
}

uint32_t getMultipleCmd(void)
{
	return MULTIPLE->CMD;
}

STATUS getFinishStatus(void)
{
	if(((MULTIPLE->CMD&STATUS_FINISHED)>>1))
	{
		return FINISHED_STATUS;
	}
	else
	{
		return NO_FINISHED_STATUS;
	}
}
