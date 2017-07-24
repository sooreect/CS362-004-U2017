/*************************************************************************************************
 * Tida Sooreechine
 * CS362 Quiz 2 - Random Testing Quiz
 * 7/23/17
*************************************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	int randNum;
	char ch;
	
	randNum = rand() % 13;

	if (randNum == 0) 
		ch = '[';
	else if (randNum == 1)
		ch = ']';
	else if (randNum == 2)
		ch = '(';
	else if (randNum == 3)
		ch = ')';
	else if (randNum == 4)
		ch = '{';
	else if (randNum == 5)
		ch = '}';
	else if (randNum == 6)
		ch = 'a';
	else if (randNum == 7)
		ch = 'e';
	else if (randNum == 8)
		ch = 'r';
	else if (randNum == 9)
		ch = 's';
	else if (randNum == 10)
		ch = 't';
	else if (randNum == 11)
		ch = 'x';
	else
		ch = ' ';
	
    return ch;
}

char *inputString()
{
	int i, strSize;
	static char str[6];
	
	strSize = sizeof(str);
	memset(str, 0, strSize);

	for (i = 0; i < (strSize - 1); i++) {
		str[i] = inputChar(); 
	}
	str[5] = '\0';

    return str;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
