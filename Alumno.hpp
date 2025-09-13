//
// Created by hansl on 06-09-2025.
//
#pragma once
#include <string>
#include <iostream>
#include "LinkedList.hpp"

class Curso;

// inscripcion de un curso en un alumno xd
struct Inscripcion {
    Curso* curso;                 // Curso inscrito (no es dueño)
    LinkedList<float> notas;      // Notas del alumno en ese curso
    explicit Inscripcion(Curso* c) : curso(c), notas() {}
};


class Alumno {                              // clase alumno, eso lo dice todo :)
public:
    std::string id;
    std::string nombre;
    std::string apellido;
    std::string carrera;
    int fechaIngreso;

    LinkedList<Inscripcion*> inscripciones;

    // Constructor
    Alumno(const std::string& _id, const std::string& nom,const std::string& ape, const std::string& carr, int ingreso);

    // destructor
    ~Alumno();

    // muestra alumno
    void imprimirBasico() const;

    // Funciones para manejar inscripciones y notas
    Inscripcion* buscarInscripcionPorCurso(Curso* curso); // Busca inscripción
    bool agregarInscripcion(Curso* curso);                    // agrega inscripcion si no existe
    bool eliminarInscripcionPorCurso(Curso* curso);           // elimina inscripcion
    bool agregarNotaEnCurso(Curso* curso, float nota);        // agrega nota a un curso inscrito
    float promedioEnCurso(Curso* curso) const;                // promedio de notas en un curso
    float promedioGeneral() const;                            // promedio de los cursos

};
