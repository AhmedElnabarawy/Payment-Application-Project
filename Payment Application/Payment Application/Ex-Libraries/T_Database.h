#ifndef T_Database_H
#define T_Database_H
#include"../Server/Server.h"
#include <stdbool.h>

ST_transaction_t transactionDB[255];	

EN_serverError_t listSavedTransactions(int flag)
{
	// Initialization at the beginning 
	if (flag < 1)
	{
		for (int i = 0; i < 255; i++)
		{
			transactionDB[i].transactionSequenceNumber = 0;
			strcpy_s(transactionDB[i].terminalData.transactionDate, 10, "0");
			transactionDB[i].terminalData.transAmount = 0;
			transactionDB[i].transState = 0;
			transactionDB[i].terminalData.maxTransAmount = 0;
			strcpy_s(transactionDB[i].cardHolderData.cardHolderName, 24, "0");
			strcpy_s(transactionDB[i].cardHolderData.primaryAccountNumber, 20, "0");
			strcpy_s(transactionDB[i].cardHolderData.cardExpirationDate, 5, "0");

		}

	}
	
}

#endif // !T_Database_H