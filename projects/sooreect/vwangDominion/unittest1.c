/*************************************************************************************************
 * Author: Tida Sooreechine
 * Date: 7/15/2017
 * Program: CS362 Assignment 3 Unit Test 1
 * Description: A program consisting of tests for dominion.c's updateCoins() function
*************************************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//int updateCoins(int player, struct gameState *state, int bonus);

int main() {

	int i, randNum, copperCount = 0, silverCount = 0, goldCount = 0, expectedSum = 0; 
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState test;

	printf("\n");
	printf("Testing dominion.c updateCoins() function . . . \n"); 

	//initialize the game
	srand(time(NULL));
	initializeGame(2, k, 101, &test);

	//test 1: minimum possible hand
	test.hand[0][0] = curse;
	test.hand[0][1] = smithy;
	test.hand[0][2] = duchy;
	test.hand[0][3] = feast;
	test.hand[0][4] = estate;
	updateCoins(0, &test, 0);
	printf("TEST 1 (0 treasures & 0 bonus): Expected = 0, Result = %d; ", test.coins);	
	if (test.coins != 0) 
		printf("FAIL!\n");
	else
		printf("PASS!\n");

	//test 2: large hand
	test.hand[0][0] = gold;
	test.hand[0][1] = gold;
	test.hand[0][2] = gold;
	test.hand[0][3] = gold;
	test.hand[0][4] = gold;
	updateCoins(0, &test, 100);
	printf("TEST 2 (5 golds & 100 bonus): Expected = 115, Result = %d; ", test.coins);	
	if (test.coins != 115) 
		printf("FAIL!\n");
	else
		printf("PASS!\n");

	//test 3: random hand with positive bonus
	for (i = 0; i < 5; i++) {
		randNum = rand() % (7 + 1 - 1) + 1;
		test.hand[0][i] = randNum;
		if (randNum == 4) 
			copperCount++;
		else if(randNum == 5)
			silverCount++;
		else if(randNum == 6)
			goldCount++;
	}
	expectedSum = (copperCount * 1) + (silverCount * 2) + (goldCount * 3) + 9;
	updateCoins(0, &test, 9);
	printf("TEST 3 (");
	if (copperCount != 0) {
		printf("%d copper", copperCount);
		if (silverCount != 0 || goldCount != 0)
			printf(", ");
	}
	if (silverCount != 0) {
		printf("%d silver", silverCount);
		if (goldCount != 0)
			printf(", ");
	}
	if (goldCount != 0) 
		printf("%d gold", goldCount);
	printf(" & 9 bonus): Expected = %d, Result = %d; ", expectedSum, test.coins);	
	if (test.coins != expectedSum) 
		printf("FAIL!\n");
	else
		printf("PASS!\n");

	//test 4: invalid bonus
	test.hand[0][0] = curse;
	test.hand[0][1] = smithy;
	test.hand[0][2] = duchy;
	test.hand[0][3] = feast;
	test.hand[0][4] = estate;
	updateCoins(0, &test, -9);
	printf("TEST 4 (0 treasures & -9 bonus): Expected = -9, Result = %d; ", test.coins);	
	if (test.coins != -9) 
		printf("FAIL!\n");
	else
		printf("PASS!\n");
	printf("\n");

	return 0;
}

