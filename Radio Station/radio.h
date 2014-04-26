#ifndef RADIO_H
#define RADIO_H

/*#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<fstream>
#include<sstream>*/
#include<cctype>
#include<conio.h>
#include"listener.h"

using namespace std;


class radio{
	friend void editMusic();
public:
	radio();
	radio(string radio_name, vector<music> radio_Playlist, vector<int> top_Ten,
		vector<listener> radio_listeners);
	void setName(string name);                            //changes the name of the radio
	void setRadioPlaylist(vector<music> radioPlaylist);   //changes the musics played on radio
	void setTopTen(vector<int> topTen);                 //changes the musics' topten played on radio 
	void setListeners(vector<listener> listeners);        //changes the list of listeners 
	string getName();                                     //returns the name of the radio
	vector<music> getRadioPlaylist();                     //returns the musics played on radio
	vector<int> getTopTen();                            //returns the musics' topten played on radio 
	vector<listener> getlisteners();                      //returns the list of listeners
	bool registerUser(listener &user);
	bool login(listener &user);
	bool updateTopTen(music &m);
	void saveTopTenInVector();
	void savePlaylistInVector();
	void saveUsersInVector();
	void storeUserPlaylist(listener &user);
	bool verifyRepeatedUsernames(string username);
	void selectAward();
	void modifyUserFromFile(listener &user);
	void modifyMusicFromFile(music m);
	void removeMusicIdFromFile(string nameFile,int id);
	void removeUserFromFile(listener &user);
	void removeMusicFromFile(int id);
	void choseUser(listener &user);
	void initializeTopTen();
	
private:
	string radioName;
	vector<music> radioPlaylist;
	vector<int> topTen;
	vector<listener> listeners;

};

music returnTrack(vector<music> playlist , int ID);



#endif 