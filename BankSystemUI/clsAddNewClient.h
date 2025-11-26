#pragma once

#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsBankClient.h"
using namespace std;

class clsAddNewClient : protected clsScreen
{
private:
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

public:

	static void AddNewClientScreen() {
		
		_DrawScreenHeader("\t Add New Client Screen");
		string AccountNumber = "";
		cout << "\nplease enter client acount number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\naccount number is already used, choose another account: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResult SaveResult;

		SaveResult = NewClient.Save();

		switch (SaveResult) {

		case clsBankClient::enSaveResult::svSucceeded:
			cout << "\nAccount Addeded Successfully :-)\n";
			_PrintClient(NewClient);
			break;

		case clsBankClient::enSaveResult::svFaildEmptyObject:
			cout << "\nError Account was not saved because It's Empty.";
			break;

		case clsBankClient::enSaveResult::svFaildAccountNumberExists:
			cout << "\nError account was not saved because account number is used!\n";
			break;
		}
	}
};

