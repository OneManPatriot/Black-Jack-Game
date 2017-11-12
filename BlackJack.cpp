//	  +==============================================+
//	  |		Program Name: "Black-Jack Game"			 |
//	  |		Programmer Name : Greg Groshko			 |
//	  |		Version # : 1.0							 |
//	  |		File Name : BlackJack.cpp				 |
//    +==============================================+

#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include"gameLogicSetup.h"
using namespace std;

bool menu();								//Menu Screen
void setup(gameLogicSetup&);				//Sets up decks and first two cards
void bet(int&, int&);						//Betting System
void drawScene(gameLogicSetup&);			//Draws the player turn screen
void drawSceneFinal(gameLogicSetup&);		//Draws the dealer turn screen
int PlayerTurn(gameLogicSetup&);			//Logic for player turn
void DealerTurn(gameLogicSetup&);			//Logic for dealer turn

int main() {
	srand(time(NULL)); //Initialize random seed generator


	bool play = true;	//Set play to true
	int choice;			//Choice for main menu


	while (play)
	{
		int money = 10000, betMoney = 0;	//Initialize Money and Bet values
		play = menu();						//Menu Screen
		if (!play)							//Ends the game if quit from menu
		{
			return 0;
		}

		bool gameOverMoney = false;			//Sets Game Over parameter to false (Money == 0)
		while (!gameOverMoney) {			//While Player has money, Play Game

			system("cls");					//Clears Screen
			gameLogicSetup Game;			//Setup Game class
			setup(Game);					//Sets up dealer and player decks and first two cards
			bool playerStop = false;		//Sets Player STAY function to false
			bool gameOver = false;			//Allows one game to begin

			bet(money, betMoney);			//Bet function
			while (!gameOver) {				//Begins game
				while (!playerStop) {		//Begins Players turn
					system("cls");			//Clears Screen
					drawScene(Game);		//Draws Player's turn screen

											//Logic for player's turn
					if (Game.getPlayerHand() == 21)
					{
						choice = 1;
					}
					else 
					{
						choice = PlayerTurn(Game);
					}

					if (choice == 3)		//If quitting from player turn, ends game
					{
						playerStop = true;
						gameOver = true;
						gameOverMoney = true;
					}
					else if (choice == 2)	//If player exceeds 21, end turn and dealer wins
					{
						playerStop = true;
						gameOver = true;
						cout << "Game Over - Dealer Wins" << endl;
						betMoney = 0;
					}
					else if (choice == 1)	//If player stays while under or equal to 21, end turn
					{
						playerStop = true;
					}
				}


				system("cls");				//Clear Screen
				DealerTurn(Game);			//Starts Dealer's Turn
				drawSceneFinal(Game);		//Draws Dealer Screen and End-Game Result
				
				//If player hand > dealer hand, and less than or equal to 21, player wins.
				if ((Game.getPlayerHand() > Game.getDealerHand()) && (Game.getPlayerHand() <= 21)) 
				{
					cout << "Congratulations! You won!" << endl;
					money += (betMoney * 2);
				}
				//If dealer hand exceeds 21 and player hand less than or equal to 21, player wins.
				else if ((Game.getDealerHand() > 21) && (Game.getPlayerHand() <= 21))
				{
					cout << "Congratulations! You won!" << endl;
					money += (betMoney * 2);
				}
				else
				{
					cout << "Game Over - Dealer Wins" << endl;	//When conditions above don't apply, dealer wins
					betMoney = 0;
				}

				if (money == 0) //If player runs out of money, go back to menu
				{
					gameOverMoney = true; //ends game and returns to menu
				}
				cin.ignore();
				cin.get();
				gameOver = true; //ends betting turn
			}
			system("cls"); //clear screen
		}//End of Game (Game Only)
	}//End of Program (Menu and Game)

	return 0; //end of MAIN Program
}


