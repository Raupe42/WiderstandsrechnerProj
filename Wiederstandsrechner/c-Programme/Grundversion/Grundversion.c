/*
author: Tim, Jens
Task: Erfüllung des Pflichtenhefts gemäß der Dokumentation.
Dieses Programm stellt das Prdukt als vereinbarte Grundversion dar.
*/

// Defines
#define MAXINPUT 99
#define WORTLEN 30
#define VARIANTEN 8
#define TRENNZEICHEN "-,"

#ifdef UNIX
#define CLS "clear"
#elif unix
#define CLS "clear"
#else
#define CLS "cls"
#endif

#define xstr(x) #x		//eine Konstante x direkt eintragen
#define str(x) xstr(x)	//use: str(x)  -> result: x

//VS-CE ONLY:
#define _CRT_SECURE_NO_WARNINGS
//End Defines

//Includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
//End Includes

//Proto
int aufteilen(char *zk, char *w1, char *w2, char *w3, char *w4);
int farbringe2Ziffer(char *farbwort);
double farbring2Multi(char *farbwort);
double farbring2Tolleranz(char *farbwort);

//Zusaetzliche Funktionen
void fuelleVglArr(char vglArr[][VARIANTEN][20]);
void cpyArrOfStr(char dest[][20], char source[][20]);
int inputPruefen(char * input);
int ausgabe(char worte[][WORTLEN], int pruefung);
//End Proto

int main(void)
{
	//lokale Datenfelder
	char inputStr[MAXINPUT + 1] = "";
	int pruef, i;
	char worte[4][WORTLEN];	//Mit Platz für '\0'
	//End lokale Datenfelder

	while (strcmp(inputStr, "-quit") != 0)
	{
		//Begruessung und Arbeitsauftrag fuer den Benutzer
		printf("- - - Widerstandsrechner - - -\n");
		printf("Verwendung:\nDie Ringe eines Widerstandes mit \"-\" getrennt eingeben.\n");
		printf("Zum Beenden \"-quit\" eingeben\n");

		scanf("%" str(MAXINPUT) "[^\n]", inputStr);
		while (getchar() != '\n');
		for (i = 0; *(inputStr + i) != '\0'; i++)
			*(inputStr + i) = tolower(*(inputStr + i));
		//Aufruf der Subroutinen
		pruef = inputPruefen(inputStr);
		if (pruef == 0)
			aufteilen(inputStr, worte[0], worte[1], worte[2], worte[3]);
		ausgabe(worte, pruef);

		if (strcmp(inputStr, "-quit") != 0)
		{
			printf("Eingabetaste druecken\n");
			//getchar();
			while (getchar() != '\n');
			system(CLS);
		}

		
	}
}	


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
	*(w1 + WORTLEN-1) = '\0';
	*(w2 + WORTLEN-1) = '\0';
	*(w3 + WORTLEN-1) = '\0';
	*(w4 + WORTLEN-1) = '\0';
	return 0;
}
/*
	Diese Funktion vergleicht den Inputstring farbwort mit einer Liste
	um einen Farbring zu ermitteln und gibt als ReturnValue die Ziffer
	des Farbrings wieder.
	Da diese Funktion nicht nur zur Bestimmung der Ziffern sondern für alle
	möglichen Farbringe genutzt wird, werden für Gold und Silber die Zeichen 
	die Zahlen 10 und 11 zurück gegeben.
	
	Dieses Verhalten ermöglicht eine einfache Auswertung des übergebenen Farbwortes.
	Bei Rückgabewert -1 wurde keine Übereinstimmung gefunden
	*****
	dependency: void fuelleVglArr(char vglArr[][VARIANTEN][20]);
	*****
*/
int farbringe2Ziffer(char *farbwort)
{
	int farbe, var, retValInt = -1;
	char retValStr[20];
	static char vgl[12][VARIANTEN][20];
	if (vgl [0] [0] [0]!= '0')	//Das Array soll nur einmal gefuellt werden
		fuelleVglArr(vgl);
	
	for (farbe = 0; farbe < 12; farbe++)
	{
		for (var = 1; var < VARIANTEN; var++)
		{
			//suchen durch vergleichen
			if ((strcmp(vgl[farbe][var], farbwort)) == 0)
			{
				strcpy(retValStr, vgl[farbe][0]);
				char c = retValStr[0];
				retValInt = (c - '0');
				return retValInt;
			}
			//wenn etwas gefunden wurde
			// aktuelle zeile feld 0 -> ergebenis
		}
	}
	//printf("Farbe nicht gefunden\n");	
	return -1;
}

