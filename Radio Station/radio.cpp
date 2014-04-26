#include"radio.h"


vector<int> adminPlaylist;
listener administrator(0,"ADMIN",25, 'M', adminPlaylist);

//============================================================================================================================================
//                                                    CLASS RADIO DEFINITIONS
//============================================================================================================================================

radio:: radio(){
	radioName="Unknown Radio";
	radioPlaylist;
	topTen;
	listeners;
}

radio:: radio(string radio_name, vector<music> radio_Playlist, vector<int> top_Ten,
			  vector<listener> radio_listeners){
				  radioName=radio_name;
				  radioPlaylist=radio_Playlist;
				  topTen=top_Ten;
				  listeners=radio_listeners;
}

//changes the name of the radio---------------------------------------------------------------------------------------------------------------
void radio:: setName(string name){
	radioName=name;
}

//changes the musics played on radio----------------------------------------------------------------------------------------------------------
void radio:: setRadioPlaylist(vector<music> radio_Playlist){
	radioPlaylist=radio_Playlist;
}

//changes the musics' topten played on radio--------------------------------------------------------------------------------------------------
void radio:: setTopTen(vector<int> top_Ten){
	topTen=top_Ten;
}

//changes the list of listeners --------------------------------------------------------------------------------------------------------------
void radio:: setListeners(vector<listener> radio_listener){
	listeners=radio_listener;
}

//returns the name of the radio---------------------------------------------------------------------------------------------------------------
string radio:: getName(){
	return radioName;
}

//returns the musics played on radio----------------------------------------------------------------------------------------------------------
vector<music> radio:: getRadioPlaylist(){
	return radioPlaylist;
}

//returns the musics' topten played on radio -------------------------------------------------------------------------------------------------
vector<int> radio:: getTopTen(){
	return topTen;
}

//returns the list of listeners---------------------------------------------------------------------------------------------------------------
vector<listener> radio:: getlisteners(){
	return listeners;
}

//registration process (ask and save username, age, gender of the new listener----------------------------------------------------------------
bool radio::registerUser(listener &user){
	//saves the old information from the file
	int oldId;
	string oldInfo;
	//saves the new user information
	string name;
	int age;
	char gender;
	vector<int> musicList;
	int winnerFlag;

	ifstream file;
	file.open("users.csv");
	//verifies if the file already exists
	if(!file.is_open()) //if it doesnt then creates a new file
	{					
		ofstream newFile;
		newFile.open("users.csv");
		newFile << "ID,Name,Age,Gender,WinnerFlag";
		newFile.close();
	}
	file.close();

	bool repeatedUsername;

	string readline; 

	//reads the users info
	do
	{
	system("CLS");
	cout << "Name? (\"exit\" to quit): ";
	cin.ignore();
	cin.clear(1000,"\n");
	getline(cin,name);
	

	
	//changes newName to capital letters
	for (size_t i=0; i<name.length(); ++i)
		name[i]= toupper(name[i]);

	repeatedUsername=verifyRepeatedUsernames(name); //verifies if the username is already in use

	if(repeatedUsername)
		{
			cout << " Username already in use\n";
			_getch();
	}
	else
		if(name == "ADMIN") //doesn't allow the registration of the username admin
			{
				cout << "Restricted username\n";
				_getch();
		}

	}while(repeatedUsername || name== "ADMIN");

	if(name == "EXIT")
		return false;

	do{
		cout<< "Age?(0 to quit): ";
		cin >> age;
	}while(cin.fail());

	if(age == 0)
		return false;
	do{
		cout << "Gender? (E to quit): ";
		cin >> gender;
		gender=toupper(gender);
	}while((gender != 'F' && gender != 'M' && gender != 'E') || cin.fail());

	if(gender=='E')
		return false;

	ifstream fileUsers;
	fileUsers.open("users.csv");
	ofstream temp; //temporary file that will replace the previous file
	temp.open("temp.csv");

	fileUsers >> readline;//copies the first line of the file
	temp << readline;

	

	if(fileUsers.good()) //if the file isnt empty
	{
		do{
			fileUsers >> oldId >> oldInfo >>winnerFlag;
			temp << endl<< oldId << oldInfo << winnerFlag;
		}while(fileUsers.good()); //while the file still has information
	}
	else
		oldId=0;

	//saves the new user in the file

	oldId++; //updates the id number
		
	
	//creates a new user 
	user=listener (oldId,name,age,gender,musicList);


	temp << endl << oldId << ',' << name << ','  << age << ','  << gender << ',' << user.getWinnerFlag();

	temp.close();
	fileUsers.close();



	listeners.push_back(user);

	remove("users.csv");
	rename("temp.csv","users.csv");

	return true; 
}

