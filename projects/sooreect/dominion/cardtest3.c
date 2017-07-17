/************************************************************************************************
 * Author: Tida Sooreechine
 * Date: 7/16/2017
 * Program: CS362 Assignment 3 Card Test 3 
 * Description: A program for testing dominion.c's Village card implementation
*************************************************************************************************/
 
#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


int main() {

	int originalHandCount, numActions, numBuys, opponentSize, handPos = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState test;

	printf("\n");
	printf("Testing dominion.c Village card implementation . . . \n"); 

	//initialize the game
	initializeGame(2, k, 101, &test);
	opponentSize = test.handCount[1];
	numActions = test.numActions + 2;
	numBuys = test.numBuys;
	
	//replace a card in player 0's hand with village
	test.hand[0][handPos] = village;

	originalHandCount = test.handCount[0];
	
	//use village card
	cardEffect(village, 0, 0, 0, &test, handPos, 0);

	//3 conditions to satisfy:

	//condition 1 - player 0 gains 1 additional card, discards the used village, ends with original count
	printf(" - CONDITION 1 (handsize remains the same after using village card): ");
	if (test.handCount[0] == originalHandCount) 
		printf("PASS!\n");
	else
		printf("FAIL!\n");  

	//condition 2 - test other changes to player 0' stats
	printf(" - CONDITION 2 (number of actions increases by 2 & number of buys remains unchanged): ");
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
