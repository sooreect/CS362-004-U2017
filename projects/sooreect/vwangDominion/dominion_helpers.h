#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state,
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3,
	       struct gameState *state, int handPos, int *bonus);
int cardEffectSmithy(int currentPlayer, struct gameState *state, int handPos);
int cardEffectVillage(int currentPlayer, struct gameState *state, int handPos);
int cardEffectGreatHall(int currentPlayer, struct gameState *state, int handPos);
int cardEffectOutpost(int currentPlayer, struct gameState *state, int handPos);
int cardEffectAdventurer(int currentPlayer, struct gameState *state, int drawntreasure, int cardDrawn, int *temphand, int size);
#endif
