
#include"listener.h"

//--------------------------------------------------------LISTENER CLASS DEFINITIONS-------------------------------------------------------------------
listener:: listener(){
	id=0;
	listenerName="Noname";
	listenerAge=0;
	listenerGender='U'; //'U'=="undefined"
	listenerPlaylist;
	winner = 0;
	setNameFile();
}

//--------------------------------------------------------------------------------------------------------------------------------------------
listener:: listener(int iden_num,string name, int age, char gender, vector<int> playlist){
	
	id=iden_num;
	listenerName=name;
	listenerAge=age;
	listenerGender= gender;
	listenerPlaylist=playlist;
	winner = 0;
	setNameFile();
	ofstream fileMusic;
	fileMusic.open(nameFile.c_str());
	fileMusic <<"ID";

	int newMusicId;
	
	for(unsigned i=0;i< playlist.size();i++)
	{
		newMusicId=playlist[i];
		fileMusic <<endl<< newMusicId;
	}
	fileMusic.close();
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void listener::setID(int iden_num){
	id=iden_num;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void listener:: setListenerName(string name){
	listenerName=name;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void listener:: setListenerAge(int age){
	listenerAge=age;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void listener:: setListenerGender(char gender){
	listenerGender=gender;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void listener:: setListenerPlaylist(vector<int> playlist){
	listenerPlaylist=playlist;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void listener::setWinnerFlag(){
	winner=true;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void listener::clearWinnerFlag(){
	winner=false;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void listener:: addMusic(int idMusic){
		listenerPlaylist.push_back(idMusic);
		storeMusic(idMusic);
	}

//--------------------------------------------------------------------------------------------------------------------------------------------
int listener::getListenerID(){
	return id;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
string listener:: getListenerName(){
	return listenerName;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
int listener:: getListenerAge(){
	return listenerAge;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
char listener:: getListenerGender(){
	return listenerGender;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
vector<int> listener:: getListenerPlaylist(){
	return listenerPlaylist;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
string listener::getNameFile(){
	return nameFile;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
int listener::getWinnerFlag(){
	return winner;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void listener::setNameFile(){
	//converts id from int to string
	ostringstream temp;
	string idStr;
	temp << id;
	idStr=temp.str();

	//creates the name of the file
	nameFile="playListUser"+ idStr +".csv";
}

//--------------------------------------------------------------------------------------------------------------------------------------------
bool listener::storeMusic(int idMusic){
	
	
	ifstream fileMusic;
	string readLine;
	fileMusic.open(nameFile.c_str());
	if(!fileMusic.is_open())//if the file doesnt exist
	{
		fileMusic.close();
		ofstream file;
		file.open(nameFile.c_str());
		file << "ID";
		//saves the info of the new music
		file<<endl<<idMusic;
		file.close();
		return true;
	}

	ofstream file(nameFile.c_str(),ios::app);
	file << endl<<idMusic;
	fileMusic.close();
	return true;

}

//--------------------------------------------------------------------------------------------------------------------------------------------
ostream& operator<< (ostream& out,listener &user){

	out << user.id << ',' << user.listenerName << ',' << user.listenerAge << ',' << user.listenerGender << ',' << user.winner;
	return out;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
istream& operator>> (istream& in,listener &user){

	string listenerString;

	getline(in,listenerString);

	istringstream listenerSstream(listenerString);
	
	string idStr,ageStr,winnerStr,genderStr;

	getline(listenerSstream,idStr,',');
	getline(listenerSstream,user.listenerName,',');
	getline(listenerSstream,ageStr,',');
	getline(listenerSstream,genderStr,',');
	getline(listenerSstream,winnerStr,',');

	user.id=stoi(idStr);
	user.listenerAge=stoi(ageStr);
	user.winner=stoi(winnerStr);

	user.listenerGender = genderStr.at(0);
	user.setNameFile(); 
	return in;
}