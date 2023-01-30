#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <locale.h>
#include <windows.h>

#define LONGITUD_ALFABETO 26			//Para el cifrado cesar y vinegere
#define INICIO_ALFABETO_MAYUSCULAS 65	//Para el cifrado cesar y vinegere
#define INICIO_ALFABETO_MINUSCULAS 97	//Para el cifrado cesar y vinegere
#define MOD(i, n) (i % n + n) % n

const char *alfabetoMinusculas = "abcdefghijklmnopqrstuvwxyz",	//Para el cifrado cesar y vinegere
           *alfabetoMayusculas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";	//Para el cifrado cesar y vinegere

int flag = 1;  //Para el bucle del menu
int e, d, n; //Variables para el cifrado RSA

//		Funciones útiles

//Regresa el valor entero de un caracter
int ord(char c){
    return(int)c;
}

//Limpia el buffer de entrada (en mi laptop es necesario porque no funciona el fgets sin esto no se porqué, probar si es necesario en otra pc)
void emptyBuf(const char* str)
{
    if(str[strlen(str) - 1] != '\n')
    {
      while(getchar() != '\n');
    }
}

//		Funciones necesarias para el encriptado RSA

int mcd(int a, int b){		//Comun divisor
    int q, r1, r2, r;
 
    if (a > b){
        r1 = a;
        r2 = b;
    }
    else {
        r1 = b;
        r2 = a;
    }

    while (r2 > 0){
        q = r1 / r2;
        r = r1 - q * r2;
        r1 = r2;
        r2 = r;
    }
 
    return r1;
}
 
 
int PrimarityTest(int a, int i){	//Test de numero primo
    int n = i - 1;
    int k = 0;
    int j, m, T;
 
    while (n % 2 == 0){
        k++;
        n = n / 2;
    }
 
    m = n;
    T = EncontrarT(a, m, i);
 
    if (T == 1 || T == i - 1) {
        return 1;
    }
 
    for (j = 0; j < k; j++){
        T = EncontrarT(T, 2, i);
        if (T == 1) {
            return 0;
        }
        if (T == i - 1) {
            return 1;
        }
    }
    return 0;
}

int EncontrarT(int a, int m, int n){		//Encuentra T para calcular el cifrado y decifrado
    int r;
    int y = 1;
 
    while (m > 0){
        r = m % 2;
        ExponenciacionRapida(r, n, &y, &a);
        m = m / 2;
    }
    return y;
}
 
int ExponenciacionRapida(int bit, int n, int* y, int* a){		//Funcion matematica
    if (bit == 1) {
        *y = (*y * (*a)) % n;
    }
 
    *a = (*a) * (*a) % n;
}
 
int inverso(int a, int b){										//Para el decifrado
    int inv;
    int q, r, r1 = a, r2 = b, t, t1 = 0, t2 = 1;
 
    while (r2 > 0){
        q = r1 / r2;
        r = r1 - q * r2;
        r1 = r2;
        r2 = r;
 
        t = t1 - q * t2;
        t1 = t2;
        t2 = t;
    }
 
    if (r1 == 1) {
        inv = t1;
    }
 
    if (inv < 0) {
        inv = inv + a;
    }
 
    return inv;
}
 
int GeneracionClave(){					//Genera las claves funciona con las funciones anteriores
    int p, q;
    int phi_n;
    
    do {
        do{
            do{
                printf("Ingrese un numero primo valido para la clave privada mayor que 100 y menor que 200\n");
                scanf("%d", &p);
            }while( p < 100);
        }while (p % 2 == 0);
    } while (!PrimarityTest(2, p));

    do {
        do{
             do{
                printf("Ingrese otro numero primo valido para la clave privada mayor que 100 y menor que 200\n");
                scanf("%d", &q);
            }while( p < 100);
        }while (q % 2 == 0);
    } while (!PrimarityTest(2, q));

    n = p * q;
    phi_n = (p - 1) * (q - 1);

    do{
        e = rand() % (phi_n - 2) + 2;
    }while (mcd(e, phi_n) != 1);

    d = inverso(phi_n, e);
}

int Encryption(int value, FILE* out){		//Encripta
    int cipher;
    cipher = EncontrarT(value, e, n);
    printf("%d", cipher);
    fprintf(out, "%d ", cipher);
}

int Decryption(int value, FILE* out){		//Desencripta
    int decipher;
    decipher = EncontrarT(value, d, n);
    fprintf(out, "%c", decipher);
}