/*
	Diese Funktion gibt einen Multiplikator für einen Inputstring zurück
	Der Rückgabewert ist double, da es auch die Multiplikatoren 0.1 und 0.01 gibt.
	Das eigentliche Wandeln des Farbwortes geschieht in "int farbringe2Ziffer (..)".
	Ein Returnwert von -1 zeigt einen unzulässigen Ring an dieser Position.
	Ein Returnwert von -2 zeigt eine nicht definierte Farbeeingabe.
	*****
	dependency: int farbringe2Ziffer(char *farbwort);
	*****
*/
double farbring2Multi(char *farbwort)
{
	double mulArr [12] = { 1.0, 10.0, 100.0, 1000.0, 10000.0, 100000.0, 1000000.0, 10000000.0, 100000000.0, 1000000000.0, 0.1, 0.01 };
	int retVal = farbringe2Ziffer(farbwort);
	if (retVal != -1.0)
		return mulArr[retVal];
	return -2.0;
}

/*
Diese Funktion gibt einnen Tolleranzwert für einen Inputstring zurück.
Der Rückgabewert ist double.
Das eigentliche Wandeln des Farbwortes geschieht in "int farbringe2Ziffer (..)".
Ein Returnwert von -1 zeigt einen unzulässigen Ring an dieser Position.
Ein Returnwert von -2 zeigt eine nicht definierte Farbeeingabe.
*****
dependency: int farbringe2Ziffer(char *farbwort);
*****
*/
double farbring2Tolleranz(char *farbwort)
{
	double TolArr[12] = { -1.0, 1.0, 2.0, -1.0, -1.0, 0.5, 0.25, 0.1, 0.05, -1.0, 5.0, 10.0};
	int retVal = farbringe2Ziffer(farbwort);
	if (retVal != -1.0)
		return TolArr[retVal];
	return -2.0;
}

/*
	Diese Funktion füllt ein 3-Dimensionales Array of char (Input) durch eine 
	InPlace-Substitution mit Worten, die als Vergleichspartner genutzt werden.
	Die Menge der Möglichen Varianten einen Widerstandsring einzugeben ist im
	#define VARIANTEN festgelegt. Lediglich die Länge der einzelenen Bezeichnung
	ist auf 19 Zeichen fest vergeben.
	Es besteht eine Abhängigkeit zu "void cpyArrOfStr(..)". Die Hilfsfunktion ermöglicht
	eine übersichtliche Eingabe in einzelne Arrays. Nach der Eingabe werden die Arrays in das Gesamte (input)
	Array kopiert.
	*****
	dependency: void cpyArrOfStr(char dest[][20], char source[][20]);
	*****
*/
void fuelleVglArr(char vglArr[][VARIANTEN][20])
{
	char sw[VARIANTEN][20] = { "0", "schwarz", "sw", "black", "bk" };
	char br[VARIANTEN][20] = { "1", "braun", "br", "brown", "bn" };
	char rt[VARIANTEN][20] = { "2", "rot", "rt", "red", "rd" };
	char or[VARIANTEN][20] = { "3", "orange", "or", "og" };
	char ge[VARIANTEN][20] = { "4", "gelb", "ge", "yellow", "ye" };
	char gn[VARIANTEN][20] = { "5", "gruen", "gn", "green", "gr\x81n", "gr\x9An", "grun"};
	char bl[VARIANTEN][20] = { "6", "blau", "bl", "blue", "bu" };
	char vi[VARIANTEN][20] = { "7", "violett", "vi", "voilet", "vt", "lila", "vio" };
	char gr[VARIANTEN][20] = { "8", "grau", "gr", "grey", "gy" };
	char ws[VARIANTEN][20] = { "9", "weiss", "ws", "white", "wh", "weis" };
	char au[VARIANTEN][20] = { ":", "gold", "au", "go", "gd" };				//ASCI ':' folgt '9'
	char ag[VARIANTEN][20] = { ";", "silber", "si", "silver", "sr", "ag" };	//ASCI ';' folgt ':'
	cpyArrOfStr(vglArr[0], sw);
	cpyArrOfStr(vglArr[1], br);
	cpyArrOfStr(vglArr[2], rt);
	cpyArrOfStr(vglArr[3], or);
	cpyArrOfStr(vglArr[4], ge);
	cpyArrOfStr(vglArr[5], gn);
	cpyArrOfStr(vglArr[6], bl);
	cpyArrOfStr(vglArr[7], vi);
	cpyArrOfStr(vglArr[8], gr);
	cpyArrOfStr(vglArr[9], ws);
	cpyArrOfStr(vglArr[10], au);
	cpyArrOfStr(vglArr[11], ag);
	return;
}

