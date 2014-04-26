#ifndef LISTENER_H
#define LISTENER_H

/*#include<string>
#include<vector>
#include<fstream>
#include<sstream>*/
#include"music.h"


using namespace std;


class listener{
	friend ostream& operator<< (ostream& out,listener &user);
	friend istream& operator>> (istream& in,listener &user);
public:
	listener();
	listener(int iden_num,string name, int age, char gender, vector<int> playlist);
	void setID(int iden_num);
	void setListenerName(string name);                      //changes the Listener name
	void setListenerAge(int age);                           //changes the listener age
	void setListenerGender(char gender);                    //changes the listener gender
	void setListenerPlaylist(vector<int> playlist);       //changes the listener playlist
	void setWinnerFlag();
	void clearWinnerFlag();
	void addMusic(int idMusic);                                 //add a music to listener's playlist
	int getListenerID();
	string getListenerName();                               //returns the listener name
	int getListenerAge();                                   //returns the listener age
	char getListenerGender();                               //returns the listener gender
	int getWinnerFlag();
	string getNameFile();
	vector<int> getListenerPlaylist();                    //returns the listener playlist 
	void setNameFile();										//creates the name of the file according with the id number
	bool listener::storeMusic(int idMusic);					//saves the music in the file
private:
	string nameFile;
	int id;
	string listenerName;
	int listenerAge;
	char listenerGender;
	vector<int> listenerPlaylist;
	int winner;//0-if false;1-if true
};

	
#endif