bool menu() //Prints Mneu Screen
{
	//Setup Screen
	/*
	cout << "+$$$$$$$$$$$$$$$$+   +$$$$$$$$$$$$$$$$+" << endl;
	cout << "$ A              $   $ K              $" << endl;
	cout << "$                $   $                $" << endl;
	cout << "$                $   $                $" << endl;
	cout << "$                $   $                $" << endl;
	cout << "$   Black-Jack   $   $   (A) Play     $" << endl;
	cout << "$      Game      $   $   (B) Quit     $" << endl;
	cout << "$                $   $                $" << endl;
	cout << "$                $   $                $" << endl;
	cout << "$                $   $                $" << endl;
	cout << "$              A $   $              K $" << endl;
	cout << "+$$$$$$$$$$$$$$$$+   +$$$$$$$$$$$$$$$$+" << endl;
	*/

	char menuChoice1;

	//Cards Menu
	cout << "+$$$$$$$$$$$$$$$$+   +$$$$$$$$$$$$$$$$+" << endl;
	cout << "$ A              $   $ K              $" << endl;
	cout << "$                $   $                $" << endl;
	cout << "$                $   $                $" << endl;
	cout << "$                $   $                $" << endl;
	cout << "$   Black-Jack   $   $   (A) Play     $" << endl;
	cout << "$      Game      $   $   (B) Quit     $" << endl;
	cout << "$                $   $                $" << endl;
	cout << "$                $   $                $" << endl;
	cout << "$                $   $                $" << endl;
	cout << "$              A $   $              K $" << endl;
	cout << "+$$$$$$$$$$$$$$$$+   +$$$$$$$$$$$$$$$$+" << endl << endl;

	cout << "Select an option: ";
	cin >> menuChoice1;
	if (menuChoice1 == 'A' || menuChoice1 == 'a')
	{
		return true;
	}
	else
	{
		return false;
	}
}



void setup(gameLogicSetup& Game) // Sets up player and dealer decks and first two cards
{
	Game.setDealerDeck();
	Game.setPlayerDeck();

	for (int i = 0; i < 2; i++)
	{
		Game.getPlayerNextCard();
		if (Game.getPlayerHand() > 21 && Game.getPlayerAces() > 0)
		{
			Game.decreasePlayerHandAce();
		}
		Game.getDealerNextCard();
		if (Game.getDealerHand() > 21 && Game.getDealerAces() > 0)
		{
			Game.decreaseDealerHandAce();
		}
	}
}


void bet(int& purse, int& bet) // Sets up betting
{
	int setBet;

	if (purse > 50)
	{
		cout << "Money: $" << purse << endl;
		cout << "Bet (Min: 50  Max: 1000): ";
		cin >> setBet;
	}
	else if(purse <= 50)
	{
		setBet = purse;
	}

	while ((setBet > purse) || (setBet > 1000) || (setBet < 50 && purse > 50) || (!(setBet)))
	{
		cin.clear();
		cin.ignore();
		cout << endl << "Must set a valid bet!" << endl;
		cout << "Bet (Min: 50  Max: 1000): ";
		cin >> setBet;
	}

	purse = purse - setBet;
	bet = setBet;
}


void drawScene(gameLogicSetup& Game) // Sets up player turn screen
{
	/*

	Small Card Setup

	+$$$$$+  
	$     $
	$  A  $
	$     $
	+$$$$$+

	*/

	//Dealer's Side
	cout << "Dealer: ??" << endl << endl;
	for (int i = 0; i < (Game.getDealerTurnCard()); i++)
	{
		cout << "+$$$$$+  ";
	}
	cout << endl;

	for (int i = 0; i < (Game.getDealerTurnCard()); i++)
	{
		cout << "$     $  ";
	}
	cout << endl;

	for (int i = 0; i < (Game.getDealerTurnCard()); i++)
	{
		if (i == 1) 
		{
			cout << "$  ?  $  ";
		}
		else
		{
			cout << "$  " << Game.getDealerLetterDeck(i) << "  $  ";
		}
	}
	cout << endl;

	for (int i = 0; i < (Game.getDealerTurnCard()); i++)
	{
		cout << "$     $  ";
	}
	cout << endl;

	for (int i = 0; i < (Game.getDealerTurnCard()); i++)
	{
		cout << "+$$$$$+  ";
	}
	cout << endl << endl;


	//Player's Side
	cout << "Player: " << Game.getPlayerHand() << endl << endl;
	for (int i = 0; i < (Game.getPlayerTurnCard()); i++)
	{
		cout << "+$$$$$+  ";
	}
	cout << endl;

	for (int i = 0; i < (Game.getPlayerTurnCard()); i++)
	{
		cout << "$     $  ";
	}
	cout << endl;

	for (int i = 0; i < (Game.getPlayerTurnCard()); i++)
	{
		cout << "$  " << Game.getPlayerLetterDeck(i) << "  $  ";
	}
	cout << endl;

	for (int i = 0; i < (Game.getPlayerTurnCard()); i++)
	{
		cout << "$     $  ";
	}
	cout << endl;

	for (int i = 0; i < (Game.getPlayerTurnCard()); i++)
	{
		cout << "+$$$$$+  ";
	}
	cout << endl << endl;

	//Choice Menu
	cout << "(A) Hit (B) Stay (X) Quit" << endl;
	cout << "Choice: ";
}


