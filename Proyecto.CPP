#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctype.h>
#include <functional>
#include <limits>
#include <stdlib.h>     
#include <time.h>

using namespace std;

struct CFG_t{
	char startSymbol;
	string alfabeto;
	string NoTerminales;
	vector<string> producciones;
};
string elimiarEspacios(string aux){

	for (size_t k = 0; k < aux.length(); k++) {
       	if (aux[k] == ' ' || aux[k] == '\n' || aux[k] == '\t') {
        	aux.erase(k, 1);
           	k--;
        }
    }
    return aux;
}
void imprimirVector(vector<string> v){

	for (vector<string>::iterator i = v.begin(); i != v.end(); ++i)
 	{
 		cout << *i  << endl;
 	}
}

CFG_t recibirCFG(){

	CFG_t CFG;
	cout << "" << endl;
	cout << "Ingrese el simbolo de inicio: " << endl;
	cin >> CFG.startSymbol;
	cout << "" << endl;

	int verAlfabeto = 0;
	string alfabeto;
	cout << "Ingrese alfabeto " << "\n" << " letras pegadas y en minuscula " << "\n no use la letra 'e'(elemento vacia) : " << endl;
	while(verAlfabeto == 0){
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> alfabeto;
		verAlfabeto = 1;
		alfabeto = elimiarEspacios(alfabeto);
		int it = 0;
		for(it ; it < alfabeto.length() && verAlfabeto == 1; it++){
   			if(alfabeto[it] >= 'A' && alfabeto[it] <= 'Z'){
   				cout << "El alfabeto tiene letras mayusculas" << endl;
   				verAlfabeto = 0;
   			}
   			if(alfabeto[it] == 'e' ){
   				cout << "el alfabeto tiene la cadena vacia" << endl;
   				verAlfabeto = 0;
   			}
   		}
	   	if(verAlfabeto == 0){
	   		cout << "Ingrese el alfabeto correctamente: " << endl;
	   	}
	}
	CFG.alfabeto = alfabeto;
	cout << "" << endl;

	int verNT= 0;
	string NT;
	cout << "Ingrese conjunto de no terminales " <<  "\n letras en mayuscula y pegadas: "  << endl;
	while(verNT == 0){
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> NT;
		verNT = 1;
		NT = elimiarEspacios(NT);
		int it = 0;
		for(it ; it < NT.length() && verNT == 1; it++){
   			if(NT[it] >= 'a' && NT[it] <= 'z'){
   				cout << "El conjunto NT no debe tener letras minusculas" << endl;
   				verNT = 0;
   			}
	   		if(verNT == 0){
	   			cout << "Ingrese el conjunto NT correctamente: " << endl;
	   		}
	   	}
	}
	CFG.NoTerminales = NT;
	cout << "" << endl;
	cout << "Las producciones deben organizarce de esta forma : S->AB" << "\n" << " 'e' es la cadena vacia" << endl;
	cout << "Los caracteres en mayuscula son considerados No terminales y los minuscula terminales." << endl;
	cout << "Ingrese la cantidad de producciones :" << endl; 
	cout << "" << endl;
	int cantidadProducciones;
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin >> cantidadProducciones;
	cout << "Ingrese las producciones :" << endl; 
	cout << "" << endl;

	int i = 0;
	while(i < cantidadProducciones){
		cout << "Produccion # " << i+1 << endl;
		string Produccion;
		string auxiliar;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> Produccion;
		auxiliar = Produccion;
		Produccion = elimiarEspacios(Produccion);
		string::size_type found;
		found = Produccion.find("->");
		if(found != string::npos){
   				if(Produccion[0] >= 'A' && Produccion[0] <= 'Z' && Produccion.length()>= 4){
   					int l = 0;
   					for(l; l < auxiliar.length(); l++){
   						if(auxiliar[l] >= 'A' && auxiliar[l] <= 'Z' ||  auxiliar[l] == '-' || auxiliar[l] == '>'){
   							
   							auxiliar.erase(0,auxiliar[l]);
   						}
   					}
   					int bandera = 0;
   					int j = 0, k = 0;
   					int out = 0;
   					while( j < auxiliar.length() && out == 0){
   						k = 0;
   						bandera = 0;
   						while( k < CFG.alfabeto.length()){
   							if( auxiliar[j] == CFG.alfabeto[k]){
   								bandera = 1;
   							} k++;
   						}
   						if(bandera == 0){
   							cout << "Las producciones no estan en el alfabeto" << endl;
   							out = 1;
   						}
   						j++;
   					}
   					if(out == 0){
   						CFG.producciones.push_back(Produccion);
   						i++;
   					}
   				}
   				else{
   					cout << "Los terminales no pueden producir." << endl;
   				}
   		}
   		else{
   			cout << "La produccion no esta escrita correctamente." << endl;
   		}

	}
	return CFG;
}

