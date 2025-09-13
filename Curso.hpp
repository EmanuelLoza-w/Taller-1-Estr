//
// Created by hansl on 06-09-2025.
//

#pragma once
#include <string>
#include <iostream>

class Curso {
public:
    std::string idc;
    std::string nombre;
    int         cupoMax;
    std::string carrera;
    std::string profesor;
    int         inscritos;


    Curso(const std::string& idc, const std::string& nom, int cupo,
          const std::string& carr, const std::string& prof);


    void imprimir() const;
};