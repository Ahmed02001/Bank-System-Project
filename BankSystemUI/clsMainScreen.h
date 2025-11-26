#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsCLientListScreen.h"
#include"clsAddNewClient.h"
#include"clsDeleteCLientScreen.h"
#include"clsUpdateClient.h"
#include"clsFindClient.h"
#include"clsTransactionsScreen.h"
#include"clsManageUsersScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen{

private:
	enum enMainMenueOptions {
		eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
		eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
		eManageUsers = 7, eExit = 8
	};

	static short _ReadMainMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 8]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 8, "Enter Number between 1 to 8? ");
		return Choice;
	}

	static  void _GoBackToMainMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

		system("pause>0");
		ShowMainMenue();
	}

	static void _ShowAllClientsScreen()
	{
		//cout << "\nClient List Screen Will be here...\n";

		clsCLientListScreen::ShowClientsList();

	}

	static void _ShowAddNewClientsScreen()
	{
		//cout << "\nAdd New Client Screen Will be here...\n";

		clsAddNewClient::AddNewClientScreen();

	}

	static void _ShowDeleteClientScreen()
	{
		//cout << "\nDelete Client Screen Will be here...\n";

		clsDeleteCLientScreen::ShowDeleteClientScreen();

	}

	static void _ShowUpdateClientScreen()
	{
		// cout << "\nUpdate Client Screen Will be here...\n";

		clsUpdateClient::ShowUpdateClientScreen();

	}

	static void _ShowFindClientScreen()
	{
		//cout << "\nFind Client Screen Will be here...\n";

		clsFindClient::ShowFindClient();

	}

	static void _ShowTransactionsMenue()
	{
		//cout << "\nTransactions Menue Will be here...\n";

		clsTransactionsScreen::ShowTransactionMenue();

	}

	static void _ShowManageUsersMenue()
	{
		//cout << "\nUsers Menue Will be here...\n";

		clsManageUsersScreen::ShowManageUsersMenue();

	}

	static void _ShowEndScreen()
	{
		cout << "\nEnd Screen Will be here...\n";

	}

	static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
	{
		switch (MainMenueOption)
		{
		case enMainMenueOptions::eListClients:
		{
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eAddNewClient:
			system("cls");
			_ShowAddNewClientsScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eDeleteClient:
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eUpdateClient:
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eFindClient:
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eShowTransactionsMenue:
			system("cls");
			_ShowTransactionsMenue();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eManageUsers:
			system("cls");
			_ShowManageUsersMenue();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eExit:
			system("cls");
			_ShowEndScreen();
			_GoBackToMainMenue();
			//Login();

			break;
		}

	}
public:


	static void ShowMainMenue() {

		system("cls");
		_DrawScreenHeader("\t\tMain Screen");

		cout << setw(37) << left << "" << "============================================\n";
		cout << setw(37) << left << "" << "\t\t\t Main Menue\n";
		cout << setw(37) << left << "" << "============================================\n";
		cout << setw(37) << left << "" << "\t[1] Show CLient List." << endl;
		cout << setw(37) << left << "" << "\t[2] Add New Client." << endl;
		cout << setw(37) << left << "" << "\t[3] Delete CLient." << endl;
		cout << setw(37) << left << "" << "\t[4] Update Client Info." << endl;
		cout << setw(37) << left << "" << "\t[5] Find Client." << endl;
		cout << setw(37) << left << "" << "\t[6] Transactions." << endl;
		cout << setw(37) << left << "" << "\t[7] Manage User." << endl;
		cout << setw(37) << left << "" << "\t[8] Logout." << endl;
		cout << setw(37) << left << "" << "============================================\n";

		_PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
	}

};

