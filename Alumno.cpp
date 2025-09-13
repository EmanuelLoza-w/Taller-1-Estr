//
// Created by hansl on 06-09-2025.
//

#include "Alumno.hpp"                        // Incluimos la declaración de Alumno
#include "Curso.hpp"                         // Para usar Curso*


Alumno::Alumno(const std::string& _id, const std::string& nom,const std::string& ape, const std::string& carr, int ingreso): id(_id), nombre(nom), apellido(ape), carrera(carr),
  fechaIngreso(ingreso), inscripciones(nullptr) {}


Alumno::~Alumno() {
    inscripcionNodo* i = inscripciones;
    while (i) {
        NotaNode* n = i->notasHead;
        while (n) {
            NotaNode* tmpn = n->next;
            delete n;
            n = tmpn;
        }
        inscripcionNodo* tmpi = i->next;
        delete i;
        i = tmpi;
    }
}


void Alumno::imprimirBasico() const {
    std::cout << "ID: " << id << " , Nombre: " << nombre << " " << apellido<< " , Carrera: " << carrera<< " , Ingreso: " << fechaIngreso << "\n";
}

/
inscripcionNodo* Alumno::buscarInscripcionPorCurso(Curso* curso) {
    inscripcionNodo* p = inscripciones;
    while (p) {
        if (p->curso == curso) return p;
        p = p->next;
    }
    return nullptr;
}