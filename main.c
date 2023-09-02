#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "funciones.h"

struct Libro{
    char titulo[51];                //Titulo del libro
    char autor[51];                 //Autor del libro
    char genero[51];                //Genero del libro
    int ISBN;                       //Identificador del libro
    char ubicacion[51];             //Ubicacion del libro en la biblioteca
    char estado[11];                //Disponible - Prestado - Reservado
    char nombreUltimoPrestado[21];  //Nombre de la persona que se le presto el libro
    List* reservas;                 //Lista de reservas que tiene el libro
};

int main(){

    menu();    //Menu con opciones

    return 0;
}

void menu(){

    int opcion;

    //Se crea la lista que se usara durante todo el programa
    List* listaLibros = createList();
  
    do{

        printf("\nBienvenido gestion de biblioteca\n");
        printf("---------------------------------\n");
        printf("\n1.Registrar libro");
        printf("\n2.Mostrar datos un libro");
        printf("\n3.Mostrar todos los libros");
        printf("\n4.Reservar un libro");
        printf("\n5.Cancelar reserva de un libro");
        printf("\n6.Retirar libro");
        printf("\n7.Devolver libro");
        printf("\n8.Mostrar libros prestados");
        printf("\n9.Importar libros desde un archivo CSV");
        printf("\n10.Exportar libros a un archivo CSV");
        printf("\n11.Salir\n");
        printf("\nOpcion: ");
        scanf(" %d", &opcion);

        //Se envia la opcion elegida a un switch
        proceso(listaLibros,opcion);

    }while(opcion != 11);
}

//Proceso para cada opcion del menu
void proceso(List* listaLibros,int opcion){
  
    printf("\n-----------------------\n");

    //Todo el proceso segun la opcion
    switch(opcion){
        case 1:
            registrarLibro(listaLibros);
            break;
        case 2:
            mostrarDatosLibro(listaLibros);
            break;
        case 3:
            mostrarTodosLibros(listaLibros);
            break;
        case 4:
            reservarLibro(listaLibros);
            break;
        case 5:
            cancelarReserva(listaLibros);
            break;
        case 6:
            retirarLibro(listaLibros);
            break;
        case 7:
            devolverLibro(listaLibros);
            break;
        case 8:
            mostrarLibrosPrestados(listaLibros);
            break;
        case 9:
            importarLibrosCSV(listaLibros);
            break;
        case 10:
            exportarLibrosCSV(listaLibros);
            break;
        case 11:
            printf("\nAdios\n");
            //Se libera la memoria de las reservas y lista
            liberarReservas(listaLibros);
            cleanList(listaLibros);
            free(listaLibros);
            break;
        default:
            printf("\nOpcion no valida\n");
            break;
    }
}

//Funcion opcion 1
void registrarLibro(List* listaLibros){

    //Se crea un libro que se añadira a la lista de la biblioteca
    Libro* libro = (Libro*)malloc(sizeof(Libro));
    if(libro == NULL){
        printf("\nError al reservar memoria para el libro\n");
        return;
    }

    //Se preguntan todos los datos del libro
    printf("\nIngrese el nombre del libro\n");
    scanf(" %50[^\n]", libro->titulo);

    printf("\nIngrese el autor del libro\n");
    scanf(" %50[^\n]", libro->autor);

    printf("\nIngrese el genero del libro\n");
    scanf(" %50[^\n]", libro->genero);

    printf("\nIngrese el ISBN del libro\n");
    scanf(" %d", &(libro->ISBN));

    printf("\nIngrese la ubicacion del libro\n");
    scanf(" %50[^\n]", libro->ubicacion);

    //Se inicializa el estado del libro
    strcpy(libro->estado,"Disponible");

    //Se crea la lista de reserva del libro
    libro->reservas = createList();

    //Se añade a la lista
    pushFront(listaLibros,libro);
}

//Funcion opcion 2
void mostrarDatosLibro(List* listaLibros){

    //Se convierte el nodo del libro a tipo Libro
    Libro* libroEncontrado = (Libro*)pedidaDeDatos(listaLibros);
    if(libroEncontrado == NULL) return; //Si no se encontro se termina la funcion

    //Se muestran los datos del libro
    printf("\nLibro encontrado:\n");
    printf("Título: %s\n", libroEncontrado->titulo);
    printf("Autor: %s\n", libroEncontrado->autor);
    printf("Genero: %s\n", libroEncontrado->genero);
    printf("ISBN: %d\n", libroEncontrado->ISBN);
    printf("Ubicacion: %s\n", libroEncontrado->ubicacion);
    printf("Estado: %s\n", libroEncontrado->estado);

    //Si exite no una lista de reservas se terimna la funcion
    if(firstList(libroEncontrado->reservas) == NULL) return;

    //Si existe se muestra
    printf("\nReservado por:\n");

    //Se muestra la lista de reserva del libro
    mostrarReservas(libroEncontrado->reservas);
}

