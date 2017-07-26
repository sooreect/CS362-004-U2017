/*************************************************************************************************
 * Author: Tida Sooreechine
 * Date: 7/15/2017
 * Program: CS362 Assignment 3 Unit Test 2
 * Description: A program consisting of tests for dominion.c's discardCard() function
*************************************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag);

int main() {

	int randNum, expectedHand, expectedPlayed;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState test;

	printf("\n");
	printf("Testing dominion.c discardCard() function . . . \n"); 

	//initialize the game
	srand(time(NULL));
	initializeGame(2, k, 101, &test);

	//test 1: discard a valid played card
	expectedHand = test.handCount[0];
	expectedPlayed = test.playedCardCount;
	randNum = rand() % expectedHand;
	printf("TEST 1 (Discarding a valid played card - card #%d of %d):\n", randNum + 1, test.handCount[0]);
	printf(" - Before - Hand count = %d, Played pile count = %d\n", test.handCount[0], test.playedCardCount); 
	discardCard(randNum, 0, &test, 0);
	expectedHand--;
	expectedPlayed++;
	printf(" - After - Hand count = %d & Played pile count = %d\n", test.handCount[0], test.playedCardCount); 
	if ((test.handCount[0] == expectedHand) && (test.playedCardCount == expectedPlayed))
		printf(" - PASS!\n");
	else
		printf(" - FAIL!\n");

	//test 2: discard a valid trash-flagged card
	expectedHand = test.handCount[0];
	expectedPlayed = test.playedCardCount;
	randNum = rand() % expectedHand;
	printf("TEST 2 (Discarding a to-be-trashed card - card #%d of %d):\n", randNum + 1, test.handCount[0]);
	printf(" - Before - Hand count = %d, Played pile count = %d\n", test.handCount[0], test.playedCardCount); 
	discardCard(randNum, 0, &test, 1);
	expectedHand--;
	printf(" - After - Hand count = %d, Played pile count = %d\n", test.handCount[0], test.playedCardCount); 
	if ((test.handCount[0] == expectedHand) && (test.playedCardCount == expectedPlayed))
		printf(" - PASS!\n");
	else
		printf(" - FAIL!\n");

	//test 3: discard an invalid card, part 1
	expectedHand = test.handCount[0];
	expectedPlayed = test.playedCardCount;
	printf("TEST 3 (Discarding a non-existing card - card #%d of %d):\n", test.handCount[0] + 1, test.handCount[0]);
	printf(" - Before - Hand count = %d, Played pile count = %d\n", test.handCount[0], test.playedCardCount); 
	discardCard(test.handCount[0] + 1, 0, &test, 0);
	printf(" - After - Hand count = %d & Played pile count = %d\n", test.handCount[0], test.playedCardCount); 
	if ((test.handCount[0] == expectedHand) && (test.playedCardCount == expectedPlayed))
		printf(" - PASS!\n");
	else
		printf(" - FAIL!\n");

	//test 4: discard an invalid card, part 2
	expectedHand = test.handCount[0];
	expectedPlayed = test.playedCardCount;
	printf("TEST 4 (Discarding an invalid card - card #-1 of %d):\n", test.handCount[0]);
	printf(" - Before - Hand count = %d, Played pile count = %d\n", test.handCount[0], test.playedCardCount); 
	discardCard(-1, 0, &test, 0);
	printf(" - After - Hand count = %d & Played pile count = %d\n", test.handCount[0], test.playedCardCount); 
	if ((test.handCount[0] == expectedHand) && (test.playedCardCount == expectedPlayed))
		printf(" - PASS!\n");
	else
		printf(" - FAIL!\n");

	//test 5: discard a card from zero handsize
	while (test.handCount[0] > 0) {
		discardCard(0, 0, &test, 0);
	}
	expectedHand = test.handCount[0];
	expectedPlayed = test.playedCardCount;
	printf("TEST 5 (Discarding a card from zero handsize):\n");
	printf(" - Before - Hand count = %d, Played pile count = %d\n", test.handCount[0], test.playedCardCount); 
	discardCard(0, 0, &test, 0);
	printf(" - After - Hand count = %d & Played pile count = %d\n", test.handCount[0], test.playedCardCount); 
	if ((test.handCount[0] == expectedHand) && (test.playedCardCount == expectedPlayed))
		printf(" - PASS!\n");
	else
		printf(" - FAIL!\n");
	printf("\n");
 
	return 0;
}

