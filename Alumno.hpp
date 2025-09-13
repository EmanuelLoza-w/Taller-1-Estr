//
// Created by hansl on 06-09-2025.
//
#pragma once
#include <string>
#include <iostream>

class Curso;

struct NotaNode {
    float valor;
    NotaNode* next;
    explicit NotaNode(float v) : valor(v), next(nullptr) {}
};


struct inscripcionNodo {
    Curso* curso;
    NotaNode* notasHead;
    inscripcionNodo* next;
    explicit inscripcionNodo(Curso* c) : curso(c), notasHead(nullptr), next(nullptr) {}
};

class Alumno {
public:
    std::string id;
    std::string nombre;
    std::string apellido;
    std::string carrera;
    int         fechaIngreso;
    inscripcionNodo* inscripciones;


    Alumno(const std::string& _id, const std::string& nom,
           const std::string& ape, const std::string& carr, int ingreso);


    ~Alumno();


    void imprimirBasico() const;


    inscripcionNodo* buscarInscripcionPorCurso(Curso* curso);
    bool agregarInscripcion(Curso* curso);
    bool eliminarInscripcionPorCurso(Curso* curso);
    bool agregarNotaEnCurso(Curso* curso, float nota);
    float promedioEnCurso(Curso* curso) const;
    float promedioGeneral() const;
};
