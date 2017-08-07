/************************************************************************************************
 * Author: Tida Sooreechine
 * Date: 8/6/2017
 * Program: CS362 Assignment 5 - Random Test Adventurer Card for BWALTON
 * Description: A random tester for refactored version of dominion.c's Adventurer card 
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

//adventurer card implementation
//player gains up to 2 aditional treasure cards from deck, discards the used adventurer card, ends with original hand count + (-1 to 1)

int main() {
	
	srand(time(NULL));

	int i, j, x, errors, seed, handPos, wrongCards;
	int treasuresHand, treasuresDeck, treasuresDiscard, treasuresToDraw, treasuresTotal, treasuresHand2, treasuresDeck2, treasuresDiscard2, treasuresTotal2;
	int numPlayers = 2;
	int numTests = 1000; 
	int successCounts = 0;
	int successCounts1 = 0;
	int successCounts2 = 0;
	float successPercent = 0;
	int tempHand[MAX_HAND];
	int k[10] = {adventurer, baron, council_room, feast, gardens, great_hall, mine, remodel, smithy, village};
	struct gameState G1, G2;

	printf("\n");
	printf("Random testing of Adventurer: \n\n"); 

	//begin testing iterations	
	for (x = 0; x < numTests; x++) {
	
		printf("Iteration %d: ", x + 1);
	
		//initialize the game
		seed = rand();
		initializeGame(numPlayers, k, seed, &G1);
		errors = 0;			
		treasuresHand = 0;
		treasuresDeck = 0;
		treasuresDiscard = 0;
		treasuresToDraw = 0;	
		treasuresTotal = 0;
		treasuresHand2 = 0;
		treasuresDeck2 = 0;
		treasuresDiscard2 = 0;
		treasuresTotal2 = 0;	
		wrongCards = 0;
		
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
			G1.deckCount[i] = rand() % 50;	
			for (j = 0; j < G1.deckCount[i]; j++) 
				G1.deck[i][j] = rand() % 27;
				
			//set up discard
			G1.discardCount[i] = rand() % 50;	
			for (j = 0; j < G1.discardCount[i]; j++) 
				G1.discard[i][j] = rand() % 27;
		}

		//place adventurer card in player's hand
		handPos = rand() % G1.handCount[0];
		G1.hand[0][handPos] = adventurer;

		//make copy of game state
		memcpy(&G2, &G1, sizeof(struct gameState));

		//play refactored adventurer card
		if (x < (numTests / 2))
			cardEffect(adventurer, 0, 0, 0, &G2, handPos, 0);
		else 
			adventurerEffect(&G2); 
	
		//check original treasure card counts in the three piles
		for (i = 0; i < G1.handCount[0]; i++) {
			if ((G1.hand[0][i] == copper) || (G1.hand[0][i] == silver) || (G1.hand[0][i] == gold))
				treasuresHand++;
		}
		for (i = 0; i < G1.deckCount[0]; i++) {
			if ((G1.deck[0][i] == copper) || (G1.deck[0][i] == silver) || (G1.deck[0][i] == gold))
				treasuresDeck++;
		}
		for (i = 0; i < G1.discardCount[0]; i++) {
			if ((G1.discard[0][i] == copper) || (G1.discard[0][i] == silver) || (G1.discard[0][i] == gold))
				treasuresDiscard++;
		}
		treasuresToDraw = treasuresDeck + treasuresDiscard;
		treasuresTotal = treasuresDeck + treasuresDiscard + treasuresHand;
		
		//check treasure card counts after play
		for (i = 0; i < G2.handCount[0]; i++) {
			if ((G2.hand[0][i] == copper) || (G2.hand[0][i] == silver) || (G2.hand[0][i] == gold))
				treasuresHand2++;
		}
		for (i = 0; i < G2.deckCount[0]; i++) {
			if ((G2.deck[0][i] == copper) || (G2.deck[0][i] == silver) || (G2.deck[0][i] == gold))
				treasuresDeck2++;
		}
		for (i = 0; i < G2.discardCount[0]; i++) {
			if ((G2.discard[0][i] == copper) || (G2.discard[0][i] == silver) || (G2.discard[0][i] == gold))
				treasuresDiscard2++;
		}
		treasuresTotal2 = treasuresDeck2 + treasuresDiscard2 + treasuresHand2;

		//check total treasure cards before and after play
		if (treasuresTotal != treasuresTotal2) {
			printf("\n");
			printf(" - FAIL: Total treasure cards are different before and after play");
			errors = 1;
		}		
		//check player's hand
		//3 cases
		//case 1: draw 2 treasure cards and discard played adventurer (original hand count + 1)
		//case 2: draw 1 treasure card and discard played adventurer (original hand count + 0)
		//case 3: draw 0 cards and discard played adventurer (original hand count - 1)
		if (treasuresToDraw > 1) {
			//check hand count
			if (G2.handCount[0] != G1.handCount[0] + 1) {
				printf("\n");
				printf(" - FAIL: Incorrect hand count for player 0 ");
				printf("(Expected: %d, Actual: %d)", G1.handCount[0] + 1, G2.handCount[0]);
				errors = 1;
			}
			else { 
				//if hand count is correct, check that new cards added are treasure cards 
				//new cards should be in old adventurer card's position and be the last card added to deck
				if (G2.hand[0][handPos] != copper) {
					if (G2.hand[0][handPos] != silver) {
						if (G2.hand[0][handPos] != gold) {
							wrongCards++;
							errors = 1;
						}
					}
				}
				if (G2.hand[0][G2.handCount[0] - 1] != copper) {
					if (G2.hand[0][G2.handCount[0] - 1] != silver) {
						if (G2.hand[0][G2.handCount[0] - 1] != gold) {
							wrongCards++;
							errors = 1;
						}
					}
				}
				if (wrongCards == 2) {
					printf("\n");
					printf(" - FAIL: New cards added to hand are not treasure cards");
				}
				else if (wrongCards == 1) {
					printf("\n");
					printf(" - FAIL: New card added to hand is not a treasure card");	
				}
			}
		}
		else if (treasuresToDraw == 1) {
			if (G2.handCount[0] != G1.handCount[0]) {
				printf("\n");
				printf(" - FAIL: Incorrect hand count for player 0 ");
				printf("(Expected: %d, Actual: %d)", G1.handCount[0], G2.handCount[0]);
				errors = 1;
			}
			else {
				if (G2.hand[0][handPos] != copper) {
					if (G2.hand[0][handPos] != silver) {
						if (G2.hand[0][handPos] != gold) {
							printf("\n");
							printf(" - FAIL: New card added to hand is not a treasure card");
							errors = 1;
						}
					}
				}
			}
		}
		else { 
			if (G2.handCount[0] != G1.handCount[0] - 1) {
				printf("\n");
				printf(" - FAIL: Incorrect hand count for player 0 ");
				printf("(Expected: %d, Actual: %d)", G1.handCount[0] - 1, G2.handCount[0]);
				errors = 1;
			}
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

		//discard deck increases by at least 1, depending on the randomness of cards in deck pile
		if (G2.discardCount[0] <= G1.discardCount[0]) {
			printf("\n");
			printf(" - FAIL: Adventurer card was not discarded properly after play");
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
	printf("Total successful tests using adventurerEffect(): %d of %d (%.2f%%)\n", successCounts2, numTests / 2, successPercent);
	successCounts = successCounts1 + successCounts2;
	successPercent = (float)successCounts / numTests * 100;
	printf("Total successful tests: %d of %d (%.2f%%)\n", successCounts, numTests, successPercent);
	printf("\n");
	return 0;
}

