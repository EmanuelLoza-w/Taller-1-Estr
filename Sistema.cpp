//
// Created by hansl on 10-09-2025.
//
#include "Sistema.hpp"
#include <iostream>
#include <limits>
#include <string>
#include "LinkedList.hpp"
#include "Util.hpp"

using std::cout;
using std::cin;
using std::string;

Sistema::Sistema() : alumnos(), cursos() {}

Sistema::~Sistema() {
    // alumnos
    for (auto* p = alumnos.head(); p; p = p->siguiente) delete p->dato;
    alumnos.clear();
    // cursos
    for (auto* p = cursos.head(); p; p = p->siguiente) delete p->dato;
    cursos.clear();
}
// busquedas con punteros
Alumno* Sistema::buscarAlumnoPorIdPtr(const string& id) {
    for (auto* p = alumnos.head(); p; p = p->siguiente) {
        if (p->dato && p->dato->id == id) return p->dato;
    }
    return nullptr;
}
Curso* Sistema::buscarCursoPorCodigoPtr(const string& codigo) {
    for (auto* p = cursos.head(); p; p = p->siguiente) {
        if (p->dato && p->dato->codigo == codigo) return p->dato;
    }
    return nullptr;
}

bool Sistema::crearAlumno(const string& id, const string& nombre,
                          const string& apellido, const string& carrera,
                          int fechaIngreso) {
    if (buscarAlumnoPorIdPtr(id)) return false;
    auto* a = new Alumno(id, nombre, apellido, carrera, fechaIngreso);
    alumnos.push_front(a);
    return true;
}

void Sistema::buscarAlumnoPorId(const string& id) const {
    for (auto* p = alumnos.head(); p; p = p->siguiente) {
        if (p->dato && p->dato->id == id) { p->dato->imprimirBasico(); return; }
    }
    cout << "Alumno no encontrado.\n";
}

void Sistema::buscarAlumnoPorNombre(const string& nombre) const {
    bool hallado = false;
    for (auto* p = alumnos.head(); p; p = p->siguiente) {
        if (p->dato && p->dato->nombre == nombre) {
            p->dato->imprimirBasico();
            hallado = true;
        }
    }
    if (!hallado) cout << "No se encontraron alumnos con ese nombre.\n";
}

bool Sistema::eliminarAlumnoPorId(const string& id) {
    int idx = -1, i = 0;
    for (auto* p = alumnos.head(); p; p = p->siguiente, ++i) {
        if (p->dato && p->dato->id == id) { idx = i; break; }
    }
    if (idx < 0) return false;
    Alumno* victima = nullptr;
    alumnos.get(static_cast<std::size_t>(idx), victima);
    delete victima;
    return alumnos.remove_at(static_cast<std::size_t>(idx));
}

void Sistema::listarTodosAlumnos() const {
    cout << "== Alumnos ==\n";
    if (alumnos.empty()) { cout << "(vacio)\n"; return; }
    for (auto* p = alumnos.head(); p; p = p->siguiente) {
        if (p->dato) p->dato->imprimirBasico();
    }
}


bool Sistema::crearCurso(const string& codigo, const string& nombre,
                         int cupoMax, const string& carrera,
                         const string& profesor) {
    if (buscarCursoPorCodigoPtr(codigo)) return false;
    auto* c = new Curso(codigo, nombre, cupoMax, carrera, profesor);
    cursos.push_front(c);
    return true;
}

void Sistema::buscarCursoPorCodigo(const string& codigo) const {
    for (auto* p = cursos.head(); p; p = p->siguiente) {
        if (p->dato && p->dato->codigo == codigo) { p->dato->imprimir(); return; }
    }
    cout << "Curso no encontrado.\n";
}

void Sistema::buscarCursoPorNombre(const string& nombre) const {
    bool hallado = false;
    for (auto* p = cursos.head(); p; p = p->siguiente) {
        if (p->dato && p->dato->nombre == nombre) { p->dato->imprimir(); hallado = true; }
    }
    if (!hallado) cout << "No se encontraron cursos con ese nombre.\n";
}

bool Sistema::eliminarCursoPorCodigo(const string& codigo) {
    int idx = -1, i = 0;
    for (auto* p = cursos.head(); p; p = p->siguiente, ++i) {
        if (p->dato && p->dato->codigo == codigo) { idx = i; break; }
    }
    if (idx < 0) return false;

    Curso* victima = nullptr;
    cursos.get(static_cast<std::size_t>(idx), victima);

    // sacar el curso de todos los alumnos antes de borrarlo
    for (auto* a = alumnos.head(); a; a = a->siguiente) {
        if (a->dato) a->dato->eliminarInscripcionPorCurso(victima);
    }
    delete victima;
    return cursos.remove_at(static_cast<std::size_t>(idx));
}

