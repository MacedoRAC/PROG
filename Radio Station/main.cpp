#include<stdio.h>
#include<conio.h>
#include<algorithm>
#include "radio.h"

using namespace std;

int positionNextMusic=0;

void playlistDisplayFormatTable(string playlist_name);
listener registerUser();
void mainMenu();
void exitMenu();
void radioLogin();
void radioRegistration();
bool verifyRepeatedUsernames(string username);
void adminHome();
void userHome(listener &user);
int displayMusicsRadio();
void addNewMusic();
void removeMusicRadio();
void editMusic();
void resetPlaylist();
void displayTopTen(listener &user);
void searchMusic(listener &user);
int  displayMusics(listener &user);
void displayPlaylist(listener &user);
void changePLaylist(listener &user);
void addMusic(listener &user);
void removeMusic(listener &user);
void rateMusic(listener &user);
music nextMusic();
void play(listener &user);


fstream radioTrackList;
radio radioStation;



int main()
{
	
	string readLine;
	music musicFromFile;
	vector<music> musics;
	vector<int> idMusics;

	//exports list of musics from file to radio playlist
	radioStation.savePlaylistInVector();
	//exports top ten to the vector
	radioStation.saveTopTenInVector();
	//saves the users of the radio in the vector
	radioStation.saveUsersInVector();

	mainMenu();
	
	


}

//-------------------------------------------------- table format to show a playlist--------------------------------------------------------
void playlistDisplayFormatTable(string playlist_name){
	cout << setw(40) << playlist_name << endl
		<< "___________________________________________________________________________\n"
		<< setw(3) << "Id" << " |" << setw(8) << "Title" << " |" << setw(8) << "Artist" << "  |"
		<< setw(8) << "Author" << " |" << setw(8) << "Album" << " |" << setw(5) << "Genre" 
		<< " |" << setw(3) << "Year" <<  " |" << setw(3) << "Likes" <<" |" << setw(3) <<"Dislikes" <<  endl
		<< "____|_________|__________|_________|_________|______|_____|______|_________\n";
}

//-------------------------------------------------- main menu of the application -----------------------------------------------------------
void mainMenu(){

	system("CLS");

	listener user;
	ifstream iradioTrackList;
	char choice;


	iradioTrackList.open("radioStationMusics.csv");
	if(!iradioTrackList.good()) //verifies if the file "radioStationMusics.csv" already exixts
	{
		ofstream radioTrackList;						    //if it does not exist 
		radioTrackList.open("radioStationMusics.csv");		//creates a new file "radioStationMusics.csv" with the intial conditions
		radioTrackList << "TrackID,TrackTitle, Artist, Author, Album, MusicGenre, Year, Likes, Dislikes, Availability, Times Played";		    
		radioTrackList.close();
	}													
	iradioTrackList.close();

	//verifies if the file topten exists,if it doesnt creates a new file
	ifstream topTenFile;
	topTenFile.open("topTen.csv");
	if(!topTenFile.is_open())
		{ //if file doesnt exist creates a new file
			ofstream newTopTenFile;
			newTopTenFile.open("topTen.csv");
			newTopTenFile << "Id";
			newTopTenFile.close();
	}
	topTenFile.close();

	//radioStation.saveUsersInVector();

	cout <<"\n\n		You are now listening to T2G08 Radio\n";
	cout <<"	 with your favorite brodcasters Liliana and Macedo\n\n";


	cout << "[L]ogin\n"
		<<"[R]egister\n"
		<<"[E]xit\n\n";

	do
	{
		cout << "What do you want to do? ";
		cin >> choice;
		choice= toupper(choice);


	}while(choice != 'L' && choice != 'R' && choice != 'E');


	switch(choice)
	{
	case 'L': radioLogin();break;
	case 'R': radioRegistration();break;
	case 'E': exitMenu();break;
	}
}

//-------------------------------------------------- shows goodbye message to the user-------------------------------------------------------
void exitMenu()
{
	system("CLS");
	cout << "\n\n    Thanks for listening to T2G08 Radio\n    Goodbye!\n";
	_getch();
}

