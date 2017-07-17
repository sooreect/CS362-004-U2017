/************************************************************************************************
 * Author: Tida Sooreechine
 * Date: 7/16/2017
 * Program: CS362 Assignment 3 Card Test 1
 * Description: A program for testing dominion.c's Adventurer card implementation
*************************************************************************************************/
 
#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


int main() {

	int i, originalHandCount, originalTreasurePoints, numActions, numBuys, opponentSize;
	int treasureInDeck = 0, treasurePoints = 0, handPos = 4;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState testA, testB, testC;

	printf("\n");
	printf("Testing dominion.c Adventurer card implementation . . . \n"); 

	//3 conditions to satisfy:

	//condition 1 - player 0 gains 0, 1, or 2 additional treasure cards, discards the used adventurer, 
	//ends with original count or original count + 1 or original count - 1
	printf(" - CONDITION 1 (player gains correct number of treasure cards):\n");
	
	//condition 1A
	printf(" - CONDITION 1A (if there are at least 2 treasure cards left, player gains 2 and discards used adventurer): ");
	initializeGame(2, k, 101, &testA);
	opponentSize = testA.handCount[1];
	numActions = testA.numActions;
	numBuys = testA.numBuys;
	
	//replace a card in player 0's hand with adventurer
	testA.hand[0][handPos] = adventurer;

	//check player 0's hand
	originalHandCount = testA.handCount[0];
	for (i = 0; i < testA.handCount[0]; i++) {
		if (testA.hand[0][i] == copper)
			treasurePoints += 1;
		else if (testA.hand[0][i] == silver)
			treasurePoints += 2;
		else if (testA.hand[0][i] == gold)
			treasurePoints += 3;
	}
	originalTreasurePoints = treasurePoints;

	//check how many treasure cards there are in deck and discard piles
	for (i = 0; i < testA.deckCount[0]; i++) {
		if (testA.deck[0][i] == copper)
			treasureInDeck++;
		else if (testA.deck[0][i] == silver)
			treasureInDeck++;
		else if (testA.deck[0][i] == gold)
			treasureInDeck++;
	}
	for (i = 0; i < testA.discardCount[0]; i++) {
		if (testA.discard[0][i] == copper)
			treasureInDeck++;
		else if (testA.discard[0][i] == silver)
			treasureInDeck++;
		else if (testA.discard[0][i] == gold)
			treasureInDeck++;
	}

	//use adventurer card
	cardEffect(adventurer, 0, 0, 0, &testA, handPos, 0);
	treasurePoints = 0;
	for (i = 0; i < testA.handCount[0]; i++) {
		if (testB.hand[0][i] == copper)
			treasurePoints += 1;
		else if (testA.hand[0][i] == silver)
			treasurePoints += 2;
		else if (testA.hand[0][i] == gold)
			treasurePoints += 3;
	}

	if ((testA.handCount[0] == originalHandCount + 1) && (treasurePoints > originalTreasurePoints + 1) && (testA.hand[0][handPos] != adventurer))
		printf("PASS\n");
	else
		printf("FAIL\n");

	//condition 1b
	printf(" - CONDITION 1B (if there is just 1 treasure card in deck & discard piles, player gains 1 and discard used adventurer): ");
	initializeGame(2, k, 101, &testB);

	//make sure there's only one treasure card in the deck
	for (i = 0; i < testB.deckCount[0]; i++) 
		testB.deck[0][i] = duchy;
	testB.deck[0][0] = copper;	

	//replace a card in player 0's hand with adventurer
	testB.hand[0][handPos] = adventurer;

	//check player 0's hand
	treasurePoints = 0;
	originalHandCount = testB.handCount[0];
	for (i = 0; i < testB.handCount[0]; i++) {
		if (testB.hand[0][i] == copper)
			treasurePoints += 1;
		else if (testB.hand[0][i] == silver)
			treasurePoints += 2;
		else if (testB.hand[0][i] == gold)
			treasurePoints += 3;
	}
	originalTreasurePoints = treasurePoints;

	//check how many treasure cards there are in deck and discard piles
	treasureInDeck = 0;
	for (i = 0; i < testB.deckCount[0]; i++) {
		if (testB.deck[0][i] == copper)
			treasureInDeck++;
		else if (testB.deck[0][i] == silver)
			treasureInDeck++;
		else if (testB.deck[0][i] == gold)
			treasureInDeck++;
	}
	for (i = 0; i < testB.discardCount[0]; i++) {
		if (testB.discard[0][i] == copper)
			treasureInDeck++;
		else if (testB.discard[0][i] == silver)
			treasureInDeck++;
		else if (testB.discard[0][i] == gold)
			treasureInDeck++;
	}

	//use adventurer card
	cardEffect(adventurer, 0, 0, 0, &testB, handPos, 0);

	treasurePoints = 0;
	for (i = 0; i < testB.handCount[0]; i++) {
		if (testB.hand[0][i] == copper)
			treasurePoints += 1;
		else if (testB.hand[0][i] == silver)
			treasurePoints += 2;
		else if (testB.hand[0][i] == gold)
			treasurePoints += 3;
	}

	if ((testB.handCount[0] == originalHandCount) && (treasurePoints > originalTreasurePoints) && (testB.hand[0][handPos] != adventurer))
		printf("PASS\n");
	else
		printf("FAIL\n");

	//condition 1c
	printf(" - CONDITION 1C (if there are zero treasure cards to be drawned, player gains 0 and discards used adventurer): ");
	initializeGame(2, k, 101, &testC);

	//make sure there's only one treasure card in the deck
	for (i = 0; i < testC.deckCount[0]; i++) 
		testC.deck[0][i] = duchy;

	//replace a card in player 0's hand with adventurer
	testC.hand[0][handPos] = adventurer;

	//check player 0's hand
	treasurePoints = 0;
	originalHandCount = testC.handCount[0];
	for (i = 0; i < testC.handCount[0]; i++) {
		if (testC.hand[0][i] == copper)
			treasurePoints += 1;
		else if (testC.hand[0][i] == silver)
			treasurePoints += 2;
		else if (testC.hand[0][i] == gold)
			treasurePoints += 3;
	}
	originalTreasurePoints = treasurePoints;

	//check how many treasure cards there are in deck and discard piles
	treasureInDeck = 0;
	for (i = 0; i < testC.deckCount[0]; i++) {
		if (testC.deck[0][i] == copper)
			treasureInDeck++;
		else if (testC.deck[0][i] == silver)
			treasureInDeck++;
		else if (testC.deck[0][i] == gold)
			treasureInDeck++;
	}
	for (i = 0; i < testC.discardCount[0]; i++) {
		if (testC.discard[0][i] == copper)
			treasureInDeck++;
		else if (testC.discard[0][i] == silver)
			treasureInDeck++;
		else if (testC.discard[0][i] == gold)
			treasureInDeck++;
	}

	//use adventurer card
	cardEffect(adventurer, 0, 0, 0, &testC, handPos, 0);

	treasurePoints = 0;
	for (i = 0; i < testC.handCount[0]; i++) {
		if (testC.hand[0][i] == copper)
			treasurePoints += 1;
		else if (testC.hand[0][i] == silver)
			treasurePoints += 2;
		else if (testC.hand[0][i] == gold)
			treasurePoints += 3;
	}

	if ((testC.handCount[0] <= originalHandCount) && (treasurePoints == originalTreasurePoints) && (testC.hand[0][handPos] != adventurer))
		printf("PASS\n");
	else
		printf("FAIL\n");

	//condition 2 - no other changes to player 0
	printf(" - CONDITION 2 (no changes to number of actions or buys): ");
	if ((testA.numActions == numActions) && (testA.numBuys == numBuys))
		printf("PASS!\n");
	else
		printf("FAIL!\n");

	//condition 3 - no changes to player 1's handsize
	printf(" - CONDITION 3 (no changes to opponent's handsize): ");
	if (testA.handCount[1] == opponentSize) 
		printf("PASS!\n");
	else
		printf("FAIL!\n");  
	printf("\n");

	return 0;
}
