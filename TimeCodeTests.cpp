
#include <iostream>
#include <assert.h>
using namespace std;

#include "TimeCode.h"

//Test all functions! 
void TestComponentsToSeconds(){
	cout << "Testing ComponentsToSeconds" << endl;
	
	// Random but "safe" inputs
	long long unsigned int t = TimeCode::ComponentsToSeconds(3, 17, 42);
	assert(t == 11862);
	
	// More tests go here!
	t = TimeCode::ComponentsToSeconds(4, 61, 99); //try some to prove rollover works
	assert(t==18159);
	
	cout << "PASSED!" << endl << endl;
}


void TestDefaultConstructor(){
	cout << "Testing Default Constructor" << endl;
	TimeCode tc;
	
	cout << "Testing ToString()" << endl;
	cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	//assert(tc.ToString)
	
	cout << "PASSED!" << endl << endl;
}


void TestComponentConstructor(){
	cout << "Testing Component Constructor" << endl;
	TimeCode tc = TimeCode(0, 0, 0);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	// more tests go here!
	//test exactly one hour
	TimeCode tc2 = TimeCode(1,0,0);
	assert(tc2.ToString() == "1:0:0");
	
	
	// Roll-over inputs
	TimeCode tc3 = TimeCode(3, 71, 3801);
	//cout << "tc3: " << tc3.ToString() << endl;
	assert(tc3.ToString() == "5:14:21");
	
	// More tests go here!
	TimeCode tc4 = TimeCode(0, 61, 61);
	assert(tc4.ToString()=="1:2:1");
	//cout<< (tc4.ToString() == "1:2:1");
	
	cout << " PASSED!" << endl << endl;
}


void TestGetComponents(){
	cout << "Testing GetComponents" << endl;
	
	unsigned int h;
	unsigned int m;
	unsigned int s;
	
	// Regular values
	TimeCode tc = TimeCode(5, 2, 18);
	tc.GetComponents(h, m, s);
	assert(h == 5 && m == 2 && s == 18);
	
	// More tests go here!
	//test rollover
	TimeCode tc2 = TimeCode(1, 61, 61);
	tc2.GetComponents(h, m, s);
	assert(h==2 && m==2 && s==1);

	
	cout << "PASSED!" << endl << endl;
}
//math tests 
//addition
void TestAddittion(){
	cout << "Testing Addittion" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 + tc2;
	assert(tc3.ToString() == "1:50:0");
	
	//dont need to check for negs

	// more tests
	//roll over
	TimeCode tc6= TimeCode(2, 30, 0);
	TimeCode tc7 = TimeCode(1,31,0);
	TimeCode newTC = tc6+tc7;
	assert(newTC.ToString()=="4:1:0");
	//subtracting to a negative
	
	cout << "PASSED!" << endl << endl;
}

//subtraction
void TestSubtract(){
	cout << "Testing Subtract" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	assert(tc3.ToString() == "0:10:0");
	
	
	TimeCode tc4 = TimeCode(1, 15, 45);//checks neg! 
	try{
		TimeCode tc5 = tc1 - tc4;
		cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just leave this empty
		// and keep doing more tests
	}

	// more tests
	//roll over
	TimeCode tc6= TimeCode(2, 30, 0);
	TimeCode tc7 = TimeCode(1,31,0);
	TimeCode newTC = tc6-tc7;
	assert(newTC.ToString()=="0:59:0");
	//subtracting to a negative
	
	cout << "PASSED!" << endl << endl;
}
// multiplication
void TestMultiplication(){
	cout<<"Testing Multiplication" <<endl;
	TimeCode tc1 = TimeCode(1,0,0);
	double a = 0.5;
	TimeCode mult1 = tc1*a;
	assert(mult1.ToString() == "0:30:0");
	//test w/ a 0
	//TimeCode tc2 = TimeCode (2, 0, 0);
	double b = 0;
	TimeCode mult2 = tc1*b;
	assert(mult2.ToString() == "0:0:0");
	// try with negative 
	double c = -1;
	try{
		TimeCode mult3 = tc1*c;
		cout << "tc5: " << mult3.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just leave this empty
		// and keep doing more tests
		//caught in code 
	}
	cout<< "PASSED!!" << endl;
}
//test division 
void TestDivision(){
	cout<<"Testing Division" <<endl;
	TimeCode tc1 = TimeCode(1,0,0);
	double a = 0.5;
	TimeCode mult1 = tc1/a;
	assert(mult1.ToString() == "2:0:0");
	//test w/ a 0
	TimeCode tc2 = TimeCode (2, 5, 0);
	double b = 0;
	TimeCode mult2 = tc1/b;
	assert(mult2.ToString() == "0:0:0");
	// try with negative 
	double c = -1;
	try{
		TimeCode mult3 = tc1/c;
		cout << "tc5: " << mult3.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just leave this empty
		// and keep doing more tests
		//caught in code 
	}
	cout<< "PASSED!!" << endl;
}


//TEST SETTERS
//seconds
void TestSetSeconds()
{
	cout << "Testing SetSeconds" << endl;

	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetSeconds(15); // test valid change
	assert(tc.ToString() == "8:5:15");

	try
	{
		tc.SetMinutes(80);  // test invalid change
		assert(false);
	}
	catch (const invalid_argument &e)
	{
		//work?
	}	

	assert(tc.ToString() == "8:5:15");
	//cout <<"\n";
	cout << "PASSED!" << endl << endl;
}
//minutes
void TestSetMinutes()
{
	cout << "Testing SetMinutes" << endl;

	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetMinutes(15); // test valid change
	assert(tc.ToString() == "8:15:9");

	try
	{
		tc.SetMinutes(80);  // test invalid change
		assert(false);
	}
	catch (const invalid_argument &e)
	{
		//cout<< e.what() << endl;
		//work?
	}	

	assert(tc.ToString() == "8:15:9");
	//cout <<"\n";
	cout << "PASSED!" << endl << endl;
}
//hours
void TestSetHours()
{
	cout << "Testing SetHours" << endl;

	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetHours(15); // test valid change
	assert(tc.ToString() == "15:5:9");
	//ALL HOUR VALUES are valid
	cout << "PASSED!" << endl << endl;
}

