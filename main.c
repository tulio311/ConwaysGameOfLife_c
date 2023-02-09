#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	int i,j,ind;
	
	// Creamos matrices con 2 más de ancho y de largo 
	// para poner espacios en los bordes, esto es para
	// que las células vivas que estén en la orilla de la pantalla
	// puedan decidir si vivir o morir con el mismo algoritmo que las
	// demás.
	char** C1 = createMatrix(SCREEN_NR+2,SCREEN_NC+2);
	char** C2 = createMatrix(SCREEN_NR+2,SCREEN_NC+2);
	
	inicializa(C1,SCREEN_NR+2,SCREEN_NC+2);
	inicializa(C2,SCREEN_NR+2,SCREEN_NC+2);
	
	printf("\n Escribe 1 si quieres una configuracion aleatoria y \n 0 si quieres leer tu configuracion: "); scanf("%d", &ind);
	
	if(ind){
		randomConfig(C1);
	}else{
		leerConfiguracion("configuracion.txt",C1);
	}
		
	while(1){
		
		printMatScreen(C1,SCREEN_NR+2,SCREEN_NC+2); 
		
		nuevaConfiguracion(&C1,&C2,SCREEN_NR+2,SCREEN_NC+2);
		
		Delay(200);
		
		printMatScreen(C2,SCREEN_NR+2,SCREEN_NC+2); 
		
		nuevaConfiguracion(&C2,&C1,SCREEN_NR+2,SCREEN_NC+2);
		
		Delay(200);
		
	}
	
	getchar();
	    
	return 0;
}
