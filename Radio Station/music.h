#ifndef MUSIC_H

#define MUSIC_H

#include<iomanip>
#include<iostream>
#include <string>
#include <vector>
#include<sstream>
#include<fstream>
using namespace std;

class music{
	
public:
	friend ostream& operator<<(ostream& out,music& m);
	friend istream& operator>> (istream& in,music &m);
	//constructors:
	music();
	music(int ident_num, string title_song,string artist_song,string author,
			string album_song,string music_genre_song,int year_song,int likes_song,int dislikes_song);
	void setID(int number);				//changes the id number of the song
	void setTitle(string name);			//changes the title of the song
	void setArtist(string name);		//changes the name of the artist
	void setAuthor(string name);//changes the name of the author
	void setAlbum(string name);			//changes the name of the album 
	void setMusic_genre(string name);	//changes the music_genre of the song
	void setYear(int y);				//changes the year of the song
	void setLikes(int l);				//changes the number of likes
	void setDislikes(int d);			//changes the number of dislikes of the song
	void setAvailability(char availabilityNew);
	void setTimesPlayed(int timesPlayedNew);
	void like();						//adds a like to the song
	void dislike();						//adds a dislike to the song
	void changeAvailability();
	void Play();
	void showTrackInformation();        //show track information (id, title, artist, album, author, music genre)
	int getID();						//returns the id of the song
	string getTitle();					//returns the title of the song
	string getArtist();					//returns the artist of the song
	string getAuthor();			//returns the author of the song
	string getAlbum();					//returns the album of the song
	string getMusic_genre();			//returns the music_genre of the song
	int getYear();						//returns the year when the song was made
	int getLikes();						//returns the number of likes of the song
	int getDislikes();					//returns the number of dislikes of the song
	char getAvailability();
	int getNumberTimesPlayed();
	void displayMusic();
private:
	int id;
	string title;
	string artist;
	string author;
	string album;
	string music_genre;
	int year;
	int likes;
	int dislikes;
	char availability;
	int timesPlayed;
};

bool operator==(music musicRight,music musicLeft);
#endif // !MUSIC_H