vector<string> quitarElementoVacio(vector<string> produccionesNormales){
	int cont = 0;
	int pos = -1;
	for (vector<string>::iterator i = produccionesNormales.begin(); i != produccionesNormales.end(); ++i)
	{
		int j = 0;
		for(j;j < (*i).length();++j){
			if((*i)[j] == 'e'){
				pos = cont;
			}
		}
		cont++;
	}
	if(pos == -1){
		return produccionesNormales;
	}
	vector<string> Modificar;
	char NoTerminalConVacio = produccionesNormales[pos][0];
	cont = 0;
	for (vector<string>::iterator i = produccionesNormales.begin(); i != produccionesNormales.end(); ++i)
	{
		if(cont != pos){
			Modificar.push_back(*i);
		}
		cont++;
	}
	vector<string> VectorSinVacios;
	string auxiliarEliminador;
	std::string CadenaSinVacios;
	char Inicial;
	for (vector<string>::iterator i = Modificar.begin(); i != Modificar.end(); ++i)
	{
		string::size_type encontrar;
		encontrar = (*i).find(NoTerminalConVacio);
		CadenaSinVacios = "";
		if(encontrar != string::npos){
			string::size_type found;
			VectorSinVacios.push_back(*i);
			Inicial = (*i)[0];
			auxiliarEliminador = (*i).erase(0,1);
			found = (auxiliarEliminador).find(NoTerminalConVacio);
			if(found != string::npos){
   				auxiliarEliminador.erase(found,1);
   				if(auxiliarEliminador.length() > 3){
					CadenaSinVacios.append(1,Inicial);
					CadenaSinVacios.append(auxiliarEliminador);
					VectorSinVacios.push_back(CadenaSinVacios);
				}			
			}
		}
		else{
			VectorSinVacios.push_back(*i);
		}
	}
	cont = 0;
	pos = -1;
	for (vector<string>::iterator i = VectorSinVacios.begin(); i != VectorSinVacios.end(); ++i)
	{
		int j = 0;
		for(j;j < (*i).length();++j){
			if((*i)[j] == 'e'){
				pos = cont;
			}
		}
		cont++;
	}
	if(pos == -1){
		return VectorSinVacios;
	}

	return quitarElementoVacio(VectorSinVacios);
}

