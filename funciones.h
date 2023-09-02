#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "list.h"

typedef struct Libro Libro;

/*
    Se muestra el menu y sus opciones.
*/

void menu();

/*
    Todo el proceso que se toma con la opcion elegida en el menu.
*/

void proceso(List*,int);

/*
    Se ingresa los datos un libro y se almacena en la lista.
*/

void registrarLibro(List*);

/*
    Se muestran los datos de un libro
*/

void mostrarDatosLibro(List*);

/*
    Se muestra titulo y autor de todos los libros de la lista
*/

void mostrarTodosLibros(List*);

/*
    Se crea la lista de reserva, se añade un alumno a ella y se cambia estado del libro
*/

void reservarLibro(List*);

/*
    Se borra a un estudiante de la lista de reserva de un libro
*/

void cancelarReserva(List*);

/*
    Se cambia el estado del libro y se borra al primero de la lista de reserva
*/

void retirarLibro(List*);

/*
    Se cambia el estado del libro a disponible o reservado si hay 1 o mas estudiantes en lista de reserva
*/

void devolverLibro(List*);

/*
    Se muestra todos los libros con estado Prestado y a quien se les presto
*/

void mostrarLibrosPrestados(List*);

/*
    Se importa un CSV y se añade a la lista de libros de la biblioteca
*/

void importarLibrosCSV(List*);

/*
    Se exportan todos los libros de la lista a un CSV
*/

void exportarLibrosCSV(List*);

/*
    Se pide titulo y autor del libro que se solicita, retorna un puntero su nodo
*/

void* pedidaDeDatos(List*);

/*
    Con los datos pedidos se busca el libro en la lista, se retorna su nodo
*/

void* encontrarLibro(List*, const char*, const char*);

/*
    Se muestra a los estudiantes en la lista de reservas
*/

void mostrarReservas(List*);

/*
    Revisa la cola de reserva y compara si el nombre esta en ella, si la encuentra retornar su nodo
*/

void* encontrarReserva(List*, char*);

/*
    Se libera la memoria de la lista de reserva de cada libro
*/

void liberarReservas(List*);


#endif