//		Funciones de encriptado/Desencriptado
//Encriptado Cesar
void cesar(){
    
    char mensaje[101], mensajeCifrado[101];
    char c;
    int x, i = 0;
    
    printf("Ingrese el mensaje para codificar:\n");
	emptyBuf(mensaje);
    fgets(mensaje, 101, stdin);
    printf("Ingrese su x:\n");
    scanf("%d", &x);

    while (mensaje[i]){
        char caracterActual = mensaje[i];
        int pos = ord(caracterActual);
		
        if (!isalpha(caracterActual)){
            mensajeCifrado[i] = caracterActual;
            i++;
            continue;
        }
        if (isupper(caracterActual)){
            mensajeCifrado[i] = alfabetoMayusculas[(pos - INICIO_ALFABETO_MAYUSCULAS + x ) % LONGITUD_ALFABETO];
            } else{
                mensajeCifrado[i] = alfabetoMinusculas[(pos - INICIO_ALFABETO_MINUSCULAS + x ) % LONGITUD_ALFABETO];
            }
        i++;
    }

	puts(mensajeCifrado);
    printf("Presione enter para volver \n");
    getch();
	menuPrincipal();

}

//Desencriptado Cesar
void desCesar(){

	char mensajeCifrado[101], mensajeDCifrado[101];
    char c;
    int x, i = 0;

	printf("Ingrese el mensaje para decodificar:\n");
	emptyBuf(mensajeCifrado);
    fgets(mensajeCifrado, 101, stdin);
    printf("Ingrese su x:\n");
    scanf("%d", &x);

	while (mensajeCifrado[i]) {
		char caracterActual = mensajeCifrado[i];
		int pos = ord(caracterActual);
		if (!isalpha(caracterActual)) {
			mensajeDCifrado[i] = caracterActual;
			i++;
			continue;
		}
		if (isupper(caracterActual)) {
			mensajeDCifrado[i] = alfabetoMayusculas[MOD(pos - INICIO_ALFABETO_MAYUSCULAS - x, LONGITUD_ALFABETO)];
		} else {
			mensajeDCifrado[i] = alfabetoMinusculas[MOD(pos - INICIO_ALFABETO_MINUSCULAS - x, LONGITUD_ALFABETO)];
			}
		i++;
	}

	puts(mensajeDCifrado);
	printf("Presione enter para volver \n");
    getch();
	menuPrincipal();

}

//Encriptado Vinegere
void cifradoVinegere(){
	char mensaje[101], mensajeCifrado[101], llave[11];
    char c;
    int x = 0, i = 0;
    
    printf("Ingrese el mensaje para codificar:\n");
	emptyBuf(mensaje);
	fgets(mensaje, 101, stdin);
	printf("Ingrese la clave (max 10 letras):\n");
	fgets(llave, 11, stdin);
	int llave_len = strlen(llave);

	while (mensaje[i]){
    	char caracterActual = mensaje[i];
    	int pos = ord(caracterActual);
    	if (x == llave_len) x = 0;

    	if (!isalpha(caracterActual)){
        	mensajeCifrado[i] = caracterActual;
        	i++;
        	x++;
        	continue;
    	}
    	if (isupper(caracterActual)){
        	mensajeCifrado[i] = alfabetoMayusculas[(pos - INICIO_ALFABETO_MAYUSCULAS + ord(llave[x]) ) % LONGITUD_ALFABETO];
    	} else{
        	mensajeCifrado[i] = alfabetoMinusculas[(pos - INICIO_ALFABETO_MINUSCULAS + ord(llave[x]) ) % LONGITUD_ALFABETO];
    	}
    	i++;
    	x++;
	}

	puts(mensajeCifrado);
	printf("Presione enter para volver \n");
	getch();
	menuPrincipal();
}

//desifrado Vinegere
void dCifradoVinegere(){
	char mensajeCifrado[101], mensajeDCifrado[101], llave[11];
    char c;
    int x = 0, i = 0;
    
    printf("Ingrese el mensaje para decodificar:\n");
	emptyBuf(mensajeCifrado);
	fgets(mensajeCifrado, 101, stdin);
	printf("Ingrese la clave (max 10 letras):\n");
	fgets(llave, 11, stdin);
	int llave_len = strlen(llave);

	while (mensajeCifrado[i]){
    	char caracterActual = mensajeCifrado[i];
    	int pos = ord(caracterActual);
    	if (x == llave_len) x = 0;

    	if (!isalpha(caracterActual)){
        	mensajeDCifrado[i] = caracterActual;
        	i++;
        	x++;
        	continue;
    	}
    	if (isupper(caracterActual)) {
			mensajeDCifrado[i] = alfabetoMayusculas[MOD(pos - INICIO_ALFABETO_MAYUSCULAS - ord(llave[x]), LONGITUD_ALFABETO)];
		} else {
			mensajeDCifrado[i] = alfabetoMinusculas[MOD(pos - INICIO_ALFABETO_MINUSCULAS - ord(llave[x]), LONGITUD_ALFABETO)];
			}
    	i++;
    	x++;
	}
	puts(mensajeDCifrado);
	printf("Presione enter para volver \n");
    getch();
	menuPrincipal();
}

