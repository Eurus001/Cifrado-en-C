#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <locale.h>
#include <windows.h>

#define LONGITUD_ALFABETO 26
#define INICIO_ALFABETO_MAYUSCULAS 65
#define INICIO_ALFABETO_MINUSCULAS 97
#define MOD(i, n) (i % n + n) % n

const char *alfabetoMinusculas = "abcdefghijklmnopqrstuvwxyz",
           *alfabetoMayusculas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int flag = 1;

int ord(char c){
    return(int)c;
}

void emptyBuf(const char* str)
{
    if(str[strlen(str) - 1] != '\n')
    {
      while(getchar() != '\n');
    }
}

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

void desCesar(){

	char mensajeCifrado[101], mensajeDCifrado[101];
    char c;
    int x, i = 0;

	printf("Ingrese el mensaje para codificar:\n");
	emptyBuf(mensajeCifrado);
    fgets(mensajeCifrado, 101, stdin);
    printf("Ingrese su x:\n");
    scanf("%d", &x);

	while (mensaje[i]) {
		char caracterActual = mensaje[i];
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


void menuInf(){
	printf("Agregar informacion\n Enter para volver \n");
	getch();
	printf("\n");
	menuPrincipal();
}

void menuCod(){
	int cod;
	printf("Elegir codificacion \n 1. Encriptado por sustitucion de Cesar \n 2. Encriptado por RSA \n 3. Encriptado por X \n 4. Salir \n");
	scanf("%d", &cod);
	
	switch (cod){
		case 1:
		    cesar();
		    break;
		case 2:
		    
		case 3:
		   
		case 4:
		    menuPrincipal();
	}
	
}

void menuDecod(){
	int cod1;
	printf("Elegir codificacion \n 1. Desencriptado por sustitucion de Cesar \n 2. Desencriptado por RSA \n 3. Desencriptado por X \n 4. Salir \n");
	scanf("%d", &cod1);
	
	switch (cod1){
		case 1:
		    
		case 2:
		    
		case 3:
		   
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