//Funcion opcion 3
void mostrarTodosLibros(List* listaLibros){

    //Se empieza el proceso con el primer nodo
    void* current = firstList(listaLibros);

    //Si no hay libros se termina la funcion
    if(current == NULL){
        printf("\nNo hay libros registrados.\n");
        return;
    }
    //Ciclo para mostrar todos los libros
    while(current != NULL){
        Libro* libro = (Libro*)current;
        printf("\nTítulo: %s\n", libro->titulo);
        printf("Autor: %s\n", libro->autor);
        printf("\n");

        //Se accede al siguiente libro
        current = nextList(listaLibros);
    }
}

//Funcion opcion 4
void reservarLibro(List* listaLibros){

    //Se convierte el nodo del libro a tipo Libro
    Libro* libroEncontrado = (Libro*)pedidaDeDatos(listaLibros);
    if(libroEncontrado == NULL) return; //Si no se encontro se termina la funcion

    //Se pide el nombre del estudiante que quiere reservar el libro
    char nombreEstudiante[21];
  
    printf("\nIngrese el nombre del estudiante que reserva\n");
    scanf(" %20[^\n]", nombreEstudiante);

    //Se cambia el estado y se añade al estudiante a la lista de reservas del libro
    strcpy(libroEncontrado->estado,"Reservado");
    
    pushBack(libroEncontrado->reservas, strdup(nombreEstudiante)); //Se añade al final

    printf("\nLibro reservado\n");
}

//Funcion opcion 5
void cancelarReserva(List* listaLibros){

    //Se convierte el nodo del libro a tipo Libro
    Libro* libroEncontrado = (Libro*)pedidaDeDatos(listaLibros);
    if(libroEncontrado == NULL) return; //Si no se encontro se termina la funcion

    //Se pide el nombre del estudiante que quiere cancelar reserva del libro
    char nombreEstudiante[21];
  
    printf("\nIngrese el nombre del estudiante que cancela la reserva\n");
    scanf(" %20[^\n]", nombreEstudiante);

    //Busca la reserva en la lista
    void* nodoReserva = encontrarReserva(libroEncontrado->reservas, nombreEstudiante);

    //Si no existe termina la funcion
    if(nodoReserva == NULL){
        printf("\nEl estudiante no tiene una reserva para este libro\n");
        return;
    }

    //Se borra el nodo que tiene el estudiante y se libera el nodo
    popCurrent(libroEncontrado->reservas);
    free(nodoReserva);

    //En caso de que no halla mas estudiantes en la lista se cambia el estado del libro
    if(firstList(libroEncontrado->reservas) == NULL){
        strcpy(libroEncontrado->estado,"Disponible");
    }

    printf("\nReserva cancelada con éxito\n");
}

//Funcio opcion 6
void retirarLibro(List* listaLibros){

    //Se convierte el nodo del libro a tipo Libro
    Libro* libroEncontrado = (Libro*)pedidaDeDatos(listaLibros);
    if(libroEncontrado == NULL) return; //Si no se encontro se termina la funcion

    //Se pide el nombre del estudiante que quiere retirar el libro
    char nombreEstudiante[21];
  
    printf("\nIngrese el nombre del estudiante que retira el libro\n");
    scanf(" %20[^\n]", nombreEstudiante);

    //Se revisa el estado y se cambia
    if(strcmp(libroEncontrado->estado,"Disponible") == 0){  
      //En caso de estar disponible
      strcpy(libroEncontrado->estado,"Prestado");
      strcpy(libroEncontrado->nombreUltimoPrestado, nombreEstudiante);
      printf("\nSe retiro con exito\n");
      return;
    }
    else if(strcmp(libroEncontrado->estado,"Reservado") == 0){
        //En caso de estar reservado se revisa si el estudiante esta de primero en la lista
        if(strcmp(nombreEstudiante, (char*)firstList(libroEncontrado->reservas)) == 0){
            //Si lo esta se retira exitosamente
            strcpy(libroEncontrado->estado,"Prestado");
            strcpy(libroEncontrado->nombreUltimoPrestado, nombreEstudiante);
            popFront(libroEncontrado->reservas); //Se borra al estudiante de la lista
            printf("\nSe retiro con exito\n");
            return;
        }
    }

    //El estudiante no cumplio ninguna condicion
    printf("\nEl libro ya fue prestado o no tiene prioridad en la reservas\n");
    return;
}

