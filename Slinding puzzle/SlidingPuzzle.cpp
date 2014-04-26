/* 
DATE : 2013/04/21
Developers : Liliana Ribeiro and Mário Macedo,grupo 8
PROGRAM PURPOSE: 
- Sliding Puzzle game
*/ 


#include<iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <cstdio>
#include<sstream>


using namespace std;

void format(int &number_tiles,int &num_col);
void organizedBoard(vector<vector<int>> &board,int number_tiles);
void searchNumber(const vector<vector<int>> &board,const int number,int &i,int &j);
bool validNumber(const vector<vector<int>> &board,const int number,const int num_col);
void moveTile(vector<vector<int>> &board,const int number1,const int number2);
void rearrangeBoard(vector<vector<int>> &vetor,const int number_tiles,int num_col);
void showBoard(const vector<vector<int>> &board);
bool correctBoard(const vector<vector<int>> &board,const int number_tiles);
void trainingMode();
void competitionMode();
void exitMessage();
void menuMain();
string newFile(const int num_col);
void updateBoardStatistics(const int num_col);
void boardToNewFile(const vector<vector<int>> &board,string nameOfFile,const string username,const int age,const char sex,const time_t time);
void showBoardFromFile(string nameOfFile,const int num_col);
void showOldPuzzles(string username,const int age,const char sex);
void updateRecords(string nameFile,const int num_col,string username,const int age,const char sex, const time_t time);
void Compformat(int &number_tiles,int &num_col);
void gameFromFile(string nameOfFile,vector<vector<int>> &board);
void playGame(const int number_tiles, const int num_col, string next_move, int move, vector<vector<int>> board);
void setcolor(unsigned int color) ;
string intToString(int number);

fstream boardStatistics; //create a file with number of puzzles played



/*==================================== MAIN ===========================================*/

int main()
{
	ifstream iboardStatistics;
	iboardStatistics.open("puzzle_numbers.txt");
	if(!iboardStatistics.good()) //verifies if the file "puzzle_numbers" already exixts
	{
		ofstream boardStatistics;						 //if it does not exist 
		boardStatistics.open("puzzle_numbers.txt");		//creates a new file "puzzle_numbers"
		boardStatistics << "3x3 0\n4x4 0\n5x5 0";		//with the intial conditions
		boardStatistics.close();
	}													
	iboardStatistics.close();

	srand((unsigned int)time(NULL));

	menuMain();
	return 0 ;
}


/*==============================creates a organized board====================================*/
void organizedBoard(vector<vector<int>> &board,const int number_tiles)
{
	int number = 1;
	for(unsigned int i=0; i < board.size();i++)
		for(unsigned int j=0; j < board[i].size(); j++)
		{
			if(number <= number_tiles)
			{
				board[i][j] = number;
				number++;
			}
			else
				board[i][j] = 0; //last tile is always blank
		}
}


/*==================================disrups an organized board===========================*/
void rearrangeBoard(vector<vector<int>> &vetor,const int number_tiles,int num_col)
{
	int number_moves = number_tiles + 20; //number of moves

	num_col = num_col-1;
	do
	{
		int number = rand()%number_tiles+1; //generates a random number between 1 and the number of tiles
		if(validNumber(vetor,number,num_col)) //verifies if that number can be moved
		{
			moveTile(vetor,number,0); //changes that number with the blank space
			number_moves--; 
		} //if validNumber==false generates another random number without decrementing the counter "number_moves"
	}while(number_moves > 0);
}


/* ==========================================verify if the puzzle is solved=================================*/
bool correctBoard(const vector<vector<int>> &board,const int number_tiles)
{
	unsigned int num_col;
	if(number_tiles == 8) //"num_col" depends of "number_max" 
		num_col = 3; 
	//number_max={8,15,24}
	else
		if(number_tiles == 15)
			num_col = 4;
		else
			num_col = 5;

	vector<vector<int>> ordered_board(num_col,vector<int> (num_col)); //creates an organized board of the same size of the other...
	organizedBoard(ordered_board,number_tiles);                      //...to compare both

	bool correct; //true if a number is in the right position

	unsigned int i = 0;
	unsigned int j =0;
	do
	{
		j=0; //guarantees that starts always on the first column of each line of the board
		do
		{ 

			if(board[i][j] == ordered_board[i][j]) //compares each position of the board solved by the user and the "ordered_board"
				correct = true;
			else
				return false; 
			j++;
		}while(correct && j < num_col);
		i++; //move to the next line of the board
	}while(correct && i < num_col);

	return correct;
}


