/*
	author: Tim, Jens

	task: Dieses Programm soll die Funktion 
	int aufteilen (..)
	testen.
	Dabei sollen die Funktion und der Umgang mit Fehleingaben geprüft werden.
	Die Fehleingaben solleb sich dabei an den Bedingungen der Funktion orientieren.
	Dieses Programm stellt alle zur Funktion benötigten Parameter und Funktionen bereit.
*/

//Defines
#define TRENNZEICHEN "-,"
#define WORTLEN 30
#define MAXINPUT 999
#define INPUTn 4
//VS-CE ONLY:
#define _CRT_SECURE_NO_WARNINGS
//End Defines

//Includes
#include <stdio.h>
#include <string.h>
//End Includes

//Proto

//End Proto

int main(void)
{
	int i, j;
	char inputs[INPUTn][MAXINPUT + 1] = {"Eine-Eingabe-mit-Trenner", "Eine-Eingabe-mit-zuLangemWortAmEndeDennEsIstLaengerAlsWortlenErlaubt", "AuchWennDieErsteEingabeZuLangIstAlsoVielZuLang-dann-geht-das", "12345678901234567890123456789012345-10-8-9"};
	char worte[4][WORTLEN+1];
	printf("Testen der Funktion int aufteilen (..)\n");
	for (i = 0; i < INPUTn; i++)
	{
		printf("In:       %s\n", inputs[i]);
		aufteilen(inputs[i], worte[0], worte[1], worte[2], worte[3]);
		for (j = 0; j < 4; j++)
			printf("worte[%i]: %s\n", j, worte[j]);
	}
}

/*******************************************
Zu testende Funktion
*******************************************/
/*
Diese Funktion zerteilt den Inputstring zk in vier Bestandteile.
Die Trennung erfolgt bei den Trennzeichen, die in der Define-Section definiert sind.
Die Ergebnisstrings werdn in form einer InPlace-Substitution an w1 bis w4 übergeben
Diese Funktion geht von einer Korrekten Eingabe (Menge der Trennzeichen) aus, die zuvor sicher gestellt werden muss.
*/
int aufteilen(char *zk, char *w1, char *w2, char *w3, char *w4)
{
	strncpy(w1, strtok(zk, TRENNZEICHEN), WORTLEN);
	strncpy(w2, strtok(NULL, TRENNZEICHEN), WORTLEN);
	strncpy(w3, strtok(NULL, TRENNZEICHEN), WORTLEN);
	strncpy(w4, strtok(NULL, TRENNZEICHEN), WORTLEN);
	*(w1+ WORTLEN) = '\0';
	*(w2 + WORTLEN) = '\0';
	*(w3 + WORTLEN) = '\0';
	*(w4 + WORTLEN) = '\0';
	return 0;
}
