#pragma once
#include<iostream>
#include "clsBankClient.h"
#include"clsInputValidate.h"
#include"clsScreen.h"

using namespace std;

class clsUpdateClient:protected clsScreen
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

	static void _ReadClientInfo(clsBankClient& Client) {

		cout << "\nEnter FirstName : ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName : ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Gmail : ";
		Client.Gmail = clsInputValidate::ReadString();

		cout << "\nEnter Phone : ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nEnter PinCode : ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "\nEnter Account balance :";
		Client.AccountBalance = clsInputValidate::ReadDblNumber();

	}

public:
	static void ShowUpdateClientScreen() {

		string AccountNumber = "";
		cout << "\nplease enter client acount number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\naccount number is not found, choose another account: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClient(Client1);

		cout << "\nUpdate Client Info:\n";
		cout << "\n___________________\n";

		_ReadClientInfo(Client1);

		clsBankClient::enSaveResult SaveResult;

		SaveResult = Client1.Save();

		switch (SaveResult) {

		case clsBankClient::enSaveResult::svSucceeded:
			cout << "\nAccount Update Successfully :-)\n";
			_PrintClient(Client1);
			break;

		case clsBankClient::enSaveResult::svFaildEmptyObject:
			cout << "\nError Account was not saved because It's Empty.";
			break;
		}
	}
};

