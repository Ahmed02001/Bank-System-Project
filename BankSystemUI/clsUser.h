#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"clsPerson.h"
#include"clsString.h"
class clsUser : public clsPerson
{
	enum enMode {EmptyMode = 1, UpdateMode = 2, AddNewMode = 3};
	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;

	bool _MarkedForDelete = false;

	static clsUser _ConvertLineToUserObject(string Line, string Seprator = "#//#") {

		vector <string> vUserData;

		vUserData = clsString::Split(Line, Seprator);

		return clsUser(UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3], vUserData[4], vUserData[5], stoi(vUserData[6]));
	}

	static clsUser _GetEmptyUserObject() {

		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _ConvertUserRecordToLine(clsUser User, string Seperator = "#//#") {

		string stUserRecord = "";
		stUserRecord += User.FirstName + Seperator;
		stUserRecord += User.LastName + Seperator;
		stUserRecord += User.Gmail + Seperator;
		stUserRecord += User.Phone + Seperator;
		stUserRecord += User.UserName + Seperator;
		stUserRecord += User.Password + Seperator;
		stUserRecord += to_string(User.Permissions);


		return stUserRecord;
	}

	static vector <clsUser> _LoadUsersDataFromFile() {

		vector <clsUser> vUserData;
		fstream MyFile;

		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;
			while (getline(MyFile, Line)) {

				clsUser User = _ConvertLineToUserObject(Line);
				vUserData.push_back(User);
			}

			MyFile.close();
		}
		return vUserData;
	}

	static void _SaveUserDataToFile(vector <clsUser> vUsers) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::out);

		string DataLine;

		if (MyFile.is_open()) {

			for (clsUser C : vUsers) {

				if (C.MarkedForDelete() == false) {

					DataLine = _ConvertUserRecordToLine(C);
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}
	}

	void _Update() {

		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers) {

			if (U.UserName == UserName) {

				U = *this;
				break;
			}
		}

		_SaveUserDataToFile(_vUsers);
	}

	void _AddNew() {

		_AddDataLineToFile(_ConvertUserRecordToLine(*this));
	}

	void _AddDataLineToFile(string stDataLine) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::out || ios::app);

		if (MyFile.is_open()) {

			MyFile << stDataLine << endl;

			MyFile.close();
		}
	}

public:
	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClients = 2, pDeleteClients = 4, pUpdateClients = 8, pFindClients = 16, 
		pTransactions = 32, pManageUsers = 64
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Gmail, string Phone, string UserName, string Password, int Permissions) :
		clsPerson(FirstName, LastName, Gmail, Phone) {

		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}
		
	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDelete() {

		return _MarkedForDelete;
	}

	string GetUserName() {

		return _UserName;
	}

	void SetUserName(string UserName) {

		_UserName = UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserName))string UserName;

	string GetPassword() {

		return _Password;
	}

	void SetPassword(string Password) {

		_Password = Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword))string Password;

	int GetPermissions() {

		return _Permissions;
	}

	void SetPermissions(int Permissions) {
		_Permissions = Permissions;
	}

	__declspec(property(get = GetPermissions, put = SetPermissions))int Permissions;

	static clsUser Find(string UserName) {

		fstream MyFile;

		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open()) {

			string Line;
			while (getline(MyFile, Line)) {

				clsUser User = _ConvertLineToUserObject(Line);

				if (User.UserName == UserName) {
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password) {

		fstream MyFile;

		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open()) {

			string Line;
			while (getline(MyFile, Line)) {

				clsUser User = _ConvertLineToUserObject(Line);

				if (User.UserName == UserName && User.Password == Password) {
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

	enSaveResults Save()
	{

		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{
				return enSaveResults::svFaildEmptyObject;
			}
		}

		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;

			break;
		}

		case enMode::AddNewMode:
		{
			//This will add new record to file or database
			if (clsUser::IsUserExist(_UserName))
			{
				return enSaveResults::svFaildUserExists;
			}
			else
			{
				_AddNew();
				//We need to set the mode to update after add new
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}

			break;
		}
		}

	}

	static bool IsUserExist(string UserName)
	{

		clsUser User = clsUser::Find(UserName);
		return (!User.IsEmpty());
	}

	bool Delete()
	{
		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers)
		{
			if (U.UserName == _UserName)
			{
				U._MarkedForDelete = true;
				break;
			}

		}

		_SaveUserDataToFile(_vUsers);

		*this = _GetEmptyUserObject();

		return true;

	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	static vector <clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

};

