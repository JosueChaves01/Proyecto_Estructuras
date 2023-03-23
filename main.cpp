#include <iostream>

using namespace std;



struct horarioDisponible{
    //sublista simple
    string dia;
    int horaDeInicio;
    int horaFinal;
    horarioDisponible* sig;

    horarioDisponible(string d, int horaI, int horaF){
        dia = d;
        horaFinal = horaF;
        horaDeInicio = horaI;
        sig = NULL;
    }
};

void imprimirHorarioDisponible(horarioDisponible* horario) {
    while (horario != NULL) {
        cout << "Dia: " << horario->dia << endl;
        cout << "Hora de inicio: " << horario->horaDeInicio << endl;
        cout << "Hora final: " << horario->horaFinal << endl<<endl;
        horario = horario->sig;
    }
}

struct persona{
    //lista doble
    string nombre;
    string cedula;
    int edad;
    horarioDisponible* horarios=NULL;

    persona*sig;
    persona*ant;

    persona(string n, string c, int e){
        nombre = n;
        cedula = c;
        edad = e;
        sig = NULL;
        ant = NULL;
    }
}*primeraPersona;

persona* buscarPorCedula( string cedula) {
    while (primeraPersona != NULL) {
        if (primeraPersona->cedula == cedula) {
            return primeraPersona;
        }
        primeraPersona = primeraPersona->sig;
    }
    return NULL;
}


void imprimirLista() {
    while (primeraPersona != NULL) {
        cout << "Nombre: " << primeraPersona->nombre << endl;
        cout << "Cedula: " << primeraPersona->cedula << endl;
        cout << "Edad: " << primeraPersona->edad << endl;
        cout << "Horario disponible: " << endl;
        horarioDisponible * horario = primeraPersona->horarios;
        imprimirHorarioDisponible(horario);
        cout << endl;
        primeraPersona = primeraPersona->sig;
    }
}

struct subListaIntegrantes{
    persona * integrante;
    subListaIntegrantes*sig;


};
void imprimirIntegrantes(subListaIntegrantes * Integrantes){
    subListaIntegrantes * tempI = Integrantes;
    while(tempI->sig!=NULL){
        cout << "nombre: " << tempI->integrante->nombre << endl;
        tempI = tempI->sig;
    }
}
struct evento{
    //lista simple
    string nombre;
    string lugar;
    string hora;
    string dia;
    int duracion;
    evento*sig;

    evento(string n, string l, string h, string d, int dur){
        nombre = n;
        lugar = l;
        hora = h;
        dia = d;
        duracion = dur;
        sig = NULL;
    }
};



struct subListaEventos{
    evento * e;
    subListaEventos * sig;
};
struct grupoMusical{
    //lista simple
    int edad;
    string nombre;
    string anioDeFundacion;

    persona * director;
    subListaIntegrantes * integrates;
    subListaEventos * eventos;
    grupoMusical*sig;

    grupoMusical(string n, string a){
        nombre = n;
        anioDeFundacion = a;
        sig = NULL;
        persona * director = NULL;
        subListaIntegrantes * integrates = NULL;
        subListaEventos * eventos = NULL;
        grupoMusical*sig = NULL;
    }
}*primerGrupoMusical;

void imprimirGrupoMusical(){
    if(primerGrupoMusical == NULL)
        std::cout<< "\nNo hay grupos\n";
    else{
        grupoMusical * tempG = primerGrupoMusical;
        while(tempG->sig!=NULL){
            cout << "nombre: " << tempG->nombre << endl;
            cout << "anio de funacion: " << tempG->anioDeFundacion << endl;
            cout << "director: " << tempG->director->nombre << endl;
            imprimirIntegrantes(tempG->integrates);
            tempG = tempG->sig;
        }
        cout << "anio de funacion: " << tempG->anioDeFundacion << endl;
        cout << "nombre: " << tempG->nombre << endl;
        cout << "director: " << tempG->director->nombre << endl;

    }
}

grupoMusical* buscarGrupoMusicalPorNombre(string nombre) {
    grupoMusical* actual = primerGrupoMusical;
    while (actual != NULL) {
        if (actual->nombre == nombre) {
            return actual;
        }
        actual = actual->sig;
    }
    return NULL;
}

struct historiaEventos{
    //lista doble y circular
    evento * eventos;
    int calificacion;
    grupoMusical * grupo;

    historiaEventos*sig;
    historiaEventos*ant;