vector<string> quitarElementosUnitarios(vector<string> produccionesNormales){
	int cont = 0;
	int pos = -1;
	for (vector<string>::iterator i = produccionesNormales.begin(); i != produccionesNormales.end(); ++i)
	{
		
		if((*i).length() == 4){
			if((*i)[3] >= 'A' && (*i)[3] <= 'Z'){
				pos = cont;
			}
		}
		cont++;
	}
	if(pos == -1){
		return produccionesNormales;
	}
	vector<string> Modificar;
	char NoTerminalUnitario = produccionesNormales[pos][0];
	char NoTerminalDestino = produccionesNormales[pos][3];
	cont = 0;
	for (vector<string>::iterator i = produccionesNormales.begin(); i != produccionesNormales.end(); ++i)
	{
		if(cont != pos){
			Modificar.push_back(*i);
		}
		cont++;
	}
	vector<string> VectorSinUnitarios;
	string auxiliarEliminador;
	std::string CadenaSinUnitarios;
	for (vector<string>::iterator i = Modificar.begin(); i != Modificar.end(); ++i)
	{
		if((*i)[0] == NoTerminalDestino && (*i)[3] != 'e'){
			VectorSinUnitarios.push_back(*i);
			CadenaSinUnitarios = "";
			auxiliarEliminador = (*i).erase(0,1);
			CadenaSinUnitarios.append(1,NoTerminalUnitario);
			CadenaSinUnitarios.append(auxiliarEliminador);
			VectorSinUnitarios.push_back(CadenaSinUnitarios);
		}
		else{
			VectorSinUnitarios.push_back(*i);
		}
	}
	cont = 0;
	pos = -1;
	for (vector<string>::iterator i = VectorSinUnitarios.begin(); i != VectorSinUnitarios.end(); ++i)
	{
		
		if((*i).length() == 4){
			if((*i)[3] >= 'A' && (*i)[3] <= 'Z'){
				pos = cont;
			}
		}
		cont++;
	}
	if(pos == -1){
		return VectorSinUnitarios;
	}

	return quitarElementosUnitarios(VectorSinUnitarios);
}
string generarProduccion(char NT, char Ter){
	string retorno;
	string flecha = "->";
	retorno.append(1,NT);
	retorno.append(flecha);
	retorno.append(1,Ter);
	return retorno;
}
char seleccionarLetra(string lista){
	string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i = 0,j = 0, bandera = 0;
	char valor;
	for(i;i < alfabeto.length() && bandera == 0; ++i){
		j = 0;
		bandera = 1;
		for(j;j < lista.length() && bandera == 1;++j){
			if(lista[j] == alfabeto[i]){
				bandera = 0;
			}
		}
		if(bandera == 1){
			valor = alfabeto[i];
		}
	}
	return valor;
}

string reescribirProduccion(string produccion, int posQuitar, char NoTerminalNuevo){
	int i;
	string retorno;
	for (i = 0; i < produccion.length(); ++i)
	{
		if(i != posQuitar){
			retorno.append(1,produccion[i]);
		}
		else{
			retorno.append(1,NoTerminalNuevo);
		}
	}
	return retorno;
}
void quitarProduccionesMixtas(vector<string> *produccionesNormales,string *NoTerminales){

	int cont = 0;
	int iterador;
	char NoTerminalNuevo;
	char letraAcambiar;
	string nuevaProduccion;
	int largo = 0;
	int segundoIterador;
	vector<string> guardarTemporalmente;
	for (vector<string>::iterator i = produccionesNormales->begin(); i != produccionesNormales->end(); ++i)
	{	
		if((*i).length() > 4){
			iterador = 0;
			largo = (*i).length();
			for(iterador;iterador < largo;iterador++){
				nuevaProduccion = "";
				NoTerminalNuevo = ' ';
				if((*i)[iterador] >= 'a' && (*i)[iterador] <= 'z'){
					letraAcambiar = (*i)[iterador];
					NoTerminalNuevo = seleccionarLetra(*NoTerminales);
					(*i) = reescribirProduccion((*i),iterador,NoTerminalNuevo);
					for (vector<string>::iterator j = produccionesNormales->begin(); j != produccionesNormales->end(); ++j){
						if((*j).length() > 4){
							for(segundoIterador = 0; segundoIterador < (*j).length();segundoIterador++){
								if(letraAcambiar == (*j)[segundoIterador]){
									(*j) = reescribirProduccion((*j),segundoIterador,NoTerminalNuevo);
								}
							}
						}
					}
					nuevaProduccion = generarProduccion(NoTerminalNuevo,letraAcambiar);
					NoTerminales->append(1,NoTerminalNuevo);
					guardarTemporalmente.push_back(nuevaProduccion);
				}
			}
		}
		cont++;
	}	
	for (vector<string>::iterator j = guardarTemporalmente.begin(); j != guardarTemporalmente.end(); ++j)
	{
		(*produccionesNormales).push_back(*j);
	}
}

