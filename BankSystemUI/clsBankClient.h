#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include"clsPerson.h"
#include"clsString.h"


using namespace std;

class clsBankClient : public clsPerson {

private:

	enum enMode {
		EmptyMode = 0,
		UpdateMode = 1,
		AddNewMode = 2
	};

	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkedForDelete = true;

	static clsBankClient _convertLineToClientObject(string Line, string seperate = "#//#") {

		vector <string> vClientDate;

		vClientDate = clsString::Split(Line, seperate);

		return clsBankClient(enMode::UpdateMode, vClientDate[0], vClientDate[1], vClientDate[2],
			vClientDate[3], vClientDate[4], vClientDate[5], stof(vClientDate[6]));
	}

	static clsBankClient _EmptyClientObject() {

		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string seprator = "#//#") {

		string stClientRecord = "";
		stClientRecord += Client.FirstName + seprator;
		stClientRecord += Client.LastName + seprator;
		stClientRecord += Client.Gmail + seprator;
		stClientRecord += Client.Phone + seprator;
		stClientRecord += Client.AccountNumber() + seprator;
		stClientRecord += Client.PinCode + seprator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;

	}

	static vector <clsBankClient> _LoadClientsDataFromFile() {

		vector <clsBankClient> vClients;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open()) {

			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _convertLineToClientObject(Line);
				vClients.push_back(Client);
			}
			MyFile.close();

		}
		return vClients;
	}

	static void _SaveClientDataToFile(vector <clsBankClient> vClients) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);

		string DataLine;
		if (MyFile.is_open()) {

			for (clsBankClient C : vClients) {
				DataLine = _ConvertClientObjectToLine(C);
				MyFile << DataLine << endl;
			}
			MyFile.close();
		}
	}

	void _Update() {

		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients) {

			if (C.AccountNumber() == AccountNumber()) {

				C = *this;

				break;
			}
		}

		_SaveClientDataToFile(_vClients);
	}

	void _AddNew() {
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Gmail, string Phone, string AccountNumber, string PinCode, float AccountBalance) :
		clsPerson(FirstName, LastName, Gmail, Phone) {

		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty() {

		return (_Mode == enMode::EmptyMode);
	}

	//Read only
	string AccountNumber() {

		return _AccountNumber;

	}

	// set property
	void setPinCode(string PinCode) {

		_PinCode = PinCode;

	}

	//get Propeerty
	string getPinCode() {

		return _PinCode;

	}

	__declspec(property(get = getPinCode, put = setPinCode)) string PinCode;


	// set property
	void setAccountBalance(double AccountBalance) {

		_AccountBalance = AccountBalance;

	}

	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}
	//get Propeerty
	double getAccountBalance() {

		return _AccountBalance;

	}

	__declspec(property(get = getAccountBalance, put = setAccountBalance)) double AccountBalance;

	//void Print() {

	//	cout << "\n Client Card" << endl;
	//	cout << "\n__________________________\n";
	//	cout << "\nFirstName  : " << FirstName;
	//	cout << "\nLastName   : " << LastName;
	//	cout << "\nFullName   : " << FullName();
	//	cout << "\nGmail      : " << Gmail;
	//	cout << "\nPhone      : " << Phone;
	//	cout << "\nAcc Number : " << _AccountNumber;
	//	cout << "\nPassword   : " << _PinCode;
	//	cout << "\nAcc Balance: " << _AccountBalance;
	//	cout << "\n__________________________\n";

	//}

	static clsBankClient Find(string AccountNumber) {

		vector <clsBankClient> vClients;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);	 //read Mode.

		if (MyFile.is_open()) {

			string Line;
			while (getline(MyFile, Line)) {

				clsBankClient Client = _convertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber) {

					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _EmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode) {

		vector<clsBankClient> vClients;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;
			while (getline(MyFile, Line)) {

				clsBankClient Client = _convertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode) {

					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _EmptyClientObject();
	}

	enum enSaveResult { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists };

	enSaveResult Save() {

		switch (_Mode) {

		case enMode::EmptyMode:

			return enSaveResult::svFaildEmptyObject;

		case enMode::UpdateMode:

			_Update();
			return enSaveResult::svSucceeded;

		case enMode::AddNewMode:

			if (clsBankClient::IsClientExist(_AccountNumber)) {
				return enSaveResult::svFaildAccountNumberExists;
			}
			else {
				_AddNew();
			}
		}

	}

	bool Delete()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkedForDelete = true;
				break;
			}

		}

		_SaveClientDataToFile(_vClients);

		*this = _EmptyClientObject();

		return true;

	}

	static bool IsClientExist(string AccountNumber) {

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		return (!Client1.IsEmpty());
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	static vector <clsBankClient> GetClientsList() {

		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances() {
		vector <clsBankClient> vClients = GetClientsList();
		double TotalBalances = 0;

		for (clsBankClient Client : vClients) {
			TotalBalances += Client.AccountBalance;
		}
		return TotalBalances;
	}

	void Deposit(double Amount) {
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount) {
		if (Amount > _AccountBalance) {
			return false;
		}
		else {
			_AccountBalance -= Amount;
			Save();
		}
		
	}

};


