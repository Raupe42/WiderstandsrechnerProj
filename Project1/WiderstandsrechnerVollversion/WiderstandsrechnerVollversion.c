/*
author: Tim, Jens

Dies ist die Vollversion des Widerstandsrechners.
Der Grundansprucht ist wie in der Grundversion:
Task: Erfüllung des Pflichtenhefts gemäß der Dokumentation.
Dieses Programm stellt das Prdukt als vereinbarte Vollversion dar.
Das Programm nutzt nicht mehr die vorgeschlageen Prototypen.
Das Programm wurde erstellt auf Basis der Grundversion des Commits
f4065afa2c78b3363072cd485e62e28dac27f17a [f4065af]
vom 06.04.18
Die zusätzlichen Features gegenüber der Grundversion sind:
- Verbesserte Arbeitsanweisung
- Automatische Auflistung der möglichen Trennzeichen
- "-quit" oder "-q" zum beenden
- Es kann auch nach erfolgter Ausgabe beendet werden
  oder etwas neues eingegeben werden. Anschließend muss 
  ernuet Enter gerückt werden oder die Eingabe kann überschrieben
  werden.
- Eingabe und Verarbneitung von Widerständen mit 5 oder 6 Ringen
- Umlaute in Ausgaben mit
	ä : \x84
	ö : \x94
	ü : \x81
	Ä : \x8E
	Ö : \x99
	Ü : \x9A
	ß : \xE1
	von: http://www.c-programmieren.com/C-Lernen.html#Umlaute
- Angabe des Widerstandstyps (Kohle oder Metallschicht)
- Anzeige der möglichen schreibweisen je Wort


*/

// Defines
#define MAXINPUT 99
#define WORTLEN 30
#define VARIANTEN 8
#define TRENNZEICHEN "-,/"

#ifdef UNIX
#define CLS "clear"
#elif unix
#define CLS "clear"
#else
#define CLS "cls"
#endif
/*
von https://stackoverflow.com/questions/142508/how-do-i-check-os-with-a-preprocessor-directive
show GCC defines on Windows:
gcc -dM -E - <NUL:

on Linux:
gcc -dM -E - </dev/null
*/
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
#include <locale.h>
//End Includes

//Proto
int aufteilen(char *zk, char worte [] [WORTLEN], int wortmenge);
int farbringe2Ziffer(char *farbwort);
double farbring2Multi(char *farbwort);
double farbring2Tolleranz(char *farbwort);

//Zusaetzliche Funktionen
void fuelleVglArr(char vglArr[][VARIANTEN][20]);
void cpyArrOfStr(char dest[][20], char source[][20]);
int inputPruefen(char * input);
int ausgabe(char worte[][WORTLEN], int pruefung);

char * eingabe(char * inputStr[]);
void hilfeAnzeigen();
void farbenAnzeigen();
//End Proto

int main(void)
{
	
	//lokale Datenfelder
	char inputStr[MAXINPUT + 1] = "";
	int pruef;
	char worte[6][WORTLEN];
	//End lokale Datenfelder

	//setlocale(LC_ALL, "");		//Funktioniert nicht, die Eingabe wird falsch eingelesen
	//setlocale(LC_NUMERIC, "");	//mit jeweils zwei '\0' zwischen jedem Buchstaben
	while (strcmp(inputStr, "-quit") != 0 && strcmp(inputStr, "-q") != 0)
	{
		eingabe(inputStr);
		if (strcmp(inputStr, "-quit") != 0 && strcmp(inputStr, "-q") != 0)
		{
			if (strcmp(inputStr, "-?") == 0 || strcmp(inputStr, "-help") == 0)
				hilfeAnzeigen();
			else if (strcmp(inputStr, "-1") == 0)
				farbenAnzeigen();
			/*else if (strcmp(inputStr, "-x") == 0)
				erweiterteAnzeige();*/
			else	//Normaler Programmaufruf
			{
				//Aufruf der Subroutinen
				pruef = inputPruefen(inputStr);
				if (pruef >= 0)
				{
					aufteilen(inputStr, worte, pruef);
				}
				ausgabe(worte, pruef);


				printf("Eingabetaste druecken\n");
				scanf("%" str(MAXINPUT) "[^\n]", inputStr);
				while (getchar() != '\n');

				system(CLS);
			}
		}

	}
}

