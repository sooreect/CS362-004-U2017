/************************************************************************************************
 * Author: Tida Sooreechine
 * Date: 7/15/2017
 * Program: CS362 Assignment 3 Unit Test 4 
 * Description: A program consisting of tests for dominion.c's fullDeckCount() function
*************************************************************************************************/
 
#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//int fullDeckCount(int player, int card, struct gameState *state);

int main() {

	int i, target, expectedCount, count;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState test;

	printf("\n");
	printf("Testing dominion.c fullDeckCount() function . . . \n"); 

	//initialize the game
	initializeGame(2, k, 101, &test);
	target = 6; //search for gold
	
	//test 1: zero cards - should return zero
	
	//initialize deck
	test.handCount[0] = 0;
	test.discardCount[0] = 0;
	test.deckCount[0] = 0;
	expectedCount = 0;
	count = fullDeckCount(0, target, &test);
	printf("TEST 1 (search for golds in empty piles): Expected = %d, Result = %d; ", expectedCount, count);
	if (count != expectedCount)
		printf("FAIL!\n");
	else 
		printf("PASS!\n");

	//test 2: cards only in one deck - should return a positive value if target exists
	test.handCount[0] = 9;
	for (i = 0; i < test.handCount[0]; i++) {
		if ((i % 2) == 0) {
			test.hand[0][i] = 6;
			expectedCount++;
		}
		else 
			test.hand[0][i] = 5;
	}
	count = fullDeckCount(0, target, &test);
	printf("TEST 2 (search for golds when cards only exist in hands): Expected = %d, Result = %d; ", expectedCount, count);
	if (count != expectedCount)
		printf("FAIL!\n");
	else 
		printf("PASS!\n");

	//test 3: varying number of targets in varying-sized deck - should return a positive value if target exists
	test.discardCount[0] = 7;
	for (i = 0; i < test.discardCount[0]; i++) {
		if ((i == 2) || (i == 3)) {
			test.discard[0][i] = 6;
			expectedCount++;
		}
		else
			test.discard[0][i] = 4;
	}
	test.deckCount[0] = 11;
	for (i = 0; i < test.deckCount[0]; i++) {
		if (i >= 9) {
			test.deck[0][i] = 6;
			expectedCount++;
		}
		else
			test.deck[0][i] = 7;
	}
	count = fullDeckCount(0, target, &test);
	printf("TEST 3 (search for golds of varying amounts in random positions in non-empty piles): Expected = %d, Result = %d; ", expectedCount, count);
	if (count != expectedCount)
		printf("FAIL!\n");
	else 
		printf("PASS!\n");

	//test 4: target does not exist - should return zero 
	//use existing decks
	target = 9;	//search for feasts
	expectedCount = 0;
	count = fullDeckCount(0, target, &test);
	printf("TEST 4 (search for non-existing feast cards): Expected = %d, Result = %d; ", expectedCount, count);
	if (count != expectedCount)
		printf("FAIL!\n");
	else 
		printf("PASS!\n");
	
	//test 5: invalid target - should return zero
	//use existing decks
	target = -9;	//invalid card
	count = fullDeckCount(0, target, &test);
	printf("TEST 5 (search for an invalid card): Expected = %d, Result = %d; ", expectedCount, count);
	if (count != expectedCount)
		printf("FAIL!\n");
	else 
		printf("PASS!\n");
	printf("\n");
	
	return 0;
}
