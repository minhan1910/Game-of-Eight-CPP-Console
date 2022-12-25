#include <iostream>
#include <cctype>

using namespace std;

const int MIN_OPTIONS = 1;
const int MAX_OPTIONS = 3;
const int PLAYER_ONE = 1;
const int PLAYER_TWO = 2;
const int IGNORE_CHARS = 256;
const int DEFAULT_LATEST_NUMBER = -1;

/*
The Game of Eight

------------------

The game of 8 is played by 2 players. 
The game starts with the initial number 8 (from here on refered to as the initial number). 
The first player will choose a number from 1 to 3 (from here on refered to as the chosen number). 
If the player inputs something outside of the 1 to 3 range it should be an error and the player must choose again.
The initial number is subtracted by the chosen number. 
Then the next player's turn happens. 
The next player cannot choose the number that the last player chose. 
If the initial number goes to 0 on your turn, then you win. 
Otherwise if the number goes below 0, your opponent wins. 
The player should always see what choices are available to him when prompted to enter his choice. 
After the game is over, the user should be prompted whether they want to play again.

-------------
Analysis:

The variable store the initial number 8.

The first is for player one and choose the option from 1 to 3 
if the player choose out of range then it should be an error and choose again
-> The initial number substracted by the player's choice

-> turn the player

the limit range is 0 -> win
otherwise < 0 -> your opposite wins

*/
void DisplayPlayerOptions();
void DisplayResults(int initialNumber, int player);
void PlayGame();
bool WantToPlayAgain();
bool IsGameOver(int initialNumber);
int GetNumber(int latestNumber);

int main()
{
	do {
		PlayGame();
	} while (WantToPlayAgain());

	return 0;
}

void PlayGame() {
	int count = 1;
	int initialNumber = 8;
	int number;
	int player;
	int latestNumber = DEFAULT_LATEST_NUMBER;

	do {
		player = count % 2 == 0 ? PLAYER_TWO : PLAYER_ONE;
		++count;

		cout << "The current number : " << initialNumber << endl;
		cout << "The player " << player << endl;

		number = GetNumber(latestNumber);
		latestNumber = number;

		// logic check
		initialNumber -= number;
		

	} while (!IsGameOver(initialNumber));


	DisplayResults(initialNumber, player);
}

void DisplayResults(int initialNumber, int player) {
	if (initialNumber == 0) {
		cout << "Congratulations, Player " << player << " is victory !";
	}
	else {
		cout << "Congratulations, Player " << player - 1 << " is victory !";
	}
}

bool IsGameOver(int initialNumber) {
	return initialNumber <= 0;
}

bool WantToPlayAgain() {
	char input;
	bool failure;

	do {
		failure = false;
		cout << "Do you want to play again? Enter Y";
		cin >> input;
		
		if (cin.fail()) {
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			failure = true;
			cout << "Input error!  Please try again" << endl;
		}
		else {
			cin.ignore(IGNORE_CHARS, '\n');
			input = tolower(input);
		}

	} while (failure);

	return input == 'y';
}

int GetNumber(int latestNumber) {
	int number;
	bool failure;

	do {
		failure = false;
		
		DisplayPlayerOptions();
		cin >> number;

		if (cin.fail()) {
			failure = true;
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << "Input error! Please try again" << endl;
		}
		else if (number < MIN_OPTIONS) {
			failure = true;
			cin.ignore(IGNORE_CHARS, '\n');
			cout << "The choice should be greater than " << MIN_OPTIONS << endl;
		}
		else if(number > MAX_OPTIONS) { // number > MAX_OPTIONS
			failure = true;
			cin.ignore(IGNORE_CHARS, '\n');
			cout << "The choice should be greater than " << MAX_OPTIONS << endl;
		}
		else if (latestNumber == number) { // duplicate options with player || number == latestNumber
			failure = true;
			cout << "Your choice must be different from the previous player" << endl;
		}

	} while (failure);

	return number;
}

void DisplayPlayerOptions() {
	cout << "1. Choose number 1" << endl;
	cout << "2. Choose number 2" << endl;
	cout << "3. Choose number 3" << endl;
	cout << "Your choice: ";
}