void drawSceneFinal(gameLogicSetup& Game) // Sets up dealer turn screen and end result
{

	//Dealer's Side

	cout << "Dealer: " << (Game.getDealerHand()) << endl << endl;
	for (int i = 0; i < (Game.getDealerTurnCard()); i++)
	{
		cout << "+$$$$$+  ";
	}
	cout << endl;

	for (int i = 0; i < (Game.getDealerTurnCard()); i++)
	{
		cout << "$     $  ";
	}
	cout << endl;

	for (int i = 0; i < (Game.getDealerTurnCard()); i++)
	{
		cout << "$  " << Game.getDealerLetterDeck(i) << "  $  ";
	}
	cout << endl;

	for (int i = 0; i < (Game.getDealerTurnCard()); i++)
	{
		cout << "$     $  ";
	}
	cout << endl;

	for (int i = 0; i < (Game.getDealerTurnCard()); i++)
	{
		cout << "+$$$$$+  ";
	}
	cout << endl << endl;


	//Player's Side

	cout << "Player: " << Game.getPlayerHand() << endl << endl;
	for (int i = 0; i < (Game.getPlayerTurnCard()); i++)
	{
		cout << "+$$$$$+  ";
	}
	cout << endl;

	for (int i = 0; i < (Game.getPlayerTurnCard()); i++)
	{
		cout << "$     $  ";
	}
	cout << endl;

	for (int i = 0; i < (Game.getPlayerTurnCard()); i++)
	{
		cout << "$  " << Game.getPlayerLetterDeck(i) << "  $  ";
	}
	cout << endl;

	for (int i = 0; i < (Game.getPlayerTurnCard()); i++)
	{
		cout << "$     $  ";
	}
	cout << endl;

	for (int i = 0; i < (Game.getPlayerTurnCard()); i++)
	{
		cout << "+$$$$$+  ";
	}
	cout << endl << endl;
}

int PlayerTurn(gameLogicSetup& Game) // Logic for player's turn
{
	char Choice;
	int returnDecision = -1, bet;

	if (Game.getPlayerHand() == 21)
	{
		Choice = 'B';
	}

	//Subsequent Turns
	cin >> Choice;
	
	if (Choice == 'A' || Choice == 'a')
	{
		returnDecision = 0;
		(Game.getPlayerNextCard());
	}
	else if (Choice == 'B' || Choice == 'b')
	{
		returnDecision = 1;
	}
	else if (Choice == 'X' || Choice == 'x')
	{
		returnDecision = 3;
	}

	//Decision tree
	while (!Choice || returnDecision == -1)
	{
		cout << endl << "Please select a valid option: ";  
		cin >> Choice;


		if (Choice == 'A' || Choice == 'a')
		{
			returnDecision = 0;
			(Game.getPlayerNextCard());
		}
		else if (Choice == 'B' || Choice == 'b')
		{
			returnDecision = 1;
		}
		else if (Choice == 'X' || Choice == 'x')
		{
			returnDecision = 3;
		}
	}


	//Decide fate from player's hand
	if(Game.getPlayerHand() == 21) 
	{
		returnDecision = 1;
	}
	else if (Game.getPlayerHand() > 21)
	{
		returnDecision = 2;
	}
	else if (Game.getPlayerHand() > 21 && Game.getPlayerAces() > 0)
	{
		Game.decreasePlayerHandAce();
		if (Game.getPlayerHand() > 21) 
		{
			returnDecision = 2;
		}
	}
	else if (returnDecision == 3){}


	//Return fate
	return returnDecision;
}

void DealerTurn(gameLogicSetup& Game) // Logic for dealer's turn
{
	//Repeats until it beats player hand or soft 17
	do 
	{
		if((Game.getDealerHand() < 17) || ((Game.getDealerHand() < Game.getPlayerHand()) && (Game.getPlayerHand() <= 21)))
		{
			Game.getDealerNextCard();
		}

		if (Game.getDealerHand() > 21 && Game.getDealerAces() > 0)
		{
			Game.decreaseDealerHandAce();
		}
	} while (Game.getDealerHand() < 17);
}