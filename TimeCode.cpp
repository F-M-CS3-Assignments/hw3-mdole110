#include <iostream>
using namespace std;

#include "TimeCode.h"

/* accept variable input... 
throw exception if signed...
then convert to unsigned */

///NOTE: READ ALL THREE NOTES AT THE BEGINNING OF ASSIGNMENT 3 PART 2

TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec){
    
    //test inputs 
    //convert the extra seconds to minutes
   /*
    while(sec >=60){
        min++;
        sec = sec-60;
    }
    //conv extra mins to hr 
    while(min >= 60){
        hr++;
        min = min-60;
    }
    //t is the total seconds (3600 s in hr, 60 s in min, and then j s)
    t = hr*3600 + min*60 + sec;
    //cout << "t: " << t;
    */
   t=ComponentsToSeconds(hr, min, sec);
}
//copy constructor 
TimeCode::TimeCode(const TimeCode& tc){
    t = tc.t;
}

void TimeCode::SetHours(unsigned int hours){ //hours != hr!!? how to chnage hr then? //JUST CHANGED THE T -- ALL THAT MATTERS 
//make sure hours is within range 
    if(hours>0){
        //revise t to include new hours
        //need to call min and sec functions to be able to use them here
        unsigned int min = GetMinutes();
        unsigned int sec = GetSeconds();
        t = hours*3600 + min*60 + sec;
    }
    else{
         throw invalid_argument("Current INVALID hours input. Hours value must be positive. Inputted value was: "  + to_string(hours));
    }
}
//same idea for sec and mins for those sets 
void TimeCode::SetMinutes(unsigned int minutes){
//make sure hours is within range 
    if(minutes>0 && minutes<60){
        //revise t to include new mins
        //need to call hr and sec functions to be able to use them here
        unsigned int hr = GetHours();
        unsigned int sec = GetSeconds();
        t = hr*3600 + minutes*60 + sec;
       
    }
    else{
         throw invalid_argument("Current INVALID minutes input. Minutes value must be between 0-59. Inputted value was: " + to_string(minutes));
    }
}
void TimeCode::SetSeconds(unsigned int seconds){
//make sure hours is within range 
    if(seconds>0 && seconds<60){
        //revise t to include new mins
        //need to call hr and sec functions to be able to use them here
        unsigned int hr = GetHours();
        unsigned int min = GetMinutes();
        t = hr*3600 + min*60 + seconds;
       
    }
    else{
         throw invalid_argument("Current INVALID seconds input. Seconds value must be between 0-59. Inputted value was:" + to_string(seconds));
    }
}
void TimeCode::reset(){
    t=0;
    
}; //fill in!! what does it do??

void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const{
    //t doesnt need to be passed as parameter?
    hr = t/3600;
    //remainder that is divisble by 60 is mins
    min = (t%3600)/60; 
    //remainder is sec 
    sec = t%60; // or t%60?

}
long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec){
    //static method..dont need TimeCode::
    
    //t undefined in method
    return hr*3600 + min*60+sec;
}


// Get methods //need get components?
unsigned int TimeCode::GetHours() const{
    //use GetComponents for subsequent times u need to seperate components
    unsigned int hr;
    unsigned int min;
    unsigned int sec;
    GetComponents(hr, min, sec);
    return hr;
}
unsigned int TimeCode::GetMinutes() const{
    unsigned int hr;
    unsigned int min;
    unsigned int sec;
    GetComponents(hr, min, sec);
    return min;
}
unsigned int TimeCode::GetSeconds() const{
    unsigned int hr;
    unsigned int min;
    unsigned int sec;
    GetComponents(hr, min, sec);
    return sec;
}
// form the actual time code output
string TimeCode::ToString() const{
    unsigned int hr;
    unsigned int min;
    unsigned int sec;
    GetComponents(hr, min, sec);
    string String = to_string(hr)+":" + to_string(min) + ":" + to_string(sec); //geeksforgeeks for converting int to strings :  https://www.geeksforgeeks.org/converting-number-to-string-in-cpp/
    return String;
    //cout << String;
}