    historiaEventos(int c, grupoMusical*g,evento*&e){
        eventos = e;
        calificacion = c;
        grupo = g;
    }

};
struct instrumentos{
    //lista circular
    string id;
    string nombre;
    string tipo;

    instrumentos*sig;
    instrumentos*ant;

    instrumentos(string i, string n, string t){
        id = i;
        nombre = n;
        tipo = t;
        sig = NULL;
        ant = NULL;
    }


};


//===============================INSERCIONES DE LISTAS========================
//--------------------Insercion lista simple grupo musicar------------
void insercionAlInicioGrupoMusical(string nombre , string anioDeFundacion, grupoMusical *& grupo){
    grupoMusical* nuevoGrupo = new grupoMusical(nombre, anioDeFundacion);
    nuevoGrupo-> sig = grupo;
    grupo = nuevoGrupo;
}
void insertarDirectoraGrupoMusical(string cedula, string nombre){
    persona * per = buscarPorCedula(cedula);
    grupoMusical * grupo = buscarGrupoMusicalPorNombre(nombre);

    if((per==NULL)||(grupo==NULL)){
        cout<< "Datos Invalidos"<<endl;
        return;
    }
    grupo->director = per;
}
void insertarIntegranteaGrupoMusical(string cedula, string nombre){
    persona * per = buscarPorCedula(cedula);
    grupoMusical * grupo = buscarGrupoMusicalPorNombre(nombre);

    if((per==NULL)||(grupo==NULL)){
        cout<< "Datos Invalidos"<<endl;
        return;
    }

    subListaIntegrantes * nuevaSublista = grupo->integrates;
    nuevaSublista->integrante = per;
    grupo->integrates = nuevaSublista;



}
//--------------------Insercion lista doble ordenada por cedula Persona------------
void insertarOrdenado(persona *& p, string nombre, string cedula, int edad) {
    persona *nuevo = new persona(nombre, cedula, edad);

    if (p == NULL) {  // Si la lista esta vacia, el nuevo nodo sera el primer elemento
        p = nuevo;
        return;
    }

    if (cedula < p->cedula) {  // Si la cedula del nuevo nodo es menor que la del primer elemento
        nuevo->sig = p;
        p->ant = nuevo;
        p = nuevo;
        return;
    }

    persona *actual = p;

    while (actual->sig != NULL && actual->sig->cedula < cedula) {  // Buscamos la posicion donde insertar el nuevo nodo
        actual = actual->sig;
    }

    nuevo->sig = actual->sig;
    if (actual->sig != NULL) {
        actual->sig->ant = nuevo;
    }
    actual->sig = nuevo;
    nuevo->ant = actual;
}
 void agregarHorarioaPersona(){
    string cedula;
    cout<< "Ingrese el numero de cedula de la persona a la que desea agregarle un horario"<<endl;
    cin>>cedula;
    persona * per = buscarPorCedula(cedula);
    if(per==NULL){
        cout << "La persona no existe" << endl;
        return;
    }
    int opcion = 10;
    string dia;
    int horaInicio;
    int horaFinal;
    while(opcion != 0){
        cout<<"Ingrese 1 si desea ingresar un nuevo horario y 0 para terminar de agregar horarios"<<endl;
        cin>>opcion;
        if(opcion == 0){
            break;
        }
        if(opcion == 1){
            cout<< "ingrese un dia de la semana"<<endl;
            cin>>dia;
            cout<< "ingrese la hora de inicio"<<endl;
            cin>>horaInicio;
            cout<< "ingrese la hora de finalizacion"<<endl;
            cin>>horaFinal;

            horarioDisponible * nuevoHorario = new horarioDisponible(dia,horaInicio,horaFinal);

            if(per->horarios == NULL){
                per->horarios = nuevoHorario;
            }
            else{
                horarioDisponible * tempH = per->horarios;
                while(tempH->sig != NULL){
                    tempH = tempH->sig;
                }
                tempH->sig = nuevoHorario;
            }
        }
        int opcion = 10;
    }
 }

