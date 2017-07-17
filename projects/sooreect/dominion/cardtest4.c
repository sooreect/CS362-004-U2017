/************************************************************************************************
 * Author: Tida Sooreechine
 * Date: 7/16/2017
 * Program: CS362 Assignment 3 Card Test 4 
 * Description: A program for testing dominion.c's Council Room card implementation
*************************************************************************************************/
 
#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


int main() {

	int newHandCount, numActions, numBuys, opponentSize, handPos = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState test;

	printf("\n");
	printf("Testing dominion.c Council Room card implementation . . . \n"); 

	//initialize the game
	initializeGame(2, k, 101, &test);
	opponentSize = test.handCount[1];
	numActions = test.numActions;
	numBuys = test.numBuys + 1;
	
	//replace a card in player 0's hand with council room
	test.hand[0][handPos] = council_room;

	newHandCount = test.handCount[0] + 3;
	
	//use council room card
	cardEffect(council_room, 0, 0, 0, &test, handPos, 0);

	//3 conditions to satisfy:

	//condition 1 - player 0 gains 4 additional card, discards the used village, ends with original count + 3
	printf(" - CONDITION 1 (handsize increases by 3 after using council room card): ");
	if (test.handCount[0] == newHandCount) 
		printf("PASS!\n");
	else
		printf("FAIL!\n");  

	//condition 2 - test other changes to player 0' stats
	printf(" - CONDITION 2 (number of actions remains unchanged & number of buys increases by 1): ");
	if ((test.numActions == numActions) && (test.numBuys == numBuys))
		printf("PASS!\n");
	else
		printf("FAIL!\n");

	//condition 3 - player 1's draws a card
	printf(" - CONDITION 3 (opponent's handsize increases by 1): ");
	if (test.handCount[1] == opponentSize + 1) 
		printf("PASS!\n");
	else
		printf("FAIL!\n");  
	printf("\n");

	return 0;
}
