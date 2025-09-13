//
// Created by hansl on 06-09-2025.
//
#include "Alumno.hpp"
#include <iostream>


Alumno::Alumno(const std::string& _id, const std::string& nom,
               const std::string& ape, const std::string& carr, int ingreso)
    : id(_id), nombre(nom), apellido(ape), carrera(carr),
      fechaIngreso(ingreso), inscripciones() {}   // ¡OJO! nada de nullptr

Alumno::~Alumno() {
    // Liberamos cada Inscripcion* (su LinkedList<float> interno se limpia solo)
    for (auto* p = inscripciones.head(); p; p = p->siguiente) {
        delete p->dato;
    }
    inscripciones.clear();   // borra los nodos
}

//  impresion
void Alumno::imprimirBasico() const {
    std::cout   << "id: " << id << " - "
                << "nombre: " << nombre << " - "
                << "apellido: " << apellido<< " - "
                << "carrera: " << carrera << " -  ingreso " << fechaIngreso << "\n";
}



// inscripciones
Inscripcion* Alumno::buscarInscripcionPorCurso(Curso* curso) {
    for (auto* p = inscripciones.head(); p; p = p->siguiente) {
        if (p->dato && p->dato->curso == curso) return p->dato;
    }
    return nullptr;
}

bool Alumno::agregarInscripcion(Curso* curso) {
    if (!curso) return false;
    if (buscarInscripcionPorCurso(curso)) return false; // ya existe
    auto* nuevo = new Inscripcion(curso);
    inscripciones.push_front(nuevo);
    return true;
}

bool Alumno::eliminarInscripcionPorCurso(Curso* curso) {
    int idx = -1, i = 0;
    for (auto* p = inscripciones.head(); p; p = p->siguiente, ++i) {
        if (p->dato && p->dato->curso == curso) { idx = i; break; }
    }
    if (idx < 0) return false;
    Inscripcion* victima = nullptr;
    inscripciones.get(static_cast<std::size_t>(idx), victima);
    delete victima;
    return inscripciones.remove_at(static_cast<std::size_t>(idx));
}

bool Alumno::agregarNotaEnCurso(Curso* curso, float nota) {
    Inscripcion* ins = buscarInscripcionPorCurso(curso);
    if (!ins) return false;
    ins->notas.push_back(nota);
    return true;
}

float Alumno::promedioEnCurso(Curso* curso) const {
    Alumno* self = const_cast<Alumno*>(this);
    Inscripcion* ins = self->buscarInscripcionPorCurso(curso);
    if (!ins) return 0.0f;

    float suma = 0.0f; int n = 0;
    for (auto* p = ins->notas.head(); p; p = p->siguiente) {
        suma += p->dato; ++n;
    }
    return (n > 0) ? (suma / n) : 0.0f;
}

float Alumno::promedioGeneral() const {
    float suma = 0.0f; int n = 0;
    for (auto* i = inscripciones.head(); i; i = i->siguiente) {
        if (!i->dato) continue;
        for (auto* p = i->dato->notas.head(); p; p = p->siguiente) {
            suma += p->dato; ++n;
        }
    }
    return (n > 0) ? (suma / n) : 0.0f;
}
