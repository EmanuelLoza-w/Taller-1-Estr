//
// Created by hansl on 06-09-2025.
//

#pragma once

#include <string>
#include <iostream>

class Curso {  // Definicion de la clase Curso
public:
    std::string codigo;
    std::string nombre;
    int cupoMax;
    std::string carrera;
    std::string profesor;
    int inscritos;

    // Constructor
    Curso(const std::string& cod, const std::string& nom, int cupo,
          const std::string& carr, const std::string& prof);

    void imprimir() const;                 // Metodo constante solo imprimi no modifica nada
};