//GET tests 

void TestGetSeconds(){
	cout << "Testing Get Seconds" << endl;
	TimeCode tc = TimeCode(1, 1, 50);
	int seconds = tc.GetSeconds();
	assert(seconds == 50);
	cout << "PASSED!!" << endl;
}
void TestGetMinutes(){
	cout << "Testing Get Minutes" << endl;
	TimeCode tc = TimeCode(1, 50, 1);
	int minutes = tc.GetMinutes();
	assert(minutes == 50);
	cout << "PASSED!!" << endl;
}
void TestGetHours(){
	cout << "Testing Get Hours" << endl;
	TimeCode tc = TimeCode(50, 1, 1);
	int hours = tc.GetHours();
	assert(hours == 50);
	cout << "PASSED!!" << endl;
}
//comparison operators 


void TestisEqualTo(){
	cout << "Testing ==" << endl;
	TimeCode tc1 = TimeCode(0,1,1);
	TimeCode tc2 = TimeCode(0,1,1);
	bool sayTrue = tc1==tc2;
	assert(sayTrue == true);
	TimeCode tc3 = TimeCode(1,0,1);
	bool sayFalse = tc1==tc3;
	assert(sayFalse == false);
	cout<< "PASSED!!" << endl;

}
void TestNOTEqualTo(){
	cout<< "Testing !=" << endl;
	TimeCode tc1 = TimeCode(0,1,1);
	TimeCode tc2 = TimeCode(0,1,1);
	bool sayFalse = tc1!=tc2;
	assert(sayFalse == false);
	TimeCode tc3 = TimeCode(1,0,1);
	bool sayTrue = tc1!=tc3;
	assert(sayTrue == true);
	cout<< "PASSED!!" << endl;
}
void TestLESSthan(){
	cout << "Testing <" << endl;
	//check equal
	TimeCode tc1 = TimeCode(0,1,0);
	TimeCode tc2 = TimeCode(0,1,0);
	bool sayFalsecuzEqual = tc1<tc2;
	assert(sayFalsecuzEqual == false);
	//check LESS than
	TimeCode tc3 = TimeCode(0, 1, 1);
	bool sayTrue= tc1<tc3;
	assert(sayTrue == true);
	//check GREATER than
	bool sayFalsecuzeatsLESS= tc1>tc3;
	assert(sayFalsecuzeatsLESS == false);
	

}
void TestGREATERthan(){
	cout << "Testing >" << endl;
	TimeCode tc1 = TimeCode(0,1,0);
	TimeCode tc2 = TimeCode(0,1,0);
	TimeCode tc3 = TimeCode(0, 1, 1);
	//check equal
	bool sayFalsecuzEqual = tc1<tc2;
	assert(sayFalsecuzEqual == false);
	//check greater than
	bool sayTRUE = tc3>tc1;
	assert(sayTRUE== true);
	//check less than
	bool sayFalsecuzLess = tc1>tc3;
	assert(sayFalsecuzLess == false);
}
void TestLESSorequal(){
	cout << "Testing <=" << endl;
	TimeCode tc1 = TimeCode(0,1,0);
	TimeCode tc2 = TimeCode(0,1,0);
	TimeCode tc3 = TimeCode(0, 1, 1);
	//check equal
	bool sayTruecuzEqual = tc1<=tc2;
	assert(sayTruecuzEqual == true);
	//check picking the less (wrong)
	bool sayFalsecuzPicksLower = tc3<=tc1;
	assert(sayFalsecuzPicksLower == false);
	//check true
	bool sayTrue = tc1<=tc3;
	assert(sayTrue == true);
}
void TestGREATERorequal(){
	cout << "Testing >=" <<endl;
	TimeCode tc1 = TimeCode(0,1,0);
	TimeCode tc2 = TimeCode(0,1,0);
	TimeCode tc3 = TimeCode(0, 1, 1);
	//check equal
	bool sayTruecuzEqual = tc1>=tc2;
	assert(sayTruecuzEqual == true);
	//test picking smaller
	bool sayFalsecuzPicksLower = tc1>=tc3;
	assert(sayFalsecuzPicksLower == false);
	//test picking greater (true)
	bool sayTrue = tc3>=tc1;
	assert(sayTrue = true);

}



//MULTIPLE TESTS TEST TOSTRING ALREADY
// Many More Tests...


int main(){
	
	TestComponentsToSeconds();
	TestDefaultConstructor();
	TestComponentConstructor();
	TestGetComponents();
	TestAddittion();
	TestSubtract();
	TestMultiplication();
	TestDivision();

	TestSetSeconds();
	TestSetMinutes();
	TestSetHours();

	TestGetSeconds();
	TestGetMinutes();
	TestGetHours();

	TestisEqualTo();
	TestNOTEqualTo();
	TestLESSthan();
	TestGREATERthan();
	TestLESSorequal();
	TestGREATERorequal();
	
	// Many othere test functions...
	
	cout << "PASSED ALL TESTS!!!" << endl;
	return 0;
}
