#include <iostream>

using namespace std;

struct grupoMusical{
    //lista simple
    int edad;
    string nombre;
    string anioDeFundacion;


    grupoMusical*sig;

    grupoMusical(string n, string a){
        nombre = n;
        anioDeFundacion = a;
        sig = NULL;
    }
};

struct horarioDisponible{
    //sublista simple
    string dia;
    string horaDeInicio;
    string horaFinal;
    horarioDisponible* sig;

    horarioDisponible(string d, string horaI, string horaF){
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
    horarioDisponible* horario;

    persona*sig;
    persona*ant;

    persona(string n, string c, int e, horarioDisponible*h){
        nombre = n;
        cedula = c;
        edad = e;
        sig = NULL;
        ant = NULL;
        horario = h;
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
crearHorario();
void insertarOrdenado(persona *&p, string nombre, string cedula, int edad) {
    horarioDisponible*horario = crearHorario();
    persona *nuevo = new persona(nombre, cedula, edad, horario);

    if (p == NULL) {  // Si la lista est� vac�a, el nuevo nodo ser� el primer elemento
        p = nuevo;
        return;
    }

    if (cedula < p->cedula) {  // Si la c�dula del nuevo nodo es menor que la del primer elemento
        nuevo->sig = p;
        p->ant = nuevo;
        p = nuevo;
        return;
    }

    persona *actual = p;

    while (actual->sig != NULL && actual->sig->cedula < cedula) {  // Buscamos la posici�n donde insertar el nuevo nodo
        actual = actual->sig;
    }

    nuevo->sig = actual->sig;
    if (actual->sig != NULL) {
        actual->sig->ant = nuevo;
    }
    actual->sig = nuevo;
    nuevo->ant = actual;
}

void imprimirLista(persona *p) {
    while (p != NULL) {
        cout << "Nombre: " << p->nombre << endl;
        cout << "C�dula: " << p->cedula << endl;
        cout << "Edad: " << p->edad << endl;
        cout << "Horario disponible: " << endl;

        cout << endl;
        p = p->sig;
    }
}


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

struct eventos{
    //lista simple
    string nombre;
    string lugar;
    string hora;
    string dia;
    int duracion;
    eventos*sig;

    eventos(string n, string l, string h, string d, int dur){
        nombre = n;
        lugar = l;
        hora = h;
        dia = d;
        duracion = dur;
        sig = NULL;
    }
};

struct historiaEventos{
    //lista doble y circular
    eventos * evento;
    int calificacion;
    grupoMusical * grupo;

    historiaEventos*sig;
    historiaEventos*ant;

    historiaEventos(eventos * e , int c, grupoMusical*g){
        evento = e;
        calificacion = c;
        grupo = g;
    }

};

struct subListaIntegrantes{
    persona * integrante;
    subListaIntegrantes*sig;

    subListaIntegrantes(persona* i){
        integrante = i;
        sig = NULL;
    }
};

struct subListaHorarios{
    horarioDisponible*horario;
    subListaHorarios*sig;

    subListaHorarios(horarioDisponible*h){
        horario = h;
        sig = NULL;
    }

};

subListaHorarios* crearHorario() {
    int dias;
    cout<<"cuantos dia de la semana trabaja en el horario?\n";
}


int main()
{
    insertarOrdenado(primeraPersona,"Josue","208260603",21)
}
