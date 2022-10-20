#include"Terminal.h"
#include"../Card/Card.h"
#include<stdio.h>
#include<string.h>
#include <stdlib.h>

float Max_Amount;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	printf("Please enter the Transaction Date [DD/MM/YY]: ");
	gets(termData->transactionDate);
	if ((strlen(termData->transactionDate) == 10) && termData->transactionDate[2] == '/' && termData->transactionDate[5] == '/')
	{return ok;}
	else
	{return WRONG_DATE;}
}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	char y1[2] = { cardData.cardExpirationDate[3],cardData.cardExpirationDate[4] };
	char y2[2] = { termData.transactionDate[8],termData.transactionDate[9] };
	char M1[2] = { cardData.cardExpirationDate[0],cardData.cardExpirationDate[1] };
	char M2[2] = { termData.transactionDate[3],termData.transactionDate[4] };
	int y_c = atoi(y1);
	int y_t = atoi(y2);
	int M_c = atoi(M1);
	int M_t = atoi(M2);
	if (y_c > y_t)
	{
		return ok;
	}
	else if(y_c < y_t)
	{
		return EXPIRED_CARD;
	}
	else if (y_c > y_t && M_c > M_t)
	{
		return ok;
	}
	
}
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{

}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("Please enter the Transaction Amount : ");
	scanf_s("%f", &termData->transAmount);
	if (termData->transAmount <= 0)
	{return INVALID_AMOUNT;}
	else
	{return ok;}
	
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	printf("Please enter the Max transaction Amount : ");
	scanf_s("%f", &termData->maxTransAmount);
	Max_Amount = termData->maxTransAmount;
	if (termData->maxTransAmount <= 0)
	{return INVALID_MAX_AMOUNT;}
	else
	{return ok;}
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > Max_Amount)
	{return EXCEED_MAX_AMOUNT;}
	else
	{return ok;}
}