/*
Diese Funktiongibt eine Einleitung,
Fragt eine Eingabe ab 
und führt die vorverarbeitung durch
Die Eingabe wird als InPlaceSubstitutuion zurück gegeben
mit gleichzeitig der Adresse davon als Rückgabewert
*/

char * eingabe(char * inputStr[])
{
	//lokale Datenfelder
	int i;
	char * trennz = TRENNZEICHEN;
	//End lokale Datenfelder

	//Begruessung und Arbeitsauftrag fuer den Benutzer
	printf("- - - Widerstandsrechner Vollverion - - -\n");
	//OUT: "Verwendung:\nDie Ringe eines Widerstandes mit TRENNZEICHEN getrennt eingeben.\n"
	printf("Verwendung:\nDie Ringe eines Widerstandes entweder mit ");
	for (i = 0; *(trennz + i) != '\0'; i++)
	{
		printf("\"%c\" ", *(trennz + i));
		if (*(trennz + i + 1) != '\0')
			printf("oder ");
	}
	printf("getrennt eingeben.\n");
	
	printf("-help: Hilfe anzeigen (kurz: \" -?\"\n");
	printf("Zum Beenden \"-quit\" eingeben. (kurz: \"-q\")\n");

	scanf("%" str(MAXINPUT) "[^\n]", inputStr);
	while (getchar() != '\n');
	for (i = 0; *(inputStr + i) != '\0'; i++)
		*(inputStr + i) = tolower(*(inputStr + i));

	return inputStr;
}

	/*
	Diese Funktion zerteilt den Inputstring zk in <wortmenge> Bestandteile.
	Die Trennung erfolgt bei den TRENNZEICHEN, die in der Define-Section definiert sind.
	Die Ergebnisstrings werdn in form einer InPlace-Substitution an worte übergeben
	Diese Funktion geht von einer Korrekten Eingabe (Menge der Trennzeichen) aus, die zuvor sicher gestellt werden muss.
	*/
int aufteilen(char *zk, char worte [] [WORTLEN], int wortmenge)
{
	int i;
	strncpy(worte[0], strtok(zk, TRENNZEICHEN), WORTLEN);
	for (i = 1; i < wortmenge; i++)	//i = 1 ist WICHTIG!!
	{
		strncpy(worte[i], strtok(NULL, TRENNZEICHEN), WORTLEN);
		*(worte[i] + WORTLEN - 1) = '\0';
	}
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
	if (vgl[0][0][0] != '0')	//Das Array soll nur einmal gefuellt werden
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
	double mulArr[12] = { 1.0, 10.0, 100.0, 1000.0, 10000.0, 100000.0, 1000000.0, 10000000.0, 100000000.0, 1000000000.0, 0.1, 0.01 };
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
	double TolArr[12] = { -1.0, 1.0, 2.0, -1.0, -1.0, 0.5, 0.25, 0.1, 0.05, -1.0, 5.0, 10.0 };
	int retVal = farbringe2Ziffer(farbwort);
	if (retVal != -1.0)
		return TolArr[retVal];
	return -2.0;
}

