#ifndef C_Database_H
#define C_Database_H

#include"../Server/Server.h"
//
////Implement server-side accounts' database
ST_accountsDB_t accountsDB[255];
void AccountDBlist()
{
	accountsDB[0].balance = 2000;
	accountsDB[1].balance = 8000;
	accountsDB[2].balance = 10000;
	accountsDB[3].balance = 3000;
	accountsDB[4].balance = 1500;

	accountsDB[0].state = RUNNING;
	accountsDB[1].state = RUNNING;
	accountsDB[2].state = RUNNING;
	accountsDB[3].state = BLOCKED;
	accountsDB[4].state = BLOCKED;

	strcpy_s(accountsDB[0].primaryAccountNumber, 20, "4989563279436851");
	strcpy_s(accountsDB[1].primaryAccountNumber, 20, "8989374615983851");
	strcpy_s(accountsDB[2].primaryAccountNumber, 20, "5807007076043875");
	strcpy_s(accountsDB[3].primaryAccountNumber, 20, "3808754169320875");
	strcpy_s(accountsDB[4].primaryAccountNumber, 20, "9183964731982765");


}

#endif // !C_Database_H