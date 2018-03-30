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

#define xstr(x) #x		//eine Konstante x direkt eintragen
#define str(x) xstr(x)	//use: str(x)  -> result: x

//VS-CE ONLY:
#define _CRT_SECURE_NO_WARNINGS
//End Defines

//Includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
	int pruef;
	char worte[4][WORTLEN];
	//End lokale Datenfelder

	while (strcmp(inputStr, "quit") != 0)
	{
		//Begruessung und Arbeitsauftrag fuer den Benutzer
		printf("Gib die bloeden Ringe ein!!\n");
		
		scanf("%" str(MAXINPUT) "[^\n]", inputStr);
		while (getchar() != '\n');
		//Aufruf der Subroutinen
		pruef = inputPruefen(inputStr);
		if (pruef == 0)
			aufteilen(inputStr, worte[0], worte[1], worte[2], worte[3]);
		ausgabe(worte, pruef);

		// T E S T	 T E S T	 T E S T	 T E S T	 T E S T	 T E S T	 T E S T	 T E S T	 T E S T 
		/*for (i = 0; i < 4; i++)
		{
			printf("%s: ", worte[i]);
			//farbringe2Ziffer(worte[i]);
			//printf("%i", ret);
			printf("%i\n", farbringe2Ziffer(worte[i]));
		}
		printf("%g\n", farbring2Multi(worte[2]));
		int zehner, einer;
		double mul, r, tol;
		zehner = 10 * farbringe2Ziffer(worte[0]);
		einer = farbringe2Ziffer(worte[1]);
		mul = farbring2Multi(worte[2]);
		tol = farbring2Tolleranz(worte[3]);
		printf("Der eingegebene Widerstand hat: ");
		//printf("%d Ohm ", ((10 * farbringe2Ziffer(worte[0]) + farbringe2Ziffer(worte[1]))* farbring2Multi(worte[2])));
		printf("%f ", ((zehner + einer)* mul));
		//printf("+/- %i%", farbring2Tolleranz (worte[3]));
		printf("+/- %f \%", tol);
		//Ausgabe an den Benutzer
		*/
		// T E S T	 T E S T	 T E S T	 T E S T	 T E S T	 T E S T	 T E S T	 T E S T	 T E S T 
	}
}	//Hier wird in VS ein Breakpoint beoetigt

/*
	Diese Funktion zerteilt den Inputstring zk in vier Bestandteile.
	Die Trennung erfolgt bei den Trennzeichen, die in der Define-Section definiert sind.
	Die Ergebnisstrings werdn in form einer InPlace-Substitution an w1 bis w4 übergeben
*/
int aufteilen(char *zk, char *w1, char *w2, char *w3, char *w4)
{
	//									TODO	String prüfen
	strcpy(w1, strtok(zk, TRENNZEICHEN));
	strcpy (w2, strtok(NULL, TRENNZEICHEN));
	strcpy (w3, strtok(NULL, TRENNZEICHEN));
	strcpy (w4, strtok(NULL, TRENNZEICHEN));

	//reste Verwerten						TODO

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
	printf("text\n");				// TODO					Etwas sinnvolles ausgeben
	return -1;
}

/*
	Diese Funktion gibt einen Multiplikator für einen Inputstring zurück
	Der Rückgabewert ist double, da es auch die Multiplikatoren 0.1 und 0.01 gibt.
	Das eigentliche Wandeln des Farbwortes geschieht in "int farbringe2Ziffer (..)".
	*****
	dependency: int farbringe2Ziffer(char *farbwort);
	*****
*/
double farbring2Multi(char *farbwort)
{
	double mulArr [12] = { 1, 10, 100, 1000, 10000, 100000, 1000000, -1, -1, -1, 0.1, 0.01 };
	return mulArr[farbringe2Ziffer(farbwort)];
}
double farbring2Tolleranz(char *farbwort)
/*
Diese Funktion gibt einnen Tolleranzwert für einen Inputstring zurück.
Der Rückgabewert ist double.
Das eigentliche Wandeln des Farbwortes geschieht in "int farbringe2Ziffer (..)".
*****
dependency: int farbringe2Ziffer(char *farbwort);
*****
*/
{
	double TolArr[12] = { -1, 1, 2, -1, -1, -1, -1, -1, -1, -1, 5, 10 };
	return TolArr[farbringe2Ziffer(farbwort)];
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
	char gn[VARIANTEN][20] = { "5", "grue", "gn", "green" };
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
	return 0;
}

int ausgabe(char worte[][WORTLEN], int pruefung)
{
	int zehner, einer;
	double mul, r, tol;
	
	switch (pruefung)
	{
	case 0:
		printf("Eingabe korrekt\n\n");
		zehner = 10 * farbringe2Ziffer(worte[0]);
		einer = farbringe2Ziffer(worte[1]);
		mul = farbring2Multi(worte[2]);
		tol = farbring2Tolleranz(worte[3]);
		printf("---|  %s  %s  %s    %s      |---\n", worte [0], worte[1], worte[2], worte[3]);
		printf("Ein Widerstand mit %.1f Ohm", (zehner + einer)*mul);
		printf (" +/- %.f %%\n\n", tol);
		break;
	case 1:
		printf("Die Eingabe ist Fehlerhaft (zu wenige Trennzeichen)\n");
		break;
	case 2:
		printf("Die Eingabe ist Fehlerhaft (zu viele Trennzeichzen)\n");
		break;
	default:	
		printf("schwerer Eingabefehler\n");
	}
}