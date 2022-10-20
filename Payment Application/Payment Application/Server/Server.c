#include"Server.h"
#include<stdio.h>
#include<string.h>
#include"../Ex-Libraries/C_Database.h"
#include"../Ex-Libraries/T_Database.h"


int index = 0;
uint32_t transactionsequencenumber = 0;
int flag_Start = 0;
int cont;

EN_transState_t recieveTransactionData(ST_transaction_t* transData , bool Max_T , bool EXP)
{
	
	if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND || isBlockedAccount() == BLOCKED_ACCOUNT || EXP == false)
	{
		transData->transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}
	if (isBlockedAccount() == OK_serverError && isValidAccount(&transData->cardHolderData)== OK_serverError && isAmountAvailable(&transData->terminalData) == OK_serverError  && Max_T && EXP)
	{
	
		transData->transState = APPROVED;
		
		return APPROVED;
	}
	if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE || Max_T == false )
	{
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}

	
	
}
EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	AccountDBlist();
	flag_Start = 1;
	bool identical = false;
	uint8_t* PAN = cardData->primaryAccountNumber;
	
	bool found = false;
	int count=0;
	for (int x = 0; x < 20; x++)
	{
		if (PAN[x] != '\0')
		{
			count++;
		}
		else if (PAN[x] == '\0')
		{
			break;
		}
		
	}

for (int i = 0; i < 255; i++)
{ 
	bool search = true;
	if (count > 2)
	{ 
	
		for(int j=0 ; j < count; j++)
		{
			if (accountsDB[i].primaryAccountNumber[j] != PAN[j])
			{
				search = false;
				break;
			}
		
		}
		 if (search == true)
			{
			 identical = true;
			 index = i;
			 break;
			}
	}
}
if (!identical) {
	count = 0;
	return ACCOUNT_NOT_FOUND;	
}
count = 0;
return OK_serverError;
}
EN_serverError_t isBlockedAccount()
{
	AccountDBlist();
	
	if (accountsDB[index].state == 0)
	{
		return OK_serverError;
	}
	else if (accountsDB[index].state == 1)
	{
		return BLOCKED_ACCOUNT;
	}
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	AccountDBlist();
	if (termData->transAmount < accountsDB[index].balance)
	{
		return OK_serverError;
	}
	else if (termData->transAmount > accountsDB[index].balance)
	{	return LOW_BALANCE;}
}
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	listSavedTransactions(flag_Start);
	AccountDBlist();
	transactionDB[transactionsequencenumber].terminalData.maxTransAmount = accountsDB[index].balance - transData->terminalData.transAmount;
	printf("\n\t--------Press 1 To Get Account Info. Or Press 2 To Skip.....\n");
	scanf_s("%d", &cont);
	if(cont ==1)
	{ 
	printf("\n \t -------------Account Info.--------------------\n");
	printf("\n\t|* Card Holder Name : %s \n", transData->cardHolderData.cardHolderName);
	printf("\t|* Card primary number PAN : %s \n", transData->cardHolderData.primaryAccountNumber);
	printf("\t|* Card Expiration Date : %s \n", transData->cardHolderData.cardExpirationDate);
	printf("\t|* Your Total Balance : %f \n", accountsDB[index].balance);
	printf("\t|* The withdrawn amount is : %f \n", transData->terminalData.transAmount);
	printf("\t|* Current Balance is : %f \n", transactionDB[transactionsequencenumber].terminalData.maxTransAmount);
	printf("\t|* The date of transaction is : %s \n", transData->terminalData.transactionDate);
	printf("\t|* This was the %d transaction during the day \n", transactionsequencenumber);
	
	
	if (transData->transState == APPROVED)
	{
		printf("\t|* The state fot your account is : APPROVED \n");
	}
	else if (transData->transState == DECLINED_INSUFFECIENT_FUND)
	{
		printf("\t|* The state fot your account is : DECLINED_INSUFFECIENT_FUND \n");
	}
	else if (transData->transState == DECLINED_STOLEN_CARD)
	{
		printf("\t|* The state fot your account is : DECLINED_STOLEN_CARD \n");
	}
	else if (transData->transState == INTERNAL_SERVER_ERROR)
	{
		printf("\t|* The state fot your account is : INTERNAL_SERVER_ERROR \n");
	}
	
	printf("\t|-----------------------------------------------------------\n\n");
	}
	else if (cont ==2)
	{
		return OK_serverError;
	}
	
	else 
	{
		return SAVING_FAILED;
	}

	transactionsequencenumber++;
}
