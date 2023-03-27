#include <iostream>

using namespace std;


//==============================Estructuras==============================
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

struct subListaIntegrantes{
    persona * integrante;
    subListaIntegrantes*sig = NULL;
};

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
}*primerEvento;

struct subListaEventos{
    evento * e;
    subListaEventos * sig;
};

struct grupoMusical{
    //lista simple
    int edad;
    string nombre;
    string anioDeFundacion;

    persona * director=NULL;
    subListaIntegrantes * integrates=NULL;
    subListaEventos * eventos=NULL;
    grupoMusical*sig=NULL;

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

struct historiaEventos{
    //lista doble y circular
    evento * eventos;
    int calificacion;
    grupoMusical * grupo;
    subListaIntegrantes * integrantes  = grupo->integrates;
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

//==============================Buscar==============================
//-----------------buscar grupo musical-----------------
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

//-----------------buscar persona
persona* buscarPersona(string cedula, persona* primeraPersona) {
    persona* actual = primeraPersona;
    while (actual != NULL) {
        if (actual->cedula == cedula) {
            return actual;
        }
        actual = actual->sig;
    }

   return NULL;
}

evento* buscarEventoPorNombre(string nombre, evento* inicio) {
    evento* actual = inicio;
    while (actual != NULL) {
        if (actual->nombre == nombre) {
            return actual; // evento encontrado
        }
        actual = actual->sig;
    }
    return NULL; // evento no encontrado
}


//===============================INSERCIONES DE LISTAS========================
//--------------------Insercion lista simple grupo musicar------------
void insercionAlInicioGrupoMusical(string nombre , string anioDeFundacion, grupoMusical *& grupo){
    grupoMusical* nuevoGrupo = new grupoMusical(nombre, anioDeFundacion);
    nuevoGrupo-> sig = grupo;
    grupo = nuevoGrupo;
}

void insertarDirectoraGrupoMusical(string cedula, string nombre){
    persona * per = buscarPersona(cedula,primeraPersona);
    grupoMusical * grupo = buscarGrupoMusicalPorNombre(nombre);

    if((per==NULL)||(grupo==NULL)){
        cout<< "Datos Invalidos"<<endl;
        return;
    }
    grupo->director = per;
}

void insertarIntegranteEnGrupo(string cedula, string nombreGrupo) {
    persona* p = buscarPersona(cedula,primeraPersona);
    if (p == NULL) {
        cout << "La persona con cedula " << cedula << " no existe." << endl;
        return;
    }
    grupoMusical* g = buscarGrupoMusicalPorNombre(nombreGrupo);
    if (g == NULL) {
        cout << "El grupo musical " << nombreGrupo << " no existe." << endl;
        return;
    }
    subListaIntegrantes* nodo = new subListaIntegrantes;
    nodo->integrante = p;
    if (g->integrates == NULL) {
        g->integrates = nodo;
    } else {
        subListaIntegrantes* temp = g->integrates;
        while (temp->sig != NULL) {
            temp = temp->sig;
        }
        temp->sig = nodo;
    }
}


void insertarEvento(string nombre, string lugar, string hora, string dia, int duracion) {
    evento* nuevoEvento = new evento(nombre, lugar, hora, dia, duracion);
    if (primerEvento == NULL) {
        primerEvento = nuevoEvento;
    } else {
        evento* actual = primerEvento;
        while (actual->sig != NULL) {
            actual = actual->sig;
        }
        actual->sig = nuevoEvento;
    }
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
void agregarHorarioaPersona(string cedula, string dia, int horaInicio, int horaFinal) {
    persona* per = buscarPersona(cedula, primeraPersona);
    if (per == NULL) {
        cout << "La persona no existe" << endl;
        return;
    }
    horarioDisponible* nuevoHorario = new horarioDisponible(dia, horaInicio, horaFinal);

    if (per->horarios == NULL) {
        per->horarios = nuevoHorario;
    }
    else {
        horarioDisponible* tempH = per->horarios;
        while (tempH->sig != NULL) {
            tempH = tempH->sig;
        }
        tempH->sig = nuevoHorario;
    }
}


void agregarHorarioaPersonaManual(){
    string cedula;
    cout<< "Ingrese el numero de cedula de la persona a la que desea agregarle un horario"<<endl;
    cin>>cedula;
    persona * per = buscarPersona(cedula,primeraPersona);
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

//==============================Imprimir==============================
//----------------imprimir Persona----------------
void imprimirHorarioDisponible(horarioDisponible* horario) {
    while (horario != NULL) {
        cout << "Dia: " << horario->dia << endl;
        cout << "Hora de inicio: " << horario->horaDeInicio << endl;
        cout << "Hora final: " << horario->horaFinal << endl<<endl;
        horario = horario->sig;
    }
}

void imprimirListaPersona() {
    cout << "--------------------------Personas--------------------------"<<endl;
    while (primeraPersona != NULL) {
        cout << "-------------Persona-------------"<<endl;
        cout << "Nombre: " << primeraPersona->nombre << endl;
        cout << "Cedula: " << primeraPersona->cedula << endl;
        cout << "Edad: " << primeraPersona->edad << endl;
        cout << "Horario disponible: " << endl;

        horarioDisponible * horario = primeraPersona->horarios;
        if(horario != NULL){
            imprimirHorarioDisponible(horario);
        }
        cout << endl;
        primeraPersona = primeraPersona->sig;
    }
}
//----------------Imprimir Integrantes----------------
void imprimirIntegrantes(subListaIntegrantes * Integrantes){
    cout << "--------------------------Integrantes--------------------------"<<endl;
    while(Integrantes != NULL){
        cout << "-------------Integrante-------------"<<endl;
        cout << "Nombre: " << Integrantes->integrante->nombre << endl;
        cout << "Cedula: " << Integrantes->integrante->cedula << endl;
        cout << "Edad: " << Integrantes->integrante->edad << endl;
        cout << "Horario disponible: " << endl;

        horarioDisponible * horario = Integrantes->integrante->horarios;
        if(horario != NULL){
            imprimirHorarioDisponible(horario);
        }
        Integrantes = Integrantes->sig;
    }

}


//----------------Imprimir Grupo----------------
void imprimirGrupo(){
    while(primerGrupoMusical != NULL){
        cout << "-------------Grupo-------------"<<endl;
        cout << "Nombre: " << primerGrupoMusical->nombre << endl;
        cout << "Anio de funacion: " << primerGrupoMusical->anioDeFundacion << endl;
        cout << "Director: " << primerGrupoMusical->director->nombre << endl;
        cout << "Integrantes: "<< endl;
        grupoMusical* tempG = primerGrupoMusical;
        if(tempG->integrates == NULL){
            cout << "Sin integrantes"<<endl;
        }
        else{
            cout << "--------------------------Integrantes--------------------------"<<endl;
            subListaIntegrantes * Integrantes = primerGrupoMusical->integrates;
            while(Integrantes != NULL){
            cout << "-------------Integrante-------------"<<endl;
            cout << "Nombre: " << Integrantes->integrante->nombre << endl;
            cout << "Cedula: " << Integrantes->integrante->cedula << endl;
            cout << "Edad: " << Integrantes->integrante->edad << endl;
            cout << "Horario disponible: " << endl;

            horarioDisponible * horario = Integrantes->integrante->horarios;
            if(horario != NULL){
                imprimirHorarioDisponible(horario);
            }
            else{
                cout<< "sin asignar" << endl;
            }
            Integrantes = Integrantes->sig;
            }
        primerGrupoMusical = primerGrupoMusical->sig;
        }
    }
}


//----------------Imprimir Eventos----------------
void imprimirEventos() {
    evento* actual = primerEvento;
    cout << "--------------------------Eventos--------------------------"<<endl;
    while (actual != NULL) {
        cout << "-------------Evento-------------"<<endl;
        cout << "Nombre: " << actual->nombre << endl;
        cout << "Lugar: " << actual->lugar << endl;
        cout << "Hora: " << actual->hora << endl;
        cout << "Dia: " << actual->dia << endl;
        cout << "Duracion: " << actual->duracion << endl;
        actual = actual->sig;
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
            break;
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
            imprimirListaPersona();
            imprimirEventos();
            imprimirGrupo();
        }

        else if(op == 2){
            imprimirListaPersona();
        }

        else if(op == 3){
            imprimirGrupo();
        }

        else if(op == 4){

        }

        else if(op == 5){
            break;
        }

        else{
            std::cout <<"<<<Opcion invalida. ingrese un valor valido>>>" <<std::endl;
        }
        int op = 0;
    }

}
//------------------------Cargar Datos--------------------------------

void cargarDatos(){
    insercionAlInicioGrupoMusical("Ajenos","2007",primerGrupoMusical);
    insercionAlInicioGrupoMusical("Morat","2015",primerGrupoMusical);

    insertarOrdenado(primeraPersona,"Josue","208260603",21);
    insertarOrdenado(primeraPersona,"Carlos","302540673",20);
    insertarOrdenado(primeraPersona,"Luis","603210123",19);
    insertarOrdenado(primeraPersona,"Roberth","104820912",22);


    insertarDirectoraGrupoMusical("208260603","Ajenos");
    insertarDirectoraGrupoMusical("302540673","Morat");

    insertarIntegranteEnGrupo("603210123","Ajenos");
    insertarIntegranteEnGrupo("104820912","Morat");

    agregarHorarioaPersona("208260603", "lunes", 1000, 1600);
    agregarHorarioaPersona("208260603", "Martes", 1130, 1630);
    agregarHorarioaPersona("302540673", "Lunes", 7000, 1200);
    agregarHorarioaPersona("302540673", "Jueves", 8000, 1300);
    agregarHorarioaPersona("603210123", "Sabado", 1300, 2000);
    agregarHorarioaPersona("603210123", "Domingo", 9000, 1400);
    agregarHorarioaPersona("104820912", "Miercoles", 8000, 1800);
    agregarHorarioaPersona("104820912", "Viernes", 7030, 1530);

    insertarEvento("BaileFortuna","Fortuna","07:00","Lunes",3.5);

}

bool buscarCedulaEnSublista(string cedula, subListaIntegrantes* sublista) {
    subListaIntegrantes* actual = sublista;
    while (actual != NULL) {
        if (actual->integrante->cedula == cedula) {
            return true; // cédula encontrada en la sublista
        }
        actual = actual->sig;
    }
    return false; // cédula no encontrada en la sublista
}

int main()
{
    cargarDatos();
    int op = 0;

    while( op != 5){
        std::cout <<"\n==========Menu principal==========" <<std::endl;
        std::cout <<"1) Ingresar y actualizar informacion" <<std::endl;
        std::cout <<"2) Consultas" <<std::endl;
        std::cout <<"3) Reportes" <<std::endl;
        std::cout <<"4) Cargar Datos" <<std::endl;
        std::cout <<"5) Salir" <<std::endl;

        std::cout <<"Ingrese la opcion que desea realizar: ";
        std::cin >> op;
        if(op == 5){
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
        else if(op == 4){
          cargarDatos();
        }

        else{
            std::cout <<"<<<Opcion invalida. ingrese un valor valido>>>" <<std::endl;
        }
        int op = 0;
    }

}
