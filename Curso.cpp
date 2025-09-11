//
// Created by hansl on 06-09-2025.
//

#include "Curso.hpp"

Curso::Curso(const std::string& cod, const std::string& nom, int cupo,const std::string& carr, const std::string& prof)
: idc(cod),
    nombre(nom),
    cupoMax(cupo),
carrera(carr),// inicializacion
profesor(prof),
inscritos(0) {} // profe y contador

// Imprime todos los datos relevantes del curso
void Curso::imprimir() const {
    std::cout << "Codigo: " << idc
              << "Nombre: " << nombre
              << "CupoMax: " << cupoMax
              << "Carrera: " << carrera
              << "Profesor: " << profesor
              << "Inscritos: " << inscritos << "\n";
}