//
// Created by hansl on 08-09-2025.
//
#pragma once
#include <cstddef>
#include "Nodo.hpp"
template <typename T>
class LinkedList {
private:
    Nodo<T>* cabeza;
    std::size_t cantidad;
public:
    LinkedList() : cabeza(nullptr), cantidad(0) {}
    ~LinkedList() { clear(); }
    bool empty() const { return cabeza == nullptr; }
    std::size_t size() const { return cantidad; }
    void push_front(const T& valor) {
        auto* n = new Nodo<T>(valor); n->siguiente = cabeza; cabeza = n; cantidad++;
    }
    void push_back(const T& valor) {
        if (!cabeza) { push_front(valor); return; }
        auto* p = cabeza; while (p->siguiente) p = p->siguiente;
        p->siguiente = new Nodo<T>(valor); cantidad++;
    }
    bool insert_at(std::size_t index, const T& valor) {
        if (index > cantidad) return false;
        if (index == 0) { push_front(valor); return true; }
        auto* p = cabeza; for (std::size_t i=0;i<index-1;++i) p = p->siguiente;
        auto* n = new Nodo<T>(valor); n->siguiente = p->siguiente; p->siguiente = n; cantidad++; 
       return true;
    }
    bool pop_front() {
        if (!cabeza) return false;
        auto* tmp = cabeza; cabeza = cabeza->siguiente; delete tmp; cantidad--; 
return true;
    }
    bool remove_at(std::size_t index) {
        if (index >= cantidad) return false;
        if (index == 0) return pop_front();
        auto* p = cabeza; for (std::size_t i=0;i<index-1;++i) p = p->siguiente;
        auto* tmp = p->siguiente; p->siguiente = tmp->siguiente; delete tmp; cantidad--; 
return true;
    }
    bool remove_value(const T& valor) {
        if (!cabeza) return false;
        if (cabeza->dato == valor) return pop_front();
        auto* p = cabeza; while (p->siguiente && !(p->siguiente->dato == valor)) p = p->siguiente;
        if (!p->siguiente) return false;
        auto* tmp = p->siguiente; p->siguiente = tmp->siguiente; delete tmp; cantidad--; return true;
    }
    bool get(std::size_t index, T& out) const {
        if (index >= cantidad) return false;
        auto* p = cabeza; for (std::size_t i=0;i<index;++i) p = p->siguiente;
        out = p->dato; return true;
    }
    T* get_ptr(std::size_t index) {
        if (index >= cantidad) return nullptr;
        auto* p = cabeza; for (std::size_t i=0;i<index;++i) p = p->siguiente;
        return &(p->dato);
    }
    int index_of(const T& valor) const {
        std::size_t i=0; for (auto* p=cabeza; p; p=p->siguiente) { if (p->dato == valor) return (int)i; ++i; }
        return -1;
    }
    void clear() {
        while (cabeza) { auto* tmp=cabeza; cabeza=cabeza->siguiente; delete tmp; }
        cantidad=0;
    }
    Nodo<T>* head() const { return cabeza; }
};