void Sistema::listarTodosCursos() const {
    cout << "== Cursos ==\n";
    if (cursos.empty()) { cout << "(vacio)\n"; return; }
    for (auto* p = cursos.head(); p; p = p->siguiente) {
        if (p->dato) p->dato->imprimir();
    }
}

bool Sistema::inscribirAlumnoEnCurso(const std::string& idAlumno, const std::string& codCurso) {
    Alumno* a = buscarAlumnoPorIdPtr(idAlumno);
    Curso*  c = buscarCursoPorCodigoPtr(codCurso);
    if (!a || !c) return false;

    if (a->buscarInscripcionPorCurso(c)) return false;

    // erificar cupo disponible
    int inscritos = 0;
    for (auto* it = alumnos.head(); it; it = it->siguiente) {
        if (it->dato && it->dato->buscarInscripcionPorCurso(c)) {
            ++inscritos;
        }
    }

    const int cupoMax = c->cupoMax;
    if (inscritos >= cupoMax) {
        return false;
    }

    return a->agregarInscripcion(c);
}


bool Sistema::eliminarInscripcion(const string& idAlumno, const string& codCurso) {
    Alumno* a = buscarAlumnoPorIdPtr(idAlumno);
    Curso*  c = buscarCursoPorCodigoPtr(codCurso);
    if (!a || !c) return false;
    return a->eliminarInscripcionPorCurso(c);
}

bool Sistema::registrarNota(const string& idAlumno, const string& codCurso, float nota) {
    Alumno* a = buscarAlumnoPorIdPtr(idAlumno);
    Curso*  c = buscarCursoPorCodigoPtr(codCurso);
    if (!a || !c) return false;
    return a->agregarNotaEnCurso(c, nota);
}

//reportes
void Sistema::listarAlumnosPorCarrera(const string& carrera) const {
    bool hallado = false;
    for (auto* a = alumnos.head();a; a = a->siguiente) {
        if (a->dato && a->dato->carrera == carrera) { a->dato->imprimirBasico(); hallado = true; }
    }
    if (!hallado) cout << "No hay alumnos en esa carrera.\n";
}

void Sistema::listarCursosDeAlumno(const string& idAlumno) const {
    Alumno* a = const_cast<Sistema*>(this)->buscarAlumnoPorIdPtr(idAlumno);
    if (!a) { cout << "Alumno no encontrado.\n"; return; }

    cout << "Cursos de " << a->nombre << " (" << a->id << "):\n";
    bool alguno = false;
    // sin acceder a miembros internos de Alumno: recorro cursos y pregunto si está inscripto
    for (auto* c = cursos.head(); c; c = c->siguiente) {
        if (c->dato && a->buscarInscripcionPorCurso(c->dato)) {
            c->dato->imprimir();
            alguno = true;
        }
    }
    if (!alguno) cout << "  (sin inscripciones)\n";
}

void Sistema::promedioAlumnoEnCurso(const string& idAlumno, const string& codCurso) const {
    Alumno* a = const_cast<Sistema*>(this)->buscarAlumnoPorIdPtr(idAlumno);
    Curso*  c = const_cast<Sistema*>(this)->buscarCursoPorCodigoPtr(codCurso);
    if (!a || !c) { cout << "Alumno o curso no encontrado.\n"; return; }
    float prom = a->promedioEnCurso(c);
    cout << "Promedio: " << prom << "\n";
}

void Sistema::promedioGeneralAlumno(const string& idAlumno) const {
    Alumno* a = const_cast<Sistema*>(this)->buscarAlumnoPorIdPtr(idAlumno);
    if (!a) { cout << "Alumno no encontrado.\n"; return; }
    float prom = a->promedioGeneral();
    cout << "Promedio general: " << prom << "\n";
}


namespace {
    string pedirLinea(const string& prompt) {
        cout << prompt; string s; std::getline(cin, s); return s;
    }
    int    pedirEntero(const string& prompt) {
        for (;;) { string s = pedirLinea(prompt);
            try {
                return std::stoi(s);
            } catch (...) {
                cout << "Numero invalido\n";
            } }
    }

}

