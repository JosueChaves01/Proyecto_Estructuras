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
}*PrimerInstrumento;

struct subListaInstrumentos{
    instrumentos * instrumento = NULL;
    subListaInstrumentos * sig = NULL;
};

struct subListaInstrumentosSolicitados{
    int cant = 0;
    instrumentos * instrumento = NULL;
    subListaInstrumentosSolicitados * sig = NULL;
};

struct subListaGrupos;

struct persona{
    //lista doble
    string nombre;
    string cedula;
    int edad;
    horarioDisponible* horarios=NULL;
    subListaInstrumentos * instrumentos= NULL;
    subListaGrupos * grupos = NULL;
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
    evento*sig = NULL;
    subListaInstrumentosSolicitados * instrumentosSolicitados = NULL;

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
    evento * e = NULL;
    subListaEventos * sig = NULL;
};

struct grupoMusical{
    //lista simple
    int edad;
    string nombre;
    string anioDeFundacion;

    persona * director=NULL;
    subListaIntegrantes * integrates=NULL;
    subListaEventos * eventos = NULL;
    grupoMusical*sig=NULL;

    grupoMusical(string n, string a){
        nombre = n;
        anioDeFundacion = a;
        sig = NULL;
    }
}*primerGrupoMusical;

struct subListaGrupos{
    grupoMusical * grupo=NULL;
    subListaGrupos * sig = NULL;
};

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

}*primerHistorialEventos;

//==============================Funciones==============================
//---------------------Verificar datos repetidos grupo---------------

bool verificarGrupo(string nombre){
    grupoMusical *actual = primerGrupoMusical;
    while (actual != NULL) {
        if (actual->nombre == nombre) {
            return false; // Nombre encontrado, no es único
        }
        actual = actual->sig;
    }
    return true; // Nombre no encontrado, es único
}
//---------------------Verificar datos repetidos persona---------------

bool verificarPersonaPorCedula(string cedula){
    persona *actual = primeraPersona;
    while (actual != NULL) {
        if (actual->cedula == cedula) {
            return false;
        }
        actual = actual->sig;
    }
    return true;
}
//---------------------Verificar datos repetidos Evento---------------

bool verificarEventoPorNombre(string nombre){
    evento * actual = primerEvento;
    while(actual != NULL) {
        if(actual->nombre == nombre){
            return false;
        }
        actual = actual->sig;
    }
    return true;
}

//---------------------Verificar datos repetidos instrumento---------------

bool verificarInstrumentoPorNombre(string nombre){
    instrumentos * actual = PrimerInstrumento;
    while(actual != NULL) {
        if(actual->id == nombre){
            return false;
        }
        actual = actual->sig;
        if(actual == PrimerInstrumento){ // Si se llega al primer elemento nuevamente, salir del bucle
            break;
        }
    }
    return true;
}


//---------------------BuscarPersona en integrantes---------------
bool buscarCedulaEnSublista(string cedula, subListaIntegrantes* sublista) {
    subListaIntegrantes* actual = sublista;
    while (actual != NULL) {
        if (actual->integrante->cedula == cedula) {
            return true;
        }
        actual = actual->sig;
    }
    return false;
}



//---------------------PERSONA CON MAS PARTICIPACIONES EN EVENTOS---------------

void personaMasParticipaciones() {
    persona* p =primeraPersona;
    int maxParticipaciones = 0;
    persona* maxPersona = primeraPersona;
    historiaEventos * primerH = primerHistorialEventos;



    while (p != NULL) {
        int participaciones = 0;
        historiaEventos * tempH = primerH;
        while (tempH != primerH->ant) {

            if(buscarCedulaEnSublista(p->cedula,tempH->integrantes) == true){
                participaciones++;
            }
            tempH = tempH->sig;
        }

        if (participaciones > maxParticipaciones) {
            maxParticipaciones = participaciones;
            maxPersona = p;
        }

        p = p->sig;
    }

    if (maxPersona != NULL) {
        cout << "La persona con más participaciones en eventos es " << maxPersona->nombre << " con " << maxParticipaciones << " participaciones." << endl;
    }
    else {
        cout << "No hay ninguna persona registrada en el sistema." << endl;
    }
}


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

