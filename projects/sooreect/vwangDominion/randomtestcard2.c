/************************************************************************************************
 * Author: Tida Sooreechine
 * Date: 7/26/2017
 * Program: CS362 Assignment 4 - Random Test Card 2
 * Description: A random tester for dominion.c's Council Room card 
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
//for 4 players, there should be a total of 308 cards total

//council room card implementation
//player gains 4 aditional cards, discards the used council room, ends with original count + 3

int main() {
	
	srand(time(NULL));

	int i, j, x, errors, seed, numPlayers, handPos;
	int numTests = 1000; 
	int successCounts = 0;
	float successPercent = 0;
	int k[10] = {adventurer, baron, council_room, feast, gardens, great_hall, mine, remodel, smithy, village};
	struct gameState G1, G2;

	printf("\n");
	printf("Random testing of Council Room card: \n\n"); 
	//begin testing iterations	
	for (x = 0; x < numTests; x++) {
	
		printf("Iteration %d: ", x + 1);
	
		//initialize the game
		seed = rand();
		numPlayers = rand() % 3 + 2;
		initializeGame(numPlayers, k, seed, &G1);
		errors = 0;			

		//create player card piles	
		for (i = 0; i < numPlayers; i++) {	
			
			//set up hand
			if (i == 0)
				G1.handCount[i] = rand() % 6 + 5;	//player 1 gets a realistic number of 5-10 cards in hand
			else
				G1.handCount[i] = 5; //opponents have not had their turn yet, so they should have just 5 cards
			for (j = 0; j < G1.handCount[i]; j++) 
				G1.hand[i][j] = rand() % 27;	//27 possible choices of cards
		
			//set up deck
			G1.deckCount[i] = rand() % 40 + 10;	
			for (j = 0; j < G1.deckCount[i]; j++) 
				G1.deck[i][j] = rand() % 27;
		}
	
		//place council room card in player's hand
		handPos = rand() % G1.handCount[0];
		G1.hand[0][handPos] = council_room;

		//make copy of game state
		memcpy(&G2, &G1, sizeof(struct gameState));

		//play council room card
		cardEffect(council_room, 0, 0, 0, &G2, handPos, 0);
	
		//verify game states
		
		//hand count + 3
		if (G2.handCount[0] != G1.handCount[0] + 3) {
			printf("\n");
			printf(" - FAIL: Incorrect hand count for player 0 ");
			printf("(Expected: %d, Actual: %d)", G1.handCount[0] + 3, G2.handCount[0]);
			errors = 1;
		}

		//the other hand cards remain the same
		for (i = 0; i < G1.handCount[0]; i++) {
			if (i != handPos) {
				if (G2.hand[0][i] != G1.hand[0][i]) {
					printf("\n");
					printf(" - FAIL: Changes has been made to other cards");
					errors = 1;
					break;
				}
			}	
		}

		//deck count - 4
		if (G2.deckCount[0] != G1.deckCount[0] - 4) {
			printf("\n");
			printf(" - FAIL: Incorrect deck count for player 0 ");
			printf("(Expected: %d, Actual: %d)", G1.deckCount[0] - 4, G2.deckCount[0]);
			errors = 1;
		}

		//played count + 1
		if ((G2.playedCardCount != G1.playedCardCount + 1) && (G2.playedCards[G2.playedCardCount - 1] != council_room)) {
			printf("\n");
			printf(" - FAIL: Council Room card was not discarded properly after play");
			errors = 1;
		} 

		//number of actions stays the same
		if (G2.numActions != G1.numActions) {
			printf("\n");
			printf(" - FAIL: Incorrect number of actions for player 0 ");
			printf("(Expected: %d, Actual: %d)", G1.numActions, G2.numActions);
			errors = 1;
		}
		
		//number of buys + 1
		if (G2.numBuys != G1.numBuys + 1) {
			printf("\n");
			printf(" - FAIL: Incorrect number of buys for player 0 ");
			printf("(Expected: %d, Actual: %d)", G1.numBuys + 1, G2.numBuys);
			errors = 1;
		}
		
		//opponents' cards
		for (i = 1; i < numPlayers; i++) {
			//check opponents' hand counts: should increase by 1
			if (G2.handCount[i] != G1.handCount[i] + 1) {
				printf("\n");
				printf(" - FAIL: Incorrect hand count for player %d ", i);
				printf("(Expected: %d, Actual: %d)", G1.handCount[i] + 1, G2.handCount[i]);
				errors = 1;
			}
			//check opponent's deck counts: should decrease by 1
			if (G2.deckCount[i] != G1.deckCount[i] - 1) {
				printf("\n");
				printf(" - FAIL: Incorrect deck count for player %d ", i);
				printf("(Expected: %d, Actual: %d)", G1.deckCount[i] - 1, G2.deckCount[i]);
				errors = 1;
			}
			//check that the correct card was drawn from deck
			if (G2.hand[i][G2.handCount[i] - 1] != G1.deck[i][G1.deckCount[i] - 1]) {
				printf("\n");
				printf(" - FAIL: Incorrect card was added to hand for player %d", i);
				errors = 1;
			}
		}

		if (!errors) { 
			successCounts++;
			printf("PASS!\n"); 
		}
		else
			printf("\n");
	}

	printf("\n");
	printf("Summary: \n");
	successPercent = (float)successCounts / numTests * 100;
	printf("Total successful tests: %d of %d (%.2f%%)\n", successCounts, numTests, successPercent);
	printf("\n");

	return 0;
}

