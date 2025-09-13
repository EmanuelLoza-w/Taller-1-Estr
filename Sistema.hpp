//
// Created by hansl on 10-09-2025.
//

#pragma once
#include <string>
#include "Alumno.hpp"
#include "Curso.hpp"
#include "Util.hpp"
#include "LinkedList.hpp"

class Sistema {                             // Clase principal del sistema
private:
    LinkedList<Alumno*> alumnos;
    LinkedList<Curso*> cursos;                 // Cabeza de la lista enlazada de cursos


    Alumno* buscarAlumnoPorIdPtr(const std::string& id);
    Curso*  buscarCursoPorCodigoPtr(const std::string& codigo);

    // Menús internos (cada uno con switch-case)
    void menuAlumnos();
    void menuCursos();
    void menuInscripciones();
    void menuNotas();
    void menuReportes();

public:                                     // Interfaz pública
    Sistema();                               // Constructor (inicia listas vacías)
    ~Sistema();                              // Destructor (libera memoria)

    void menuPrincipal();                    // Muestra el menú principal

    // Operaciones de alumnos
    bool crearAlumno(const std::string& id, const std::string& nombre,
                     const std::string& apellido, const std::string& carrera,
                     int fechaIngreso);
    void buscarAlumnoPorId(const std::string& id) const;
    void buscarAlumnoPorNombre(const std::string& nombre) const;
    bool eliminarAlumnoPorId(const std::string& id);

    // Operaciones de cursos
    bool crearCurso(const std::string& codigo, const std::string& nombre,
                    int cupoMax, const std::string& carrera,
                    const std::string& profesor);
    void buscarCursoPorCodigo(const std::string& codigo) const;
    void buscarCursoPorNombre(const std::string& nombre) const;
    bool eliminarCursoPorCodigo(const std::string& codigo);

    // Inscripciones y notas
    bool inscribirAlumnoEnCurso(const std::string& idAlumno, const std::string& codCurso);
    bool eliminarInscripcion(const std::string& idAlumno, const std::string& codCurso);
    bool registrarNota(const std::string& idAlumno, const std::string& codCurso, float nota);

    // Reportes
    void listarAlumnosPorCarrera(const std::string& carrera) const;
    void listarCursosDeAlumno(const std::string& idAlumno) const;
    void promedioAlumnoEnCurso(const std::string& idAlumno, const std::string& codCurso) const;
    void promedioGeneralAlumno(const std::string& idAlumno) const;

    void listarTodosAlumnos() const;
    void listarTodosCursos() const;
};