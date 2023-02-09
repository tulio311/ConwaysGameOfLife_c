#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "funciones.h"


void leerConfiguracion(char* nombre, char** mat){
	
	int i,k;
	char var; // Basura
	
	FILE* mapa = fopen(nombre, "r");
	
	if(!mapa){
		printf("No se pudo abrir %s", nombre);
		return;
	}
	
	// Los bordes de la matriz van a tener puros espacios
	for(i=1;i<=SCREEN_NR;i++){
		for(k=1;k<=SCREEN_NC;k++){
			fscanf(mapa,"%jnjhc",&mat[i][k]);
		}
		// El Enter
		fscanf(mapa,"%c",&var);
		fscanf(mapa,"%c",&var);
	}
	
	fclose(mapa);
	
}


void randomConfig(char** mat){
	
	srand(time(NULL));
	
	int i,k;
	
	for(i=1;i<=SCREEN_NR;i++){
		for(k=1;k<=SCREEN_NC;k++){
			
			if(rand() % 2 == 0){
				mat[i][k] = '*';
			}else{
				mat[i][k] = ' ';
			}
			
		}
	}
	
}


void nuevaConfiguracion(char*** mat, char*** mat2, int nrens, int ncols){
	
	// Esta función coloca en una matriz la siguiente configuración después
	// de aplicar las reglas del juego de la vida a otra matriz
	
	int x,y;
	
	// Tenemos que decidir si se cambiará el estado de todos los caracteres
	// que no están en los bordes
	for(x=1;x<ncols-1;x++){
		for(y=1;y<nrens-1;y++){
			if(decide(*mat,nrens,ncols,x,y)){
				(*mat2)[y][x] = '*';
			}else{
				(*mat2)[y][x] = ' ';
			}	
		}
	}

}

int decide(char** mat, int nr, int nc, int x, int y){
	
	int cont=0;
	
	// Checamos si hay '*' en todas las casillas contiguas
	if(isOn(mat,x-1,y-1)) cont++;
	if(isOn(mat,x,y-1)) cont++;
	if(isOn(mat,x+1,y-1)) cont++;
	if(isOn(mat,x+1,y)) cont++;
	if(isOn(mat,x+1,y+1)) cont++;
	if(isOn(mat,x,y+1)) cont++;
	if(isOn(mat,x-1,y+1)) cont++;
	if(isOn(mat,x-1,y)) cont++;
	
	// Aplicamos las condiciones del juego de la vida
	if(mat[y][x] == '*'){
	
		if(cont == 2 || cont == 3) return 1; 
		else return 0;
		
	}else{
		
		if(cont == 3) return 1; 
		else return 0;
		
	}
}


int isOn(char** mat, int x, int y){
	if(mat[y][x] == '*') return 1;
	else return 0;
}

void printMatScreen(char** mat, int nrens, int ncols){
	
	srand(time(NULL));
		
	int i,k;
	for(i=1;i<nrens-1;i++){
		
		gotoxy(0,i-1);
		
		for(k=1;k<ncols-1;k++){
			
			//setColor(rand()%8);
			printf("%c",mat[i][k]);
			
		}
		
	}
}

char** createMatrix(int nr, int nc){
	int i;
	char** mat = (char**) malloc(nr*sizeof(char*));
	for(i=0;i<nr;i++) mat[i] = (char*) malloc(nc*sizeof(char)); 
	return mat;
}

void inicializa(char** mat, int nr, int nc){
	int i,k;
	for(i=0;i<nr;i++){
		for(k=0;k<nc;k++){
			mat[i][k] = ' ';
		}
	}
}

void freeMat(char** m, int r){
	int i;
	for(i=0;i<r;i++) free(m[i]);
	free(m);
}

void Delay(int n){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
		}
	}
}

void gotoxy(int x, int y) // en windows 
{ 
	COORD coord;
	coord.X = x;
	coord.Y = y; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); 
}

void clearScreen(void){

	int r,c;

    for( r=0;r<SCREEN_NR;r++)
        for( c=0;c<SCREEN_NC;c++){
            gotoxy(c,r);
            printf(" ");
        }
}

void setColor(int idxColor){
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Save current attributes */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    
    
    switch (idxColor) {
        case I_NRM:
            SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
            break;
        case I_RED:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            break;
        case I_GRN:
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            break;
        case I_YEL:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
            break;
        case I_BLU:
            SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
            break;
        case I_MAG:
            SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
            break;
        case I_CYN:
            SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;
        case I_WHT:
            SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;
    }

}