static float pedirNotaEnRango(const std::string& prompt, float min, float max) {
    for (;;) {
        try {
            return leerFloatEnRango(prompt, min, max);
        } catch (const NotaFueraDeRango& e) {
            cout << e.what() << "\n";
        } catch (const std::invalid_argument&) {
            cout << " Numero invalido\n";
        }
    }
}


void Sistema::menuPrincipal() {
    for (;;) {
        cout << "\n=== MENU PRINCIPAL ===\n"
                "1) Menu Alumnos\n"
                "2) Menu Cursos\n"
                "3) Menu Inscripciones\n"
                "4) Menu Notas\n"
                "5) Menu Reportes\n"
                "0) Salir\n> ";
        string s; std::getline(cin, s);
        int op = 0; try { op = std::stoi(s);} catch (...) { op = -1; }

        if (op == 0) break;
        else if (op == 1) menuAlumnos();
        else if (op == 2) menuCursos();
        else if (op == 3) menuInscripciones();
        else if (op == 4) menuNotas();
        else if (op == 5) menuReportes();
        else cout << "Opcion invalida\n";
    }
}


    void Sistema::menuAlumnos() {
        for (;;) {
            cout << "\nALUMNOS: \n"
                    "1) Crear alumno\n"
                    "2) Listar todos\n"
                    "3) Buscar por ID\n"
                    "4) Buscar por nombre\n"
                    "5) Eliminar por ID\n"
                    "6) Listar por carrera\n"
                    "7) Listar cursos de un alumno\n"
                    "0) Volver\n> ";
            string s; std::getline(cin, s); int op = 0; try { op = std::stoi(s);} catch (...) { op = -1; }
            if (op == 0) break;
            else if (op == 1) {
                string id   = pedirLinea("ID: ");
                string nombre  = pedirLinea("Nombre: ");
                string apellido  = pedirLinea("Apellido: ");
                string carrera = pedirLinea("Carrera (ejemplo: icci, iti, ici): ");
                int ingreso = pedirEntero("Ano de ingreso: "); //aqui dirá anio :(
                bool ok = crearAlumno(id, nombre, apellido, carrera, ingreso);
                cout << (ok ? " Alumno creado\n" : " ID duplicado\n");

            } else if (op == 2) { listarTodosAlumnos();  }
            else if (op == 3) {
                string id = pedirLinea("ID: "); buscarAlumnoPorId(id);
            }
            else if (op == 4) {
                string nom = pedirLinea("Nombre: "); buscarAlumnoPorNombre(nom);
            }
            else if (op == 5) {
                string id = pedirLinea("ID a eliminar: ");
                bool ok = eliminarAlumnoPorId(id); cout << (ok ? " Eliminado\n" : " No encontrado\n");
            }
            else if (op == 6) {
                string carr = pedirLinea("Carrera: "); listarAlumnosPorCarrera(carr);
            }
            else if (op == 7) {
                string id = pedirLinea("ID del alumno: "); listarCursosDeAlumno(id);
            }
            else cout << " Opcion invalida\n";
        }
    }

void Sistema::menuCursos() {
    for (;;) {
        cout << "\nCURSOS:\n"
                "1) Crear curso\n"
                "2) Listar todos\n"
                "3) Buscar por codigo\n"
                "4) Buscar por nombre\n"
                "5) Eliminar por codigo\n"
                "0) Volver\n> ";
        string s;std::getline(cin, s);
        int op = 0;
        try {
            op = std::stoi(s);
        } catch (...) { op = -1; }
        if (op == 0) break;
        else if (op == 1) {
            string cod  = pedirLinea("Codigo: ");
            string nom  = pedirLinea("Nombre: ");
            int    cupo = pedirEntero("Cupo maximo: ");
            string carr = pedirLinea("Carrera: ");
            string prof = pedirLinea("Profesor: ");
            bool ok = crearCurso(cod, nom, cupo, carr, prof);
            cout << (ok ? "Curso creado\n" : "Codigo duplicado\n");

        } else if (op == 2) {
            listarTodosCursos();
        }else if (op == 3) {
            string cod = pedirLinea("Codigo: "); buscarCursoPorCodigo(cod);
        }else if (op == 4) {
            string nom = pedirLinea("Nombre: "); buscarCursoPorNombre(nom);
        }else if (op == 5) {
            string cod = pedirLinea("Codigo a eliminar: ");
            bool ok = eliminarCursoPorCodigo(cod); cout << (ok ? "Eliminado\n" : "No encontrado\n");
        }
        else cout << "Opcion invalida\n";
    }
}

