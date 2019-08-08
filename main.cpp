#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <fstream>
#include <sys/stat.h> 
#include <sys/types.h> 
#include <direct.h>
#include <string.h>


using namespace std;


/*   Definisco alcune variabili globali da sistemare in futuro con altre singole funzioni per catturare ogni valore   */
long double codenumber = 0;
int patternnumber = 0;
bool showcodes;


/*   Definisco i tipi di dizionari da usare per la scelta del numero o lettera randomico   */
char  a[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
char b[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
char c[] = {"0123456789"};


/*   Definisco i pattern dei codici di amazon generabili   */
string pattern[6] = {"", "XXXXXXXX0XX00X0", "XX0XXX0XXXXX0XX", "XXXXX0X0XXX0XXX", "XX0XXXXXXX0XXX", "0XXXX0XXX000X0"};


/*   Prototipi di funzione   */
string currentdate();
int menu();
int codesoutput();


int main() {
	
	system("title \'AMAZON GIFTCARD GENERATOR\'");
	
	/*   Tramite la funzione currentdate prelevo la data corrente per crearne una cartella che contenga i codici generati   */
	string date_ = currentdate();
	string date = date_;
	
	/*	Creo la cartella dove andrannno ad essere salvati i codici e creo una stringa che contiele la path	  */
	string mydir;
	string mydir2;
	mydir = "Results";
	mkdir(mydir.c_str());
	mydir2 = "Results//" + date;
	mkdir(mydir2.c_str());
	
	/*   Do un titolo iniiale alla finestra   */	
	cout << "AMAZON GIFTCARDS GENERATOR" << endl;
	cout << "Coded by KeltonSchmidt & co." << endl;
	cout << endl;
	
	/*   Avvio la funzione del menu in modo che ottenga numero del pattern e dei codici da generare   */
	int patternnum = menu();
	
	/*   Inizializzo il numeratore randomico ed apro un flusso di dati in output (scrittura del file con i codici)  */
	srand(time(NULL));
	fstream codici;
	string path = "Results//" + date + "//AMAZON CODES.txt";
    codici.open(path.c_str(),  ios::out);
    
    /*   Inizializzo le variabili utili   */
    int charnumber, k = 0, l = 0;
	int j, x, y, i;
	
	/*   Controllo il numero di caratteri nel pattern selezionato in modo da creare un array dimensionato correttamente   */
	if((patternnumber == 1) || (patternnumber == 2) || (patternnumber == 3)) {
		charnumber = 15;
	}
	else {
		charnumber = 14;
	}
	
	/*   Creo i puntatori a char per utilizzarli per immagazzinare dati e switcharli come temp   */
	char* code = new char[charnumber];
	char* tocharpattern = new char[charnumber];
	///string codesarray[codenumber];
	
	/*   Con il comando "strcpy" copio il contenuto dell'array in una stringa, "code"   */
	switch (patternnumber) {
    case 1:
        strcpy(code, pattern[1].c_str());
        break;

    case 2:
        strcpy(code, pattern[2].c_str());
        break;

    case 3:
        strcpy(code, pattern[3].c_str());
        break;

    case 4:
        strcpy(code, pattern[4].c_str());
        break;
    
    case 5:
        strcpy(code, pattern[5].c_str());
        break;
	}

	/*   Trovo la dimensione da utilizzare per la funzione randomica   */
	x = sizeof(b) - 1;														//   Si riferisce alle lettere
    y = sizeof(c) - 1;														//   Si riferisce ai numeri

	
    /*   Utilizzo la funzione randomica e genero singolarmente ogni carattere alfanumerico per aggiungerlo all'array da stampare e ripulire   */
    for(j = 0; j < codenumber; j++)
    {
        for(i = 0; i < charnumber; i++)
        {
            if(code[i] == '0') {											//   code[i] rappresenta l'attuale carattere da randomizzare
                tocharpattern[k] = c[(rand() % y)];							//   tocharpattern invece contiene a mano a mano tutti i caratteri della stringa generata dai singoli alfanumerici
                codici << tocharpattern[k];									//   Codici viene usata analogamente a cout per scrivere nel file ciò che viene dopo "<<"
                
                if(showcodes == true) {										//   Se l'utente ha scelto di abilitare la vista dei codici generati, essi verranno stampati sulla console, ma richiederanno molto tempo
                	cout << tocharpattern[k];
				}
            }
            else {
                tocharpattern[k] = b[(rand() % x)];
                codici << tocharpattern[k];
                
	            if(showcodes == true) {
                	cout << tocharpattern[k];
				}
            }
        }
        codici << endl;
        
        if(showcodes == true) {
                	cout << endl;
		}
    }
    
	return 0;
}


/*   Funzione per ottenere la data corrente per crearne la cartella   */
string currentdate()
{
	/*   Utilizzo la libreria 'time.h' per farmi dire l'ora dal sistema (lavora in ticks)   */
    time_t t = time(0);
    tm* now = localtime(&t);		// Prendo l'address di t perchè dovrebbe essere riservato
    
    /*   Inizializzo le variabili che mi servono   */
    char* date;
    int year, month, day;
    
    /*   Uso una funzione di libreria con un metodo imparato a scuola per agire sulle classi degli header ("now->" risulta molto simile a "this->")   */
    year = (now->tm_year + 1900);
    month = (now->tm_mon + 1);
    day = now->tm_mday;
    
    /*   "sprintf" funziona come un printf ma salva il contenuto generato in una stringa, quella passata nel primo parametro   */
    sprintf(date, "%d-%d-%d", day, month, year);
    
    
    return date;
}

/*   La funzione menu serve per richiedere i vari parametri da prendere in consideraione   */
int menu()
{
	/*   Definisco le variabili che servono   */
	int i = 1;
	string codeshown;
	
	/*   Con un ciclo while ed un do-while gestisco le casisteche di overflow della scelta del pattern, per evitare che venga selezionato un numero non esistente   */
	do{
		
		while(i <= 5) {
			cout << "Pattern " << i << ": " << pattern[i] << endl;
			i++;
		}
		
		cout << "Which pattern do you want to use? ";
		cin >> patternnumber;
		
	} while(patternnumber > 5);
	
	/*   Qui mi assicuro che il numero di codici da generare non sia 0   */
	do{
		cout << "How many codes do you want to generate? ";
		cin >> codenumber;
	}while(codenumber == 0);
	
	/*   Chiedo se vuole risparmaire un po di tempo (1 milione di codici a 15 cifre senza stamparli sulla console ci impiegano solo circa 13 secondi   */
	cout << "Do you want the codes to be shown while generating ('NO' will save much time.)? ";
	cin >> codeshown;
	
	if((codeshown == "NO") || (codeshown == "No") || (codeshown == "no")) {
		showcodes = false;
	}
	else {
		showcodes = true;
	}

	return patternnumber;
}
