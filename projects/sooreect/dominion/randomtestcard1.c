/************************************************************************************************
 * Author: Tida Sooreechine
 * Date: 7/26/2017
 * Program: CS362 Assignment 4 - Random Test Card 1
 * Description: A random tester for the refactored version of dominion.c's Smithy card 
*************************************************************************************************/

#include <math.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//for 2 players, there should be a total of 270 cards total

//smithy card implementation
//player gains 3 additional cards, discards the used smithy, ends with original count + 2

int main() {
	
	srand(time(NULL));

	int i, j, x, errors, seed, handPos;
	int numPlayers = 2;  
	int numTests = 1000; 
	int successCounts = 0;
	int successCounts1 = 0;
	int successCounts2 = 0;
	float successPercent = 0;
	int k[10] = {adventurer, baron, council_room, feast, gardens, great_hall, mine, remodel, smithy, village};
	struct gameState G1, G2;

	printf("\n");
	printf("Random testing of Smithy card: \n\n"); 

	//begin testing iterations	
	for (x = 0; x < numTests; x++) {
	
		printf("Iteration %d: ", x + 1);
	
		//initialize the game
		seed = rand();
		initializeGame(numPlayers, k, seed, &G1);
		errors = 0;			

		//create player card piles	
		for (i = 0; i < numPlayers; i++) {	
			
			//set up hand
			if (i == 0)
				G1.handCount[i] = rand() % 6 + 5;	//player 1 gets a realistic number of 5-10 cards in hand
			else
				G1.handCount[i] = 5; //opponent has not had their turn yet, so they should have just 5 cards
			for (j = 0; j < G1.handCount[i]; j++) 
				G1.hand[i][j] = rand() % 27;	//27 possible choices of cards
		
			//set up deck
			G1.deckCount[i] = rand() % 40 + 10;	
			for (j = 0; j < G1.deckCount[i]; j++) 
				G1.deck[i][j] = rand() % 27;
		}
	
		//place smithy card in player's hand
		handPos = rand() % G1.handCount[0];
		G1.hand[0][handPos] = smithy;

		//make copy of game state
		memcpy(&G2, &G1, sizeof(struct gameState));

		//play smithy
		if (x < (numTests / 2))
			cardEffect(smithy, 0, 0, 0, &G2, handPos, 0);
		else 
			smithyCard(&G2, handPos, 0);

		//verify game states
		
		//hand count + 2
		if (G2.handCount[0] != G1.handCount[0] + 2) {
			printf("\n");
			printf(" - FAIL: Incorrect hand count for player 0 ");
			printf("(Expected: %d, Actual: %d)", G1.handCount[0] + 2, G2.handCount[0]);
			errors = 1;
		}
	
		//the other hand cards remain the same
		for (i = 0; i < G1.handCount[0]; i++) {
			if (i != handPos) {
				if (G2.hand[0][i] != G1.hand[0][i]) {
					printf("\n");
					printf(" - FAIL: Changes has been made to other cards\n");
					errors = 1;
					break;
				}
			}	
		}
		
		//deck count - 3
		if (G2.deckCount[0] != G1.deckCount[0] - 3) {
			printf("\n");
			printf(" - FAIL: Incorrect deck count for player 0 ");
			printf("(Expected: %d, Actual: %d)", G1.deckCount[0] - 3, G2.deckCount[0]);
			errors = 1;
		}

		//played count + 1
		if ((G2.playedCardCount != G1.playedCardCount + 1) && (G2.playedCards[G2.playedCardCount - 1] != smithy)) {
			printf("\n");
			printf(" - FAIL: Smithy card was not discarded properly after play\n");
			errors = 1;
		}

		if (!errors) { 
			if (x < (numTests / 2)) 
				successCounts1++;
			else 
				successCounts2++;
			printf("PASS!\n"); 
		}
		else
			printf("\n");
			
	}

	printf("\n");
	printf("Summary: \n");
	successPercent = (float)successCounts1 / (numTests / 2) * 100;
	printf("Total successful tests using cardEffect(): %d of %d (%.2f%%)\n", successCounts1, numTests / 2, successPercent);
	successPercent = (float)successCounts2 / (numTests / 2) * 100;
	printf("Total successful tests using playSmithy(): %d of %d (%.2f%%)\n", successCounts2, numTests / 2, successPercent);
	successCounts = successCounts1 + successCounts2;
	successPercent = (float)successCounts / numTests * 100;
	printf("Total successful tests: %d of %d (%.2f%%)\n", successCounts, numTests, successPercent);
	printf("\n");

	return 0;
}