vector<string> quitarProduccionesLagras(vector<string> produccionesChomsky,string *NoTerminales){

	int pos = -1;
	int cont = 0;
	for (vector<string>::iterator i = produccionesChomsky.begin(); i != produccionesChomsky.end(); ++i){
		if((*i).length() > 5){
			pos = cont;
		}
		cont++;
	}
	if(pos == -1){
		return produccionesChomsky;
	}
	vector<string> VectorSinProduccionesLargas;
	string ProduccionLarga = produccionesChomsky[pos];
	cont = 0;
	for (vector<string>::iterator i = produccionesChomsky.begin(); i != produccionesChomsky.end(); ++i)
	{
		if(cont != pos){
			VectorSinProduccionesLargas.push_back(*i);
		}
		cont++;
	}
	char productor = ProduccionLarga[0];

	char nuevoNT = seleccionarLetra(*NoTerminales);
	NoTerminales->append(1,nuevoNT);
	ProduccionLarga.erase(0,3);
	string nuevaProduccion1 = "";
	string flecha = "->";
	string nuevaProduccion2 = "";
	nuevaProduccion1.append(1,productor);
	nuevaProduccion1.append(flecha);
	nuevaProduccion1.append(1,nuevoNT);
	nuevaProduccion1.append(1,ProduccionLarga[ProduccionLarga.length()-1]);
	VectorSinProduccionesLargas.push_back(nuevaProduccion1);

	nuevaProduccion2.append(1,nuevoNT);
	nuevaProduccion2.append(flecha);
	int k = 0;
	for(k; k < ProduccionLarga.length()-1; ++k){
		nuevaProduccion2.append(1,ProduccionLarga[k]);
	}

	VectorSinProduccionesLargas.push_back(nuevaProduccion2);
	cont = 0;
	pos = -1;
	for (vector<string>::iterator i = VectorSinProduccionesLargas.begin(); i != VectorSinProduccionesLargas.end(); ++i)
	{
		
		if((*i).length() > 5){
			pos = cont;
		}
		cont++;
	}
	if(pos == -1){
		return VectorSinProduccionesLargas;
	}

	return quitarProduccionesLagras(VectorSinProduccionesLargas, NoTerminales);
}
vector<string> cambiarAgreibachAlgoritmo(vector<string> producciones){

	int cantidadEncontrada = 0;
	int produccionAbuscar;
	string insertar;
	for (vector<string>::iterator i = producciones.begin(); i != producciones.end(); ++i)
	{
		if((*i).length() > 4){
			produccionAbuscar = (*i)[3];
			for (vector<string>::iterator j = producciones.begin(); j != producciones.end(); ++j)
			{
				if((*j)[0] == produccionAbuscar && (*j).length() > 4 && *i != *j){
					(*i).erase(3,1);
					insertar = (*j).erase(0,3);
					(*i).insert(3,insertar);
					(*j) = "";
					return cambiarAgreibachAlgoritmo(producciones);
				}
			}
		}
	}
	return producciones;
}

vector<string> ponerMinusculasIniciales(vector<string> producciones){

	char busqueda;
	string terminalCambio;
	int cont,cont2,largoCadena,bandera;
	for (vector<string>::iterator i = producciones.begin(); i != producciones.end(); ++i)
	{
		if((*i).length() > 4){
			busqueda = (*i)[3];
			cont = 0;
			bandera = 0;
			for (vector<string>::iterator j = producciones.begin(); j != producciones.end(); ++j)
			{
				if((*j)[0] == busqueda && (*j).length() == 4){
					terminalCambio = (*j)[3];
					(*i).erase(3,1);
					(*i).insert(3,terminalCambio);
					cont2 = 0;
					for (vector<string>::iterator k = producciones.begin(); k != producciones.end(); ++k)
					{
						if(cont != cont2){
							largoCadena = (*k).length();
							for(int l = 0; l < largoCadena; ++l){
								if((*k)[l] == busqueda){
									bandera = 1;
								}
							}
						}
						cont2++;
					}
					if(bandera == 0){
						(*j) = "";
					}
				}
				cont++;
			}
		}
	}
	vector<string> greibachFinal;
	for (vector<string>::iterator i = producciones.begin(); i != producciones.end(); ++i)
	{
		if((*i) != ""){
			if( (*i).length() == 4){
				if((*i)[3] >= 'a' && (*i)[3] <= 'z'){
					greibachFinal.push_back(*i);
				}
			}
			else{
				greibachFinal.push_back(*i);
			}
		}
	}
	return greibachFinal;
}

