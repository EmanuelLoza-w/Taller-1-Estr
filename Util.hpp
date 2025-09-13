//
// Created by hansl on 10-09-2025.
//

#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

// exceopcio para nota
struct NotaFueraDeRango : public std::runtime_error {
    NotaFueraDeRango() : std::runtime_error("La nota debe estar entre 1.0 y 7.0") {}
};

// Función para leer una línea de texto desde consola
static std::string leerLinea(const std::string& msg) { // 'inline' sugiere al compilador expandir aquí
    std::cout << msg;                                   // Muestra el mensaje al usuario
    std::string s;                                      // Variable para almacenar lo ingresado
    std::getline(std::cin, s);                          // Lee toda la línea (permite espacios)
    return s;                                           // Retorna el texto ingresado
}

// lee un entero desde una línea y lanza una excepcion si no es numero
static int leerEnteroThrow(const std::string& msg) {    // funcion que devuelve un int
    std::string s = leerLinea(msg);
    try {
        size_t idx = 0;                                 // indice para verificar conversión completa
        int valor = std::stoi(s, &idx);                   // Convierte string a int
        if (idx != s.size())
            throw std::invalid_argument("error caracteres extras"); // lanza error
        return valor;                                     // devuelve el entero leído
    } catch (...) {
        throw std::invalid_argument("Entrada no es un entero válido");
    }
}
// lee un float desde una linea y lanza excepcion si ingresa un valor invalido
static float leerFloatThrow(const std::string& msg) {   // Función que devuelve un float
    std::string s = leerLinea(msg);
    try {                                               // Intentamos convertir a float
        size_t idx = 0;
        float valor = std::stof(s, &idx);                 // convierte string a float
        if (idx != s.size())
            throw std::invalid_argument("error caracteres extras"); // tira error
        return valor;                                     // devuelve el nimero leido
    } catch (...) {
        throw std::invalid_argument("Entrada no es un número válido"); // mensaje de excepcion
    }
}
static float leerFloatEnRango(const std::string& msg, float min, float max) {
    float v = leerFloatThrow(msg);
    if (v < min || v > max) throw NotaFueraDeRango();
    return v;
}