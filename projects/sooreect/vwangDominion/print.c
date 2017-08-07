printf("BEFORE\n");
for (i = 0; i < 2; i++) {
	if (i == 0)
		printf("Hand Position = %d\n", handPos);
		printf("Player %d handcount = %d\n", i, G1.handCount[i]);
		for (j = 0; j < G1.handCount[i]; j++)
			printf("%d. %d\t", j, G1.hand[i][j]);
		printf("\n");
		printf("Player %d deckcount = %d\n", i, G1.deckCount[i]);
		for (j = 0; j < G1.deckCount[i]; j++)				printf("%d. %d\t", j, G1.deck[i][j]);
		printf("\n");
		printf("Player %d discardcount = %d\n", i, G1.discardCount[i]);
		for (j = 0; j < G1.discardCount[i]; j++)
			printf("%d. %d\t", j, G1.discard[i][j]);
		printf("\n\n");
}
