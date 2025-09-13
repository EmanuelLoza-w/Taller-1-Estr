//
// Created by hansl on 10-09-2025.
//
#pragma once


// pa usar todo tipo de datos
//
template <typename T>
class Nodo {
public:
    T dato;
    Nodo<T>* siguiente;
    Nodo() : dato(), siguiente(nullptr) {}
    explicit Nodo(const T& valor) : dato(valor), siguiente(nullptr) {}
};
