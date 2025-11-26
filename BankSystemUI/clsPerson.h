#pragma once

#include<iostream>
using namespace std;

class clsPerson {

private:

	string _FirstName;
	string _LastName;
	string _Gmail;
	string _Phone;

public:

	// defult Constructor
	clsPerson(string FirstName, string LastName, string Gmail, string Phone) {

		_FirstName = FirstName;
		_LastName = LastName;
		_Gmail = Gmail;
		_Phone = Phone;
	}

	//set Property
	void setFirstName(string FirstName) {

		_FirstName = FirstName;

	}

	//get Property
	string  getFirstName() {

		return _FirstName;

	}

	__declspec(property(get = getFirstName, put = setFirstName)) string FirstName;

	//set Property
	void setLastName(string LastName) {

		_LastName = LastName;

	}

	//set Property
	string getLastName() {

		return _LastName;

	}

	__declspec(property(get = getLastName, put = setLastName)) string LastName;

	//set Property
	string FullName() {

		return _FirstName + " " + _LastName;

	}

	//set Property
	void setGmail(string Gmail) {

		_Gmail = Gmail;

	}

	//set Property
	string getGmail() {

		return _Gmail;
	}

	__declspec(property(get = getGmail, put = setGmail)) string Gmail;

	//set Property
	void setPhone(string Phone) {

		_Phone = Phone;

	}

	//set Property
	string getPhone() {

		return _Phone;

	}

	__declspec(property(get = getPhone, put = setPhone)) string Phone;

};