/*
	Diese Funktion kopiert eine Menge von #define VARIANTEN Strings
	aus einem Array of String (Array of Array of char) genannt source
	in ein Zielarray (Array of String). 
*/
void cpyArrOfStr(char dest[][20], char source[][20])
{
	int i;
	for (i = 0; i < VARIANTEN; i++)
	{
		strcpy(dest[i], source[i]);
	}
}

/*
	Diese Funktion überprüft die Eingabe auf ihre Gültigkeit
	und gibt bei Falscheingaben in Abhängigkeit vom Fehler
	einen int-Wert zurück.
	Erfüllt eine Eingabe alle Anforderungen - enthält jedoch
	nicht definierte Worte wird dies an anderer Stelle bearbeitet.
	Rückgabewerte:
	 0: input IO
	-1: kritischer Fehler
	 1: zu wenige Worte (Trennzeichen)
	 2: zu viele Worte (Trennzeichen)
*/
int inputPruefen(char * input)
{
	int wortmenge = 4;	//entspricht länge des worte[]
	int i = 0, k = 0, l = 0;
	char * trennz = TRENNZEICHEN;
	while (*(input + i) != '\0')
	{
		while (*(trennz + k) != '\0')
		{
			if (*(input + i) == *(trennz + k))
				l++;
			k++;
		}
		k = 0;
		i++;
	}
	if (l < wortmenge-1)	//n(trennz.) = wortmenge -1
		return 1;
	if (l > wortmenge-1)
		return 2;
	
	i = k = l = 0;
	while (*(input + i) != '\0')	//Den String entlang iterieren
	{
		while (*(trennz + k) != '\0')	//Die Trennzerichen durchprobieren für zeichen i
		{
			if (*(input + i) == *(trennz + k))
				while (*(trennz + l) != '\0')	
				{
					if (*(trennz + l) == *(input + i + 1) || *(input + i + 1) == '\0')
						return 3;
					l++;
				}
			l = 0;
			k++;
			
		}
		k = 0;
		i++;
	}
	
	return 0;
}

/*
	Diese Funktion verwaltet und erzeugt die Ausgaben an den Benutzer
	inklusieve der Fehlerbeschreibung bei falschen Eingaben
	*****
	dependency: int farbringe2Ziffer(char *farbwort);
				double farbring2Multi(char *farbwort);
				double farbring2Tolleranz(char *farbwort);
	*****
*/
int ausgabe(char worte[][WORTLEN], int pruefung)
{
	int zehner, einer, exp = 0;
	double mul, r, tol;
	char expChar[5] = " kMG";
	switch (pruefung)
	{
	case 0:
		//printf("Eingabe korrekt\n\n");
		zehner = farbringe2Ziffer(worte[0]);
		einer = farbringe2Ziffer(worte[1]);
		mul = farbring2Multi(worte[2]);
		tol = farbring2Tolleranz(worte[3]);
		printf("---|  %s  %s  %s    %s      |---\n", worte [0], worte[1], worte[2], worte[3]);
		if (zehner > -1 && einer > -1 && mul > -1 && tol > -1)
		{
			r = (zehner * 10 + einer)*mul;
			while (r >= 1000)
			{
				r = r / 1000;
				exp++;
			}
			printf("Ein Widerstand mit %.1f %cOhm", r, *(expChar+exp));
			printf(" +/- %.f %%\n\n", tol);
		}
		else
		{
			if (zehner < 0)
				printf("%s ist nicht als moegliche Farbe definiert!\n", worte [0]);
			else if (einer < 0)
				printf("%s ist nicht als moegliche Farbe definiert!\n", worte[1]);
			else if (mul < 0)
			{
				if (mul == -1)
					printf("%s ist an dieser Stelle nicht zulaessig.\n",worte[2]);
				else if (mul == -2)
					printf ("%s ist nicht als moegliche Farbe definiert!\n", worte[2]);
			}
			else if (tol < 0)
			{
				if (tol == -1)
					printf("%s ist als Multiplikator nicht zulässig.\n", worte[3]);
				else if (tol == -2)
					printf("%s ist nicht als moegliche Farbe definiert!\n", worte[3]);
			}
			printf("Mindestens eine der eingegebenen Farben existiert (in dieser Kombination) nicht.\n");
			printf("korrektes Eingabebeispiel: \"braun-braun-schwarz-gold\"\n");
		}
		break;
	case 1:
		printf("Die Eingabe ist fehlerhaft (zu wenige Trennzeichen)\n");
		break;
	case 2:
		printf("Die Eingabe ist fehlerhaft (zu viele Trennzeichen)\n");
		break;
	case 3:
		printf("Die Eingabe enthaelt zu wenige Farbringe (ausreichend Trennzeichen)");
		break;
	default:	
		printf("schwerer Eingabefehler\n");
	}
}