/*===============================shows board to the user=====================================*/
void showBoard(const vector<vector<int>> &board)
{
	

	for(unsigned int i = 0; i < board.size();i++)
	{
		for(unsigned int j = 0; j < board[i].size();j++)
		{
			if( board[i][j] != 0)
				cout << setw(4) << board[i][j] ;
			else
				cout <<setw(4) << "  "; //"0" is not shown to the player
		}
		cout << endl;
	}
	cout << endl;
}


/* =================================gives a number's position on the board==================================*/
void searchNumber(const vector<vector<int>> &board,const int number,int &i,int &j)
{
	for(unsigned int x = 0; x < board.size();x++)
		for(unsigned int y = 0; y < board[x].size();y++)
			if(board[x][y] == number)
			{
				//position of the number in the board
				i = x; 
				j = y;
				break;
			}
}


/*======================verifies if it's possible to move a certain tile=============================*/
bool validNumber(const vector<vector<int>> &board,const int number,const int num_col)
{
	int i_number,j_number;

	searchNumber(board,number,i_number,j_number); //move to i_number and j_number the "number"'s position on the board
	if(i_number + 1 <= num_col && board[i_number+1][j_number]== 0) //returns "true" if exists a blank space adjacent to "number"
		return true;
	else
		if(i_number -1 >= 0 && board[i_number-1][j_number]== 0)
			return true;
		else
			if(j_number +1 <=num_col && board[i_number][j_number+1] == 0)
				return true;
			else
				if(j_number-1 >= 0 && board[i_number][j_number-1] == 0)
					return true;
				else
					return false;//if the "number" is not a blank space adjacent returns false
}


/*===================================interchange the position of number1 with number2=======================*/
void moveTile(vector<vector<int>> &board,const int number1,const int number2)
{
	int i_number1,j_number1;
	int i_number2,j_number2;
	int tmp;

	searchNumber(board,number1,i_number1,j_number1);
	searchNumber(board,number2,i_number2,j_number2);

	//changes the position of the numbers
	tmp = board[i_number1][j_number1];
	board[i_number1][j_number1] = board[i_number2][j_number2];
	board[i_number2][j_number2] = tmp;
}

/*=============================================================================================================================*/
void playGame(const int number_tiles, const int num_col, string next_move,int move, vector<vector<int>> board)
{
	bool board_correct = false; //true if the board ir ordered


	do
	{
		showBoard(board);

		setcolor(3);
		cout << "What is your next move? Choose the tile to move (Q to quit the game)...";
		setcolor(2);
		getline(cin,next_move);

		if(next_move == "Q" || next_move == "q") //verifies if the user wants to quit
		{
			system("CLS");
			setcolor(3);
			cout << endl << endl << "                                    GAME OVER!!\n";
			_getch(); //waits for a key to continue
			menuMain(); //returns to main menu
			break;

		}
		else
		{
			move = atoi (next_move.c_str()); //converts string "next_move" to integer "move"
			if (move > number_tiles) //verifies if the introduced number is bigger then the number of tiles
			{
				system("CLS");
				setcolor(3);
				cout << "INVALID NUMBER!!!\n ...\nPress any key to try again!";
				_getch();
				system("CLS");
			}
			else
				if(validNumber(board,move,num_col-1)) //verifies if the introduced number can be moved
				{
					system("CLS");
					moveTile(board,0,move);
				}
				else
				{
					system("CLS");	
					setcolor(3);
					cout << "INVALID MOVE!!!\n TRY AGAIN!!!\n";
					_getch();
					system("CLS");
				}
		}

		board_correct = correctBoard(board,number_tiles);
		if(board_correct)
		{
			setcolor(3);
			cout << "Congratulations!!!\n";
		}
	}while(!board_correct); //finish the loop if the board is ordered
}

