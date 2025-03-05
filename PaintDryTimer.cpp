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
    //store all of the batches in vector 
	vector<DryingSnapShot> Batches;
	// one" << endl;
	//ask user to choose A Q or V
	char userCHOICE;
	bool running = true; //change running to false when quit is chosen
	while(running){
		cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
		
		cin >> userCHOICE;
		char upperUserChoice = toupper(userCHOICE); //make all inputs upper case so you dont have to handke lower/upper

		if(upperUserChoice == 'A'){
			DryingSnapShot dss; //enter here so you can set up specific dss values
			//values in dss:
			/*
			string name;
			time_t startTime;
			TimeCode *timeToDry;
			*/
			dss.name = "Batch - " + to_string(int(rand())); //string name
			//now user needs to enter a radius for the calculations
			cout << "radius: ";
			double userRadius; //only ints?
			cin >> userRadius;
			//use radius to calculate the timecode (first need the surface area)
			double sa = get_sphere_sa(userRadius);
			//now use the sa to get the timeToDry
			dss.timeToDry = compute_time_code(sa); //dss object
			//start time to 0? always? yeah probs 
			dss.startTime = time(0);

			//create a new drying snap shot string
            //cout << "snapshot here: " << endl;
            //get everything to string 

           

            //get everuyhing onto a string for output
            string timeToDryString = dss.timeToDry->ToString(); //time codes's to string method...right
            long long int timeRemaining = get_time_remaining(dss);
            //conv the int to a timecode 
            TimeCode* TCofTimeReamining = compute_time_code(timeRemaining);
			//string result of the snapshot
            string snapshotResult = dss.name + "(take " + timeToDryString + " to dry) time remaining: " + TCofTimeReamining->ToString();
            cout << snapshotResult << endl;
             //Create a new batch in the vector and push onto the vector 
            DryingSnapShot addBatch;
            addBatch.name = dss.name;
            addBatch.startTime = time(0);
            addBatch.timeToDry = dss.timeToDry;
            //push back onto the vector
            Batches.push_back(addBatch);
		}
        else if (upperUserChoice == 'V'){
            //view the batches in action already
            //first, if theere are none say that
            if(Batches.empty()==true){
                cout << "No batches in progress to view." << endl;
            }
            else{
                for(size_t i=0; i<Batches.size(); i++){//for all of the batches in the vector
                    //get the amount of time each batch has left so you can build the string
                    long long int timeRemainingNUM = get_time_remaining(Batches[i]);
                    //convert to time code format
                    TimeCode* TCofTimeReamining = compute_time_code(timeRemainingNUM);
                    //get time to dry for each too for the string
                    string timeToDryString = Batches[i].timeToDry->ToString();
                    //now print the string using all of these components
                    string snapshotResult = Batches[i].name + "(takes " + timeToDryString + " to dry) time remaining: " + TCofTimeReamining->ToString();
                    cout << snapshotResult << endl;
                } 
                //print num of things being trackes (batches in vector)
                cout << Batches.size() << " batches being tracked." << endl;
            }

        }
        else if(upperUserChoice == 'Q'){
            running = false;
            break;
        }
    }
    Batches.clear();
		

	tests();
	return 0;
}