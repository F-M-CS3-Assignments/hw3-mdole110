#include <ctime> // for time(0)
#include <iostream> // for cin and cout
#include <cmath> // for M_PI and others
#include <vector> // for vectors (duh)
#include <cstdlib> // for random
#include <cassert> // for assert in the tests() function
#include "TimeCode.h" // for timecode's (duh)

using namespace std;
//question... when and where to i free/deallocate

struct DryingSnapShot {
	// This is a struct, it's like an object
	// that doesn't have any methods.
	// You can read more about them in the ZyBook
	// just search for "struct"
	string name;
	time_t startTime;
	TimeCode *timeToDry;
};


long long int get_time_remaining(DryingSnapShot dss){
	time_t start = time(0);
	//to get the time remaining you need time passed-timeToDry (the timeCode)
	//time passed = duration?
	unsigned int hours =0;
	unsigned int minutes =0;
	unsigned int seconds=0;
	dss.timeToDry->GetComponents(hours, minutes, seconds);//pointer used ->
	long long int SECONDStoDry = dss.timeToDry->ComponentsToSeconds(hours, minutes, seconds);

	time_t end = time(0);
	time_t duration = end -start;
	long long int time_remaining= SECONDStoDry - duration;
	/*
	if(time_remaining = 0){
		delete dss.timeToDry;
	}
	*/
	//duration - current time = time remaining
	return time_remaining;
}


string drying_snap_shot_to_string(DryingSnapShot dss){
	// Replace with your code
	//drying snapshot includes string name,start time, and TimeCode *timeToDry
	//use TimeCode ToString Method

	string TimeToDryString = (*dss.timeToDry).ToString();
	//convert time_t (startTime) to a string
	string startTimeString = ctime(&dss.startTime); //https://stackoverflow.com/questions/997512/string-representation-of-time-t


	string String = "Name: " + dss.name + " Start Time: " + startTimeString + " Time to Dry: " + TimeToDryString;
	return "";
}


double get_sphere_sa(double rad){
	return 4*M_PI*rad*rad; //M_PI = pi
}


TimeCode *compute_time_code(double surfaceArea){
	//convert the surface area into time code (assuming surface area is the number of seconds -- confirmed by directions)
	unsigned int hours = surfaceArea/3600;
	int surfaceAreaInt = int(surfaceArea); //potential error source..go back poss
	unsigned int mins = (surfaceAreaInt%3600)/60;
	unsigned int secs = surfaceAreaInt % 60;
	TimeCode* timeToDry = new TimeCode(hours, mins, secs); //dynamic allocate; *... pointer
	//cout << TimeToDry << endl;
	return timeToDry;
}


void tests(){
	// get_time_remaining
	DryingSnapShot dss;
	dss.startTime = time(0);
	TimeCode tc = TimeCode(0, 0, 7);
	dss.timeToDry = &tc;
	long long int ans = get_time_remaining(dss);
	assert(ans > 6 && ans < 8);
	// add more tests here
	TimeCode tc4 = TimeCode (0, 1, 2);
	dss.timeToDry = &tc4;
	long long int answer2 = get_time_remaining(dss);
	assert(answer2> 61&&answer2<63); //so yes, returns seconds remaining...should it?
	//delete &tc4;
	//test with 0
	/*
	TimeCode tcZERO = TimeCode(0,0,0);
	dss.timeToDry = &tcZERO;
	long long int answer3 = get_time_remaining(dss);
	assert(answer3>-1 && answer3<1);
	*/


	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);
	// add more tests here
	double sa2 = get_sphere_sa(4.5);
	assert(254.4690 < sa2 && sa2 < 254.4691);


	// compute_time_code
	TimeCode *tc2 = compute_time_code(1.0);
	//cout << "tc: " << tc.GetTimeCodeAsSeconds() << endl;
	assert(tc2->GetTimeCodeAsSeconds() == 1);
	delete tc2;
	TimeCode *tc3 = compute_time_code(27.0);
	assert(tc3->GetTimeCodeAsSeconds() ==27);


	// add more tests here


	cout << "ALL TESTS PASSED!" << endl;

}


int main(){
	// replace with your code
	tests();
	return 0;
}