/*===========================shows main menu of the game===================================================*/
void menuMain()
{
	char game_mode;
	bool invalid_mode;



	do
	{
		system("CLS");
		invalid_mode=false;

		setcolor(2);
		cout << endl << "              SLIDING PUZZLE\n\n" << "Developed by Liliana and Macedo\n\n";
		cout << "[T]"; setcolor(3); cout << "raining Mode\n";
		setcolor(2); cout << "[C]"; setcolor(3); cout << "ompetition Mode\n";
		setcolor(2); cout << "[H]"; setcolor(3); cout << "elp\n";
		setcolor(2); cout << "[E]"; setcolor(3); cout << "xit\n\n";
		cout << "What do you want to do? "; setcolor(2); cin >> game_mode;
		game_mode= toupper(game_mode);

		switch (game_mode)
		{
		case 'T':
			trainingMode();
			break;
		case 'C':
			competitionMode();
			break;
		case 'E':
			exitMessage();
			break;
		case 'H':
			system("CLS");
			setcolor(3);
			cout << "\n\nThe goal of the game is to rearrange the tiles to put them in ascending order.\n"
				<< "You can only move them horizontally or vertically.\nTo move the tiles write the number you want to move and press enter"
				<< "\n\n Press 'B' to go back to main menu...\n";
			_getch();
			menuMain();
			break;
		default:
			invalid_mode=true;
			break;
		}

	}while(invalid_mode);

}

/*============================exit message=================================*/
void exitMessage()
{
	
	system("CLS");
	setcolor(3);
	cout << endl << "                Thank you for playing!!!\n" << "                Next time you will be even better! Goodbye\n";
	_getch();
}


/*===================================TRAINING MODE=================================================================*/
void trainingMode()
{
	char another_game='Y';
	string next_move; //number of the next tile to be moved or 'q' to quit
	int number_tiles;
	int num_col;
	int move; //if next_move is a number,saves that number
	move = atoi (next_move.c_str()); //converts string "next_move" to integer "move"

	system("CLS");


	do
	{
		setcolor(3);
		cout << endl <<"Welcome to training! May the force be with you...\n\n";
		format(number_tiles,num_col);
		system("CLS");
		vector<vector<int>> board(num_col,vector<int>(num_col)); //creates a board 
		organizedBoard(board,number_tiles); //initializes board on the correct order


		do
		{
			rearrangeBoard(board,number_tiles,num_col); //disrupts board
		}while(correctBoard(board,number_tiles));


		bool board_correct = false; //true if the board ir ordered
		time_t  startingTime;  //variables to calculate the time... 
		time_t delta_time;//...needed to complete the puzzle
		time(&startingTime); //saves the time when the game begins
		cin.ignore(1000,'\n');

		playGame(number_tiles, num_col, next_move, move, board);

		time_t endingTime;
		time(&endingTime); //saves the time spent playing
		delta_time = (endingTime - startingTime); //calculates the time needed to put the board in the correct order

		setcolor(3);
		cout << "Time: " << delta_time << " sec" << endl;



		do //if the input is neither 'Y' or 'N', the question is repeated
		{
			
			cout << "Do you want to play again(Y/N)?";
			setcolor(2);
			cin >> another_game;
			another_game= toupper(another_game);
			system("CLS");
		}while(another_game != 'Y' && another_game != 'N');

	}while(another_game == 'Y');

	if(another_game == 'N')  //goes back to the main menu if the user doesn´t want to train again
	{
		setcolor(3);
		cout << "\n\n                           Excellent!\n             I think you're ready to beat some records!\n";
		_getch();
		menuMain();
	}

}

