/************************************************************************************************
 * Author: Tida Sooreechine
 * Date: 7/16/2017
 * Program: CS362 Assignment 3 Card Test 2 
 * Description: A program for testing dominion.c's Smithy card implementation
*************************************************************************************************/
 
#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


int main() {

	int newHandCount, numActions, numBuys, opponentSize, handPos = 3;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState test;

	printf("\n");
	printf("Testing dominion.c Smithy card implementation . . . \n"); 

	//initialize the game
	initializeGame(2, k, 101, &test);
	opponentSize = test.handCount[1];
	numActions = test.numActions;
	numBuys = test.numBuys;
	
	//replace a card in player 0's hand with smithy
	test.hand[0][handPos] = smithy;

	newHandCount = test.handCount[0] + 2;
	
	//use smithy card
	cardEffect(smithy, 0, 0, 0, &test, handPos, 0);

	//3 conditions to satisfy:

	//condition 1 - player 0 gains 3 additional cards, discards the used smithy, ends with original count + 2
	printf(" - CONDITION 1 (handsize should go up by a total of 2): ");
	if (test.handCount[0] == newHandCount) 
		printf("PASS!\n");
	else
		printf("FAIL!\n");  

	//condition 2 - no other changes to player 0
	printf(" - CONDITION 2 (no changes to number of actions or buys): ");
	if ((test.numActions == numActions) && (test.numBuys == numBuys))
		printf("PASS!\n");
	else
		printf("FAIL!\n");

	//condition 3 - no changes to player 1's handsize
	printf(" - CONDITION 3 (no changes to opponent's handsize): ");
	if (test.handCount[1] == opponentSize) 
		printf("PASS!\n");
	else
		printf("FAIL!\n");  
	printf("\n");

	return 0;
}
