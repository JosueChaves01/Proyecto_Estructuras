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


int main()
{
    cout << "Hello world!" << endl;
    return 0;
}

std::cout <<"Prueba";
