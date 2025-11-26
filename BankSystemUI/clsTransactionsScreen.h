#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsDepositScreen.h"
#include"clsWithdrawScreen.h"
#include"clsTotalBalancesScreen.h"

using namespace std;

class clsTransactionsScreen: protected clsScreen
{
private:

	enum enTransactionMenueOptions {
		Deposit = 1,
		Withdraw = 2,
		TotalBalances = 3,
		MainMenue = 4
	};

	static short _ReadMainMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 4]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 4, "Enter Number between 1 to 4? ");
		return Choice;
	}

	static  void _GoBackToMainMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

		system("pause>0");
		ShowTransactionMenue();
	}

	static void _ShowDepositFunction() {
		//cout << "Sorry, I working here." << endl;

		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawFunction() {
		// cout << "Sorry, We Working here.\n";

		clsWithdrawScreen::ShowWithDrawScreen();
	}

	static void _ShowTotalBalancesFunction() {
		//cout << "Sorry, We Prepare this Function." << endl;

		clsTotalBalancesScreen::ShowTotalBalances();
	}

	static void _ShowMainMenue() {
		cout << "we Making This problem." << endl;
	}

	static void _PreformTransactionMenueOption(enTransactionMenueOptions TransactionMenueOptions) {

		switch (TransactionMenueOptions) {

		case enTransactionMenueOptions::Deposit:
			system("cls");
			_ShowDepositFunction();
			_GoBackToMainMenue();
			break;

		case enTransactionMenueOptions::Withdraw:
			system("cls");
			_ShowWithdrawFunction();
			_GoBackToMainMenue();
			break;

		case enTransactionMenueOptions::TotalBalances:
			system("cls");
			_ShowTotalBalancesFunction();
			_GoBackToMainMenue();
			break;

		case enTransactionMenueOptions::MainMenue:
		{
			//do nothing here the main screen will handle it :-) ;

		}

		}
	}

public:

	static void ShowTransactionMenue() {

		system("cls");
		_DrawScreenHeader("\t  Transactions Screen");

		cout << setw(37) << left << "" << "============================================\n";
		cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
		cout << setw(37) << left << "" << "============================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit." << endl;
		cout << setw(37) << left << "" << "\t[2] Withdraw." << endl;
		cout << setw(37) << left << "" << "\t[3] Total Balances." << endl;
		cout << setw(37) << left << "" << "\t[4] Main Menue." << endl;
		cout << setw(37) << left << "" << "============================================\n";

		_PreformTransactionMenueOption(enTransactionMenueOptions(_ReadMainMenueOption()));
	}

};

