#include "main.h"
#include ".\include\glut.h"	
#include <sstream>
#include <string> //Header class for a string

using namespace std;

//Class for the game time
class MTimer
{
	int mins;  //Variable to store minutes remaining
	int secs;  //Variable to store seconds remaining
	
	//Make the following code public
public:
	
	//Timer class constructor, initializes the variables minutes and seconds to ones provided
	MTimer(int mins, int secs){this->mins = mins; this->secs = secs;}
	
	//Method to set the amount of minutes remaining
	void setMins(int newmins){
		mins = mins + newmins;
	}

	//Method to set the amount of seconds remaining
	void setSecs(int newsecs){
		secs = secs + newsecs;
		//Checks to see if the seconds remaining exceeds 59
		while (secs > 59){
			secs = secs - 60;
			mins++;
		}
	}

	//Method to return the remaining minutes
	int getMins(){
		return mins;
	}

	//Method to return the remaining seconds
	int getSecs(){
		return secs;
	}
};