/*=======================updates the variable number_tiles and num_col according  with the choice of the user=================*/
void format(int &number_tiles,int &num_col)
{
	bool correct_option; //true if user introduces a valid option
	char choice; 

	do
	{
		cin.ignore(1000,'\n'); //clears the buffer
		correct_option = true;
		cout << "Choose the difficulty of the game!\n" << endl << endl; 
		setcolor(2); cout << "     [E]"; setcolor(3); cout << "asy (3x3)\n";   //[E]asy(3x3)
		setcolor(2); cout << "     [M]"; setcolor(3); cout << "edium (4x4)\n"; //[M]edium(4x4)
		setcolor(2); cout << "     [H]"; setcolor(3); cout << "ard (5x5)\n";   //[H]ard(5x5)
		setcolor(2); cout << "     [B]"; setcolor(3); cout << "ack\n\n";       //[B]ack
		cout << "Choice: "; setcolor(2); cin >> choice; // 'E','M','H',or'B'
		choice = toupper(choice);

		switch(choice)
		{
		case 'E':
			number_tiles = 8;
			num_col = 3;
			break;
		case 'M':
			number_tiles = 15;
			num_col = 4;
			break;
		case 'H':
			number_tiles = 24;
			num_col = 5;
			break;
		case 'B':
			menuMain();
			break;
		default:
			{
				system("CLS");
				cout << "Invalid choice!\n";
				_getch();
				system("CLS");
				correct_option = false;
			}
		}
	}while(!correct_option);
}

/*=============================COMPETITION MODE=====================================================*/
void competitionMode()
{
	string next_move; //number of the next tile to be moved or 'q' to quit
	int number_tiles;
	int num_col;
	char another_game='Y';
	string username;
	int age;
	char typeOfGame, sex;
	string player; //saves all the user information(name,age,gender and time)
	int move; //if next_move is a number,saves that number
	move = atoi (next_move.c_str()); //converts string "next_move" to integer "move"

	system("CLS");

	setcolor(3);
	cout << "Welcome to Competition Mode!\n\n";

	

	/* user informations*/
	cout << "Username: "; 
	cin.ignore(1000,'\n'); //cleans buffer
	setcolor(2); getline(cin, username);


	do
	{
		setcolor(3); cout << "Age: ";
		setcolor(2); cin >> age;
		cin.clear();
		cin.ignore(1000,'\n');
	}while(cin.fail());

	do
	{
		setcolor(3); cout << "Gender[M/F]: ";
		setcolor(2); cin >> sex;
		sex = toupper(sex);

	}while(sex != 'F' && sex != 'M');

	system("CLS"); 

	
	setcolor(3); cout << "Competition Mode\n\n";
	setcolor(2); cout << "[N]"; setcolor(3); cout << "ew Board\n"; //[N]ew Board
	setcolor(2); cout << "[O]"; setcolor(3); cout << "ld Board\n"; //[O]ld Board
	setcolor(2); cout << "[B]"; setcolor(3); cout << "ack\n\n";    //[B]ack
	cout << "Choice: "; 
	setcolor(2); cin >> typeOfGame;
	typeOfGame= toupper(typeOfGame);

	switch (typeOfGame)
	{
	case 'N':
		{
			system("CLS");
			format(number_tiles,num_col);
			system("CLS");
			vector<vector<int>> board(num_col,vector<int>(num_col)); //creates a board 
			organizedBoard(board,number_tiles); //initializes board on the correct order
			vector<vector<int>> copyBoard(num_col,vector<int> (num_col)); //saves a copy of the puzzle to save in the data file later

			do
			{
				rearrangeBoard(board,number_tiles,num_col); //disrupts board
			}while(correctBoard(board,number_tiles));

			for(int i=0; i<num_col; i++) //copies the unsolved puzzle to copyBoard
			{
				for(int j=0; j<num_col; j++)
				{
					copyBoard[i][j]= board[i][j];
				}
			}


			bool board_correct = false; //true if the board ir ordered
			time_t  startingTime;  //variables to calculate the time... 
			time_t delta_time;//...needed to complete the puzzle
			time(&startingTime); //saves the time when the game begins
			cin.ignore(1000,'\n');

			playGame(number_tiles, num_col, next_move, move, board);

			time_t endingTime;
			time(&endingTime); //saves the time spent playing
			delta_time = (endingTime - startingTime); //calculates the time needed to put the board in the correct order

			setcolor(3);
			cout << "Time: " << delta_time << " sec" << endl;
			updateBoardStatistics(num_col);
			string nameNewFile;
			nameNewFile = newFile(num_col);
			boardToNewFile(copyBoard,nameNewFile,username,age,sex,delta_time);
			showBoardFromFile(nameNewFile, num_col);
			cout << "\n\n Press 'B' to go back to main menu.";
			_getch();
			menuMain();
		}
		break;
	case 'O':
		showOldPuzzles(username,age,sex);
		break;
	case 'B': //returns to the initial menu
		menuMain();
		break;
	default:
		break;
	}

}

