#include"../Card/Card.h"
#include"../Terminal/Terminal.h"
#include"../Server/Server.h"
#include"App.h"
#include<stdio.h>
#include <string.h>

ST_cardData_t C_user;
ST_terminalData_t T_user;
ST_transaction_t transData;


void app()
{

	uint8_t C_var;//Card Data
	uint8_t T_var;//Terminal Data
	float T_var_f = 0;
	uint8_t T_state;
	bool Max;
	bool EXP;


		//Check card holder name
	C_var = getCardHolderName(&C_user);
		if (C_var == 0)
		{printf("\t<<<Name is OK>>> \n");}
		else if (C_var == 1)
		{printf("\t<<<Name is WRONG_NAME>>> \n");}
		//Check card expiry date
	C_var = getCardExpiryDate(&C_user);
		if (C_var == 0)
		{printf("\t<<<ExpiryDate is OK>>> \n");}
		else if (C_var == 2)
		{printf("\t<<<ExpiryDate is WRONG_DATE>>> \n");}
		//Check card PAN
	C_var = getCardPAN(&C_user);
		if (C_var == 0)
		{printf("\t<<<PAN is OK>>> \n");}
		else if (C_var == 3)
		{printf("\t<<<WRONG_PAN>>> \n");}

//////////////////////Terminal//////////////////////////////////
	//Get transaction date
	T_var = getTransactionDate(&T_user);
		if (T_var == 0)
		{printf("\t<<<Date is OK>>> \n");}
		else if (T_var == 1)
		{printf("\t<<<WRONG_DATE>>> \n");}
		//Check the card expiration date
	T_var = isCardExpired(C_user,T_user);
		if (T_var == 0)
		{
			EXP = true;
			printf("\t<<<The card is valid>>> \n");
		}
		else if (T_var == 2)
		{
			EXP = false;
			printf("\t<<<EXPIRED_CARD>>> \n");
		}
		//Get transaction amount
	T_var_f = getTransactionAmount(&T_user.transAmount);
		if (T_var_f == 0)
		{printf("\t<<<Transaction amount is OK>>> \n");}
		else if (T_var_f == 4)
		{printf("\t<<<INVALID_AMOUNT>>> \n");}
		//Set Max Amount
	T_var_f = setMaxAmount(&T_user.maxTransAmount);
		if (T_var_f == 0)
		{printf("\t<<<Max Amount is OK>>> \n");}
		else if (T_var_f == 6)
		{printf("\t<<<INVALID_MAX_AMOUNT>>> \n");}
		//Check if the transaction amount below the max amount
	T_var_f = isBelowMaxAmount(&T_user);
		if (T_var_f == 0)
		{
			printf("\t<<<Below Max Amount>>> \n");
			Max = true;
		}
		else if (T_var_f == 5)
		{
			printf("\t<<<EXCEED_MAX_AMOUNT>>> \n");
			Max = false;
		}

/////////////////////Server/////////////////////////////////
		transData.cardHolderData = C_user;
		transData.terminalData = T_user;
		EN_transState_t States = recieveTransactionData(&transData , Max, EXP);
		if (States == DECLINED_STOLEN_CARD )
		{
			printf("\n\t DECLINED STOLEN CARD/ACCOUNT_NOT_FOUND/Expired\n");
		}
		else if (States == DECLINED_INSUFFECIENT_FUND )
		{
			printf("\n\tDECLINED_INSUFFECIENT_FUND/Exceed Max Limits\n");
		}
		else if (States == APPROVED)
		{
			printf("\n\t >>>>APPROVED\n");
			printf("\t >>>>Transaction saved\n");
			printf("\t >>>>Account data is loading.....\n");
		}
		EN_serverError_t final =saveTransaction(&transData);
		if (final == OK_serverError)
		{
			printf("\t..............Thank you!..................\n");
		}
		else if (final==SAVING_FAILED)
		{
			printf("\t..............SAVING_FAILED!..................\n");
		}
		
		
		
}