//Cifrado RSA 
void cifradoRSA(){
	FILE *inp, *out;
    char mensaje[101], mensajeDecifrado[101];

    // destruir el contenido de estos archivos (de ejecuciones anteriores, si corresponde)
    emptyBuf(mensaje);
    out = fopen("textoCifrado.txt", "w+");
    fclose(out);

    out = fopen("textoDecifrado.txt", "w+");
    fclose(out);

    out = fopen("textoOriginal.txt", "w+");
    printf("Ingrese el mensaje (max 100 caracteres)\n");
    fgets(mensaje, 101, stdin);
    fprintf(out, "%s", mensaje);
    fclose(out);

    GeneracionClave();

    inp = fopen("textoOriginal.txt", "r+");
    if (inp == NULL){
        printf("Error abriendo archivo de fuente.\n");
        exit(1);
    }
 
    out = fopen("textoCifrado.txt", "w+");
    if (out == NULL){
        printf("Error abriendo archivo destino.\n");
        exit(1);
    }
	
	printf("El mensaje cifrado es: \n");

    // Comienza el cifrado
    while (1){
        char ch = getc(inp);
        if (ch == -1) {
            break;
        }
        int value = toascii(ch);
        Encryption(value, out);
    }
 
    fclose(inp);
    fclose(out);
 
    // Domienza el decifrado
    inp = fopen("textoCifrado.txt", "r");

    if (inp == NULL){
        printf("Error abriendo textoCifrado Text.\n");
        exit(1);
    }
    
    out = fopen("textoDecifrado.txt", "w+");
    if (out == NULL){
        printf("Error abriendo archivo.\n");
        exit(1);
    }
 
    while (1){
        int cip;
        if (fscanf(inp, "%d", &cip) == -1) {
            break;
        }
        Decryption(cip, out);
    }

    fclose(out);
    out = fopen("textoDecifrado.txt", "r");
    fgets(mensajeDecifrado, 101, out);
    printf("\nEl mensaje decifrado es: \n%s\n", mensajeDecifrado);
    fclose(out);
	printf("Presione enter para volver\n");
	getch();
}

//No hay no existe
void dCifradoRSA(){
}

void menuInf(){
	printf("Cifrado cesar: El cifrado de sustitucion de Cesar consiste en\n reemplazar cada letra de la palabra por la que corresponde al\n avanzar x numero de letras en el abecedario, utilizando el alfabeto\n de 27 letras del español si decimos que (𝑥 = 4) la palabra HOLA se\n escribiria LSOE. Para usar este cifrado debe elegir un numero.\n\n");
	printf("Cifrado Vinegere: El cifrado de Vigenere es un cifrado poli alfabético\n y de sustitucion basado en diferentes series de caracteres\n o letras del cifrado Cesar formando de estos caracteres una\n tabla, llamada tabla de Vigenere, que se usa como clave.\n Para poder utilizar este cifrado, debe ingresar una palabra que sera su clave.\n\n");
	printf("Cifrado RSA: RSA es un algoritmo que  trabaja con una clave\n publica y una clave privada. La clave publica es el medio por el cual\n todo el contenido de texto plano sera cifrado, y la clave privada\n es el medio por el cual se desencriptara el contenido, para poder\n utilizar este encriptado usted debe definir (p y q) (estos tienen\n que ser numeros dos primos de preferencia que representen\n grandes cantidades se recomienda que sean de mas de tres cifras)\n\n");
	printf("\nPresione enter para volver\n");
	getch();
}

void menuCod(){
	int cod;
	printf("Elegir codificacion \n 1. Encriptado por sustitucion de Cesar \n 2. Encriptado Vinegere \n 3. Encriptado por RSA \n 4. Salir \n");
	scanf("%d", &cod);
	
	switch (cod){
		case 1:
		    cesar();
		    break;
		case 2:
		    cifradoVinegere();
			break;
		case 3:
			printf("\nDebido a la dificultad de ingresar un mensaje cifrado con RSA el cifrado y decifrado esta en una misma funcion\n");
			cifradoRSA();
			break;
		case 4:
		    menuPrincipal();
	}
}

void menuDecod(){
	int cod1;
	printf("Elegir codificacion \n 1. Desencriptado por sustitucion de Cesar \n 2. Desencriptado Vinegere \n 3. Desencriptado por RSA \n 4. Salir \n");
	scanf("%d", &cod1);
	
	switch (cod1){
		case 1:
		    desCesar();
			break;
		case 2:
		    dCifradoVinegere();
			break;
		case 3:
			printf("\nDebido a la dificultad de ingresar un mensaje cifrado con RSA el cifrado y decifrado esta en una misma funcion\n");
			cifradoRSA();
			break;
		case 4:
		    menuPrincipal();
	}
	
}

void menuPrincipal(){
	int menu;	
	printf("Elija una opcion \n 1. Informacion \n 2. Codificar \n 3. Decodificar \n 4. Salir \n \n");
	scanf("%d", &menu);
	
	switch (menu){
		case 1:
			menuInf();
			break;
		case 2: 
			menuCod();
			break;
		case 3:
			menuDecod();
			break;
		case 4:
		    flag = 0;
		    break;
	}
	return;
}


int main(){
   
	setlocale(LC_ALL, "spanish");
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);

	while (flag == 1){
		menuPrincipal();
	} 

	return 0;
}