/*===========================updates the number of puzzles played========================*/
void updateBoardStatistics(const int num_col)
{
	string readLine;
	int firstCharacter; //saves the first and third characters,that are the same
	int puzzle_number; // saves the number o f puzzles played
	char x; //saves the character 'x'


	ifstream boardStatistics;
	boardStatistics.open("puzzle_numbers.txt");
	ofstream temp;
	temp.open("temp.txt"); //temporary file

	for(int i=0;i < 3;i++)
	{
		boardStatistics >> firstCharacter >> x >> firstCharacter >> puzzle_number;
		if(firstCharacter == num_col)
		{
			puzzle_number++;
			temp << firstCharacter << x << firstCharacter << " " << puzzle_number << endl;
		}
		else
			temp << firstCharacter << x << firstCharacter << " " << puzzle_number << endl;
	}

	boardStatistics.close();
	temp.close();
	//saves the new file with the name of the original file,deleting the original
	remove("puzzle_numbers.txt");
	rename("temp.txt","puzzle_numbers.txt");
}

/*===========================creates new name for file for puzzle========================*/
string newFile(const int num_col)
{
	string readLine; //compares each line of the file "puzzle_numbers" with the type of board the user chose,to create the name of the new file
	int firstCharacter; //first character of readLine
	int puzzle_number; //number of puzzles played until the user chooses "new board"
	char x;
	string fileName;

	boardStatistics.open("puzzle_numbers.txt");

	do
	{
		boardStatistics >> firstCharacter >> x >> firstCharacter >> puzzle_number;
		if(firstCharacter == num_col)
		{
			if(puzzle_number < 10)
				fileName = "puzzle_" + intToString(firstCharacter)+ x +intToString(firstCharacter) + "_00" + intToString(puzzle_number) + ".txt";
			else
				if(puzzle_number<100)
					fileName = "puzzle_"+ intToString(firstCharacter)+ x +intToString(firstCharacter) + "_0" + intToString(puzzle_number) + ".txt";
				else
					fileName = "puzzle_" + intToString(firstCharacter)+ x +intToString(firstCharacter) + "_" + intToString(puzzle_number) + ".txt";
		}
	}while(boardStatistics.good());
	boardStatistics.close();
	return fileName;
}

/*==========================copies the board and the user information to a new text file,with the name that is indicated in nameOfFile==================*/
void boardToNewFile(const vector<vector<int>> &board,string nameOfFile,string username,const int age,const char sex,const time_t time)
{
	ofstream newfile;

	newfile.open(nameOfFile.c_str());

	for(unsigned int i = 0;i < board.size();i++)
	{
		for(unsigned int j = 0;j < board.size(); j++)
			newfile << setw(4) << board[i][j];
		newfile << endl;
	}
	newfile << endl;
	newfile << setw(20) << username << setw(3) << age << setw(2) << sex << setw(5) << time; //saves the player's information
	newfile.close();
}

/*================================shows a board previously saved in a text file====================*/
void showBoardFromFile(string nameOfFile,const int num_col)
{
	int number;
	string line;
	ifstream file;
	file.open(nameOfFile.c_str());

	setcolor(3);
	//shows board
	for(int i=0;i < num_col;i++)
	{
		for(int j = 0;j < num_col;j++)
		{
			file >> number;
			if(number == 0)
				cout << setw(3) <<  " ";
			else
				cout << setw(3) <<  number;
		}
		cout << endl;
	}

	//shows previous players
	while(file.good())
	{
		getline(file,line);
		cout << line << endl;
	}

	file.close();
}

