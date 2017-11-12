//	  +==============================================+
//	  |		Program Name: "Black-Jack Game"			 |
//	  |		Programmer Name : Greg Groshko			 |
//	  |		Version # : 1.0							 |
//	  |		File Name : gameLogicSetup.h			 |
//    +==============================================+

#ifndef GAMELOGICSETUP_H
#define GAMELOGICSETUP_H

#include<iostream>

//Game Initial Logic Setup Class
class gameLogicSetup {

//Private Variables
private:
	short int deck[13] = { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };			//Card Deck
	char letterDeck[13] = { 'A','2','3','4','5','6','7','8','9','T','J','Q','K' };	//Letter Deck
	short int cardsDrawn[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };						//Cards Drawn from Deck
	short int dealerDeck[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };							//Dealer's Deck from Card Deck
	char dealerLetterDeck[12];														//Dealer's Letter Deck
	short int playerDeck[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };							//Player's Deck from Card Deck
	char playerLetterDeck[12];														//Player's Letter Deck
	short int dealerHand, playerHand, dealerTurnCard,								
		playerTurnCard, dealerCardAmount, playerCardAmount;							// Initialize starting values (continue in constructor)
	short int dealerAces, playerAces;												//Number of Aces in Decks

//Public Functions
public:

	//Initialize Constructor
	gameLogicSetup() 
	{
		dealerHand = 0;																//Dealer's Hand Count
		playerHand = 0;																//Player's Hand Count
		dealerTurnCard = 0;															//Number of Dealer's Cards Turned
		playerTurnCard = 0;															//Number of Player's Cards Turned
		dealerCardAmount = 0;														//Number of Cards on Table
		playerCardAmount = 0;														//Number of Cards on Table
		dealerAces = 0;																//Number of Dealer Aces in Deck
		playerAces = 0;																//Number of Player Aces in Deck
	}

	//Set Value or Character Functions
	void decreaseDealerHandAce();													//Decrease Dealer's Hand Amount if there is an ace and hand count > 21
	void decreasePlayerHandAce();													//Decrease Player's Hand Amount if there is an ace and hand count > 21
	void setDealerDeck();															//Sets Dealer's Deck from main card deck
	void setPlayerDeck();															//Sets Player's Deck from main card deck
	void setDealerTurnCard();														//Sets number of cards turned (For Next Card Logic and Drawing Scene)
	void setPlayerTurnCard();										
	void setCardsDrawn(short int);													//Sets Cards Drawn (Keeps track of same card (4 of same value, different suit))
	void setDealerAces();															//Sets Dealer Aces
	void setPlayerAces();															//Sets Player Aces
	void setDealerLetterDeck(short int, char);										//Sets Dealer Letter Deck (for Drawing Scene)
	void setPlayerLetterDeck(short int, char);										//Sets Player Letter Deck (For Drawing Scene)

	//Get Value or Character Functions
	short int getCardsDrawn(short int);
	short int getDealerHand();
	short int getPlayerHand();
	short int getDealerTurnCard();
	short int getPlayerTurnCard();
	short int getDealerDeck(short int);
	short int getPlayerDeck(short int);
	short int getDealerAces();
	short int getPlayerAces();
	char getLetterDeck(short int);
	char getDealerLetterDeck(short int);
	char getPlayerLetterDeck(short int);

	//Draw Functions
	void getDealerNextCard();
	void getPlayerNextCard();
};


void gameLogicSetup::decreaseDealerHandAce()
{
	dealerHand -= 10;
	dealerAces -= 1;
}

void gameLogicSetup::decreasePlayerHandAce()
{
	playerHand -= 10;
	playerAces -= 1;
}

void gameLogicSetup::setDealerDeck()
{
	int card;
	for (int i = 0; i < 12; i++)
	{
		card = rand() % 13;
		dealerDeck[i] = deck[card];
		while (cardsDrawn[card] == 4)
		{
			card = rand() % 13;
			dealerDeck[i] = deck[card];
		}
		if (card == 0)
		{
			setDealerAces();
		}
		setCardsDrawn(card);
		setDealerLetterDeck(i, getLetterDeck(card));
	}
}

void gameLogicSetup::setPlayerDeck()
{
	int card;
	for (int i = 0; i < 12; i++)
	{
		card = rand() % 13;
		playerDeck[i] = deck[card];
		while (cardsDrawn[card] == 4)
		{
			card = rand() % 13;
			playerDeck[i] = deck[card];
		}
		if (card == 0)
		{
			setPlayerAces();
		}
		setCardsDrawn(card);
		setPlayerLetterDeck(i, getLetterDeck(card));
	}
}

void gameLogicSetup::setCardsDrawn(short int C)
{
	cardsDrawn[C] += 1;
}

void gameLogicSetup::setDealerTurnCard()
{
	dealerTurnCard += 1;
}

void gameLogicSetup::setPlayerTurnCard()
{
	playerTurnCard += 1;
}

void gameLogicSetup::setDealerAces()
{
	dealerAces += 1;
}

void gameLogicSetup::setPlayerAces()
{
	playerAces += 1;
}

void gameLogicSetup::setDealerLetterDeck(short int i, char a)
{
	dealerLetterDeck[i] = a;
}

void gameLogicSetup::setPlayerLetterDeck(short int i, char a)
{
	playerLetterDeck[i] = a;
}

short int gameLogicSetup::getCardsDrawn(short int C)
{
	return cardsDrawn[C];
}

short int gameLogicSetup::getDealerHand()
{
	return dealerHand;
}

short int gameLogicSetup::getPlayerHand()
{
	return playerHand;
}

short int gameLogicSetup::getDealerTurnCard()
{
	return dealerTurnCard;
}

short int gameLogicSetup::getPlayerTurnCard()
{
	return playerTurnCard;
}

short int gameLogicSetup::getDealerDeck(short int c)
{
	return dealerDeck[c];
}

short int gameLogicSetup::getPlayerDeck(short int c)
{
	return playerDeck[c];
}

short int gameLogicSetup::getDealerAces()
{
	return dealerAces;
}

short int gameLogicSetup::getPlayerAces()
{
	return playerAces;
}

void gameLogicSetup::getDealerNextCard()
{
	dealerHand += dealerDeck[getDealerTurnCard()];
	setDealerTurnCard();
}

void gameLogicSetup::getPlayerNextCard()
{
	playerHand += playerDeck[getPlayerTurnCard()];
	setPlayerTurnCard();
}

char gameLogicSetup::getLetterDeck(short int i)
{
	return letterDeck[i];
}

char gameLogicSetup::getDealerLetterDeck(short int i) 
{
	return dealerLetterDeck[i];
}

char gameLogicSetup::getPlayerLetterDeck(short int i)
{
	return playerLetterDeck[i];
}

#endif 
