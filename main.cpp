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

persona* buscarPorCedula(persona* p, string cedula) {
    while (p != NULL) {
        if (p->cedula == cedula) {
            return p;
        }
        p = p->sig;
    }
    return NULL;
}


void imprimirLista(persona *p) {
    while (p != NULL) {
        cout << "Nombre: " << p->nombre << endl;
        cout << "Cedula: " << p->cedula << endl;
        cout << "Edad: " << p->edad << endl;
        cout << "Horario disponible: " << endl;
        horarioDisponible * horario = p->horarios;
        imprimirHorarioDisponible(horario);
        cout << endl;
        p = p->sig;
    }
}

struct subListaIntegrantes{
    persona * integrante;
    subListaIntegrantes*sig;

    subListaIntegrantes(persona* i){
        integrante = i;
        sig = NULL;
    }
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
    }
}*primerGrupoMusical;

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
void insercionAlInicioGrupoMusical() {
    string nombre ;
    string anioDeFundacion;
    cout << "Ingrese el nombre"<<endl;
    cin >> nombre;
    cout << "ingrese el anio de fundacion"<<endl;
    cin >> anioDeFundacion;
    grupoMusical* nuevoGrupo = new grupoMusical(nombre, anioDeFundacion);
    nuevoGrupo-> sig = primerGrupoMusical;
    primerGrupoMusical = nuevoGrupo;
}
//--------------------Insercion lista doble ordenada por cedula Persona------------
void insertarOrdenado(persona *&p, string nombre, string cedula, int edad) {
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
    persona * per = buscarPorCedula(primeraPersona,cedula);
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
int main()
{
    insertarOrdenado(primeraPersona,"Josue","208260603",21);
    insertarOrdenado(primeraPersona,"Carlos","209212333",20);
    agregarHorarioaPersona();
    imprimirLista(primeraPersona);
}