void Sistema::menuInscripciones() {
    for (;;) {
        cout << "\nINSCRIPCIONES:\n"
                "1) Inscribir alumno en curso\n"
                "2) Eliminar inscripcion de un alumno en un curso\n"
                "0) Volver\n> ";
        string s; std::getline(cin, s);
        int op = 0;
        try {
            op = std::stoi(s);
        } catch (...) {
            op = -1;
        }

        if (op == 0) break;

        if (op == 1) {
            string id  = pedirLinea("ID del alumno: ");
            string cod = pedirLinea("Codigo del curso: ");
            bool ok = inscribirAlumnoEnCurso(id, cod);
            cout << (ok ? "Inscrito\n" : "Alumno/curso inexistente o ya inscripto\n");

        } else if (op == 2) {
            string id  = pedirLinea("ID del alumno: ");
            string cod = pedirLinea("Codigo del curso: ");
            bool ok = eliminarInscripcion(id, cod);
            cout << (ok ? "Inscripcion eliminada\n" : "No existe esa inscripcion\n");

        } else {
            cout << "Opcion invalida\n";
        }
    }
}

// --- menú de notas ---
void Sistema::menuNotas() {
    for (;;) {
        cout << "\nNOTAS:\n"
                "1) Agregar nota a alumno en curso\n"
                "2) Cargar varias notas (mismo alumno/curso)\n"
                "0) Volver\n> ";
        std::string s; std::getline(std::cin, s);
        int op = 0; try { op = std::stoi(s); } catch (...) { op = -1; }

        if (op == 0) break;

        if (op == 1) {
            std::string id  = pedirLinea("ID del alumno: ");
            std::string cod = pedirLinea("Codigo del curso: ");
            float n = pedirNotaEnRango("Nota [1.0 - 7.0]: ", 1.0f, 7.0f);
            bool ok = registrarNota(id, cod, n);
            cout << (ok ? "Nota agregada\n"
                        : "Alumno/curso inexistente o no inscripto\n");

        } else if (op == 2) {
            std::string id  = pedirLinea("ID del alumno: ");
            std::string cod = pedirLinea("Codigo del curso: ");
            int k = pedirEntero("Cantidad de notas a cargar: ");

            int okCount = 0, failCount = 0;
            for (int i = 1; i <= k; ++i) {
                float n = pedirNotaEnRango("Nota " + std::to_string(i) + " [1.0 - 7.0]: ",
                                           1.0f, 7.0f);
                if (registrarNota(id, cod, n)) ++okCount; else ++failCount;
            }
            cout << "Cargadas: " << okCount << ", Fallidas: " << failCount << "\n";

        } else {
            cout << "Opcion invalida\n";
        }
    }
}



void Sistema::menuReportes() {
    for (;;) {
        cout << "\nREPORTES:\n"
                "1) Informacion de un alumno\n"
                "2) Promedio del alumno en un curso\n"
                "3) Promedio general del alumno\n"
                "0) Volver\n> ";
        string s; std::getline(cin, s);
        int op = 0; try { op = std::stoi(s); } catch (...) { op = -1; }

        if (op == 0) break;

        if (op == 1) {
            string id = pedirLinea("ID del alumno: ");
            Alumno* a = buscarAlumnoPorIdPtr(id);
            if (!a) { cout << "Alumno no encontrado.\n";  continue; }

            cout << "== Cursos y notas de " << a->nombre << " (" << a->id << ") ==\n";
            bool alguno = false;
            for (auto* c = cursos.head(); c; c = c->siguiente) {
                if (!c->dato) continue;
                Inscripcion* ins = a->buscarInscripcionPorCurso(c->dato);
                if (!ins) continue;
                alguno = true;
                cout << "- " << c->dato->codigo << " - " << c->dato->nombre << "\n  Notas: ";
                // imprimir todas las notas
                if (ins->notas.empty()) {
                    cout << "(sin notas)";
                } else {
                    for (auto* n = ins->notas.head(); n; n = n->siguiente) {
                        cout << n->dato << (n->siguiente ? ' ' : '\0');
                    }
                }
                float prom = a->promedioEnCurso(c->dato);
                cout << "\n  Promedio: " << prom << "\n";
            }
            if (!alguno) cout << "  (sin inscripciones)\n";

        } else if (op == 2) {
            string id  = pedirLinea("ID del alumno: ");
            string cod = pedirLinea("Codigo del curso: ");
            promedioAlumnoEnCurso(id, cod);
        } else if (op == 3) {
            string id = pedirLinea("ID del alumno: ");
            promedioGeneralAlumno(id);
        } else {
            cout << "Opcion invalida\n";
        }
    }
}