//-------------------------------------------------------------------------------------------------------------------------------------------
void radioLogin()
{
	bool sucess;
	listener user;


	sucess=radioStation.login(user);


	system("CLS");
	if(!sucess)
	{
		cout <<endl <<"Invalid information,please try again...";
		_getch();
		mainMenu();
		return;
	}
	
		
	if(user.getListenerName()=="ADMIN"){
		adminHome();
		return;
	}
	else
	{
		if(user.getWinnerFlag() == 1)
		{
			system("CLS");
			cout << "Congratulations,you are the last winner of our prize!\n";
			user.clearWinnerFlag();
			radioStation.modifyUserFromFile(user);
			_getch();
		}
		userHome(user);
	}

}

//--------------------------------------------------- registration of a new listener ---------------------------------------------------------
void radioRegistration()
{
	bool sucess;
	listener user;
	system("CLS");

	sucess=radioStation.registerUser(user);

	if(!sucess)
		{
			_getch();
			mainMenu();
			return;
	}

	cout << "welcome " << user.getListenerName()<<endl;
	_getch();
	userHome(user);

}


//============================================================================================================================================
//                                                         ADMIN MENU
//============================================================================================================================================
void adminHome(){

	system("CLS");
	string choice;

	cout << "1- Display radio playlist\n"
		 << "2- Add New Music\n"
		 << "3- Remove Music\n"
		 << "4- Edit Music\n"
		 << "5- Reset Playlist\n"
		 << "6- Select winner\n"
		 << "7- Remove User\n"
		 << "8- Exit\n\n";
		 
	do{
		cin.clear(1000,"\n");
		cout << "Option: ";
		cin >> choice;
	}while(choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6" && choice != "7" && choice != "8");

	int intChoice;

	intChoice = stoi(choice);

	
	listener user;

	switch(intChoice)
	{
	case 1:
		displayMusicsRadio();
		_getch();
		adminHome();
		break;
	case 2:
		addNewMusic();break;
	case 3:
		removeMusicRadio();break;
	case 4:
		editMusic();break;
	case 5:
		resetPlaylist();break;
	case 6:
		radioStation.selectAward();
		adminHome();
		break;
	case 7:
		radioStation.choseUser(user);
		radioStation.removeUserFromFile(user);
		adminHome();
	case 8:
		mainMenu();
		break;
	}
}

//---------------------------------- shows all the musics int he radio.and returns the number of musics --------------------------------------
int displayMusicsRadio(){
	
	int numberMusics;
	string readLine;
	music m;

	ifstream radioTrackList;
	radioTrackList.open("radioStationMusics.csv");
	system("CLS");

	numberMusics=0;

	getline(radioTrackList,readLine);//extracts first line from file

	while(radioTrackList.good())
	{
		radioTrackList >> m;
		cout << m <<endl;
		numberMusics++;//counts the number of musics
	}
	
	radioTrackList.close();
	return numberMusics;
}

//----------------------------------------------- adds the music to radio playlist -----------------------------------------------------------
void addNewMusic(){
	system("CLS");
	
	music newMusic;//stores the music entered by admin
	unsigned int numberOfMusics; //number of musics in the radioplaylist
	vector<music> musics; //saves the radio playlist
	
	musics=radioStation.getRadioPlaylist();  
	numberOfMusics=musics.size();//is used to know the ID of the last music on Playlist
	numberOfMusics++; //id number of the music that will be added

	ifstream iradioTrackList;
	
	string readLine;
	int nextID=0;
	music oldMusic;
	bool equalID=true;
	
	while(equalID)
	{
		equalID=false;
		nextID++;
		iradioTrackList.open("radioStationMusics.csv");
		getline(radioTrackList,readLine);

		while(iradioTrackList.good())
		{
			iradioTrackList >> oldMusic;
			if(oldMusic.getID() == nextID)
				equalID=true;
		}
		iradioTrackList.close();
	}

	
	cout << "To add a new music you must follow the next standard. You also must use the ID number provided( " << nextID << " )\n\n"
		<< nextID << ",title,artist,author,album,music genre,year,likes,dislikes,availability,times played\n";
	do
	{
		cin.ignore();
		cin >> newMusic;
	}while(cin.fail());


	musics.push_back(newMusic); //inserts new music to the vector musics
	radioStation.setRadioPlaylist(musics);//that will 

	ofstream radioTrackList("radioStationMusics.csv", ios::app); //ios::app,output operations in the end of file
	radioTrackList << newMusic;//stores the new music int the file
	radioTrackList.close();

	radioStation.updateTopTen(newMusic); //updates the file and the vector top ten

	system("CLS");
	cout << "Music added sucessufully!\n Press any key to go back";

	_getch();
	adminHome();//returns to the menu of admin

}

//----------------------------------------------- removes music from radioStation ------------------------------------------------------------
void removeMusicRadio(){


	string readLine;
	music m;
	int choice;
	int numberMusics;

	ifstream radioTrackList;

	numberMusics=displayMusicsRadio();//displays all the musics and return the total of musics in the radio

	do
	{
		cout<< "Id of the music you want to remove(0 to quit): ";
		cin>>choice;
	}while(choice <0 || choice > numberMusics ||cin.fail());

	if(choice ==0)//if user wants to quit
	{
		adminHome();
		return;
	}

	//removes the music from the file "radioStationMusics.csv"
	radioStation.removeMusicFromFile(choice);

	vector<listener> radioListeners;
	radioListeners=radioStation.getlisteners();

	//removes the music id in the all the user files
	for(unsigned int i=0;i< radioListeners.size();i++)
		radioStation.removeMusicIdFromFile(radioListeners[i].getNameFile(),choice);
	
	//removes the music if from top ten
	radioStation.removeMusicIdFromFile("topTen.csv",choice);

	radioStation.savePlaylistInVector();

	adminHome();
}

//----------------------------------------------- edits music informations -------------------------------------------------------------------
void editMusic(){
	
	int choice;
	string strChoice;
	int ID; //id number chosen by the admin
	string readLine;
	music m;
	system("CLS");

	displayMusicsRadio();

	int i;//number of musics in the file
	vector<music> musics;//saves the radio playlist

	musics=radioStation.getRadioPlaylist();
	i=musics.size();


	
	do
	{
		cout << "\n\n\nChoose the ID of the music you wish to edit: ";
		cin >> ID;
	}while(ID<1 || ID > i || cin.fail());


	music selectedMusic;

	selectedMusic = returnTrack(musics,ID);
	system("CLS");
	cout <<"1-Title\n2-Artist\n3-Author\n4-Album\n5-Music Genre\n6-Year\n7-Likes\n8-Dislikes\n9-Availability\n10-Exit\n\n"
		<< "What do you want to change?\n";
	do
	{
		cin >> strChoice;
	}while(strChoice != "1" && strChoice != "2" && strChoice != "3" && strChoice != "4" && strChoice != "5" &&
		   strChoice != "6" && strChoice != "7" && strChoice != "8" && strChoice != "9" && strChoice != "10");

	choice = stoi(strChoice);//converts to integer

	string newInfo;
	int newInt;

	system("CLS");

	switch(choice)
	{
	case 1://changes the title of the music according with admin input
		cout << "New name? ";
		cin.ignore();
		cin.clear(1000,"\n");
		getline(cin,newInfo);
		selectedMusic.setTitle(newInfo);
		break;
	case 2://changes the name of the artist according with admin input
		cout << "New Artist? ";
		cin.ignore();
		cin.clear(1000,"\n");
		getline(cin,newInfo);
		selectedMusic.setArtist(newInfo);
		break;
	case 3://changes the name of the author according with admin input
		cout << "New Author? ";
		cin.ignore();
		cin.clear(1000,"\n");
		getline(cin,newInfo);
		selectedMusic.setAuthor(newInfo);
		break;
	case 4://changes the name of the album according with admin input
		cout << "New Album? ";
		cin.ignore();
		cin.clear(1000,"\n");
		getline(cin,newInfo);
		selectedMusic.setAlbum(newInfo);
		break;
	case 5://changes the music genre according with admin input
		cout << "New Music Genre? ";
		cin.ignore();
		cin.clear(1000,"\n");
		getline(cin,newInfo);
		selectedMusic.setMusic_genre(newInfo);
		break;
	case 6://changes the year of the music according with admin input
		cout << "New Year? ";
		cin >> newInt;
		selectedMusic.setYear(newInt);
		break;
	case 7:
		cout <<"Number of likes? ";
		cin >> newInt;
		selectedMusic.setLikes(newInt);
		radioStation.updateTopTen(selectedMusic);
		break;
	case 8:
		cout <<"Number dislikes? ";
		cin >> newInt;
		selectedMusic.setDislikes(newInt);
		radioStation.updateTopTen(selectedMusic);
		break;
	case 9://changes the availability of the music
		selectedMusic.changeAvailability();
		cout << "Availability Changed";
		break;
	case 10:
		adminHome();return;
		break;
	}

	//stores music in the vector
	musics[ID-1]=selectedMusic;

	
	//stores music in the file
	radioStation.modifyMusicFromFile(selectedMusic);

	//saves the modified music int the vector
	radioStation.savePlaylistInVector();
	_getch();
	editMusic();
}

//------------------------------------------ shuffles the musics in the vector playlist -------------------------------------------------------
void resetPlaylist(){

	int sizeVector;
	vector<music> musicsRadio;
	int intChoice;
	string choice;

	system("CLS");
	musicsRadio=radioStation.getRadioPlaylist();//exports the radioplaylist from the vector
	sizeVector=musicsRadio.size(); //number of musics
	

	for(int i=0; i<sizeVector; i++)//shows the previous sequence
		cout << musicsRadio[i] << endl;

	cout << endl << "1-Shuffle Playlist\n" << "2-Exit\n";
	do{
		cout << "Option: "; cin >> choice;
	}while(choice!="1" && choice !="2");

	intChoice=stoi(choice);

	if(intChoice==1){
		system("CLS");
		random_shuffle(musicsRadio.begin(),musicsRadio.end()); //suffles the musics
		radioStation.setRadioPlaylist(musicsRadio);
		for(int i=0; i<sizeVector; i++)//shows the new sequence
			cout << musicsRadio[i] << endl;
	}

	positionNextMusic=0; //starts the list of musics to play in the first music of the vector

	_getch();
	adminHome();

}



//============================================================================================================================================
//                                                         LISTENER MENU
//============================================================================================================================================
void userHome(listener &user){

	string strChoice;
	int choice;
	system("CLS");

	cout <<"1- Radio top ten\n"
		<<"2- Search Music\n"
		<<"3- See playlist\n"
		<<"4- Add/Remove music\n"
		<<"5- Like/Dislike music\n"
		<<"6- Play music\n"
		<<"7- Exit\n";

	do
	{
		cout <<"Choice: ";
		cin >> strChoice;
	}while(strChoice != "1" && strChoice != "2" && strChoice != "3" && strChoice != "4" && strChoice != "5" && strChoice != "6" && strChoice != "7");


	choice = stoi(strChoice);//converts to integer

	switch(choice)
	{
	case 1: displayTopTen(user);break;
	case 2: searchMusic(user);break;
	case 3: 
		displayMusics(user);//displays the musics from the user
		_getch();
		userHome(user);
		break;
	case 4: changePLaylist(user);break;
	case 5: rateMusic(user);break;
	case 6: play(user);
	case 7: mainMenu();break;
	}
}

//-------------------------------------- display radio top ten -------------------------------------------------------------------------------
void displayTopTen(listener &user){

	string readLine;
	vector<music> musicsRadio;
	music m;
	int id;
	ifstream topTen;
	topTen.open("topTen.csv");

	musicsRadio=radioStation.getRadioPlaylist();

	system("CLS");
	getline(topTen,readLine);

	playlistDisplayFormatTable("TopTen");
	while(topTen.good())
	{
		topTen >> id;
		m=returnTrack(musicsRadio,id);
		m.displayMusic();
	}
	topTen.close();
	_getch();
	userHome(user);
}

//--------------------------------------- searchs musics -------------------------------------------------------------------------------------
void searchMusic(listener &user){

	vector<music> radioMusics;
	music m;
	string keyword;
	radioMusics=radioStation.getRadioPlaylist();

	system("CLS");

	cout << "Welcome to our search engine. Here you can find anything!\n\n"
		<< "Keyword(title, artist, album, author, year or music genre): "; cin >> keyword;
	cout << endl << endl;
	
	playlistDisplayFormatTable("Musics found");
	for(unsigned int i=0;i < radioMusics.size();i++)
	{
		m=radioMusics[i];
		if(m.getTitle()== keyword || m.getArtist()== keyword || m.getYear()==stoi(keyword) || m.getMusic_genre()== keyword)
			m.displayMusic();
	}
	_getch();

	userHome(user);

}

//------------------------------- display the user musics and returns the number of music----------------------------------------------------- 
int  displayMusics(listener &user){

	system("CLS");

	vector<music> radioMusics;
	music musicFromUser;
	int musicID;
	string userNameFile;
	string readLine;
	int numberMusics=0;

	userNameFile= user.getNameFile(); //saves the name of the file that contains the user musics
	radioMusics=radioStation.getRadioPlaylist(); //saves the vector with the id of the user musics

	ifstream userMusics;
	userMusics.open(userNameFile.c_str());
	getline(userMusics,readLine); //Extracts "ID"


	

	playlistDisplayFormatTable("Musics");

	while(userMusics.good())
	{
		userMusics >> musicID; //extracts the id of the musics
		numberMusics++; //counts the number of musics
		musicFromUser=returnTrack(radioMusics,musicID); //returns the music that has id=musicID
		//cout << musicFromUser<< endl; //shows that music
		musicFromUser.displayMusic();
	}

	if(numberMusics==0)//if file is empty numberMusics wont be increased
		{
			cout <<"Empty\n";
			userMusics.close();
			return numberMusics;
	}

	userMusics.close();
	return numberMusics;//returns the number of musics
}

//------------------------------------------------ menu to add/remove musics -----------------------------------------------------------------
void changePLaylist(listener &user){

	int choice;
	string strChoice;
	system("CLS");

	cout <<"1- Add music to playlist\n"
		 <<"2- Remove music from playlist\n"
		 <<"3- Exit\n";
		 
	do
	{
		cout <<"Chose: ";
		cin.clear(1000,"\n");
		cin >> strChoice;
	}while(strChoice != "1" && strChoice != "2" && strChoice != "3");

	choice = stoi(strChoice);//converts to integer

	switch(choice)
	{
	case 1: addMusic(user);break;
	case 2: removeMusic(user);break;
	case 3: userHome(user);break;
	}
}

//-------------------------------------------- adds musics to listener's playlist ------------------------------------------------------------
void addMusic(listener &user){

	int numberMusics=0;
	music m;
	string readLine;
	int musicId;
	
	ifstream radioTrackList("radioStationMusics.csv");
	getline(radioTrackList,readLine);

	//shows all musics from file
	playlistDisplayFormatTable("Musics");

	while(radioTrackList.good())
	{
		radioTrackList >> m;
		m.displayMusic();
		numberMusics++;//counts the number of musics
	}

	radioTrackList.close();

	
	do
	{
		cout << "\nChose the id of the music you wish to add to your playlist ( press 0 to go back)\n";
		cin >> musicId;
	}while(musicId <0 || cin.fail());

	//saves the new music(only the id) in the user playlist
	vector<int> listenerMusics;
	listenerMusics=user.getListenerPlaylist();//extracts the user playlist
	listenerMusics.push_back(musicId);//inserts the new "music"(only the id)
	user.setListenerPlaylist(listenerMusics);//saves the new playlist


	user.storeMusic(musicId);//saves the new music in the user file
	userHome(user);
	return;
	}

//-------------------------------------------- removes music from listener's playlist --------------------------------------------------------
void removeMusic(listener &user){

	int numberMusics;
	int musicID;
	int choice;
	string nameFile;
	string readLine;
	ifstream userMusics;
	nameFile=user.getNameFile();

	//shows all the musics in the user playlist
	numberMusics=displayMusics(user);//and return the number of musics
	
	if(numberMusics==0)
	{
		cout<<"There are no musics to remove";
		_getch();
		return userHome(user);
	}


	
	do
	{
		cout <<"ID of the music you want to remove(0 to quit): ";
		cin >> choice;
	}while(choice <0  || cin.fail());

	if(choice ==0) //user wants to go back
	{
		userHome(user);
		return;
	}

	userMusics.open(nameFile.c_str());
	ofstream temp;
	vector<int> musics;
	temp.open("temp.csv");

	getline(userMusics,readLine);//extracts the first line
	temp << readLine;//and saves it in the temp file

	while(userMusics.good())
	{
		userMusics >> musicID;
		if(musicID != choice)	//saves the id in the file and in the vector
		{						//if it is not the music that the user wants to remove
			temp << musicID;
			musics.push_back(musicID);
		}
	}
	userMusics.close();
	temp.close();

	//updates user playlist
	user.setListenerPlaylist(musics);

	//changes the name of the files
	remove(nameFile.c_str());
	rename("temp.csv",nameFile.c_str());


	_getch();

	userHome(user);
	return;
	
	}

//-------------------------------------------- like/dislike a music --------------------------------------------------------------------------
void rateMusic(listener &user){

	int choice;
	string strChoice;

	system("CLS");

	cout <<"1- Like\n"
		 <<"2- Dislike\n"
		 <<"3- Exit\n";
		 

	do
	{
		cout <<"Chose: ";
		cin>> strChoice;
	}while(strChoice != "1" && strChoice != "2" && strChoice != "3");

	choice =stoi(strChoice);//converst to integer

	int numberMusics;
	int id;
	music oldMusic;
	string readLine;
	
	//shows all the musics in the user file
	numberMusics=displayMusics(user);//and returns the number of musics

	

	do
	{
		cout <<"ID of the song you like(0 to quit): ";
		cin >> id;
	}while(id <0 || id > numberMusics || cin.fail());

	ifstream radioTrackList("radioStationMusics.csv");
	ofstream temp;
	temp.open("temp.csv");

	getline(radioTrackList,readLine);//extracts first line
	temp << readLine;				 //and saves it in the temp file
	
	music selectedMusic;

	while(radioTrackList.good())//while file still has information
	{
		radioTrackList >> oldMusic; //extracts the music
		if(oldMusic.getID()==id) //if it is the music that the user likes
			if(choice==1)
				{
					oldMusic.like();	   //adds a like to that music
					selectedMusic=oldMusic;
			}
			else
				oldMusic.dislike();	   //adds a dislike to the music
		temp << oldMusic;		   //then saves the music in the temp file
		radioStation.updateTopTen(oldMusic);
	}

	radioTrackList.close();
	temp.close();

	music m;

	vector<music> radioMusics;
	radioMusics=radioStation.getRadioPlaylist();

	for(unsigned int i=0;i < radioMusics.size();i++)
	{
		m=radioMusics[i];
		if(m.getID()==id)
			radioMusics[i]= selectedMusic;
	}

	radioStation.setRadioPlaylist(radioMusics);


	//changes the name of the files
	remove("radioStationMusics.csv");
	rename("temp.csv","radioStationMusics.csv");
	userHome(user);
}

//--------------------------------------------------------------------------------------------------------------------------------------------
music nextMusic(){

	vector<music> radioMusics;
	music nextMusic;
	radioMusics=radioStation.getRadioPlaylist();
	nextMusic=radioMusics[positionNextMusic];

	if(positionNextMusic == radioMusics.size()-1)
		positionNextMusic=0;
	else
		positionNextMusic++;

	return nextMusic;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void play(listener &user){

	system("CLS");
	string readLine;
	bool play; // false if music is unavailable
	music musicToPlay;
	vector<music> radioMusics;
	radioMusics=radioStation.getRadioPlaylist();
	unsigned int numberMusics=0;

	do{

		musicToPlay=nextMusic();
		if(musicToPlay.getAvailability()== 'U' || musicToPlay.getAvailability()== 'u')
			play=false;
		else
			play=true;
		numberMusics++;
	}while(!play && numberMusics < radioMusics.size()); //if music is unvailable searchs the next one
														// the condition numberMusics < radioMusics.size() is important if all the musics are not available
	if(!play)
	{
		cout << "Sorry,there are no musics available to play...\n";
		_getch();
		userHome(user);
		return;  
	}


	musicToPlay.Play(); //adds 1 to times played

	cout << "Music playing: \n" ;
	musicToPlay.displayMusic();

	ifstream radioTRackList;
	ofstream temp;
	radioTrackList.open("radioStationMusics.csv");
	temp.open("temp.csv");
	getline(radioTrackList,readLine);

	music m;
	while(radioTrackList.good())
	{
		radioTrackList >> m;
		if(m.getID()== musicToPlay.getID())
			temp << musicToPlay;
		else
			temp << m;
	}

	radioTrackList.close();
	temp.close();

	remove("radioStationMusics.csv");
	rename("temp.csv","radioStationMusics.csv");
	_getch();
	userHome(user);
}