//--------------------------------------------------------------------------------------------------------------------------------------------
bool radio::login(listener &user){
	vector<int> newPlayList; //new vector with the old musics from the user
	int musicId; //music id that will be saved in the vector newPlayList
	string info; //string with all the user info,except the id number
	int id; //user id
	string newName; //name that 
	string name; //names from the users already registered in the radio
	string oldName;
	string readline;
	

	ifstream fileUsers;

	system("CLS");

	cout <<"Name(no spaces are allowed,\"exit\" to quit)? ";

	cin.clear(1000,"\n");
	cin >> newName;
	cin.clear(1000,"\n");

	//changes newName to capital letters
	for (size_t i=0; i<newName.length(); ++i)
		newName[i]= toupper(newName[i]);

	if(newName == "EXIT")
		return false;

	if(newName=="ADMIN")
	{
		string pass;
		do{
			cout << "Password(\"exit\" to quit): "; cin >> pass;
			for (size_t i=0; i<pass.length(); ++i)
				pass[i]= toupper(pass[i]);
			if(pass=="EXIT")//if user want to quit
				return false;
		}while(pass != "ADMIN");
		user=administrator;
		user.setListenerName("ADMIN");
		return true;
	}

	fileUsers.open("users.csv");
	getline(fileUsers,readline);

	listener newuser;

	do{	
		fileUsers >> newuser; //extracts the user from the file to compare with the name

		name=newuser.getListenerName();

		//changes name to capital letter to be compared 
		for (size_t i=0; i<name.length(); ++i)
			name[i]= toupper(name[i]);

	}while(name != newName && fileUsers.good());
	fileUsers.close();

	//if name is not in the file
	if(newName != name)
		return false;

	fstream fileMusic;
	string nameOfFile;

	//converts id from int to string
	id=newuser.getListenerID();

	ostringstream oss;
	string idStr;
	oss << id;
	idStr=oss.str();


	nameOfFile="playListUser"+ idStr + ".csv";
	fileMusic.open(nameOfFile,ios::in||ios::out); //ios::in !! ios::out -> file is used for input and output

	fileMusic << readline; //ignores first line

	//copies the user playlist to newPlayList
	while(fileMusic.good())
	{
		fileMusic >> musicId;
		newPlayList.push_back(musicId);
	}

	fileMusic.close();
	newuser.setListenerPlaylist(newPlayList);
	newuser.setNameFile();
	
	user=newuser; //copies the newuser to user,that is passed by reference

	return true;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
bool radio::updateTopTen(music &m){

	music oldMusic;
	string readLine;
	int oldId;


	int i = topTen.size()-1;

	if(topTen.size()==0) //if there were no music in the top ten
	{
		topTen.push_back(m.getID());
		ofstream radioTT;
		radioTT.open("topTen.csv",ios::app);
		radioTT << endl<<m.getID();
		radioTT.close();
		return true;
	}

	ifstream topTenFile;
	topTenFile.open("topTen.csv");
	ofstream temp;
	temp.open("temp.csv");
	getline(topTenFile,readLine);
	temp << readLine;

	int counter=0; //this counter is responsible to establish the numbers of musics
	
	do
	{
		topTenFile >> oldId; //extract the information about the 1st music
		oldMusic=returnTrack(radioPlaylist,oldId);
		if(oldMusic.getLikes()- oldMusic.getDislikes() <= m.getLikes() -m.getDislikes())
		{
			temp << endl << m.getID();
			if(counter <= 8) //else only the new music will be saved
			{
				temp << endl <<oldMusic.getID();
				counter++;
			}
			counter++;
			//saves the rest of the musics below
			while(topTenFile.good() && counter < 10)
			{
				topTenFile >> oldId;
				temp << endl <<oldId;
				counter++;
			}
		}
		else //will save the previous music that was on the file
		{
			temp << endl<< oldId;
			counter++;
		}
	}while(topTenFile.good() && counter < 10);

	temp.close();
	topTenFile.close();
	saveTopTenInVector();

	remove("topTen.csv");
	rename("temp.csv","topTen.csv");

	

return true;
}

//receive a playlist and a ID number and return a track with the respective ID----------------------------------------------------------------
music returnTrack(vector<music> playlist , int ID)
{
	unsigned int i=0;

	do
	{
		if(playlist[i].getID() == ID)
			return playlist[i];
		else
			i++;
	}while(i<playlist.size());
	return music();
}

//saves the information of "topten.csv" file in topten vector --------------------------------------------------------------------------------
void radio::saveTopTenInVector(){
	
	string readLine;
	ifstream topTenFile;
	int idFromFile;
	vector<int> idMusics;

	//copies the top ten music id from file to the vector
	topTenFile.open("topTen.csv");
	getline(topTenFile,readLine);
	while(topTenFile.good())
	{
		topTenFile >> idFromFile;
		topTen.push_back(idFromFile);
	}


	topTenFile.close();


}

//saves the information of "radioStationMusics.csv" file in radioPlaylist vector -------------------------------------------------------------
void radio::savePlaylistInVector(){
	string readLine;
	music musicFromFile;
	//vector<music> musics;

	//exports list of musics from file to radio playlist
	ifstream radioTrackList("radioStationMusics.csv");
	getline(radioTrackList,readLine);
	while(radioTrackList.good())
	{
		radioTrackList >> musicFromFile;
		radioPlaylist.push_back(musicFromFile);
	}
	radioTrackList.close();
}

//saves the information of "users.csv" file in listeners vector ------------------------------------------------------------------------------
void radio::saveUsersInVector(){

	string readLine;
	listener user;
	ifstream userFile;
	userFile.open("users.csv");

	getline(userFile,readLine);

	while(userFile.good())
	{
		userFile >> user;
		listeners.push_back(user);
	}
	userFile.close();
}

//--------------------------------------------------------------------------------------------------------------------------------------------
bool radio::verifyRepeatedUsernames(string username){

	for(unsigned int i= 0; i < listeners.size();i++)
	{
		if(listeners[i].getListenerName()== username)
			return true;
	}
	return false;
}

//selects the winner(s) of the radio prize----------------------------------------------------------------------------------------------------
void radio::selectAward(){

	int numberMusics=0;
	int oldNumberMusics=0;
	listener user;
	vector<int> playlist;
	vector<listener> winner;
	music m;

	for(unsigned int i=0; i< listeners.size(); i++)
	{
		user=listeners[i];
		storeUserPlaylist(user);
		playlist=user.getListenerPlaylist();
		
		
		for(unsigned int j=0;j< playlist.size();j++)
		{
			m = returnTrack(radioPlaylist,playlist[j]);
			for(unsigned int h=0;h< radioPlaylist.size();h++)
			{
				if(m == radioPlaylist[h] && (radioPlaylist[h].getAvailability() == 'A' || radioPlaylist[h].getAvailability() == 'a' ))
				numberMusics++;
			}
		}

		if(numberMusics == 10)
		{
			user.setWinnerFlag();
			winner.push_back(user);
		}
		else
			if(numberMusics > oldNumberMusics)
			{
				winner.clear();
				winner.push_back(user);
			}
			else
				if(numberMusics == oldNumberMusics)
				{
					winner.push_back(user);
				}

				oldNumberMusics=numberMusics;
	}


	int tam=winner.size();

	for(unsigned int z=0; z < winner.size();z++)
		{
			winner[z].setWinnerFlag();
			cout << winner[z]<< endl;
			modifyUserFromFile(winner[z]);
			
	}

	

	_getch();

}

//--------------------------------------------------------------------------------------------------------------------------------------------
void radio::modifyUserFromFile(listener &user)
{
	ifstream userFile;
	userFile.open("users.csv");
	ofstream temp;
	temp.open("temp.csv");

	string readLine;
	listener oldUser;

	getline(userFile,readLine);
	temp << readLine;

	while(userFile.good())
	{
		userFile >> oldUser;
		if(oldUser.getListenerID() == user.getListenerID())
			temp << endl<< user;
		else
			temp <<endl<<oldUser;
	}

	userFile.close();
	temp.close();

	remove("users.csv");
	rename("temp.csv","users.csv");
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void radio::removeMusicIdFromFile(string nameFile,int id)
{
	int oldId;
	string readLine;
	fstream file;
	file.open(nameFile.c_str());
	ofstream temp;
	temp.open("temp.csv");

	getline(file,readLine);
	temp << readLine;

	while(file.good())
	{
		file >> oldId;
		if(oldId != id)
			temp << endl << oldId;
	}

	file.close();
	temp.close();
	remove(nameFile.c_str());
	rename("temp.csv",nameFile.c_str());

}

//--------------------------------------------------------------------------------------------------------------------------------------------
void radio::modifyMusicFromFile(music m){

	string readLine;
	music oldMusic;
	fstream radioTrackList;
	radioTrackList.open("radioStationMusics.csv");
	ofstream temp;
	temp.open("temp.csv");

	getline(radioTrackList,readLine);
	temp << readLine;

	while(radioTrackList.good())
	{
		radioTrackList >> oldMusic;
		if(oldMusic.getID()== m.getID())
			temp << m;
		else
			 temp << oldMusic;
	}

	radioTrackList.close();
	temp.close();

	remove("radioStationMusics.csv");
	rename("temp.csv","radioStationMusics.csv");



}

//--------------------------------------------------------------------------------------------------------------------------------------------
void radio::removeUserFromFile(listener &user)
{

	string readLine;
	listener oldUser;

	ifstream userFile;
	userFile.open("users.csv");
	ofstream temp;
	temp.open("temp.csv");

	getline(userFile,readLine);
	temp << readLine;

	while(userFile.good())
	{
		userFile >> oldUser;
		if(oldUser.getListenerName() != user.getListenerName())
			temp << endl << oldUser;
	}

	userFile.close();
	temp.close();

	remove("users.csv");
	rename("temp.csv","users.csv");
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void radio::removeMusicFromFile(int id)
{
	string readLine;
	music oldMusic;

	ifstream radioTrackList;
	radioTrackList.open("radioStationMusics.csv");

	ofstream temp;
	temp.open("temp.csv");

	getline(radioTrackList,readLine);
	temp << readLine;

	while(radioTrackList.good())
	{
		radioTrackList >> oldMusic;
		if(id != oldMusic.getID())
			temp << oldMusic;
	}

	radioTrackList.close();
	temp.close();

	remove("radioStationMusics.csv");
	rename("temp.csv","radioStationMusics.csv");

}

//--------------------------------------------------------------------------------------------------------------------------------------------
void radio::storeUserPlaylist(listener &user)
{
	
	vector<int> userMusics;
	string readLine;
	string nameFile;
	int oldId;

	nameFile=user.getNameFile();

	ifstream userFile;
	userFile.open(nameFile.c_str());
	getline(userFile,readLine);

	while(userFile.good())
	{
		userFile >> oldId;
		userMusics.push_back(oldId);
	}

	userFile.close();

	user.setListenerPlaylist(userMusics);
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void radio::choseUser(listener &user){

	listener oldUser;
	int index=0;
	char choice;

	do{
		system("CLS");

		oldUser=listeners[index];
		cout << oldUser;
		cout << endl << " [N]ext [P]revious [S]elect [E]xit ";
		cin >> choice;
		choice=toupper(choice);

		if(choice == 'N')
		{
			if(index == listeners.size() -1)
				index=0;
			else
				index++;
		}
		else

			if(choice =='P')
			{
				if(index == 0)
					index = listeners.size()-1;
				else
					index--;
			}
			else
				if(choice =='S')
					break;
				else
					if(choice== 'E')
						return;

	}while(true);
	
		user=oldUser;
		return;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void radio::initializeTopTen(){
	
	music musicFromFile;
	string readLine;
	ifstream radioTrackList;
	radioTrackList.open("radioStationMusics.csv");


	getline(radioTrackList,readLine);


	while(radioTrackList.good())
	{
		radioTrackList >> musicFromFile;
		updateTopTen(musicFromFile);
	}


	radioTrackList.close();
}