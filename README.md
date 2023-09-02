
# Tarea 1 Estructura de Datos

**Descripción**

La aplicación es una gestión de biblioteca.
Se permite registrar libros, mostrarlos, retirarlos, devolverlos, mostrar los libros prestados e importar y exportar en un archivo CSV los datos de los libros.   
Cada libro posee una cola de reserva en la que se guardan estudiantes que quieran retirar el libro que deseen.

## Compilar y ejecutar código
---
### Desde sistema
* Entre a `cmd` en su sistema
* Clone el repositorio con `git clone https://github.com/LyingBeagle/Tarea-1.git`
  > Si no tiene git puede descargarlo [aquí](https://git-scm.com/downloads)
* Navegue al directorio con `cd Tarea-1`
* Compile el código con `gcc *.c -o main`
  > Si no tiene compilador puede descargalo [aquí](https://www.mingw-w64.org/downloads/)
* Ejecute la aplicación con `./main`
### Desde Replit
* Abra su cuenta en repl.it (si no tiene cree una a través de su cuenta en github)
* En el home de repl.it busque la tarea y clónela para comenzar a trabajar
  > En caso de no encontrarla inserte `https://github.com/LyingBeagle/Tarea-1.git` donde le pide la URL 
* Seleccione el lenguaje (C)
* Una vez importado, escriba `gcc *.c -o main` para configurar la compilación
* Una vez guardado, presione el botón **Run** para probar el programa
---
## Funciones

### Principales

**Funcionando correctamente**

* Agregar libro a la lista
* Mostrar datos completos de un libro, incluyendo sus reservas si es que la tienen
* Mostrar título y autor de todos los libros de la lista
* Reserva de un libro
* cancelación de reserva de un libro
* Retiro de un libro
* Devolución de un libro
* Mostrar libros prestados
* Importación de libros mediante archivo CSV
* Exportación de los libros que están registrados en la listas hacia un archivo CSV

### Secundarias

**Funcionando correctamente**

* Muestra de un menú con opciones
* El proceso que se realiza al elegir una opción
* Pedida de datos cuando se busca un libro especifico
* Muestra de las reservas que tiene un libro
* La búsqueda de una reserva especifica con indicaciones de usuario
* Liberación de memoria de las reservas de cada libro

## Contribuciones

### Alonso B:
* Desarrollo completo de la aplicación
* Diseño de la interfaz
* Documentación y redacción de README