//Funcion opcion 7
void devolverLibro(List* listaLibros){

   //Se convierte el nodo del libro a tipo Libro
    Libro* libroEncontrado = (Libro*)pedidaDeDatos(listaLibros);
    if(libroEncontrado == NULL) return; //Si no se encontro se termina la funcion

    //Dependiendo si tiene reserva o no, cambia el estado
    if(firstList(libroEncontrado->reservas) == NULL){
        strcpy(libroEncontrado->estado,"Disponible");
    }
    else{
        strcpy(libroEncontrado->estado,"Reservado");
    }  

    printf("\nSe ha devuelto el libro corretamente.\n");
}

//Funcion opcion 8
void mostrarLibrosPrestados(List* listaLibros) {

    //Se guarda al primero de la lista de reserva del libro
    void* current = firstList(listaLibros);

    //Si no hay libros en la lista termina la funcion
    if (current == NULL) {
        printf("\nNo hay libros registrados.\n");
        return;
    }

    printf("\nLibros prestados:\n");

    //Ciclo para revisar libro por libro para saber si estan prestados y por quien
    while (current != NULL) {
        Libro* libro = (Libro*)current;
        if (strcmp(libro->estado, "Prestado") == 0) {
            printf("Título: %s\n", libro->titulo);
            printf("Autor: %s\n", libro->autor);
            printf("Prestado a: %s\n", libro->nombreUltimoPrestado);
            printf("\n");
        }

        //Se pasa al siguiente libro
        current = nextList(listaLibros);
    }
}

//Funcion opcion 9
void importarLibrosCSV(List* listaLibros) {
    char nombreArchivo[100];

    //Se pide el nombre del archivo a importar
    printf("\nIngrese el nombre del archivo CSV para importar(sin .csv)\n");
    scanf(" %99[^\n]", nombreArchivo);

    //Se añade .csv automaticamente al final del texto
    strcat(nombreArchivo, ".csv");

    //Se abre el archivo en modo lectura
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("\nError al abrir el archivo.\n");
        return;
    }

    char linea[256];

    //Se quita la cabecera del texto
    fgets(linea, sizeof(linea), archivo);

    while (fgets(linea, sizeof(linea), archivo)) {
        // Eliminar cualquier caracter de nueva línea de la cadena
        char* newline = strchr(linea, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }
      
        if (strlen(linea) == 0) {
            continue;  // Ignorar líneas vacías
        }

        Libro* libro = (Libro*)malloc(sizeof(Libro));
        if (libro == NULL) {
            printf("\nError al reservar memoria para el libro.\n");
            return;
        }

        libro->reservas = createList(); //Se crea una lista de reserva al libro

        char* token;
        int tokenCount = 0;
        /*
            0 - Titulo
            1 - Autor
            2 - Genero
            3 - ISBN
            4 - Ubicacion
            5 - Estado
            6+ - Reservas
        */

        token = strtok(linea, ",");
        while (token != NULL) {
            //Dependiendo del tipo de cadena se agrega a diferente variable
            switch (tokenCount) {
                case 0: strcpy(libro->titulo, token); break;
                case 1: strcpy(libro->autor, token); break;
                case 2: strcpy(libro->genero, token); break;
                case 3: libro->ISBN = atoi(token); break;
                case 4: strcpy(libro->ubicacion, token); break;
                case 5: strcpy(libro->estado, token); break;
                default: pushBack(libro->reservas, strdup(token)); break; 
            }
            token = strtok(NULL, ",");
            tokenCount++; //Se mueve el tipo de texto para la siguiente cadena
        }

        //Se agrega a la lista
        pushFront(listaLibros, libro);
    }

    fclose(archivo);
    printf("\nLibros importados correctamente.\n");
}


