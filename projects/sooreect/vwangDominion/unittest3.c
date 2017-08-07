/*************************************************************************************************
 * Author: Tida Sooreechine
 * Date: 7/15/2017
 * Program: CS362 Assignment 3 Unit Test 3
 * Description: A program consisting of tests for dominion.c's scoreFor() function
*************************************************************************************************/
 
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//int scoreFor(int player, struct gameState *state);
//victory cards: estate = +1, duchy = +3, province = +6
//curse card: curse = -1
//action cards: great_hall = +1, gardens = +(full_deck_count/10) 

int main() {
	int i, expectedScore = 0, result = 0, fullDeck = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState test;

	printf("\n");
	printf("Testing dominion.c scoreFor() function . . . \n"); 

	//initialize the game
	//srand(time(NULL));
	initializeGame(2, k, 101, &test);
	
	//test 1: test same-size decks with victory cards 

	//initiating the 3 decks with bogus cards of no values 
	test.handCount[0] = 0;
	test.discardCount[0] = 0;
	test.deckCount[0] = 0;
	for (i = 0; i < 9; i++) {		
		test.hand[0][i] = copper;
		test.discard[0][i] = copper;
		test.deck[0][i] = copper;
		test.handCount[0]++; 
		test.discardCount[0]++;
		test.deckCount[0]++;
	}

	//filling the 3 decks with victory cards
	for (i = 0; i < 1; i++) {
		test.hand[0][i] = estate;
		test.discard[0][i] = estate;
		test.deck[0][i] = estate;
	}
	for (i = 1; i < 3; i++) {
		test.hand[0][i] = duchy;
		test.discard[0][i] = duchy;
		test.deck[0][i] = duchy;
	}	
	for (i = 3; i < 6; i++) {
		test.hand[0][i] = province;
		test.discard[0][i] = province;
		test.deck[0][i] = province;
	}

	//verifying result
	fullDeck = test.handCount[0] + test.discardCount[0] + test.deckCount[0];
	expectedScore = 3 * ((1 * 1) + (2 * 3) + (3 * 6));
	result = scoreFor(0, &test);
	printf("TEST 1 (same-size decks with victory cards only): \n");	
	printf(" - Total hand count: %d = %d estates + %d duchys + %d provinces + %d others\n", test.handCount[0], 1, 2, 3, test.handCount[0] - 6);
	printf(" - Total discard count: %d = %d estates + %d duchys + %d provinces + %d others\n", test.discardCount[0], 1, 2, 3, test.discardCount[0] - 6);
	printf(" - Total deck count: %d = %d estates + %d duchys + %d provinces + %d others\n", test.deckCount[0], 1, 2, 3, test.deckCount[0] - 6);
	printf(" - Full deck count: %d\n", fullDeck);
	printf(" - Expected score = %d; Result = %d\n", expectedScore, result);
	if (result != expectedScore) 
		printf(" - FAIL!\n"); 
	else
		printf(" - PASS!\n");

	//test 2: test varying-size decks with victory cards 

	//initiating the 3 decks with bogus cards of no values 
	test.handCount[0] = 0;
	test.discardCount[0] = 0;
	test.deckCount[0] = 0;
	for (i = 0; i < 9; i++) {		
		test.hand[0][i] = copper;
		test.handCount[0]++; 
	}
	for (i = 0; i < 5; i++) {
		test.discard[0][i] = copper;
		test.discardCount[0]++;
	}
	for (i = 0; i < 7; i++) { 
		test.deck[0][i] = copper;
		test.deckCount[0]++;
	}

	//filling the 3 decks with victory cards
	for (i = 0; i < 1; i++) {
		test.hand[0][i] = estate;
		test.discard[0][i] = estate;
		test.deck[0][i] = estate;
	}
	for (i = 1; i < 3; i++) {
		test.hand[0][i] = duchy;
		test.discard[0][i] = duchy;
		test.deck[0][i] = duchy;
	}	
	for (i = 3; i < 6; i++) {
		test.hand[0][i] = province;
		test.deck[0][i] = province;
	}
	test.discard[0][3] = province;
	test.discard[0][4] = province;

	//verifying result
	fullDeck = test.handCount[0] + test.discardCount[0] + test.deckCount[0];
	expectedScore = 3 * ((1 * 1) + (2 * 3)) + (8 * 6);
	result = scoreFor(0, &test);
	printf("TEST 2 (varying-sized decks with victory cards only): \n");	
	printf(" - Total hand count: %d = %d estates + %d duchys + %d provinces + %d others\n", test.handCount[0], 1, 2, 3, test.handCount[0] - 6);
	printf(" - Total discard count: %d = %d estates + %d duchys + %d provinces + %d others\n", test.discardCount[0], 1, 2, 2, test.discardCount[0] - 5);
	printf(" - Total deck count: %d = %d estates + %d duchys + %d provinces + %d others\n", test.deckCount[0], 1, 2, 3, test.deckCount[0] - 6);
	printf(" - Full deck count: %d\n", fullDeck);
	printf(" - Expected score = %d; Result = %d\n", expectedScore, result);
	if (result != expectedScore) 
		printf(" - FAIL!\n"); 
	else
		printf(" - PASS!\n");

	//test 3: test curse card
	
	//initiating the 3 decks with bogus cards of no values 
	test.handCount[0] = 0;
	test.discardCount[0] = 0;
	test.deckCount[0] = 0;
	for (i = 0; i < 9; i++) {		
		test.hand[0][i] = copper;
		test.discard[0][i] = copper;
		test.deck[0][i] = copper;
		test.handCount[0]++; 
		test.discardCount[0]++;
		test.deckCount[0]++;
	}

	//filling the 3 decks with victory cards
	for (i = 0; i < 1; i++) {
		test.hand[0][i] = estate;
		test.discard[0][i] = estate;
		test.deck[0][i] = estate;
	}
	for (i = 1; i < 3; i++) {
		test.hand[0][i] = duchy;
		test.discard[0][i] = duchy;
		test.deck[0][i] = duchy;
	}	
	for (i = 3; i < 6; i++) {
		test.hand[0][i] = province;
		test.discard[0][i] = province;
		test.deck[0][i] = province;
	}

	//slip curse cards into the hand deck
	for (i = 6; i < 8; i++) 
		test.hand[0][i] = curse;

	//verifying result
	fullDeck = test.handCount[0] + test.discardCount[0] + test.deckCount[0];
	expectedScore = 3 * ((1 * 1) + (2 * 3) + (3 * 6)) - 2;
	result = scoreFor(0, &test);
	printf("TEST 3 (same-sized decks with victory & curse cards): \n");	
	printf(" - Total hand count: %d = %d estates + %d duchys + %d provinces + %d curses + %d others\n", test.handCount[0], 1, 2, 3, 2, test.handCount[0] - 8);
	printf(" - Total discard count: %d = %d estates + %d duchys + %d provinces + %d curses + %d others\n", test.discardCount[0], 1, 2, 3, 0, test.discardCount[0] - 6);
	printf(" - Total deck count: %d = %d estates + %d duchys + %d provinces + %d curses + %d others\n", test.deckCount[0], 1, 2, 3, 0, test.deckCount[0] - 6);
	printf(" - Full deck count: %d\n", fullDeck);
	printf(" - Expected score = %d; Result = %d\n", expectedScore, result);
	if (result != expectedScore) 
		printf(" - FAIL!\n"); 
	else
		printf(" - PASS!\n");

	//test 4: test great hall card
	
	//slip 2 great hall cards into the discard pile
	for (i = 6; i < 8; i++) 
		test.discard[0][i] = great_hall;

	//verifying result
	fullDeck = test.handCount[0] + test.discardCount[0] + test.deckCount[0];
	expectedScore = 3 * ((1 * 1) + (2 * 3) + (3 * 6)) - 2 + 2;
	result = scoreFor(0, &test);
	printf("TEST 4 (same-sized decks with victory, curse & great hall cards): \n");	
	printf(" - Total hand count: %d = %d estates + %d duchys + %d provinces + %d curses + %d great halls + %d others\n", test.handCount[0], 1, 2, 3, 2, 0, test.handCount[0] - 8);
	printf(" - Total discard count: %d = %d estates + %d duchys + %d provinces + %d curses + %d great halls + %d others\n", test.discardCount[0], 1, 2, 3, 0, 2, test.discardCount[0] - 8);
	printf(" - Total deck count: %d = %d estates + %d duchys + %d provinces + %d curses + %d great halls + %d others\n", test.deckCount[0], 1, 2, 3, 0, 0, test.deckCount[0] - 6);
	printf(" - Full deck count: %d\n", fullDeck);
	printf(" - Expected score = %d; Result = %d\n", expectedScore, result);
	if (result != expectedScore) 
		printf(" - FAIL!\n"); 
	else
		printf(" - PASS!\n");
	
	//test 5: test gardens card

	//slip 2 garden cards into the deck pile
	for (i = 6; i < 8; i++) 
		test.deck[0][i] = gardens;

	//verifying result
	fullDeck = test.handCount[0] + test.discardCount[0] + test.deckCount[0];
	expectedScore = 3 * ((1 * 1) + (2 * 3) + (3 * 6)) - 2 + 2 + (2 * floor(fullDeck/10));
	result = scoreFor(0, &test);
	printf("TEST 5 (same-sized decks with victory, curse, great hall & gardens cards): \n");	
	printf(" - Total hand count: %d = %d estates + %d duchys + %d provinces + %d curses + %d great halls + %d gardenses + %d others\n", test.handCount[0], 1, 2, 3, 2, 0, 0, test.handCount[0] - 8);
	printf(" - Total discard count: %d = %d estates + %d duchys + %d provinces + %d curses + %d great halls + %d gardenses + %d others\n", test.discardCount[0], 1, 2, 3, 0, 2, 0, test.discardCount[0] - 8);
	printf(" - Total deck count: %d = %d estates + %d duchys + %d provinces + %d curses + %d great halls + %d gardenses + %d others\n", test.deckCount[0], 1, 2, 3, 0, 0, 2, test.deckCount[0] - 8);
	printf(" - Full deck count: %d\n", fullDeck);
	printf(" - Expected score = %d; Result = %d\n", expectedScore, result);
	if (result != expectedScore) 
		printf(" - FAIL!\n"); 
	else
		printf(" - PASS!\n");
	printf("\n");

	return 0;
}
