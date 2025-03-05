///Note: read all of the notes at beginning of assignment 

#include <iostream>
#include "TimeCode.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

//read in the file


TimeCode parse_line(const string& line, bool& isValid){ //pass in 
    //fill in 
    //need the section between the 3rd and 4th comma
    unsigned int hours =0;
    unsigned int minutes =0;

    // handling missing data 

    isValid = false; //assume it doesnt exist until we find it
    //find colon
    int lineLength = (int)line.length(); //fixing error presented by ssh for comparing int to size_t 
    int colon = -1;
    for(int i=0; i< lineLength; i++){ 
        if(line[i] == ':'){
            colon = i; //colon located
            break;
        }
    }
    
    //if(colon!=-1){//if colon exists/was found...basically
    if(colon >-1){ // if the collon was located 
        if(colon >=2 && colon +2 < lineLength){ //colon contains teh time (2 char to left and 2 chars to right)
        //hours = two characetrs before colon
        hours = (line[colon-2]-'0')*10 + (line[colon-1] - '0'); //'0' extracts them as CHARACTERS 
        //minutes = two characters after colon
        minutes = (line[colon+1]-'0')*10 + (line[colon+2]-'0');
        //we dont have a seconds value
        isValid = true;
        }
    }

    if(isValid){
       //validDataPoints +=1;
        return TimeCode(hours, minutes, 0);
    }
    else{
        return TimeCode(0,0,0);
    }
    
    
}



int main(){
    unsigned int hr;
    unsigned int min;
    unsigned int sec;
    string csvFileName = "Space_Corrected.csv"; //used beginning of this article to understand how to read in csv https://medium.com/@ryan_forrester_/reading-csv-files-in-c-how-to-guide-35030eb378ad

    ifstream csvFileOBJ(csvFileName); //opens
    //insert error here if that doesnt work?

    //ignore first line 
    string line1;
    getline(csvFileOBJ, line1);
    vector<string> lines;
    string line = "";
    while(getline(csvFileOBJ, line)){
        lines.push_back(line);
    }
    csvFileOBJ.close();



    //make a vector of all of the timecodes
    vector<TimeCode> timeCodes;
    for(const string& line:lines){
        bool isValid =false; //only wnana count the valid ones
        TimeCode t = parse_line(line, isValid); //only coiunt valid ones 
        if(isValid == true){
            //cout << timeCodes.ToString()<< endl;
            timeCodes.push_back(t);
        }
    }
    //add all of the timecodes in the vector 
    TimeCode sumOfTimeCodes(0,0,0); //start w/ all zeros
    for(const TimeCode& t:timeCodes){//all of the t (timecodes) in vector timeCodes
        sumOfTimeCodes = sumOfTimeCodes+t;
    }
    sumOfTimeCodes.GetComponents(hr, min,sec);
    unsigned long long totalSeconds = TimeCode::ComponentsToSeconds(hr, min, sec);
    //need average data points too
    cout << timeCodes.size() << " data points." << endl; //should only count valid ones now 
    //divide by the number of timecodes
    //unsigned long long average =0; //need to make a timecode object still?
    unsigned long long average = totalSeconds/timeCodes.size(); 
    unsigned int hours = average/3600;
    unsigned int minutes = (average%3600)/60;
    unsigned int seconds = average%60;
    TimeCode averageTimeCode(hours, minutes, seconds);
    
    cout << "AVERAGE: " << averageTimeCode.ToString() << endl;


return 0;
}