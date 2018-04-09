/*
author: Tim, Jens

task: Dieses Programm soll die Funktion
double farbringe2Tolleranz (..)
testen.
Dabei sollen die Funktion und der Umgang mit Fehleingaben geprüft werden.
Die Fehleingaben sollen sich dabei an den Bedingungen der Funktion orientieren.
Dieses Programm stellt alle zur Funktion benötigten Parameter und Funktionen bereit.
*/
//Defines
#define TRENNZEICHEN "-,"
#define VARIANTEN 8
#define INPUTn 16
#define WORTLEN 30

//VS-CE ONLY:
#define _CRT_SECURE_NO_WARNINGS
//End Defines

//Includes
#include <stdio.h>
#include <string.h>
#include <ctype.h>
//End Includes

//Proto
double farbring2Tolleranz(char *farbwort);
void fuelleVglArr(char vglArr[][VARIANTEN][20]);
void cpyArrOfStr(char dest[][20], char source[][20]);
int farbringe2Ziffer(char *farbwort);
//End Proto

int main(void)
{
	int i, j;
	char inputStr[99] = "";
	char inputs[INPUTn][WORTLEN] = { "Schwarz", "BrAuN", "rot", "or", "yellow", "grÜn", "bl", "lila", "gr", "GOLD", "ag", "", "schrott", "12345678901234567890123456789", "üäö", "-" };
	//Das im Quelltext eingegebene Ü ist ein anderes, als das eingelesene
	//Die Funktion zeigt sich bei der Konsoleneingabe
	printf("Testen der Funktion int farbing2Tolleranz (..)\n");
	for (i = 0; i < INPUTn; i++)
	{
		printf("In:       %s\n", inputs[i]);
		for (j = 0; *(inputs[i] + j) != '\0'; j++)
			*(inputs[i] + j) = tolower(*(inputs[i] + j));
		printf("toLower: %s\n", inputs[i]);
		printf(" out:   %g\n", farbring2Tolleranz(inputs[i]));
	}
	printf("\n***\n-quit zum beenden\n***\n");
	while (strcmp(inputStr, "-quit") != 0)
	{
		scanf("%99[^\n]", inputStr);
		while (getchar() != '\n');
		printf("In:       %s\n", inputStr);
		for (i = 0; *(inputStr + i) != '\0'; i++)
			*(inputStr + i) = tolower(*(inputStr + i));
		printf("toLower: %s\n", inputStr);
		printf(" out:   %g\n", farbring2Tolleranz(inputStr));
	}

}

/*******************************************
Zu testende Funktion
es werden nur kleingeschriebene Eingabe erwartet,
da das tolower() Setzen aller Chars im Programm bereits nach
der Eingabe erfolgt ist.
*******************************************/
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
//Abhängigkeiten
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
	char or [VARIANTEN][20] = { "3", "orange", "or", "og" };
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