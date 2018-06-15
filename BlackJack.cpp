#include <iostream> 
#include "TDAListaSencilla.h"
#include <String.h>
#include "TDAPila.h"
#include <stdlib.h> 
#include <ctime>
#include <map>
#include "cartasBlackjack.h"  // lo ultimo que se importa, pues depende de los anteriores paquetes

int main(int argc, char** argv) {
	
	struct TDAmano elCroupier;
	elCroupier.fichApuesta = 10000000;
	elCroupier.cartas = NULL;   
	
	TDAPila *pilaCartas=NULL;
	pilaCartas = barajarCartas();	

	int numJug;
	cout<<"-----  BLACK JACK -------\n";

	cout << "Número de jugadores: ";
	cin>>numJug;                      //limitar el número de jugadores máximo 4 0 5 
	TDAJugador jugadores[numJug];
	
	for(int i=0; i<numJug; i++){
		jugadores[i].mano1.cartas = NULL;
		jugadores[i].mano2.cartas = NULL;
		jugadores[i].seguro = 0;
		jugadores[i].esretirado = 0;
		
		cout << "Jugador #"<<i+1 <<endl;
		cout << "Numero de fichas a apostar: ";
		cin >> jugadores[i].mano1.fichApuesta; // no se deberían apostar más de 5o fichas para que el croupier pueda pagar las rondas
	}
	
	// repartiendo cartas a todos los jugadores incluyendo la banca
	string salida =  pedir(pilaCartas);
	elCroupier.cartas = crearLista(elCroupier.cartas, salida);
	
	cout << "Repartiendo cartas...\n";
	cout << "    LA BANCA: " << salida << endl;
	for(int i=0; i<numJug; i++){
		cout << "    Jugador #"<<i+1 << ":  ";
		
		salida = pedir(pilaCartas);
		cout << salida;
		jugadores[i].mano1.cartas = crearLista(jugadores[i].mano1.cartas, salida);  // pidiendo cartas
		
		salida = pedir(pilaCartas);
		cout << ",  " <<  salida;
		jugadores[i].mano1.cartas = crearLista(jugadores[i].mano1.cartas, salida);  // pidiendo cartas
		cout << "\n";
	}
	system("Pause");


	// en este momento es donde empieza a actuar el jugador
	int opcion, eleMano, acum;
	string newCar;
	for(int i=0; i<numJug; i++){
		bool bloqueo[8] = {true, true, true, true, true, true, true, true}; 
		do {
        system("CLS");
        cout << "            Turno de Jugador #"<<i+1 << "\n";
        cout<<"          --- Jugadas ---  \n\n\n";
        cout<<"1.  Pedir carta\n";
        cout<<"2   Mostrar mi juego y el de la banca\n";
        cout<<"3.  Mostrar mi dinero apostado\n";
        cout<<"4.  Apertura\n";
        cout<<"5.  Seguro\n";
        cout<<"6.  Doblada\n";
        cout<<"7.  Reriro\n";
		cout<<"8.  Plantarse\n ";
        
        if(puntosAcomulados(jugadores[i].mano1)  == 21 && longitud(jugadores[i].mano1.cartas) == 2 && jugadores[i].mano2.cartas == NULL){
        	cout << "----------------------------------------------------\n";
        	cout << "----------------------------------------------------\n";
        	cout << "------ El jugador #"<< i+1<<" ha obtenido Black Jack --------\n";
        	cout << "----------------------------------------------------\n";
        	cout << "----------------------------------------------------\n";
        	opcion = 8;   // se planta forzosamente, pues ya ganó
        	system("Pause");
		}else
        	cin>>opcion;
        	
        	
        if(!bloqueo[opcion-1]) {          // si la opcion esta bloqueada
        	opcion = 10;         // esta opcion no se encuentra entonces vuelve e inicia
        	cout << "Despues de haber pedido cartas no se puede hacer esta jugada\n";
        	system("Pause");
        }
        
        switch (opcion)
        	{
			case 1:
				if(jugadores[i].mano2.cartas == NULL){
					string newCar;
					newCar = pedir(pilaCartas);
					jugadores[i].mano1.cartas = crearLista(jugadores[i].mano1.cartas, newCar);
					cout << "nueva carta es: " << newCar << endl;
					bloqueo[4-1] = bloqueo[5-1] = bloqueo[6-1] = bloqueo[7-1] = false;
					if (puntosAcomulados(jugadores[i].mano1)>21){
						cout << "El jugador ha sobrepasado el límite de 21, pierde su apuesta\n";
						opcion = 8;
					}
				}else{
					string newCar;
					cout << "Seleccione mano: ";
					cin >> eleMano;
					if (eleMano == 1){
						if (puntosAcomulados(jugadores[i].mano1)>21){
							cout << "El jugador en la Mano1 ha sobrepasado el límite de 21\n";
						}else{
							newCar = pedir(pilaCartas);
							jugadores[i].mano1.cartas = crearLista(jugadores[i].mano1.cartas, newCar);
							cout << "nueva carta es: " << newCar << endl;
							bloqueo[4-1] = bloqueo[5-1] = bloqueo[6-1] = bloqueo[7-1] = false;
							if (puntosAcomulados(jugadores[i].mano1)>21){
								cout << "El jugador ha sobrepasado el límite de 21, pierde su apuesta en Mano1\n";
							}
						}
					
					}
					else if(eleMano == 2){
						if (puntosAcomulados(jugadores[i].mano1)>21){
							cout << "El jugador en la Mano2 ha sobrepasado el límite de 21\n";
						}else{	
							newCar = pedir(pilaCartas);
							jugadores[i].mano2.cartas = crearLista(jugadores[i].mano2.cartas, newCar);
							cout << "nueva carta es: " << newCar << endl;
							bloqueo[4-1] = bloqueo[5-1] =  bloqueo[6-1] = bloqueo[7-1] = false;
							if (puntosAcomulados(jugadores[i].mano2)>21){
								cout << "El jugador ha sobrepasado el límite de 21, pierde su apuesta en Mano2\n";
							}
						}
					}
					else
						cout << "Error, no existe la mano ingresada\n";
            	}
            	system("Pause");
            	break;
            	
			case 2:
				cout << "Jugador en mano1: " <<endl;
				ImprimirLista(jugadores[i].mano1.cartas);
					
				if(jugadores[i].mano2.cartas != NULL){
					cout << "Jugador en mano2: " <<endl;
					ImprimirLista(jugadores[i].mano2.cartas);
				}
				cout << "\nBanca" << endl;
				ImprimirLista(elCroupier.cartas);
				system("Pause");
	            break;
            	
            case 3:
            	cout << "Fichas en mano 1: " <<jugadores[i].mano1.fichApuesta << "\n";
            	if(jugadores[i].mano2.cartas != NULL){
            		cout << "Fichas en mano 2: " <<jugadores[i].mano2.fichApuesta << "\n";
				}
				if (jugadores[i].seguro){
					cout << "Fichas en seguro: " <<jugadores[i].mano1.fichApuesta*0.5 << "\n";
				}
				system("Pause");
            	break;
            
            case 4:
            	// sólo se permite si las dos cartas son de igual valor
            	
            	if ( valorCarta(jugadores[i].mano1.cartas->inicio->info) == valorCarta(jugadores[i].mano1.cartas->actual->info)){ 
	            	cout << "El jugador agrega otros " << jugadores[i].mano1.fichApuesta <<" a la apuesta para Apertura\n";
	            	jugadores[i].mano2.fichApuesta = jugadores[i].mano1.fichApuesta;  // asignando la misma cantidad en la otra mano, pues en apertura se apuesta el doble
	            	jugadores[i].mano2.cartas = crearLista(jugadores[i].mano2.cartas, elemEnPos(0, jugadores[i].mano1.cartas)); // pasando las cartas
	            	eliminarIndex(jugadores[i].mano1.cartas, 0);
	            	bloqueo[4-1] = bloqueo[5-1] = bloqueo[6-1] = bloqueo[7-1] = false;
	        	} else
	        		cout << "No permitido, las cartas no son de igual valor\n";
	        	system("Pause");	
	        	break;

            case 5:
            	
            	if(elCroupier.cartas->inicio->info == "A"){	// si el croupier tiene un "A" (1ra carta)
	            	jugadores[i].seguro = 1;
	            	bloqueo[4-1] = bloqueo[5-1] = bloqueo[6-1] = bloqueo[7-1] = false;
	            	cout << "Seguro comprado\n";
				}else{
					cout << "Solo es posible asegurar, si la 1ra carta del croupier es un As\n";
				}
				system("Pause");
				break;
            	
            case 6:
            	// puede doblar la apuesta siempre y cuando sus 2 primmeras cartas sumen 9, 10 u 11 puntos 
            	
            	acum = puntosAcomulados(jugadores[i].mano1);
            	
            	if (acum == 9 || acum == 10 || acum == 11){
            		
	            	jugadores[i].mano1.fichApuesta *= 2; 
	            	cout << "En este caso se esta doblando la apuesta----\n";
	            	newCar = pedir(pilaCartas);
					jugadores[i].mano1.cartas = crearLista(jugadores[i].mano1.cartas, newCar);
					cout << "nueva carta es: " << newCar << endl;
	            	opcion = 8;   // ya esta obligado a plantarse
	            	
	        	}else
	        		cout << "Para poder doblar las 2 primeras cartas deben sumar 9, 10 u 11\n";
	        	system("Pause");
	        	break;
            	
            case 7:
            	// en este caso faltaía eliminar al jugador del juego y mostrar sus resultados, al final del juego
            	jugadores[i].mano1.fichApuesta /= 2; 
            	cout << "El jugador #" << i+1 << " se ha retirado del juego\n";
            	jugadores[i].esretirado = 1;
            	opcion = 8; // se modifica la accion para sacarlo de las opciones, por lo tanto no es necesario bloquear
            	system("Pause");
            	break;
            	
			}
    	} while (opcion != 8);
	}
	

	
	// Despues de que todos los jugadores se han plantado------------------------------------------------------------------------------------------------
	system("CLS");
	showResultadosFinal(jugadores,numJug);
	
	// PRIMERO VERIFICAR EL SEGURO el croupier pide su siguiente carta
	elCroupier.cartas = crearLista(elCroupier.cartas, pedir(pilaCartas));
	if(elCroupier.cartas->inicio->info == "A" && puntosAcomulados(elCroupier) == 21){
		cout << "----------------------------------------------------------------------------------------\n";
		cout << "---------------------  BLACK JACK DEL CROUPIER, PAGANDO SEGUROS ------------------------\n";
		cout << "----------------------------------------------------------------------------------------\n";
		
		
		for(int i=0; i<numJug; i++){
			if (jugadores[i].seguro == 1){
				elCroupier.fichApuesta -= jugadores[i].mano1.fichApuesta;
				cout << "pagando Seguro y su devuelve inversion del seguro al jugador #" << i+1 << " correspondiente a " << jugadores[i].mano1.fichApuesta*1.5 << "(Mano 1) \n";
				jugadores[i].mano1.fichApuesta += 2*jugadores[i].mano1.fichApuesta;
				
			}else if(puntosAcomulados(jugadores[i].mano1) == 21 && longitud(jugadores[i].mano1.cartas) == 2 && jugadores[i].mano2.cartas == NULL){
				
				elCroupier.fichApuesta -= jugadores[i].mano1.fichApuesta*1.5;
				cout << "(Mano1)BLACKJACK: El jugador #" << i+1 << " gana " << jugadores[i].mano1.fichApuesta*1.5 << " fichas\n";
				jugadores[i].mano1.fichApuesta *= 1.5;
				
			}
			// no se verifica mano2, porque si alguien pide seguro, no puede hacer apertura
		}
		system("Pause");
	}else {
		if(elCroupier.cartas->inicio->info == "A"){
		
			for(int i=0; i<numJug; i++){
				if (jugadores[i].seguro == 1){
					elCroupier.fichApuesta += jugadores[i].mano1.fichApuesta/2;
					cout << "El jugador #" << i+1 << " PIERDE el seguro\n";
				}
			}
		}
		
	//}else{	
		while(puntosAcomulados(elCroupier) < 17){
			salida = pedir(pilaCartas);
			elCroupier.cartas = crearLista(elCroupier.cartas,salida);
		}
			
		cout << "           _____________________________________________\n";
		cout << "           |   RESULTADO FINAL DE LA BANCA\n";
		cout << "           |   CARTAS:   " << getStringLista(elCroupier.cartas) << endl;
		cout << "           |   PUNTAJE:  " << puntosAcomulados(elCroupier) << endl;
		cout << "           _____________________________________________\n\n";
		system("Pause");
			
		// Finalmente empezar a pagar, considera que se deben pagar las 2 manos y además recuerda que el black Jack se paga diferente
		// ORGANIZAR DE AQUI PARA ABAJO 
		
		// verificar antes de pagar, que el jugador no se haya retirado
		cout << "----------------------------------------------------------------------------------------\n";
		cout << "-------------------------------   PAGANDO LAS MANOS   ----------------------------------\n";
		cout << "----------------------------------------------------------------------------------------\n";
		if(puntosAcomulados(elCroupier) > 21){  
			for(int i=0; i<numJug; i++){
				if(!jugadores[i].esretirado){  // siempre y cuando el jugador no se ha retirado
					
							// Analizando Mano1
					if (puntosAcomulados(jugadores[i].mano1) <= 21){  			
						elCroupier.fichApuesta -= jugadores[i].mano1.fichApuesta*2;
						cout << "(Mano1)Se paga al jugador #" << i+1 << " correspondiente a " << jugadores[i].mano1.fichApuesta << endl;
						jugadores[i].mano1.fichApuesta *= 2;
					}else{
						// el croupier se queda con el dinero, pues el jugador sobrepasó primero los 21
						elCroupier.fichApuesta += jugadores[i].mano1.fichApuesta;
						cout << "(Mano1)Pierde el jugador #" << i+1 << " correspondiente a " << jugadores[i].mano1.fichApuesta << "  (porque el jugador sobrepaso primero los 21)\n";
						jugadores[i].mano1.fichApuesta = 0;
					}
					
							// Analizando Mano2
					if(jugadores[i].mano2.cartas != NULL){
						if(puntosAcomulados(jugadores[i].mano2) <= 21){
							elCroupier.fichApuesta -= jugadores[i].mano2.fichApuesta*2;
							cout << "(Mano2)Se paga #" << i+1 << " correspondiente a " << jugadores[i].mano2.fichApuesta << endl;
							jugadores[i].mano2.fichApuesta *= 2;
						}else{
							// el croupier se queda con el dinero, pues el jugador sobrepasó primero los 21
							elCroupier.fichApuesta += jugadores[i].mano2.fichApuesta;
							cout << "(Mano1)Pierde el jugador #" << i+1 << " correspondiente a " << jugadores[i].mano2.fichApuesta << "  (porque el jugador sobrepaso primero los 21)\n";
							jugadores[i].mano2.fichApuesta = 0;
						}
					}
						
				}else{
					cout << "El jugador #" << i+1 << " se retiró del juego\n";
				}
			}
		}else{
			for(int i=0; i<numJug; i++){
				if(!jugadores[i].esretirado){
					
					// ANALIZANDO LOS JUGADORES EN LA MANO 1
					if(puntosAcomulados(jugadores[i].mano1)  == 21 && longitud(jugadores[i].mano1.cartas) == 2 && jugadores[i].mano2.cartas == NULL){ // blackJack
						elCroupier.fichApuesta -= jugadores[i].mano1.fichApuesta*1.5;
						cout << "(Mano1)BLACKJACK: El jugador #" << i+1 << " gana " << jugadores[i].mano1.fichApuesta*1.5 << " fichas\n";
						jugadores[i].mano1.fichApuesta *= 1.5;
					}
					else if(puntosAcomulados(jugadores[i].mano1) > puntosAcomulados(elCroupier) && puntosAcomulados(jugadores[i].mano1) <= 21){
						
						elCroupier.fichApuesta -= jugadores[i].mano1.fichApuesta*2;
						cout << "(Mano1)El jugador #" << i+1 << " gana " << jugadores[i].mano1.fichApuesta << "fichas\n";
						jugadores[i].mano1.fichApuesta *= 2;
					}
					else if (puntosAcomulados(jugadores[i].mano1) < puntosAcomulados(elCroupier)  || (puntosAcomulados(jugadores[i].mano1) > puntosAcomulados(elCroupier) && puntosAcomulados(jugadores[i].mano1) > 21) ){
						
						elCroupier.fichApuesta += jugadores[i].mano1.fichApuesta;
						cout << "(Mano1)El jugador #" << i+1 << " pierde " << jugadores[i].mano1.fichApuesta << " fichas\n";
						jugadores[i].mano1.fichApuesta = 0;
						
					}else{  // en caso de que tengan el mismo numero de puntos
					
						if(puntosAcomulados(jugadores[i].mano1) != 21){
							cout << "(Mano1)Empate entre La banca y el jugador #" << i+1 << endl;
						}else{
							// si esto ocurre es porque posiblemente hay un black jack que es de la banca
							if(elCroupier.cartas->inicio->info == "A" && longitud(elCroupier.cartas) == 2 ){
								cout << "(Mano1)El jugador #" << i+1 << " pierde " << jugadores[i].mano1.fichApuesta << " fichas\n";
							}else{
								cout << "(Mano1)Empate entre La banca y el jugador #" << i+1 << endl;
								elCroupier.fichApuesta += jugadores[i].mano1.fichApuesta;
								jugadores[i].mano1.fichApuesta = 0;
							}		
						}	
					}
					
					// verificando si existe mano2
					if(jugadores[i].mano2.cartas != NULL){
						
						if(puntosAcomulados(jugadores[i].mano2) > puntosAcomulados(elCroupier)  && puntosAcomulados(jugadores[i].mano2) <= 21){
							elCroupier.fichApuesta -= jugadores[i].mano2.fichApuesta*2;
							cout << "(Mano2)El jugador #" << i+1 << " gana " << jugadores[i].mano2.fichApuesta << "fichas\n";
							jugadores[i].mano2.fichApuesta *= 2;
						}
						else if (puntosAcomulados(jugadores[i].mano2) < puntosAcomulados(elCroupier) || (puntosAcomulados(jugadores[i].mano2) > puntosAcomulados(elCroupier) && puntosAcomulados(jugadores[i].mano2) > 21)  ){  
							// no interesa validar el acomulado de las cartas del croupier, pues eso ya está validado antes
							
							elCroupier.fichApuesta += jugadores[i].mano2.fichApuesta;
							cout << "(Mano2)El jugador #" << i+1 << " pierde " << jugadores[i].mano2.fichApuesta << " fichas\n";
							jugadores[i].mano2.fichApuesta = 0;
							
						}else{  // en caso de que tengan el mismo numero de puntos
							if(puntosAcomulados(jugadores[i].mano2) != 21){
								cout << "(Mano2)Empate entre La banca y el jugador #" << i+1 << endl;
							}else{
								// si esto ocurre es porque posiblemente hay un black jack que es de la banca
								if(elCroupier.cartas->inicio->info == "A" && longitud(elCroupier.cartas) == 2 ){
									cout << "(Mano2)El jugador #" << i+1 << " pierde " << jugadores[i].mano2.fichApuesta << " fichas\n";
									elCroupier.fichApuesta += jugadores[i].mano2.fichApuesta;
									jugadores[i].mano2.fichApuesta = 0;
								}else{
									cout << "(Mano2)Empate entre La banca y el jugador #" << i+1 << endl;
								}		
							}	
						}		
					}
				}else{
					cout << "El jugador #" << i+1 << " se retiró del juego\n";
				}
			}
		}
	}
	system("Pause");
}