//-----------------buscar persona-----------------
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
//-----------------buscar Evento-----------------
evento* buscarEventoPorNombre(string nombre, evento* inicio) {
    evento* actual = inicio;
    while (actual != NULL) {
        if (actual->nombre == nombre) {
            return actual;
        }
        actual = actual->sig;
    }
    return NULL;
}
//-----------------buscar instrumento-----------------
instrumentos* buscarInstrumento(string idBuscado, instrumentos* primerInstrumento) {
    if (primerInstrumento == NULL) {
        return NULL;
    }

    instrumentos* instrumentoActual = primerInstrumento;
    do {
        if (instrumentoActual->id == idBuscado) {
            return instrumentoActual;
        }
        instrumentoActual = instrumentoActual->sig;
    } while (instrumentoActual != primerInstrumento);
    return NULL;
}



//===============================INSERCIONES DE LISTAS========================
//--------------------Insercion lista simple grupo musicar------------
void insercionAlInicioGrupoMusical(string nombre , string anioDeFundacion, grupoMusical *& grupo){
    if(verificarGrupo(nombre) == true){
    grupoMusical* nuevoGrupo = new grupoMusical(nombre, anioDeFundacion);
    nuevoGrupo-> sig = grupo;
    grupo = nuevoGrupo;
    }
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
    if(verificarEventoPorNombre(nombre)== true){
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
    else{
        cout<< "datos repetidos" << endl;
    }
}

void insertarPersona(persona *& p, string nombre, string cedula, int edad) {
    if(verificarPersonaPorCedula(cedula)==true){
        persona *nuevo = new persona(nombre, cedula, edad);
        if (p == NULL) {
            p = nuevo;
            return;
        }
        if (cedula < p->cedula) {
            nuevo->sig = p;
            p->ant = nuevo;
            p = nuevo;
            return;
        }
        persona *actual = p;
        while (actual->sig != NULL && actual->sig->cedula < cedula) {
            actual = actual->sig;
        }
        nuevo->sig = actual->sig;
        if (actual->sig != NULL) {
            actual->sig->ant = nuevo;
        }
        actual->sig = nuevo;
        nuevo->ant = actual;
    }
    else{
        cout<< "datos repetidos" << endl;
    }
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

void insertarInstrumento(instrumentos** primero, string id, string nombre, string tipo) {
    if(verificarInstrumentoPorNombre(nombre)==true){
        instrumentos* nuevo = new instrumentos(id, nombre, tipo);
        if (*primero == NULL) {
            *primero = nuevo;
            nuevo->sig = nuevo;
            nuevo->ant = nuevo;
        } else {
            instrumentos* ultimo = (*primero)->ant;
            nuevo->sig = *primero;
            nuevo->ant = ultimo;
            (*primero)->ant = nuevo;
            ultimo->sig = nuevo;
        }
    }
    else{
        cout<< "datos repetidos" << endl;
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


void insertarInstrumentoaPersona(string cedula, string id){
    instrumentos * instrumento = buscarInstrumento(id,PrimerInstrumento);
    persona *p = buscarPersona(cedula,primeraPersona);
    if(instrumento == NULL){
        cout << "No existe el instrumento"<< endl;
    }
    if(p == NULL){
        cout << "No existe la persona"<< endl;
    }
    else{
        subListaInstrumentos * nodo = new subListaInstrumentos;
        nodo->instrumento = instrumento;
        if(p->instrumentos == NULL){
            p->instrumentos = nodo;
        }
        else{
            subListaInstrumentos * tempI = p->instrumentos;
            while(tempI->sig != NULL){
                tempI = tempI->sig;
            }
            tempI->sig = nodo;

        }
    }
}

void insertarEventoaGrupo(string nombre, string nombreE){
    evento * ev = buscarEventoPorNombre(nombreE,primerEvento);
    grupoMusical * grupo = buscarGrupoMusicalPorNombre(nombre);
    if(ev == NULL){
        cout << "No existe el evento"<< endl;
    }
    if(grupo == NULL){
        cout << "No existe el grupo"<< endl;
    }
    else{

        subListaEventos * nodo = new subListaEventos;
        nodo->e = ev;
        if(grupo->eventos == NULL){
            grupo->eventos = nodo;
        }
        else{
            subListaEventos * tempE = grupo->eventos;
            while(tempE->sig != NULL){
                tempE = tempE->sig;
            }
            tempE->sig = nodo;
        }
    }
}
void insertarInstrumentosaGrupo(string id, int cant,string nombreE){
    instrumentos * inst = buscarInstrumento(id,PrimerInstrumento);
    evento * ev = buscarEventoPorNombre(nombreE,primerEvento);
    if(inst == NULL){
        cout << "No existe el instrumento"<< endl;
    }
    if(ev == NULL){
        cout << "No existe el evento"<< endl;
    }
    else{
        subListaInstrumentosSolicitados * nodo = new subListaInstrumentosSolicitados;
        nodo->cant = cant;
        nodo->instrumento = inst;
        if(ev->instrumentosSolicitados == NULL){
            ev->instrumentosSolicitados = nodo;
        }
        else{
            subListaInstrumentosSolicitados * tempI = ev->instrumentosSolicitados;
            while(tempI->sig != NULL){
                tempI = tempI->sig;
            }
            tempI->sig = nodo;
        }
    }
}

//==============================Imprimir==============================
//---------imprimir Horario Disponible-----------

void imprimirHorarioDisponible(horarioDisponible* horario) {
    while (horario != NULL) {
        cout << "Dia: " << horario->dia << endl;
        cout << "Hora de inicio: " << horario->horaDeInicio << endl;
        cout << "Hora final: " << horario->horaFinal << endl<<endl;
        horario = horario->sig;
    }
}
//----------------Imprimir Sublista Instrumentos----------------

void imprimirSubListaInstrumentos(subListaInstrumentos* lista) {
    while (lista != NULL) {
        cout << "Instrumento: " << lista->instrumento->nombre << endl;
        lista = lista->sig;
    }

}
//----------------Imprimir Sublista Instrumentos Solicitados----------------

void imprimirSubListaInstrumentosSolicitados(subListaInstrumentosSolicitados* lista) {
    while (lista != NULL) {
        cout << "Instrumento: " << lista->instrumento->nombre << endl;
        cout << "cantidad: " << lista->cant << endl;
        lista = lista->sig;
    }

}
//----------------Imprimir Sublista eventos----------------

void imprimirSubListaEventos(subListaEventos * lista) {
    while (lista != NULL) {
        cout << "Evento: " << lista->e->nombre << endl;
        lista = lista->sig;
    }
}
//----------------imprimir Persona----------------

void imprimirListaPersona() {
    cout << "--------------------------Personas--------------------------"<<endl;
    while (primeraPersona != NULL) {
        cout << "-------------Persona-------------"<<endl;
        cout << "Nombre: " << primeraPersona->nombre << endl;
        cout << "Cedula: " << primeraPersona->cedula << endl;
        cout << "Edad: " << primeraPersona->edad << endl;
        horarioDisponible * horario = primeraPersona->horarios;
        if(horario != NULL){
            cout << "Horario disponible: " << endl;
            imprimirHorarioDisponible(horario);
        }
        if(primeraPersona->instrumentos != NULL){
        cout << "Instrumentos que toca: " << endl;
            imprimirSubListaInstrumentos(primeraPersona->instrumentos);
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
void imprimirEvento(subListaEventos * event);

//----------------Imprimir Grupo----------------
void imprimirListaGruposMusicales(grupoMusical* primerGrupo) {
    cout << "--------------------------Grupos--------------------------"<<endl;

    if (primerGrupo == NULL) {
        cout << "La lista está vacia." << endl;
        return;
    }

    grupoMusical* p = primerGrupo;
    while (p != NULL) {
        cout << "-------------Grupo-------------"<<endl;

        cout << "Nombre: " << p->nombre << endl;
        cout << "Anio de fundacinn: " << p->anioDeFundacion << endl;
        if(p->director != NULL){
            cout << "Director: " << p->director->nombre << endl;
        }
        if(p->integrates != NULL){
            cout << "Integrantes: " << endl;
            imprimirIntegrantes(p->integrates);
        }
        if(p->eventos != NULL){
            subListaEventos * lista = p->eventos;
            cout << "Eventos: " << endl;
            imprimirSubListaEventos(p->eventos);
        }
        p = p->sig;
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
        if(actual->instrumentosSolicitados != NULL){
            cout << "instrumentos solicitados: " << endl;
            imprimirSubListaInstrumentosSolicitados(actual->instrumentosSolicitados);
        }
        actual = actual->sig;
    }
}
void imprimirEvento(evento * event) {
    evento * actual = event;
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
void imprimirEvento(subListaEventos * event) {
    subListaEventos* actual = event;
    cout << "--------------------------Eventos--------------------------"<<endl;
    while (actual != NULL) {
        cout << "-------------Evento-------------"<<endl;
        cout << "Nombre: " << actual->e->nombre << endl;
        cout << "Lugar: " << actual->e->lugar << endl;
        cout << "Hora: " << actual->e->hora << endl;
        cout << "Dia: " << actual->e->dia << endl;
        cout << "Duracion: " << actual->e->duracion << endl;
        actual = actual->sig;
    }
}
//----------------Imprimir Historial de Eventos----------------

void imprimirHistorialEventos(historiaEventos* primerHistorialEventos) {
    historiaEventos* historial = primerHistorialEventos->sig;
    if(primerHistorialEventos != NULL){
        cout << "No hay ningun dato regristrado" << endl;
    }
    else{
        do {
            cout << "Grupo musical: " << historial->grupo->nombre << endl;
            cout << "Calificación: " << historial->calificacion << endl;
            cout << "Eventos: " << endl;
            imprimirEvento(historial->eventos);
            cout << "Integrantes: " << endl;
            imprimirIntegrantes(historial->integrantes);
            cout << endl;
            historial = historial->sig;
        } while (historial != primerHistorialEventos);
    }
}

//----------------Imprimir Instrumentos----------------

void imprimirInstrumentos(instrumentos* primero) {
    if (primero == NULL) {
        cout << "La lista está vacía" << endl;
        return;
    }
    instrumentos* actual = primero;
    do {
        cout << "ID: " << actual->id << ", Nombre: " << actual->nombre << ", Tipo: " << actual->tipo << endl;
        actual = actual->sig;
    } while (actual != primero);
}

void personaConMasInstrumentos(persona* primeraPersona) {
    persona* personaActual = primeraPersona;
    persona* personaConMas = NULL;
    int maxInstrumentos = 0;

    while (personaActual != NULL) {
        subListaInstrumentos* sublistaActual = personaActual->instrumentos;
        int numInstrumentos = 0;

        while (sublistaActual != NULL) {
            numInstrumentos++;
            sublistaActual = sublistaActual->sig;
        }

        if (numInstrumentos > maxInstrumentos) {
            maxInstrumentos = numInstrumentos;
            personaConMas = personaActual;
        }

        personaActual = personaActual->sig;
    }

    cout << "\nLa persona que toca mas instrumentos es: " << personaConMas->nombre << " , toca: " << maxInstrumentos << " instrumentos" << endl;
}
//===========================Instrumetno mas y menos tocado==================================
void instrumentoMenosTocado() {
    struct instrumentoContador {
        instrumentos* instrumento;
        int contador;
        instrumentoContador* sig;

        instrumentoContador(instrumentos* inst) {
            instrumento = inst;
            contador = 0;
            sig = NULL;
        }
    };

    instrumentoContador* primerInstrumentoContador = NULL;

    persona* actualPersona = primeraPersona;
    while(actualPersona != NULL) {
        subListaInstrumentos* actualSubLista = actualPersona->instrumentos;
        while(actualSubLista != NULL) {
            instrumentos* actualInstrumento = actualSubLista->instrumento;

            instrumentoContador* actualInstrumentoContador = primerInstrumentoContador;
            while(actualInstrumentoContador != NULL && actualInstrumentoContador->instrumento != actualInstrumento) {
                actualInstrumentoContador = actualInstrumentoContador->sig;
            }

            if(actualInstrumentoContador == NULL) {
                actualInstrumentoContador = new instrumentoContador(actualInstrumento);
                actualInstrumentoContador->sig = primerInstrumentoContador;
                primerInstrumentoContador = actualInstrumentoContador;
            }

            actualInstrumentoContador->contador++;

            actualSubLista = actualSubLista->sig;
        }
        actualPersona = actualPersona->sig;
    }

    instrumentoContador* actualInstrumentoContador = primerInstrumentoContador;
    instrumentos* instrumentoMenosTocado = NULL;
    int contadorMasBajo = INT_MAX;
    while(actualInstrumentoContador != NULL) {
        if(actualInstrumentoContador->contador < contadorMasBajo) {
            contadorMasBajo = actualInstrumentoContador->contador;
            instrumentoMenosTocado = actualInstrumentoContador->instrumento;
        }
        actualInstrumentoContador = actualInstrumentoContador->sig;
    }

    if(instrumentoMenosTocado != NULL) {
        cout << "El instrumento menos tocado es: " << instrumentoMenosTocado->nombre << endl;
    } else {
        cout << "No hay información suficiente para determinar el instrumento menos tocado." << endl;
    }
}


void instrumentoMasTocado() {
    struct instrumentoContador {
        instrumentos* instrumento;
        int contador;
        instrumentoContador* sig;

        instrumentoContador(instrumentos* inst) {
            instrumento = inst;
            contador = 0;
            sig = NULL;
        }
    };

    instrumentoContador* primerInstrumentoContador = NULL;

    persona* actualPersona = primeraPersona;
    while(actualPersona != NULL) {
        subListaInstrumentos* actualSubLista = actualPersona->instrumentos;
        while(actualSubLista != NULL) {
            instrumentos* actualInstrumento = actualSubLista->instrumento;

            instrumentoContador* actualInstrumentoContador = primerInstrumentoContador;
            while(actualInstrumentoContador != NULL && actualInstrumentoContador->instrumento != actualInstrumento) {
                actualInstrumentoContador = actualInstrumentoContador->sig;
            }

            if(actualInstrumentoContador == NULL) {
                actualInstrumentoContador = new instrumentoContador(actualInstrumento);
                actualInstrumentoContador->sig = primerInstrumentoContador;
                primerInstrumentoContador = actualInstrumentoContador;
            }

            actualInstrumentoContador->contador++;

            actualSubLista = actualSubLista->sig;
        }
        actualPersona = actualPersona->sig;
    }

    instrumentoContador* actualInstrumentoContador = primerInstrumentoContador;
    instrumentos* instrumentoMasTocado = NULL;
    int contadorMasAlto = 0;
    while(actualInstrumentoContador != NULL) {
        if(actualInstrumentoContador->contador > contadorMasAlto) {
            contadorMasAlto = actualInstrumentoContador->contador;
            instrumentoMasTocado = actualInstrumentoContador->instrumento;
        }
        actualInstrumentoContador = actualInstrumentoContador->sig;
    }

    if(instrumentoMasTocado != NULL) {
        cout << "El instrumento más tocado es: " << instrumentoMasTocado->nombre << endl;
    } else {
        cout << "No hay información suficiente para determinar el instrumento más tocado." << endl;
    }
}


//=================PERSONA PERTENECIENTE A MAS GRUPOS MUSICALES========================
void personaEnMasGrupos(persona* primeraPersona) {
    int maxGrupos = 0;
    persona* personaMasGrupos = NULL;

    for (grupoMusical* gm = primerGrupoMusical; gm != NULL; gm = gm->sig) {
        for (subListaIntegrantes* si = gm->integrates; si != NULL; si = si->sig) {
            int numGrupos = 0;
            persona* p = si->integrante;

            for (subListaGrupos* si2 = p->grupos; si2 != NULL; si2 = si2->sig) {
                numGrupos++;
            }

            if (numGrupos > maxGrupos) {
                maxGrupos = numGrupos;
                personaMasGrupos = p;
            }
        }
    }

    if (personaMasGrupos != NULL) {
        cout << "La persona con más grupos musicales es: " << personaMasGrupos->nombre << endl;
    } else {
        cout << "No se encontró ninguna persona en la lista de grupos musicales." << endl;
    }
}

//=================GRUPO CON MAS EVENTOS======================
void grupoMasEventos(grupoMusical* grupo) {
    grupoMusical* grupoActual = primerGrupoMusical;
    grupoMusical* grupoConMas = NULL;
    int maxEventos = 0;

    while(grupo != NULL) {
        subListaEventos* sublistaAcual = grupoActual ->eventos;
        int numEventos = 0;

        while(sublistaAcual != NULL) {
            numEventos++;
            sublistaAcual = sublistaAcual->sig;
        }

        if(numEventos > maxEventos){
            maxEventos = numEventos;
            grupoConMas = grupoActual;
        }

        grupoActual = grupoActual->sig;

        cout <<"El grupo con mas eventos es: " <<grupoConMas->nombre <<" con " <<maxEventos <<" eventos" <<endl;
    }
}

//===================================Borrar===================================
//----------------Borrar Persona----------------
void borrarPersona(string cedulaBuscada, persona*& primerPersona) {
    persona* personaActual = primerPersona;

    while (personaActual != NULL) {
        if (personaActual->cedula == cedulaBuscada) {

            if (personaActual == primeraPersona) {
                primeraPersona = personaActual->sig;
                if (primeraPersona != NULL) {
                    primeraPersona->ant = NULL;
                }
            }

            else if (personaActual->sig == NULL) {
                personaActual->ant->sig = NULL;
            }

            else {
                personaActual->sig->ant = personaActual->ant;
                personaActual->ant->sig = personaActual->sig;
            }


            delete personaActual;


            return;
        }
        personaActual = personaActual->sig;
    }

    cout << "No se encontró a la persona con la cédula " << cedulaBuscada << "." << endl;
}

//----------------Borrar Evento----------------

void borrarEvento(string nombreBuscado, evento*& primerEvento) {
    evento* eventoActual = primerEvento;
    evento* eventoAnterior = NULL;

    while (eventoActual != NULL) {
        if (eventoActual->nombre == nombreBuscado) {
            if (eventoActual == primerEvento) {
                primerEvento = eventoActual->sig;
            }

            else {
                eventoAnterior->sig = eventoActual->sig;
            }
            delete eventoActual;
            return;
        }
        eventoAnterior = eventoActual;
        eventoActual = eventoActual->sig;
    }
    cout << "No se encontró el evento con el nombre " << nombreBuscado << "." << endl;
}

//----------------Borrar Grupo----------------

void borrarGrupoMusical(string nombreBuscado, grupoMusical*& primerGrupoMusical) {
    grupoMusical* grupoMusicalActual = primerGrupoMusical;
    grupoMusical* grupoMusicalAnterior = NULL;

    while (grupoMusicalActual != NULL) {
        if (grupoMusicalActual->nombre == nombreBuscado) {
            if (grupoMusicalActual == primerGrupoMusical) {
                primerGrupoMusical = grupoMusicalActual->sig;
            }

            else {
                grupoMusicalAnterior->sig = grupoMusicalActual->sig;
            }
            delete grupoMusicalActual;
            return;
        }
        grupoMusicalAnterior = grupoMusicalActual;
        grupoMusicalActual = grupoMusicalActual->sig;
    }
     cout << "No se encontró el grupo musical con el nombre " << nombreBuscado << "." << endl;
}

void borrarInstrumento(string id) {
    if (PrimerInstrumento == NULL) {
        return;
    }

    instrumentos* inicio = PrimerInstrumento;
    instrumentos* fin = PrimerInstrumento->ant;

    while (inicio != fin) {
        instrumentos* medio = inicio;

        int distancia = 0;
        while (medio->sig != inicio && distancia <= fin - inicio) {
            medio = medio->sig;
            distancia++;
        }

        if (medio->id == id) {
            inicio = fin = medio;
            break;
        } else if (medio->id < id) {
            inicio = medio->sig;
        } else {
            fin = medio->ant;
        }
    }

    if (inicio->id == id) {
        if (inicio == PrimerInstrumento) {
            PrimerInstrumento = inicio->sig;
        }

        inicio->ant->sig = inicio->sig;
        inicio->sig->ant = inicio->ant;

        delete inicio;
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
            personaMasParticipaciones();
        }

        else if(op == 2){

        }

        else if(op == 3){

        }

        else if(op == 4){
            instrumentoMasTocado();
            instrumentoMenosTocado();
        }

        else if(op == 5){
            personaEnMasGrupos(primeraPersona);
        }

        else if(op == 6){
            personaConMasInstrumentos(primeraPersona);
        }

        else if (op == 7) {

        }

        else if (op == 8) {
            grupoMasEventos(primerGrupoMusical);
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

            std::cout <<"\nLista Persona"<<endl;
            imprimirListaPersona();
            std::cout <<"\nLista Eventos"<<endl;
            imprimirEventos();
            std::cout <<"\nLista Grupos"<<endl;
            imprimirListaGruposMusicales(primerGrupoMusical);
            std::cout <<"\nLista instrumentos"<<endl;
            imprimirInstrumentos(PrimerInstrumento);

        }

        else if(op == 2){
            imprimirListaPersona();
        }

        else if(op == 3){
            imprimirListaGruposMusicales(primerGrupoMusical);
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
    //10 inserciones
    insercionAlInicioGrupoMusical("Ajenos","2007",primerGrupoMusical);
    insercionAlInicioGrupoMusical("Morat","2015",primerGrupoMusical);
    insercionAlInicioGrupoMusical("Almendros","2012",primerGrupoMusical);
    insercionAlInicioGrupoMusical("Radiohead","1985",primerGrupoMusical);
    insercionAlInicioGrupoMusical("Metallica","1981",primerGrupoMusical);
    insercionAlInicioGrupoMusical("Nirvana","1987",primerGrupoMusical);
    insercionAlInicioGrupoMusical("Coldplay","1996",primerGrupoMusical);
    insercionAlInicioGrupoMusical("Muse","1994",primerGrupoMusical);
    insercionAlInicioGrupoMusical("Korn","1993",primerGrupoMusical);
    insercionAlInicioGrupoMusical("Oasis","1991",primerGrupoMusical);
    //10 inserciones
    insertarPersona(primeraPersona,"Josue","208260603",21);
    insertarPersona(primeraPersona,"Carlos","302540673",20);
    insertarPersona(primeraPersona,"Luis","603210123",19);
    insertarPersona(primeraPersona,"Roberth","104820912",22);
    insertarPersona(primeraPersona,"Steve","209134609",22);
    insertarPersona(primeraPersona,"Ronaldo","745813926",19);
    insertarPersona(primeraPersona,"Mario","581934762",23);
    insertarPersona(primeraPersona,"Aberto","674219085",24);
    insertarPersona(primeraPersona,"Diego","420691337",17);
    insertarPersona(primeraPersona,"Rodrigo","567891234",20);
    //10 inserciones
    insertarInstrumento(&PrimerInstrumento,"1","trompeta","viento");
    insertarInstrumento(&PrimerInstrumento,"2","trombon","viento");
    insertarInstrumento(&PrimerInstrumento,"3","saxofon","viento");
    insertarInstrumento(&PrimerInstrumento,"4","violin","cuerdas");
    insertarInstrumento(&PrimerInstrumento,"5","guitarra","cuerdas");
    insertarInstrumento(&PrimerInstrumento,"6","ukelele","cuerdas");
    insertarInstrumento(&PrimerInstrumento,"7","bateria","percusion");
    insertarInstrumento(&PrimerInstrumento,"8","Bombo","percusion");
    insertarInstrumento(&PrimerInstrumento,"9","triangulo","percusion");
    insertarInstrumento(&PrimerInstrumento,"10","bajo","electricos");

    //falta
    insertarInstrumentoaPersona("302540673","1");
    insertarInstrumentoaPersona("302540673","2");
    //falta
    insertarEvento("BaileFortuna","Fortuna","07:00","Lunes",3.5);
    //falta
    insertarEventoaGrupo("Ajenos","BaileFortuna");
    //falta
    insertarInstrumentosaGrupo("3",3,"BaileFortuna");
    //falta
    insertarDirectoraGrupoMusical("603210123","Ajenos");
    insertarDirectoraGrupoMusical("302540673","Morat");
    //falta
    insertarIntegranteEnGrupo("603210123","Ajenos");
    insertarIntegranteEnGrupo("104820912","Morat");
    //10 inserciones
    agregarHorarioaPersona("208260603", "lunes", 1000, 1600);
    agregarHorarioaPersona("208260603", "Martes", 1130, 1630);
    agregarHorarioaPersona("302540673", "Lunes", 7000, 1200);
    agregarHorarioaPersona("302540673", "Jueves", 8000, 1300);
    agregarHorarioaPersona("603210123", "Sabado", 1300, 2000);
    agregarHorarioaPersona("603210123", "Domingo", 9000, 1400);
    agregarHorarioaPersona("104820912", "Miercoles", 8000, 1800);
    agregarHorarioaPersona("104820912", "Viernes", 7030, 1530);

    borrarPersona("208260603",primeraPersona);

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
