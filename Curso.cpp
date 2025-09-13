//
// Created by hansl on 06-09-2025.
//

#include "Curso.hpp"
#include <iostream>
// Implementación del constructor del curso
Curso::Curso(const std::string& cod, const std::string& nom, int cupo,const std::string& carr, const std::string& prof)
: codigo(cod),nombre(nom),cupoMax(cupo),carrera(carr),profesor(prof),inscritos(0) {}

// Imprime todos los datos relevantes del curso
void Curso::imprimir() const {
    std::cout << "Codigo: " << codigo << " - Nombre: " << nombre << " - CupoMax: " << cupoMax << " - Carrera: " << carrera << " - Profesor: " << profesor  << " - Inscritos: " << inscritos << "\n";
}