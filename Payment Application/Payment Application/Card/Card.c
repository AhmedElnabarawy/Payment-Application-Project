#include"Card.h"
#include<stdio.h>
#include<string.h>

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("Please enter the card holder name [20-24 characters]: ");
    gets(cardData->cardHolderName);
	if ((strlen(cardData->cardHolderName) <= 24) && (strlen(cardData->cardHolderName) >= 20) && (strlen(cardData->cardHolderName) != 0))
	{return OK;}
	else{return WRONG_NAME;}
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("Please enter the card expiry date [MM/YY]: ");
	gets(cardData->cardExpirationDate);
	if ((strlen(cardData->cardExpirationDate) == 5) && cardData->cardExpirationDate[2] == '/')
	{return OK;}
	else{return WRONG_EXP_DATE;}

}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("Please enter the card PAN [16-19 characters]: ");
	gets(cardData->primaryAccountNumber);
	if ((strlen(cardData->primaryAccountNumber) <= 19) && (strlen(cardData->primaryAccountNumber) >= 16) && (strlen(cardData->primaryAccountNumber) != 0))
	{return OK;}
	else
	{return WRONG_PAN;}

}
