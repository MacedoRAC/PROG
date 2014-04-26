#include"music.h"


using namespace std;

//--------------------------------------------------------MUSIC CLASS DEFINITIONS-------------------------------------------------------------

music:: music(){
	id=0;
	title="Unknown Title";
	artist="Unknown Artist";
	author="Unknown Author";
	album="Unknown Album";
	music_genre="Unknown Muisc Genre";
	year=0;
	likes=0;
	dislikes=0;
	availability ='A';
	timesPlayed=0;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
music::music(int ident_num, string title_song,string artist_song,string author_song,
			 string album_song,string music_genre_song,int year_song,int likes_song,int dislikes_song)
{
	id=ident_num;
	title=title_song;
	artist=artist_song;
	author=author_song;
	album=album_song;
	music_genre=music_genre_song;
	year=year_song;
	likes=likes_song;
	dislikes=dislikes_song;
	availability ='A';
	timesPlayed=0;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void music::setID(int number){
	id=number;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void music::setTitle(string name){
	title=name;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void music::setArtist(string name){
	artist=name;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void music::setAuthor(string name){
	author=name;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void music::setAlbum(string name){
	album=name;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void music::setMusic_genre(string name){
	music_genre=name;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void music::setYear(int y){
	year=y;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void music::setLikes(int l){
	likes=l;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void music::setDislikes(int d){
	dislikes=d;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void music::setAvailability(char availabilityNew){
	availability=availabilityNew;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void music::setTimesPlayed(int timesPlayedNew){
	timesPlayed=timesPlayedNew;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void music::like(){
	likes++;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void music::dislike(){
	dislikes++;
}

//show track information (id, title, artist, author, album, music genre)----------------------------------------------------------------------
void music::showTrackInformation(){
	cout << setw(3) << id << " |" << setw(15) << title << " |" << setw(15) << artist << " |"
		<<setw(15) << author << " |" << setw(15) << album << " |" << setw(10) << music_genre 
		 << " |" << setw(4) << year << endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
int music::getID(){
	return id;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
string music::getTitle(){
	return title;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
string music::getArtist(){
	return artist;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
string music::getAuthor(){
	return author;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
string music::getAlbum(){
	return album;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
string music::getMusic_genre(){
	return music_genre;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
int music::getYear(){
	return year;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
int music::getLikes(){
	return likes;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
int music::getDislikes(){
	return dislikes;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
char music::getAvailability(){
	return availability;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void music:: changeAvailability(){
	if(availability=='A'|| availability =='a')
		availability='U';
	else
		availability='A';
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void music:: Play(){
	timesPlayed++;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
int music:: getNumberTimesPlayed(){
	return timesPlayed;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
ostream& operator<< (ostream& out,music& m){

	out  << endl <<m.id <<',' << m.title  <<',' << m.artist   <<',' << m.author  <<',' <<m.album <<',' << m.music_genre
		 << ','<<m.year <<',' << m.likes<<',' << m.dislikes <<',' << m.availability<<',' << m.timesPlayed;

	return out;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
istream& operator>> (istream& in,music& m){
	string musicString;
	char comma;

	getline(in,musicString);
	istringstream musicSstream(musicString);
	
	musicSstream >>m.id>> comma;
	getline(musicSstream,m.title,',');
	getline(musicSstream,m.artist,',');
	getline(musicSstream,m.author,',');
	getline(musicSstream,m.album,',');
	getline(musicSstream,m.music_genre,',');

	musicSstream >> m.year >>comma >> m.likes>>comma >> m.dislikes>> comma >>m.availability >> comma >> m.timesPlayed;
	return in;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
void music::displayMusic(){
	
	cout <<setw(3) <<id << setw(10) << title << setw(10) << artist << setw(10) << author << setw(10) << album <<setw(8)<< music_genre << setw(6) << year <<setw(6) << likes << setw(6) << dislikes<< endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
bool operator==(music musicRight,music musicLeft){

	return(musicRight.getID() == musicLeft.getID() &&
		musicRight.getTitle() == musicLeft.getTitle() &&
		musicRight.getArtist() == musicLeft.getArtist() &&
		musicRight.getAuthor() == musicLeft.getAuthor() &&
		musicRight.getAlbum() == musicLeft.getAlbum() &&
		musicRight.getMusic_genre() == musicLeft.getMusic_genre() &&
		musicRight.getYear() == musicLeft.getYear() &&
		musicRight.getLikes() == musicLeft.getLikes() &&
		musicRight.getDislikes() == musicLeft.getDislikes() &&
		musicRight.getAvailability() == musicLeft.getAvailability() &&
		musicRight.getNumberTimesPlayed() == musicLeft.getNumberTimesPlayed());
}