//math
TimeCode TimeCode::operator+(const TimeCode& other) const{
    //plan - conv to total seconds and then again get components?
    //tc1 is just there?
    unsigned int hr1;
    unsigned int min1;
    unsigned int sec1;
    unsigned int hr2;
    unsigned int min2;
    unsigned int sec2;
    GetComponents(hr1, min1, sec1);
    unsigned long long totalTC1 = ComponentsToSeconds(hr1, min1, sec1);
    other.GetComponents(hr2, min2, sec2);
    unsigned long long totalTC2 = ComponentsToSeconds(hr2, min2, sec2);
    //now have total secs, add all
    unsigned long long newTC = totalTC1 + totalTC2;
    //now convert new TC to time code (get components) -- canr use getcomponents bc needs to parameters, convert manually
    unsigned int newhr;
    unsigned int newmin;
    unsigned int newsec;
    newhr = newTC/3600;
    //remainder that is divisble by 60 is mins
    newmin = (newTC%3600)/60; 
    //remainder is sec 
    newsec = newTC%60; // or t%60?
    TimeCode SUMMEDTimeCode(newhr, newmin, newsec);
    return SUMMEDTimeCode;


}
TimeCode TimeCode::operator-(const TimeCode& other) const{
    unsigned int hr1;
    unsigned int min1;
    unsigned int sec1;
    unsigned int hr2;
    unsigned int min2;
    unsigned int sec2;
    GetComponents(hr1, min1, sec1);
    unsigned long long totalTC1 = ComponentsToSeconds(hr1, min1, sec1);
    other.GetComponents(hr2, min2, sec2);
    unsigned long long totalTC2 = ComponentsToSeconds(hr2, min2, sec2);
    //now have total secs, add all
    long long CHECKnewTC = totalTC1 - totalTC2;
    //now convert new TC to time code (get components) -- canr use getcomponents bc needs to parameters, convert manually
    // neeed to check for neg?
    if(CHECKnewTC<0){
        throw invalid_argument("The difference between the first and second time code is negative and therefore invalid.");
    }
    else{
    //not convert to unsigned long long
    unsigned long long newTC = CHECKnewTC;
    unsigned int newhr;
    unsigned int newmin;
    unsigned int newsec;
    newhr = newTC/3600;
    //remainder that is divisble by 60 is mins
    newmin = (newTC%3600)/60; 
    //remainder is sec 
    newsec = newTC%60; // or t%60?
    TimeCode DIFFERENCETC(newhr, newmin, newsec);
    return DIFFERENCETC;
    }

}
// mult and divide
TimeCode TimeCode::operator*(double a) const{
    //a is given?? 
    //time code to seconds, mult  by a, convert back to components
    // convert to seconds, multiply by a, and then reconvert
    // make sure a is pos
    if(a>0){    
    unsigned int hr1;
    unsigned int min1;
    unsigned int sec1;
    GetComponents(hr1, min1, sec1); //get the components each
    unsigned long long totalTC1 = ComponentsToSeconds(hr1, min1, sec1); //convert them into total seconds
    unsigned long long newTC = totalTC1*a;
    //return back out as timecode obj
    unsigned int newhr;
    unsigned int newmin;
    unsigned int newsec;
    newhr = newTC/3600;
    //remainder that is divisble by 60 is mins
    newmin = (newTC%3600)/60; 
    //remainder is sec 
    newsec = newTC%60; // or t%60?
    TimeCode MULTTC(newhr, newmin, newsec);
    return MULTTC;
}
    else if(a==0){
        TimeCode MULTTC(0,0,0);
        return MULTTC;

    }
    
    else{
        throw invalid_argument("This program cannot multiply by a negative number.");
    }


}
TimeCode TimeCode:: operator/(double a) const{
    if(a>0){
    unsigned int hr1;
    unsigned int min1;
    unsigned int sec1;
    GetComponents(hr1, min1, sec1); //get the components each
    unsigned long long totalTC1 = ComponentsToSeconds(hr1, min1, sec1); //convert them into total seconds
    unsigned long long newTC = totalTC1/a;
    //return back out as timecode obj
    unsigned int newhr;
    unsigned int newmin;
    unsigned int newsec;
    newhr = newTC/3600;
    //remainder that is divisble by 60 is mins
    newmin = (newTC%3600)/60; 
    //remainder is sec 
    newsec = newTC%60; // or t%60?
    TimeCode DIVETC(newhr, newmin, newsec);
    return DIVETC;
    }
    else if(a==0){
        TimeCode DIVETC(0,0,0);
        return DIVETC;
    }
    else{
        throw invalid_argument("This program cannot divide by a negative number.");

    }
}

// comparison methods (=,<,>)
bool TimeCode::operator == (const TimeCode& other) const{
    if(t==other.t){
        return true;
    }
    else{
        return false;
    }
}
bool TimeCode::operator != (const TimeCode& other) const{
    if(t!=other.t){
        return true;
    }
    else{
        return false;
    }
}

bool TimeCode::operator < (const TimeCode& other) const{
    
    if(t<other.t){
        return true;
    }
    else{
        return false;
    }
}
bool TimeCode::operator <= (const TimeCode& other) const{
    if(t<=other.t){
        return true;
    }
    else{
        return false;
    }
}

bool TimeCode::operator > (const TimeCode& other) const{
    if(t>other.t){
        return true;
    }
    else{
        return false;
    }
}
bool TimeCode::operator >= (const TimeCode& other) const{
    if(t>=other.t){
        return true;
    }
    else{
        return false;
    }
}