string generarProduccion(vector<string> producciones, char simboloInicial){

	vector<string> produccionesDelInicial;
	int contador = 0;
	for (vector<string>::iterator i = producciones.begin(); i != producciones.end(); ++i)
	{
		if((*i)[0] == simboloInicial){
			produccionesDelInicial.push_back(*i);
			contador++;
		}
	}
	int numeroRandom = rand() % contador;
	string retorno;
	retorno.append(produccionesDelInicial[numeroRandom]);
	retorno.erase(0,3);
	cout << retorno << endl;
	if(retorno.length() == 1 && retorno[3] == 'e'){
		return "";
	}
	else if(retorno.length() == 1){
		return retorno;
	}
	else{
		char nuevoLetra = retorno[1];
		retorno.erase(1,1);
		retorno.insert(1,generarProduccion(producciones,nuevoLetra));
		cout << retorno << endl;
		for (int i = 0; i < retorno.length(); ++i)
		{
			if(retorno[i] >= 'A' && retorno[i] <= 'Z'){
				nuevoLetra = retorno[i];
				retorno.erase(i,1);
				retorno.insert(i,generarProduccion(producciones,nuevoLetra));
			}
		}
		return retorno;
	}	
}

int verificarExistenciaCadena(string cadenaAverificar, vector<string> producciones, char simboloInicial, string cadenaAux){

	int retorno = 0;
	string reserva = cadenaAverificar;
	string temporal;
	string temporalAux = cadenaAux;
	vector<string> produccionesConInicial;
	for (vector<string>::iterator i = producciones.begin(); i != producciones.end(); ++i)
	{
		if((*i)[0] == simboloInicial){
			produccionesConInicial.push_back(*i);
		}
	}
	if(produccionesConInicial.empty()){
		return 0;
	}
	for (vector<string>::iterator j = produccionesConInicial.begin(); j != produccionesConInicial.end(); ++j)
	{
		cadenaAverificar = reserva;
		cadenaAux = temporalAux;
		if((*j)[3] == cadenaAverificar[0]){
			if(cadenaAux == ""){
				cadenaAux = *j;
				cadenaAux.erase(0,4);
				cadenaAverificar.erase(0,1);
			}
			else{
				temporal = *j;
				temporal.erase(0,3);
				cadenaAux.erase(0,1);
				cadenaAux.insert(0,temporal);
			}
			if(cadenaAverificar.length() >= 1 && cadenaAverificar[0] == cadenaAux[0] && cadenaAux.length() >= 1){
				cadenaAux.erase(0,1);
				cadenaAverificar.erase(0,1);
			}
			if(cadenaAverificar.length() == 0 && cadenaAux.length() == 0){
				return  1;
			}
			else{
				retorno = verificarExistenciaCadena(cadenaAverificar, producciones,cadenaAux[0],cadenaAux);
				if(retorno == 1){
					return 1;
				}
				
			}
			
		}
	}
	return 0;
}

void cambiarAchomsky(CFG_t *prueba, CFG_t gramaticaNormal){

	prueba->startSymbol = gramaticaNormal.startSymbol;
	prueba->alfabeto = gramaticaNormal.alfabeto;
	prueba->NoTerminales = gramaticaNormal.NoTerminales;
	prueba->producciones = quitarElementosUnitarios(gramaticaNormal.producciones);
	quitarProduccionesMixtas(&prueba->producciones,&prueba->NoTerminales);
	prueba->producciones = quitarElementoVacio(prueba->producciones);
	prueba->producciones = quitarProduccionesLagras(prueba->producciones,&prueba->NoTerminales);

}

void cambiarAgreibach(CFG_t *prueba, CFG_t gramaticaChomsky){

	prueba->startSymbol = gramaticaChomsky.startSymbol;
	prueba->alfabeto = gramaticaChomsky.alfabeto;
	prueba->NoTerminales = gramaticaChomsky.NoTerminales;
	prueba->producciones = cambiarAgreibachAlgoritmo(gramaticaChomsky.producciones);
	prueba->producciones = ponerMinusculasIniciales(prueba->producciones);
}