/*
*/
int farbring2TK(char *farbwort)
{
	int TkArr[12] = { 200, 100, 50, 15, 25, 5, -1, -1, -1, -1, -1, 10 };
	int retVal = farbringe2Ziffer(farbwort);
	if (retVal != -1.0)
		return TkArr[retVal];
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
	char gn[VARIANTEN][20] = { "5", "gruen", "gn", "green", "gr\x81n", "gr\x9An", "grun" };
	char bl[VARIANTEN][20] = { "6", "blau", "bl", "blue", "bu" };
	char vi[VARIANTEN][20] = { "7", "violett", "vi", "voilet", "vt", "lila", "vio" };
	char gr[VARIANTEN][20] = { "8", "grau", "gr", "grey", "gy" };
	char ws[VARIANTEN][20] = { "9", "weiss", "ws", "white", "wh", "weis" };
	char au[VARIANTEN][20] = { ":", "gold", "au", "go", "gd" };				//ASCI ':' folgt '9'
	char ag[VARIANTEN][20] = { ";", "silber", "si", "silver", "sr", "ag" };	//ASCI ';' folgt ':'
	cpyArrOfStr(vglArr[0], sw);
	cpyArrOfStr(vglArr[1], br);
	cpyArrOfStr(vglArr[2], rt);
	cpyArrOfStr(vglArr[3], or );
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
Da Kohleschicht aber auch Metallschichtwiderstände berücksichtigt werden sollen,
wird hier die Anzahl der eingegebenen Ringe gezählt und wenn zulässig als positive
Zahl zurück gegeben


Fehler-Rückgabewerte:
-1: kritischer Fehler
-2: zu wenige Worte (Trennzeichen)
-3: zu viele Worte (Trennzeichen)
-4: leere Bereiche (zwischen TRENNZEICHEN)
*/
int inputPruefen(char * input)
{
	int wortmenge = 4;	//entspricht länge des worte[]
	int i = 0, k = 0, m = 0;
	char * trennz = TRENNZEICHEN;
	while (*(input + i) != '\0')
	{
		while (*(trennz + k) != '\0')
		{
			if (*(input + i) == *(trennz + k))
				m++;
			k++;
		}
		k = 0;
		i++;
	}
	if (m < wortmenge - 1)	//n(trennz.) = wortmenge -1
		return -2;
	if (m > wortmenge +1)	//Bei Wortmenge = 4 wäre wortmenge +1 der Met.R mit Tempgradient
		return -3;
	wortmenge = m + 1;

	//Prüfen ob sich Zeichen zwischen einzelnen TRENNZEICHEN befinden
	i = k = m = 0;
	while (*(input + i) != '\0')	//Den String entlang iterieren
	{
		while (*(trennz + k) != '\0')	//Die Trennzerichen durchprobieren für zeichen i
		{
			if (*(input + i) == *(trennz + k))
				while (*(trennz + m) != '\0')
				{
					if (*(trennz + m) == *(input + i + 1) || *(input + i + 1) == '\0')
						return -4;
					m++;
				}
			m = 0;
			k++;

		}
		k = 0;
		i++;
	}

	return wortmenge;
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
	
	int ring1, ring2, ring3 = 0, exp = 0, tempKoef = 0, i;
	double mul, r, tol;
	char expChar[5] = " kMG";
	char mulStr[WORTLEN], tolStr[WORTLEN], rArt [WORTLEN];
	switch (pruefung)
	{
	case 6: tempKoef = farbring2TK(worte[5]);
	case 5: ring3 = farbringe2Ziffer(worte[2]);
	case 4:
		//printf("Eingabe korrekt\n\n");
		ring1 = farbringe2Ziffer(worte[0]);
		ring2 = farbringe2Ziffer(worte[1]);
		if (pruefung >= 5)	//Metallschichtwiderstand
		{
			ring3 = farbringe2Ziffer(worte[2]);
			mul = farbring2Multi(worte[3]);
			strcpy(mulStr, worte[3]);
			tol = farbring2Tolleranz(worte[4]);
			strcpy(tolStr, worte[4]);
			strcpy(rArt, "Metallschicht");

			r = (ring1 * 100 + ring2*10 + ring3)*mul;
		}
		else				//Kohleschichtwiderstand
		{
			mul = farbring2Multi(worte[2]);
			strcpy(mulStr, worte[2]);
			tol = farbring2Tolleranz(worte[3]);
			strcpy(tolStr, worte[3]);
			r = (ring1 * 10 + ring2)*mul;
			strcpy(rArt, "Kohle");
		}
		//printf("---|  %s  %s  %s    %s      |---\n", worte[0], worte[1], worte[2], worte[3]);
		//Semigrafik des Widerstandes anzeigen

		printf("---|");
		for (i = 0; i < pruefung - 1; i++)	//ACHTUNG: i wird einmal nach dem for benötigt, dannach wieder frei
		{
			printf(("  %s "), worte[i]);
		}
		printf("    %s   |---\n", worte[i]);	//i wird benötigt

		//Bei gültiger Eingabe Wert berechnen
		if (ring1 > -1 && ring2 > -1 && ring3 > -1 && mul > -1 && tol > -1 && tempKoef > -1)
		{
			//r = (ring1 * 10 + ring2)*mul;
			while (r >= 1000)
			{
				r = r / 1000;
				exp++;
			}
			
			printf("Ein %swiderstand mit %.3f %cOhm",rArt, r, *(expChar + exp));
			printf(" +/- %.f%%", tol);
			if (tempKoef > 0)
			{
				printf(" TK +/-%ippm /K", tempKoef);
			}
			printf("\n\n");
			printf("Der Widerstandswert liegt also zwischen %.4f %cOhm und %.4f %cOhm +/-%ippm /K.\n",  r* (1 - tol * 0.01), *(expChar + exp), r * (1+tol * 0.01), *(expChar + exp), tempKoef);
			
		}
		else		//mindestens ein eingegebenes Wort konnte nicht zugeordnet werden
		{
			if (ring1 < 0)
				printf("%s ist nicht als m\x94gliche Farbe definiert!\n", worte[0]);
			else if (ring2 < 0)
				printf("%s ist nicht als m\x94gliche Farbe definiert!\n", worte[1]);
			else if (mul < 0)
			{
				if (mul == -1)
					printf("%s ist als Multiplikator nicht zul\x84ssig\n",mulStr);
				else if (mul == -2)
					printf("%s ist nicht als m\x94gliche Farbe definiert!\n", mulStr);
			}
			else if (tol < 0)
			{
				if (tol == -1)
					printf("%s ist als Tolleranzwert nicht zul\x84ssig\n", tolStr);
				else if (tol == -2)
					printf("%s ist nicht als m\x94gliche Farbe definiert!\n", tolStr);
			}
			printf("Mindestens eine der eingegebenen Farben existiert (in dieser Kombination) nicht.\n");
			printf("korrektes Eingabebeispiel: \"braun-braun-schwarz-gold\"\n");
		}
		break;

	case -2:
		printf("Die Eingabe ist fehlerhaft (zu wenige Trennzeichen)\n");
		break;
	case -3:
		printf("Die Eingabe ist fehlerhaft (zu viele Trennzeichen)\n");
		break;
	case -4:
		printf("Die Eingabe enth\x84lt zu wenige Farbringe (ausreichend Trennzeichen)");
		break;
	default:
		printf("schwerer Eingabefehler\n");
	}
}


/*
	Diese Funktion zeigt den Hilfetext an
*/
void hilfeAnzeigen()
{
	char * trennz = TRENNZEICHEN;
	int i;
	system(CLS);
	printf("---|  Widerstandsrechner Hilfe |---\n");
	printf("Bedienung: Die Ringe eines Widerstandes ablesen und eintragen.\n");
	printf("Die einzelnen Ringe sind mit");
	for (i = 0; *(trennz + i) != '\0'; i++)
	{
		printf("\"%c\" ", *(trennz + i));
		if (*(trennz + i + 1) != '\0')
			printf("oder ");
	}
	printf("zu trennen.\n");
	printf("Anschlie""\xE1""end wird der Widerstandswert, sowie Tolleranz und wenn vorhanden\n");
	printf("Temperaturkoeffizient (TK) angezeigt.\n");
	printf("zur Anzeige der Varianten eine Farbe einzugeben \" -1\" eingeben\n");

	printf("Bitte eine Taste dr""\x81""cken...\n");
	while (getchar() != '\n');
	system(CLS);
	return;
}

/*
	Diese Funktion gibt auf der Basis des vglArr die möglichen
	Eingaben des Benutzer an
*/
void farbenAnzeigen()
{
	static char vgl[12][VARIANTEN][20];
	int i, j;
	fuelleVglArr(vgl);

	system(CLS);
	printf("Varianten eine Farbe einzugeben:\n");
	for (i = 0; i < 12; i++)
	{
		for (j = 1; j < VARIANTEN; j++)
		{
			if (strcmp (vgl [i] [j], "") != 0)
				printf("|%s| ", vgl[i][j]);
		}
		printf("\n");
	}
	printf("Bitte eine Taste dr""\x81""cken...\n");
	while (getchar() != '\n');
	system(CLS);
	return;
}