//==============================MENUS Y SUB-MENUS=============================
//-----------------Menu para ingresar y actualizar informacion--------------
int main();
void menuInformacion() {
    int op = 0;

    while( op != -1){
        std::cout <<"\n==========Menu principal==========" <<std::endl;
        std::cout <<"1) Ingresar datos en listas" <<std::endl;
        std::cout <<"2) Modificar datos de listas" <<std::endl;
        std::cout <<"3) Borrar nodos de listas" <<std::endl;
        std::cout <<"4) Volver al menu principal" <<std::endl;

        std::cout <<"Ingrese la opcion que desea realizar: ";
        std::cin >> op;

        if(op == 1){
          menuInformacion();
        }

        else if(op == 2){

        }

        else if(op == 3){

        }

        else if(op == 4){

            break;
        }

        else{
            std::cout <<"<<<Opcion invalida. ingrese un valor valido>>>" <<std::endl;
        }
        int op = 0;
    }
}

//--------------------MENU DE CONSULTAS--------------------------
void menuConsultas() {
    int op = 0;

    while( op != -1){
        std::cout <<"\n==========Menu principal==========" <<std::endl;
        std::cout <<"1) Persona con mas participaciones en eventos" <<std::endl;  //punto 1
        std::cout <<"2) Eventos que no cumplen con los requisitos" <<std::endl; //punto 2
        std::cout <<"3) Eventos que no cumplen con disponibilidad horaria" <<std::endl; //punto 3
        std::cout <<"4) Instrumento mas y menos popular" <<std::endl; //punto 4
        std::cout <<"5) Persona pertenecientes a mas grupos musicales" <<std::endl; //punto 5
        std::cout <<"6) Persona que toca mas instrumentos" <<std::endl; //punto 6
        std::cout <<"7) Director con mejor calificacion" <<std::endl; //punto 7
        std::cout <<"8) Grupo con mas participaciones en eventos" <<std::endl; //punto 8
        std::cout <<"9) Volver al menu principal" <<std::endl;

        std::cout <<"Ingrese la opcion que desea realizar: ";
        std::cin >> op;

        if(op == 1){

        }

        else if(op == 2){

        }

        else if(op == 3){

        }

        else if(op == 4){

        }

        else if(op == 5){

        }

        else if(op == 6){

        }

        else if (op == 7) {

        }

        else if (op == 8) {

        }

        else if(op == 9){
            main();
        }

        else{
            std::cout <<"<<<Opcion invalida. ingrese un valor valido>>>" <<std::endl;
        }
        int op = 0;
    }
}

//----------------MENU DE REPORTES-------------------------
void menuReportes() {
    int op = 0;

    while( op != -1){
        std::cout <<"\n==========Menu principal==========" <<std::endl;
        std::cout <<"1) Imprimir todas las listas" <<std::endl;  //punto 1
        std::cout <<"2) Imprimir informacion de personas" <<std::endl; //punto 2
        std::cout <<"3) Imprimir grupos musicales" <<std::endl; //punto 3
        std::cout <<"4) Imprimir historial de eventos" <<std::endl; //punto 4;
        std::cout <<"5) Volver al menu principal" <<std::endl;

        std::cout <<"Ingrese la opcion que desea realizar: ";
        std::cin >> op;

        if(op == 1){
            imprimirGrupoMusical();
            imprimirLista();
        }

        else if(op == 2){

        }

        else if(op == 3){

        }

        else if(op == 4){

        }

        else if(op == 5){
            main();
        }

        else{
            std::cout <<"<<<Opcion invalida. ingrese un valor valido>>>" <<std::endl;
        }
        int op = 0;
    }

}

int main()
{
    int op = 0;

    while( op != 4){
        std::cout <<"\n==========Menu principal==========" <<std::endl;
        std::cout <<"1) Ingresar y actualizar informacion" <<std::endl;
        std::cout <<"2) Consultas" <<std::endl;
        std::cout <<"3) Reportes" <<std::endl;
        std::cout <<"4) Salir" <<std::endl;

        std::cout <<"Ingrese la opcion que desea realizar: ";
        std::cin >> op;
        if(op == 4){
            std::cout <<"<<<Fin del programa>>>";
            break;
        }
        else if(op == 1){
          menuInformacion();
        }

        else if(op == 2){
          menuConsultas();
        }

        else if(op == 3){
          menuReportes();
        }

        else{
            std::cout <<"<<<Opcion invalida. ingrese un valor valido>>>" <<std::endl;
        }
        int op = 0;
    }
    //===================================
    //insertarOrdenado(primeraPersona,"Josue","208260603",21);
    //insertarOrdenado(primeraPersona,"Carlos","209212333",20);
    //agregarHorarioaPersona();
    //imprimirLista(primeraPersona);
}