//Funcion opcion 10
void exportarLibrosCSV(List* listaLibros){

    char nombreArchivo[100];
  
    //Se pide el nombre del archivo a importar
    printf("\nIngrese el nombre del archivo CSV para exportar (sin .csv)\n");
    scanf(" %99[^\n]", nombreArchivo);

    //Se agrega automaticamente el .csv al final del nombre
    strcat(nombreArchivo, ".csv");

    FILE* archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        printf("\nError al abrir el archivo para escribir.\n");
        return;
    }

    //Se agrega como cabercera al texto
    fprintf(archivo, "Título,Autor,Género,ISBN,Ubicación,Estado,Reservas\n");

    //Se guarda al primer libro
    void* current = firstList(listaLibros);

    //Ciclo para toda la lista de libros
    while (current != NULL) {
        //Se convierte el nodo actual a tipo Libro
        Libro* libro = (Libro*)current;

        //Se va escribiendo linea por linea los datos
        fprintf(archivo, "%s,%s,%s,%d,%s,%s", libro->titulo, libro->autor, libro->genero, libro->ISBN, libro->ubicacion, libro->estado);

        void* reserva = firstList(libro->reservas);
        //Si el libro tiene reserva, se añade al texto
        while (reserva != NULL) {
            fprintf(archivo, ",%s", (char*)reserva);
            reserva = nextList(libro->reservas);
        }

        fprintf(archivo, "\n");

        //Se pasa al siguiente libro
        current = nextList(listaLibros);
    }

    fclose(archivo);
    printf("\nDatos exportados correctamente.\n");
}

//Funcion para saber si el estudiante tiene una reserva en el libro
void* encontrarReserva(List* listaReservas, char* nombreConReserva){

    //Se guarda al primer nodo de la lista de reserva del libro
    void* current = firstList(listaReservas);

    //En caso de que si exista al menos un nodo en la lista se empieza el ciclo
    while(current != NULL){
        //Se convierte el nodo a char (seria un string)
        char* nombreEstudiante = (char*)current;
        if(strcmp(nombreConReserva,nombreEstudiante) == 0) return current; //Si tiene, retorna el libro en el que tiene la reserva

        current = nextList(listaReservas);
    }

    return NULL; //Si no encuentra retorna NULL
  
}

//Funcion con un ciclo para mostrar los estudiantes con reservas en un libro
void mostrarReservas(List* listaReservas){

    void* current = firstList(listaReservas);

    printf("\n");

    while(current != NULL){
        char* nombreEstudiante = (char*)current;
        printf("%s\n", nombreEstudiante);

        current = nextList(listaReservas);
    }
  
}

//Funcion para encontrar libro segun datos pedidos
void* pedidaDeDatos(List* listaLibros){
    char titulo[51], autor[51];

    //Se pide titulo y autor al usuario
    printf("\n-----------------------\n");
    printf("\nIngrese el titulo del libro a buscar\n");
    scanf(" %50[^\n]", titulo);

    printf("\nIngrese el autor del libro a buscar\n");
    scanf(" %50[^\n]", autor);

    //Se busca y se retorna su nodo
    void* nodoLibro = encontrarLibro(listaLibros, titulo, autor);

    //En caso de no existir se retorna NULL
    if(nodoLibro == NULL){
        printf("\nNo existe el libro\n");
        return NULL;
    }

    return nodoLibro; //Se retorna el nodo que posee al libro
}

//Funcion que revisa la lista completa comparando titulos y autores
void* encontrarLibro(List* listaLibros, const char* titulo, const char* autor) {

    //Se guarda al primer libro de la lista
    void* current = firstList(listaLibros);

    //Si hay al menos un libro de la lista empieza el ciclo de busqueda
    while(current != NULL){
        //Se combierte el nodo actual a tipo Libro
        Libro* libro = (Libro*)current;

        //Se compara los datos ingresados por el usuarios con los libros de la lista
        if(strcmp(libro->titulo, titulo) == 0 && strcmp(libro->autor, autor) == 0){
            return current; //Se retorna el libro encontrado
        }
        //Se pasa al siguiente libro
        current = nextList(listaLibros);
    }
    
    return NULL; //No se encontro o no hay libros en la lista
}

//Funcion que se usa en opcion 11 para liberar memoria
void liberarReservas(List* listaLibros){

  //Se guarda al primer libro de la lista
  void* current = firstList(listaLibros);

  //Si hay libros en la lista empieza el ciclo
  while(current != NULL){
    //Se combierte el nodo a tipo Libro
    Libro* libroActual = (Libro*)current;

    //Si es que hay libros en su reserva se libera
    if(firstList(libroActual->reservas) != NULL){
        cleanList(libroActual->reservas);
    }

    //Se libera la lista de reserva
    free(libroActual->reservas);
    
    //Se pasa al siguiente libro
    current = nextList(listaLibros);
  }
}