void escribirArchivo(CFG_t gramatica,  int archivoBorrar){

	ofstream archivo;
	if( archivoBorrar == 1){
		remove("gramaticaInicial.txt");
		archivo.open ("gramaticaInicial.txt");
	}
	else if( archivoBorrar == 2){
		remove("gramaticaChomsky.txt");
		archivo.open ("gramaticaChomsky.txt");
	}
	else if( archivoBorrar == 3){
		remove("gramaticaGreibach.txt");
		archivo.open ("gramaticaGreibach.txt");
	}
	
	
	if (archivo.is_open()){
		
		cout << "Se escribe la gramatica en el archivo " << endl;
		archivo << gramatica.startSymbol;
		archivo << "\n";
		archivo << gramatica.alfabeto;
		archivo << "\n";
		archivo << gramatica.NoTerminales;
		archivo << "\n";
		for (vector<string>::iterator i = gramatica.producciones.begin(); i != gramatica.producciones.end(); ++i)
		{
			archivo << *i;
			archivo << "\n";
		}
		archivo.close();
	}
	else{
		printf("El archivo no se ha abierto correctamente.\n");
	}
}

int leerArchivo(CFG_t *gramatica, int archivoBorrar){

	ifstream archivo;
	if( archivoBorrar == 1){
		archivo.open ("gramaticaInicial.txt");
	}
	else if( archivoBorrar == 2){
		archivo.open ("gramaticaChomsky.txt");
	}
	else if( archivoBorrar == 3){
		archivo.open ("gramaticaGreibach.txt");
	}
	
	if (archivo.is_open()){
		string text;
		int cont = 0;
		while(getline(archivo,text)){
			archivo.clear();
			if(cont == 0){
				gramatica->startSymbol = text[0];
			}
			else if( cont == 1){
				gramatica->alfabeto = text;
			}
			else if( cont == 2){
				gramatica->NoTerminales = text;
			}
			else{
				gramatica->producciones.push_back(text);
			}
			cont++;
		}
		archivo.close();
		return 1;
	}
	else{
		printf("El archivo no se ha abierto correctamente.\n");
		return 0;
	}
}


