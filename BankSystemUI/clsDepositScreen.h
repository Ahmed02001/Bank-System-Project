#pragma once

#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"



class clsDepositScreen  : protected clsScreen
{
private: 
	static void _PrintClient(clsBankClient Client) {

		cout << "\n Client Card" << endl;
		cout << "\n__________________________\n";
		cout << "\nFirstName  : " << Client.FirstName;
		cout << "\nLastName   : " << Client.LastName;
		cout << "\nFullName   : " << Client.FullName();
		cout << "\nGmail      : " << Client.Gmail;
		cout << "\nPhone      : " << Client.Phone;
		cout << "\nAcc Number : " << Client.AccountNumber();
		cout << "\nPassword   : " << Client.PinCode;
		cout << "\nAcc Balance: " << Client.AccountBalance;
		cout << "\n__________________________\n";
	}

	static string _ReadAccountNumber() {
		string AccountNumber = "";
		cout << "\nPlease enter AccountNumber? ";
		cin >> AccountNumber;
		return AccountNumber;
	}

public:
	 
	static void ShowDepositScreen() {

		_DrawScreenHeader("\t  Deposit Screen");

		string AccountNumber = _ReadAccountNumber();

		while (!clsBankClient::IsClientExist(AccountNumber)) {

			cout << "]nClient Number [" << AccountNumber << "] does not exist.";
			AccountNumber = _ReadAccountNumber();
		}
		
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClient(Client1);

		double Amount = 0;
		cout << "\nPlease Enter Deposit amount? ";
		Amount = clsInputValidate::ReadDblNumber();

		cout << "\nAre you sure you want oreform this transaction? ";

		char Answer = 'n';

		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y') {
			Client1.Deposit(Amount);
			cout << "\nAmount Deposited Successfully.\n"; 
			cout << "\nNew Balance is: " << Client1.AccountBalance;
		}
		else {
			cout << "\nOperation was Cancelled.\n";
		}

	}
};

