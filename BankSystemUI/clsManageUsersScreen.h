#pragma once
#include<iostream>
#include"clsScreen.h"
#include<iomanip>
#include"clsInputValidate.h"
#include"clsUserListScreen.h"
#include"clsAddNewUsersScreen.h"

using namespace std;


class clsManageUsersScreen : protected clsScreen
{

private:
	enum enManageUsersMenueOptions {
		eListUser = 1,
		eAddNewUser = 2,
		eDeleteUser = 3,
		eUpdateUser = 4,
		eFindUser = 5,
		eMainMenue = 6
	};

	static short ReadManageUserMenueOptions() {
		
		cout << setw(37) << left << "" << "Choose What do you want to do? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter number between 1 to 6 please : ");
		return Choice;
	}

	static void _CoBackToManageUserMenue() {
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

		system("pause>0");
		ShowManageUsersMenue();
	}

	static void _ShowListUsersScreen() {
		//cout << "\n List User Screen Will Be Here!";

		clsUserListScreen::ShowUsersList();

	}

	static void _ShowAddNewUserScreen() {
		//cout << "\n Add New User Screen Will Be Here!";

		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen() {
		cout << "\n Delete User Screen Will Be Here!";
	}

	static void _ShowUpdateUserScreen() {
		cout << "\n Update User Screen Will Be Here!";
	}

	static void _ShowFindUserScreen() {

		cout << "\n FInd User Screen Will Be Here!";
	}

	static void _ShowMainMenueScreen() {

	}

	static void _PreformManageUsesMenueOptions(enManageUsersMenueOptions ManageMenueOption) {

		switch (ManageMenueOption) {

		case enManageUsersMenueOptions::eListUser:
			system("cls");
			_ShowListUsersScreen();
			_CoBackToManageUserMenue();
			break;

		case enManageUsersMenueOptions::eAddNewUser:
			system("cls");
			_ShowAddNewUserScreen();
			_CoBackToManageUserMenue();
			break;

		case enManageUsersMenueOptions::eDeleteUser:
			system("cls");
			_ShowDeleteUserScreen();
			_CoBackToManageUserMenue();
			break;

		case enManageUsersMenueOptions::eUpdateUser:
			system("cls");
			_ShowDeleteUserScreen();
			_CoBackToManageUserMenue();
			break;

		case enManageUsersMenueOptions::eFindUser:
			system("cls");
			_ShowFindUserScreen();
			_CoBackToManageUserMenue();
			break;

		case enManageUsersMenueOptions::eMainMenue:
		{
			//don't write any code in here.
		}

		}
	}


public:

	static void ShowManageUsersMenue() {

		system("cls");
		_DrawScreenHeader("\t Manage Users Screen");

		cout << setw(37) << left << "" << "============================================\n";
		cout << setw(37) << left << "" << "\t\t Manage Users Menue \n";
		cout << setw(37) << left << "" << "========================================== = \n";
		cout << setw(37) << left << "" << "\t [1] List Users. \n";
		cout << setw(37) << left << "" << "\t [2] Add New User. \n";
		cout << setw(37) << left << "" << "\t [3] Delete User. \n";
		cout << setw(37) << left << "" << "\t [4] Update User. \n";
		cout << setw(37) << left << "" << "\t [5] Find User. \n";
		cout << setw(37) << left << "" << "\t [6] Main Menue. \n";
		cout << setw(37) << left << "" << "============================================\n";


		_PreformManageUsesMenueOptions((enManageUsersMenueOptions)ReadManageUserMenueOptions());
	}
};