int main(){

	CFG_t prueba;
	int archivo = -1;
	srand (time(NULL));
	cout << "Desea leer una gramatica, o ingresar una nueva? (1: ingresar, 0: leer):" << endl;
	int opcion;
	cin >> opcion;
	if(opcion == 1){
		prueba = recibirCFG();
	}
	else if(opcion == 0){
		archivo = leerArchivo(&prueba,1);
		if( archivo == 0){
			cout << "No hay gramaticas guardadas, ingrese una gramatica nueva" << endl;
			prueba = recibirCFG();
		}
		else if( archivo == 1){
			cout << "Se cargo esta gramatica:" << endl;
			cout << "Simbolo inicial: " << prueba.startSymbol << endl;
			cout << "Alfabeto: " << prueba.alfabeto << endl;
			cout << "No terminales: " << prueba.NoTerminales << endl;
			cout << "Producciones: " << endl;
			imprimirVector(prueba.producciones);
		}
	}
	if(opcion == 1 || archivo == 0){
		cout << "Desea guardar la gramatica nueva? (1: si, 0: no):" << endl;
		cin >> opcion;
		if( opcion == 1){
			escribirArchivo(prueba,1);
			cout << "Se ha guardado la gramatica en gramaticaInicial.txt" << endl;
		}
		else{
			cout << "No se ha guardado la gramatica" << endl;
		}
	}
	CFG_t Chomsky;
	cout << " " << endl;
	cout << "Desea cargar una gramatica previa, o pasar a Chomsky la que se acabo de crear? (1: cargar, 0: no cargar):" << endl;
	cin >> opcion;
	if(opcion == 1){
		leerArchivo(&Chomsky,1);
		cout << "Se cargo esta gramatica: " << endl;
		cout << "Simbolo inicial: " << Chomsky.startSymbol << endl;
		cout << "Alfabeto: " << Chomsky.alfabeto << endl;
		cout << "No terminales: " << Chomsky.NoTerminales << endl;
		cout << "Producciones en Chomsky :" << endl;
		imprimirVector(Chomsky.producciones);
	}
	cout << " " << endl;
	cout << "Se va a pasar la gramatica a Chomsky" << endl;
	cout << "Gramatica en Chomsky: " << endl;
	if(opcion == 1){
		cambiarAchomsky(&Chomsky,Chomsky);
	}
	else{
		cambiarAchomsky(&Chomsky,prueba);
	}
	cout << "Simbolo inicial: " << Chomsky.startSymbol << endl;
	cout << "Alfabeto: " << Chomsky.alfabeto << endl;
	cout << "No terminales: " << Chomsky.NoTerminales << endl;
	cout << "Producciones en Chomsky :" << endl;
	imprimirVector(Chomsky.producciones);

	cout << "Desea guardar la gramatica en Chomsky ? (1: si, 0: no):" << endl;
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin >> opcion;
	if( opcion == 1){
		escribirArchivo(Chomsky,2);
		cout << "Se ha guardado la gramatica en gramaticaChomsky.txt" << endl;
	}
	else{
		cout << "No se ha guardado la gramatica Chomsky" << endl;
	}

	CFG_t Greibach;
	cout << " " << endl;
	cout << "Desea cargar una gramatica previa, o pasar a Greibach la que se acabo de crear? (1: cargar, 0: no cargar):" << endl;
	cin >> opcion;
	if(opcion == 1){
		leerArchivo(&Greibach,2);
		cout << "Se cargo esta gramatica: " << endl;
		cout << "Simbolo inicial: " << Greibach.startSymbol << endl;
		cout << "Alfabeto: " << Greibach.alfabeto << endl;
		cout << "No terminales: " << Greibach.NoTerminales << endl;
		cout << "Producciones en Greibach :" << endl;
		imprimirVector(Greibach.producciones);
	}
	cout << " " << endl;
	cout << "Se va a pasar la gramatica a Greibach" << endl;
	cout << "Gramatica: " << endl;
	if(opcion == 1){
		cambiarAgreibach(&Greibach,Greibach);
	}
	else{
		cambiarAgreibach(&Greibach,Chomsky);
	}
	cout << "Simbolo inicial: " << Greibach.startSymbol << endl;
	cout << "Alfabeto: " << Greibach.alfabeto << endl;
	cout << "No terminales: " << Greibach.NoTerminales << endl;
	cout << "Producciones en Greibach:" << endl;
	imprimirVector(Greibach.producciones);

	cout << "Desea guardar la gramatica en Greibach ? (1: si, 0: no):" << endl;
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin >> opcion;
	if( opcion == 1){
		escribirArchivo(Greibach,3);
		cout << "Se ha guardado la gramatica en gramaticaGreibach.txt" << endl;
	}
	else{
		cout << "No se ha guardado la gramatica Greibach" << endl;
	}
	CFG_t greibachParaCadena;
	cout << " " << endl;
	cout << "Se va a generar una cadena paso a paso a partir de la gramatica greibach:" << endl;
	cout << " " << endl;
	cout << "Desea cargar una gramatica previa,usar el Greibach la que se acabo de generar? (1: cargar, 0: no cargar):" << endl;
	cin >> opcion;
	if(opcion == 1){
		leerArchivo(&greibachParaCadena,3);
		cout << "Se cargo esta gramatica: " << endl;
		cout << "Simbolo inicial: " << greibachParaCadena.startSymbol << endl;
		cout << "Alfabeto: " << greibachParaCadena.alfabeto << endl;
		cout << "No terminales: " << greibachParaCadena.NoTerminales << endl;
		cout << "Producciones en Greibach :" << endl;
		imprimirVector(greibachParaCadena.producciones);
	}
	else{
		greibachParaCadena = Greibach;
	}
	cout << " " << endl;
	string produccion = generarProduccion(greibachParaCadena.producciones,greibachParaCadena.startSymbol);
	cout << "La cadena generada es: " << produccion << endl;
	cout << " " << endl;
	cout << " " << endl;
	cout << "Se va a verificar si una cadena puede ser generada con la gramatica." << endl;
	cout << "Ingrese una cadena a verificar en el CFG " << endl;
	string cadena;
	cin >> cadena;
	int verificador;
	verificador = verificarExistenciaCadena(cadena,greibachParaCadena.producciones,greibachParaCadena.startSymbol,"");
	if( verificador == 1){
		cout << "La cadena si es generada por la gramatica" << endl;
	}
	else if( verificador == 0){
		cout << "La cadena no es generada por la gramatica" << endl;
	}
}