/*===============================lets the player select the board he/she wants to play================*/
void showOldPuzzles(string username,const int age,const char sex)
{
	char x;
	string name; //name of the file to be open
	int boardSize;
	int number_tiles;
	int num_col;
	char selectBoard;
	string next_move;
	int move;
	move = atoi (next_move.c_str()); //converts string "next_move" to integer "move"

	Compformat(number_tiles,num_col);

	vector<vector<int>> board (num_col,vector<int> (num_col));

	unsigned int numberPuzzles;//number of puzzles played until this moment

	ifstream boarStatistics;
	boardStatistics.open("puzzle_numbers.txt");

	do
	{
		boardStatistics >> boardSize;
		boardStatistics >> x >> boardSize;
		boardStatistics >> numberPuzzles;
	}while(boardSize != num_col); //numberPuzzles will have the number of puzzles played,that are the same size as the player chose(num_col)

	unsigned int i=1;
	do
	{

		if(i > numberPuzzles)
			i = 1;
		else
			if(i < 1)
				i = numberPuzzles;

		system("CLS");
		name = "puzzle_" + intToString(num_col) + 'x' + intToString(num_col);  //e.g. "puzzle_3x3"
		if(i < 10)
			name=name + "_00" + intToString(i)+ ".txt"; //e.g "puzzle_3x3_001.txt"
		else
			if(i < 100)
				name = name + "_0" + intToString(i)+ ".txt";
			else
				name=name + "_" + intToString(i)+ ".txt";
		cout << name << endl;
		showBoardFromFile(name,num_col); 

		setcolor(2); cout << "\n[N]"; setcolor(3); cout << "ext  ";   //[N]ext
		setcolor(2); cout << "[P]"; setcolor(3); cout << "revious  "; //[P]revious
		setcolor(2); cout << "[S]"; setcolor(3); cout << "elect  ";   //[S]elect
		setcolor(2); cout << "[E]"; setcolor(3); cout << "xit ?";     //[E]xit
		setcolor(2); cin >> selectBoard;
		selectBoard = toupper(selectBoard);

		switch(selectBoard)
		{
		case 'N': 
			i++;
			break;
		case 'P': 
			i--;
			break;
		case 'S':
			gameFromFile(name,board);
			break;
		case 'E':
			menuMain();
			break;
		}

	}while(selectBoard != 'E' && selectBoard != 'S');



	bool board_correct = false; //true if the board ir ordered
	time_t startingTime;  //variables to calculate the time... 
	time_t delta_time;//...needed to complete the puzzle
	time(&startingTime); //saves the time when the game begins
	cin.ignore(1000,'\n');

	system("CLS");
	playGame(number_tiles, num_col, next_move, move, board);

	time_t endingTime;
	time(&endingTime); //saves the time spent playing
	delta_time = (endingTime - startingTime); //calculates the time needed to put the board in the correct order

	cout << "Time: " << delta_time << " sec" << endl;
	updateBoardStatistics(num_col);
	string nameNewFile;
	nameNewFile = newFile(num_col);
	updateRecords(name,num_col,username,age,sex,delta_time);
	showBoardFromFile(name, num_col);
	cout << "\n\n Press 'B' to go back to main menu.";
	_getch();
	return menuMain();
}

/*=============================== menu for "Playing Old Puzzles"================================================== */
void Compformat(int &number_tiles,int &num_col)
{
	bool correct_option; //true if user introduces a valid option
	char choice; 

	do
	{
		int puzzle3; //number of 3x3 puzzles played
		int puzzle4; //number of 4<4 puzzlez played
		int puzzle5; //number of 5x5 puzzle played
		char x; //saves the character 'x'
		ifstream boardStatistics;

		boardStatistics.open("puzzle_numbers.txt");
		boardStatistics >> puzzle3 >> x >> puzzle3 >>puzzle3 >> puzzle4 >> x >> puzzle4 >>puzzle4 >>puzzle5 >> x>>puzzle5 >>puzzle5;
		boardStatistics.close();

		system("CLS");
		//cin.ignore(1000,'\n'); //clears the buffer
		correct_option = true;
		
		setcolor(3);
		cout << "What board do you want to play!\n" << endl << endl;
		setcolor(2); cout << "     [E]"; setcolor(3); cout << "asy (3x3)(" << puzzle3 << ")\n";   //[E]asy (3x3)(number of puzzles played)
		setcolor(2); cout << "     [M]"; setcolor(3); cout << "edium (4x4)(" << puzzle4 << ")\n"; //[M]edium (4x4)(number of puzzles played)
		setcolor(2); cout << "     [H]"; setcolor(3); cout << "ard (5x5)(" << puzzle5 << ")\n";   //[H]ard (5x5)(number of puzzles played)
		setcolor(2); cout << "     [B]"; setcolor(3); cout << "ack\n\n";                          //[B]ack 
		cout << "Choice: ";
		setcolor(2); cin >> choice;
		choice = toupper(choice);

		switch(choice)
		{
		case 'E':
			number_tiles = 8;
			num_col = 3;
			break;
		case 'M':
			number_tiles = 15;
			num_col = 4;
			break;
		case 'H':
			number_tiles = 24;
			num_col = 5;
			break;
		case 'B':
			menuMain();
			break;
		default:
			{
				system("CLS");
				setcolor(3);
				cout << "Invalid choice!\n";
				_getch();
				system("CLS");
				correct_option = false;
			}
		}

		//verifies if the user chose a size with no boards played
		if(choice== 'E' && puzzle3 == 0)
		{
			correct_option=false;
			setcolor(3);
			cout << "There are no 3x3 boards avaiable...\nPress any key to try again!";
			_getch();
		}
		else
			if(choice == 'M' && puzzle4 == 0)
			{
				correct_option = false;
				setcolor(3);
				cout << "There are no  4x4 boards avaiable...\nPress any key to try again!";
				_getch();
			}
			else
				if(choice == 'H' && puzzle5 ==0)
				{
					correct_option = false;
					setcolor(3);
					cout << "There are no 5x5 boards avaiable...\nPress any key to try again!";
					_getch();
				}
	}while(!correct_option);
}

