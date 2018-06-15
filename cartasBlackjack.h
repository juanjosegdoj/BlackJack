// cartas black JAck
// NOTA: teniendo en cuenta que solo se puede importar de una vez, pues de lo contrario marcará error, entonces
//       todo se importará desde el main.


struct TDAmano{
	int fichApuesta;
	TDALista *cartas;
};

struct TDAJugador{
	TDAmano mano1;
	TDAmano mano2;
	bool seguro;
	bool esretirado;
};

using namespace std; 

TDAPila *barajarCartas( ){
	cout << "Barajando cartas...\n";
	string nomC[14] = {"A","2","3","4","5","6","7","8","9","10","J","Q","k"}; 

	srand(time(NULL));  // para que los números random también cambien, sin embargo aún se parecen muchos números
	
	TDALista *misCartas=NULL;
	for(int m=0; m<4; m++){
		for(int i=0; i<13;i++){
			misCartas = crearLista(misCartas,nomC[i]);
		}
	}

	TDAPila *cartBaraj=NULL;   // Esta pila va almacenar las cartas ya barajeadas
	cartBaraj =inicializarP();
	int tamanio = longitud(misCartas);
	string carta;
	
	for(int i=0; i<tamanio; i++){
		carta = elemEnPos(rand()%(tamanio-i), misCartas);
		push(cartBaraj, carta);
		BorrarElemento(misCartas, BuscarElementNODO(carta, misCartas));
	}
	return cartBaraj;
}

string pedir(TDAPila *p){
	string dato = p->tope->info; // guarda variable del nodo
	pop(p);           // se elimina nodo
	return dato;
}

map<string,int> valCartas(){
	std::map<string,int> values;
	values["A"] = 1, values["2"] = 2, values["3"] = 3, values["4"] = 4, values["5"] = 5, values["6"] = 6, values["7"] = 7;
	values["8"] = 8, values["9"] = 9, values["10"] = 10, values["J"] = 10, values["Q"] = 10, values["k"] = 10;
	return values;
}

int valorCarta(string cart){
	return valCartas().find(cart)->second;
}

int puntosAcomulados(TDAmano mano){
	std::map<string,int> values = valCartas() ;
	
	int suma_m = 0, suma_M = 0;
	bool band = 1;
	
	if (mano.cartas==NULL){
		return 0;
		
	}
	else {
	    Nodo *aux;
		aux=mano.cartas->inicio;
		while (aux!=NULL){			
			suma_m += values.find(aux->info)->second;  // la suma menor, si suma normal
			
			if(values.find(aux->info)->second == 1 && band){   // la "A" solo puede sumar una vez, para la mayor posibildad
				suma_M += 11;
				band = 0;
			}else {
				suma_M += values.find(aux->info)->second;
			}
			
			aux=aux->sig;
		}
		//cout << endl << "suma_M: " << suma_M << endl;   // imprimir puntos maximos
		//cout <<  "suma_m: " << suma_m << endl;          // imprimir puntos minimos
		//system("Pause");
		
		if(suma_M > suma_m && suma_M <= 21){
			return suma_M;
			}
		else 
			return suma_m;

	}
}
void showResultadosFinal(TDAJugador jugadores[], int numJug){
	cout << "----------------------------------------------------------------------------------------\n";
	cout << "----------------------------------RESULTADOS  GLOBALES----------------------------------\n";
	cout << "----------------------------------------------------------------------------------------\n";
	cout << "JUGADORES(mano)                  CARTAS                 PUNTOS                    DINERO\n";
	for(int i=0; i<numJug; i++){
		cout << "Jugador #"<<i+1 <<"(mano1)                   ";
		cout << getStringLista(jugadores[i].mano1.cartas); 
		cout <<"                   " << puntosAcomulados(jugadores[i].mano1);
		cout << "                " << jugadores[i].mano1.fichApuesta << "\n";
		if(jugadores[i].mano2.cartas != NULL){
			cout << "Jugador #"<<i+1 <<"(mano2)                   ";
			cout << getStringLista(jugadores[i].mano2.cartas); 
			cout <<"                   " << puntosAcomulados(jugadores[i].mano2);
			cout << "                " << jugadores[i].mano1.fichApuesta << "\n";
		}
	}
	cout << "--------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------\n\n";
}