/*=================================extract from a text file a board already played===================================*/
void gameFromFile(string nameOfFile,vector<vector<int>> &board)
{
	int tile;
	ifstream file;
	file.open(nameOfFile.c_str());

	//saves in the vector the board
	for(unsigned int i=0;i < board.size();i++)
	{
		for(unsigned int j=0; j < board[i].size();j++)
		{
			file >> tile;
			board[i][j]= tile;
		}
	}

}

/*================================update the data files with the new records======================================================*/
void updateRecords(string nameFile,const int num_col,string username,const int age,const char sex,const time_t time)
{
	int counter; //only the 10 best scores will be saved
	string oldUsername;
	int oldAge;
	int oldTime;
	char oldSex;
	string readLine;
	ofstream temp;
	temp.open("temp.txt");
	ifstream file;
	file.open(nameFile.c_str());


	for(int i = 0; i < num_col;i++) //copies the board to new file
	{
		getline(file,readLine);
		temp << readLine << endl;
	}
	counter=0; //this counter is responsible to establish the numbers of records in 10
	do
	{
		file >> oldUsername >> oldAge >> oldSex >> oldTime; //extract the information about the 1st player on records table 
		if(time <= oldTime)
		{
			temp << endl << setw(20) << username << setw(3) << age << setw(2) << sex << setw(5) << time;
			if(counter <= 8) //else only the new score will be saved,otherwise there would be 11 records
			{
				temp << endl << setw(20) << oldUsername << setw(3) << oldAge << setw(2) << oldSex << setw(5) << oldTime;
				counter++;
			}
			counter++;
			//saves the rest of the records below
			while(file.good() && counter < 10)
			{
				file >> oldUsername >> oldAge >> oldSex >> oldTime;
				temp << endl << setw(20) << oldUsername << setw(3) << oldAge << setw(2) << oldSex << setw(5) << oldTime;
				counter++;
			}
		}
		else //will save the previous record that was on the file
		{
			temp << endl<< setw(20) << oldUsername << setw(3) << oldAge << setw(2) << oldSex << setw(5) << oldTime;
			counter++;
		}
	}while(file.good() && counter < 10);


	file.close();
	temp.close();
	//saves the new file with the name of the original file,deleting the original
	remove(nameFile.c_str());
	rename("temp.txt",nameFile.c_str());
}

//================================================================================
/* 
COLOR CODES:
1   blue
2   green
3   cyan
4   red
5   magenta
6   brown
7   lightgray
8   darkgray
9   lightblue
10  lightgreen
11  lightcyan
12  lightred
13  lightmagenta
14  yellow
15  white
*/

/*===============changes the color of the console output========================*/

void setcolor(unsigned int color) 
{                                    
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon,color);
} 

string intToString(int number){
	string newString;
	stringstream ss;
	ss << number;
	ss>> newString;


	return newString;
}