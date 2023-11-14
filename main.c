#include <stdio.h>
#include <stdlib.h>
#include<wchar.h>
#include<locale.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include<conio.h>
#include <ctype.h>
#include <windows.h>

struct Clientes{
    char nombre[20];
    long DNI;
    int cantidad;
    char caja[10];
    int lugar;

    struct Clientes *sig;
};

typedef struct Clientes *ptrLista;
ptrLista Inicio = NULL;
ptrLista Final = NULL;
ptrLista InicioRapida = NULL;
ptrLista FinalRapida = NULL;
ptrLista InicioComun = NULL;
ptrLista FinalComun = NULL;

int vacia(struct Clientes *ptrActual)
{
    if (ptrActual == NULL)
        return 1;
    else
        return 0;
}

int existeDNI(long dni) {
    struct Clientes *actual = Inicio;

    while (actual != NULL) {
        if (actual->DNI == dni) {
            return 1;  // El DNI ya existe en la lista
        }
        actual = actual->sig;
    }

    return 0;
}

int verPosicion(struct Clientes *actual, struct Clientes *llegada){
    int pos = 1;
    while(actual!=llegada){
        pos = pos + 1;

        actual = actual->sig;
    }

    return pos;
}

int documentoValido(long doc){
    if(doc < 1000000 || doc > 99999999){
        return 1; //El DNI contiene menos de 7 digitos o más de 8 digitos
    }else{
        return 0;
    }
}

void Menu(){
    puts("|||||||||||||||||||||||||");
    puts("-------------------------");
    puts(" S U P E R M E R C A D O ");
    puts("-------------------------");
    puts("|||||||||||||||||||||||||\n");
    puts("Menú: \n");
    puts("1. Agregar Cliente");
    puts("2. Ver clientes");
    puts("3. Modificar cantidades");
    puts("4. Ver fila rápida");
    puts("5. Atender cliente fila rápida");
    puts("6. Ver fila común");
    puts("7. Atender cliente fila común");
    puts("8. Restricciones");
    puts("9. Salir");
    puts("----------------------------");
    printf("Elegir opción: ");
}

void agregarCajaComun(char nom[], long doc, int cant){
    struct Clientes *nuevo;
        nuevo = malloc(sizeof(struct Clientes));

        strcpy(nuevo->nombre,nom);
        nuevo->DNI = doc;
        nuevo->cantidad = cant;
        strcpy(nuevo->caja, "Común");
        nuevo->sig = NULL;

        if(vacia(InicioComun)){
            InicioComun = nuevo;
            FinalComun = nuevo;
        }else{
            FinalComun->sig = nuevo;
            FinalComun = nuevo;
        }

        nuevo->lugar = verPosicion(InicioComun,nuevo);
}

void agregarCajaRapida(char nom[], long doc, int cant){
    struct Clientes *nuevo;
        nuevo = malloc(sizeof(struct Clientes));

        strcpy(nuevo->nombre,nom);
        nuevo->DNI = doc;
        nuevo->cantidad = cant;
        strcpy(nuevo->caja, "Rápida");
        nuevo->sig = NULL;

        if(vacia(InicioRapida)){
            InicioRapida = nuevo;
            FinalRapida = nuevo;
        }else{
            FinalRapida->sig = nuevo;
            FinalRapida = nuevo;
        }

        nuevo->lugar = verPosicion(InicioRapida,nuevo);
}

void agregarCliente(){
    char nom[20];
    long doc;
    int cant;
    int op;

    do{
        system("cls");
        fflush(stdin);
        printf("Ingrese el nombre del cliente: ");
        gets(nom);
        printf("Ingrese el DNI de '%s' (sin puntos ni comas): ",nom);
        scanf("%ld",&doc);
        while(documentoValido(doc)){
            puts("-----------------------------------------------");
            printf("¡El DNI debe tener entre 7 u 8 digitos\n", doc);
            puts("-----------------------------------------------");
            printf("Ingrese el DNI de '%s' (sin puntos ni comas): ",nom);
            scanf("%ld",&doc);
        }
        while(existeDNI(doc)) {
            puts("-----------------------------------------------------");
            printf("¡El DNI '%ld' ya está en uso por otro cliente!\n", doc);
            puts("-----------------------------------------------------");
            printf("Ingrese el DNI de '%s' (sin puntos ni comas): ",nom);
            scanf("%ld",&doc);
        }
        printf("\nIngrese la cantidad de productos que lleva: ");
        scanf("%d",&cant);

        while(cant<=0){
            puts("----------------------------------------------------");
            puts("¡Opción no valida, tiene que comprar algun producto!");
            puts("----------------------------------------------------");
            printf("Elegir opción: ");
            scanf("%d",&cant);
        }

        struct Clientes *nuevo;
        nuevo = malloc(sizeof(struct Clientes));

        strcpy(nuevo->nombre,nom);
        nuevo->DNI = doc;
        nuevo->cantidad = cant;
        nuevo->sig = NULL;

        if(vacia(Inicio)){
            Inicio = nuevo;
            Final = nuevo;
        }else{
            Final->sig = nuevo;
            Final = nuevo;
        }

        if(cant<=10){
            agregarCajaRapida(nom,doc,cant);
            system("cls");
            puts("-------------------------------------");
            puts("¡Por favor dirijase a la fila rápida!");
            puts("------------------------------------");
            strcpy(nuevo->caja, "Rápida");
            system("pause");
        }else{
            agregarCajaComun(nom,doc,cant);
            system("cls");
            puts("------------------------------------");
            puts("¡Por favor dirijase a la fila comun!");
            puts("------------------------------------");
            strcpy(nuevo->caja, "Común");
            system("pause");
        }

        system("cls");
        puts("¿Desea agregar otro cliente?\n1.Si\n2.No");
        puts("-----------------");
        printf("Elegir opción: ");
        scanf("%d",&op);
        while(op>2 || op<1){
            puts("------------------------------------");
            puts("¡Opción no valida, intente de nuevo!");
            puts("------------------------------------");
            printf("Elegir opción: ");
            scanf("%d",&op);
        }
        if(op==2){
            system("cls");
            puts("--------------------------------");
            puts("¡Cliente/s agregado con éxito!");
            puts("--------------------------------");
            system("pause");
        }
    }while(op!=2);
}

void verFila(struct Clientes *actual){
    if(!vacia(Inicio)){
        puts("-------------------------------------");
        puts("Lista de clientes:");
        puts("-------------------------------------");
        while(actual!=NULL){
            printf("Nombre: %s\n",actual->nombre);
            printf("DNI: %ld\n",actual->DNI);
            printf("Cantidad: %d\n",actual->cantidad);
            printf("Caja: %s\n",actual->caja);
            puts("------------------------------");
            actual = actual->sig;
        }
        system("pause");
    }else{
        puts("-----------------------------");
        puts("¡No hay clientes actualmente!");
        puts("-----------------------------");
        system("pause");
    }
}

void verFilaComun(struct Clientes *actual){
    if(!vacia(InicioComun)){
        puts("-------------------------------------");
        puts("Caja Común (11 productos o más):");
        puts("-------------------------------------");
        puts("Próximo a atender:");
        puts("------------------------------");
        while(actual!=NULL){
            printf("Nombre: %s\n",actual->nombre);
            printf("DNI: %ld\n",actual->DNI);
            printf("Cantidad: %d\n",actual->cantidad);
            printf("Caja: %s\n",actual->caja);
            printf("Lugar: %d\n",actual->lugar);
            puts("------------------------------");
            actual = actual->sig;
        }
        system("pause");
    }else if(vacia(InicioComun) && !vacia(InicioRapida)){
        puts("----------------------------------");
        puts("¡La fila común se encuentra vacia!");
        puts("----------------------------------");
        system("pause");
    }else if(vacia(InicioComun) && vacia(InicioRapida)){
        puts("----------------------------------");
        puts("¡Ambas filas se encuentran vacias!");
        puts("----------------------------------");
        system("pause");
    }
}

void verFilaRapida(struct Clientes *actual){
    if(!vacia(InicioRapida)){
        puts("-------------------------------------");
        puts("Caja Rápida (10 productos o menos):");
        puts("-------------------------------------");
        puts("Próximo a atender:");
        puts("------------------------------");
        while(actual!=NULL){
            printf("Nombre: %s\n",actual->nombre);
            printf("DNI: %ld\n",actual->DNI);
            printf("Cantidad: %d\n",actual->cantidad);
            printf("Caja: %s\n",actual->caja);
            printf("Lugar: %d\n",actual->lugar);
            puts("------------------------------");
            actual = actual->sig;
        }
        system("pause");
    }else if(vacia(InicioRapida) && !vacia(InicioComun)){
        puts("-----------------------------------");
        puts("¡La fila rápida se encuentra vacia!");
        puts("-----------------------------------");
        system("pause");
    }else if(vacia(InicioRapida) && vacia(InicioComun)){
        puts("----------------------------------");
        puts("¡Ambas filas se encuentran vacias!");
        puts("----------------------------------");
        system("pause");
    }

}

void atenderCajaComun(struct Clientes *actual){
    if(!vacia(InicioComun)){
        puts("-----------------------------------------");
        puts("Atendiendo al primero de la fila común...");
        puts("-----------------------------------------");
        sleep(2);
        system("cls");
        puts("-----------------------------------------");
        printf("Atendiendo a '%s' ...\n",actual->nombre);
        puts("-----------------------------------------");
        sleep(2);

        system("cls");
        puts("----------------------------------");
        printf("¡Cliente '%s' atendido!\n",actual->nombre);
        puts("----------------------------------");

        eliminarClienteComun(actual->DNI);
        eliminarCliente(actual->DNI);
        system("pause");
    }else{
        if(!vacia(InicioRapida)&&InicioRapida->sig!=NULL){
            struct Clientes *actual = InicioRapida->sig;

            puts("------------------------------------------------------------------");
            puts("La fila común está vacia, se atenderá al segundo de la fila rápida");
            puts("------------------------------------------------------------------");
            system("pause");
            system("cls");
            puts("------------------------------------------");
            puts("Atendiendo al segundo de la fila rápida...");
            puts("------------------------------------------");
            sleep(2);
            system("cls");
            puts("-----------------------------------------");
            printf("Atendiendo a '%s' ...\n",actual->nombre);
            puts("-----------------------------------------");
            sleep(2);

            system("cls");
            puts("------------------------------------------");
            printf("¡Cliente '%s' atendido!\n",actual->nombre);
            puts("------------------------------------------");

            eliminarClienteRapida(actual->DNI);
            eliminarCliente(actual->DNI);
            system("pause");

        }else if(vacia(InicioComun) && !vacia(InicioRapida)){
            puts("----------------------------------");
            puts("¡La fila común se encuentra vacia!");
            puts("----------------------------------");
            system("pause");
        }else if(vacia(InicioComun) && vacia(InicioRapida)){
            puts("----------------------------------");
            puts("¡Ambas filas se encuentran vacias!");
            puts("----------------------------------");
            system("pause");
        }else if(vacia(InicioComun) && InicioRapida->sig == NULL){
            puts("-----------------------------------------------------------------------------");
            puts("¡La fila común se encuentra vacia pero hay un solo cliente en la fila rápida!");
            puts("-----------------------------------------------------------------------------");
            system("pause");
        }
    }
}

void atenderCajaRapida(struct Clientes *actual){
    if(!vacia(InicioRapida)){
        puts("------------------------------------------");
        puts("Atendiendo al primero de la fila rápida...");
        puts("------------------------------------------");
        sleep(2);
        system("cls");
        puts("-----------------------------------------");
        printf("Atendiendo a '%s' ...\n",actual->nombre);
        puts("-----------------------------------------");
        sleep(2);

        system("cls");
        puts("------------------------------------------");
        printf("¡Cliente '%s' atendido!\n",actual->nombre);
        puts("------------------------------------------");

        eliminarClienteRapida(actual->DNI);
        eliminarCliente(actual->DNI);
        system("pause");
    }else{
        if(!vacia(InicioComun)&&InicioComun->sig!=NULL){
            struct Clientes *actual = InicioComun->sig;

            puts("------------------------------------------------------------------");
            puts("La fila rápida está vacia, se atenderá al segundo de la fila común");
            puts("------------------------------------------------------------------");
            system("pause");
            system("cls");
            puts("-----------------------------------------");
            puts("Atendiendo al segundo de la fila común...");
            puts("-----------------------------------------");
            sleep(2);
            system("cls");
            puts("-----------------------------------------");
            printf("Atendiendo a '%s' ...\n",actual->nombre);
            puts("-----------------------------------------");
            sleep(2);

            system("cls");
            puts("------------------------------------------");
            printf("¡Cliente '%s' atendido!\n",actual->nombre);
            puts("------------------------------------------");

            eliminarClienteComun(actual->DNI);
            eliminarCliente(actual->DNI);
            system("pause");

        }else if(vacia(InicioRapida) && !vacia(InicioComun)){
            puts("----------------------------------");
            puts("¡La fila común se encuentra vacia!");
            puts("----------------------------------");
            system("pause");
        }else if(vacia(InicioRapida) && vacia(InicioComun)){
            puts("----------------------------------");
            puts("¡Ambas filas se encuentran vacias!");
            puts("----------------------------------");
            system("pause");
        }else if(vacia(InicioRapida) && InicioComun->sig == NULL){
            puts("-----------------------------------------------------------------------------");
            puts("¡La fila rápida se encuentra vacia pero hay un solo cliente en la fila común!");
            puts("-----------------------------------------------------------------------------");
            system("pause");
        }
    }
}

void eliminarClienteRapida(long dni) {
    struct Clientes *actual = InicioRapida;
    struct Clientes *anterior = NULL;

    while (actual != NULL && actual->DNI != dni) {
        anterior = actual;
        actual = actual->sig;
    }

    if (anterior == NULL) {
        InicioRapida = actual->sig;
    } else {
        anterior->sig = actual->sig;
    }
    free(actual);
}

void eliminarClienteComun(long dni) {
    struct Clientes *actual = InicioComun;
    struct Clientes *anterior = NULL;

    while (actual != NULL && actual->DNI != dni) {
        anterior = actual;
        actual = actual->sig;
    }

    if (anterior == NULL) {
        InicioComun = actual->sig;
    } else {
        anterior->sig = actual->sig;
    }
    free(actual);
}

void eliminarCliente(long dni) {
    struct Clientes *actual = Inicio;
    struct Clientes *anterior = NULL;

    while (actual != NULL && actual->DNI != dni) {
        anterior = actual;
        actual = actual->sig;
    }

    if (anterior == NULL) {
        Inicio = actual->sig;
    } else {
        anterior->sig = actual->sig;
    }
    free(actual);
}

void modificarCantidades(struct Clientes *actual){
    struct Clientes *anterior = NULL;

    char nom[20];
    long doc;
    int cant;

    puts("---------------------------------------------------------------------------------");
    puts("A continuación ingrese el documento del cliente agregó/sacó cosas de su changuito");
    puts("---------------------------------------------------------------------------------");
    printf("Documento n°: ");
    scanf("%ld",&doc);
    while(documentoValido(doc)){
        puts("------------------------------------------");
        printf("¡El DNI debe tener entre 7 u 8 digitos\n");
        puts("------------------------------------------");
        printf("Ingrese el DNI (sin puntos ni comas): ");
        scanf("%ld",&doc);
    }
    if(existeDNI(doc)){
        system("cls");
        puts("-----------------------------------------");
        printf("Buscando cliente con DNI '%ld'...\n",doc);
        puts("-----------------------------------------");
        sleep(2);


        while (actual != NULL && actual->DNI != doc) {
            anterior = actual;
            actual = actual->sig;
        }

        system("cls");
        puts("-----------------------------------------");
        printf("¡Cliente '%s' encontrado!...\n",actual->nombre);
        puts("-----------------------------------------");

        system("cls");
        puts("------------------------------------------------");
        printf("Ingrese la cantidad de productos que lleva: \n");
        puts("------------------------------------------------");
        printf("Cantidad: ");
        scanf("%d",&cant);

        while(cant<=0){
            puts("----------------------------------------------------");
            puts("¡Opción no valida, tiene que comprar algun producto!");
            puts("----------------------------------------------------");
            printf("Elegir opción: ");
            scanf("%d",&cant);
        }

        if(actual->cantidad <= 10 && cant<=10){
            actual->cantidad = cant;

            system("cls");
            puts("---------------------------------------------------------------");
            puts("¡Cantidad de productos actualizada, se queda en la fila rápida!");
            puts("---------------------------------------------------------------");
        }else if(actual->cantidad > 10 && cant > 10){
            actual->cantidad = cant;

            system("cls");
            puts("--------------------------------------------------------------");
            puts("¡Cantidad de productos actualizada, se queda en la fila común!");
            puts("--------------------------------------------------------------");
        }else if(actual->cantidad <= 10 && cant > 10){
            strcpy(nom,actual->nombre);
            doc = actual->DNI;

            eliminarClienteRapida(actual->DNI);

            system("cls");
            puts("--------------------------------------------------------------------------");
            puts("¡Cantidad de productos actualizada, se traslada al final en la fila común!");
            puts("--------------------------------------------------------------------------");

            struct Clientes *nuevo;
            nuevo = malloc(sizeof(struct Clientes));

            strcpy(nuevo->nombre,nom);
            nuevo->DNI = doc;
            nuevo->cantidad = cant;
            strcpy(nuevo->caja, "Común");
            nuevo->sig = NULL;

            if(vacia(InicioComun)){
                InicioComun = nuevo;
                FinalComun = nuevo;
            }else{
                FinalComun->sig = nuevo;
                FinalComun = nuevo;
            }

            nuevo->lugar = verPosicion(InicioComun,nuevo);
        }else if(actual->cantidad > 10 && cant <= 10){
            strcpy(nom,actual->nombre);
            doc = actual->DNI;

            eliminarClienteComun(actual->DNI);

            system("cls");
            puts("---------------------------------------------------------------------------");
            puts("¡Cantidad de productos actualizada, se traslada al final en la fila rápida!");
            puts("---------------------------------------------------------------------------");

            struct Clientes *nuevo;
            nuevo = malloc(sizeof(struct Clientes));

            strcpy(nuevo->nombre,nom);
            nuevo->DNI = doc;
            nuevo->cantidad = cant;
            strcpy(nuevo->caja, "Rápida");
            nuevo->sig = NULL;

            if(vacia(InicioComun)){
                InicioRapida = nuevo;
                FinalRapida = nuevo;
            }else{
                FinalRapida->sig = nuevo;
                FinalRapida = nuevo;
            }

            nuevo->lugar = verPosicion(InicioRapida,nuevo);
        }
    }else{
        system("cls");
        puts("----------------------------------------------------");
        printf("¡El DNI '%ld' no pertenece a ningún cliente\n", doc);
        puts("----------------------------------------------------");
        system("pause");
    }
}

int main()
{
    setlocale(LC_ALL, "");
    srand(time(NULL));

    int op,op3,res = 1;

    setlocale(LC_ALL, "");
    srand(time(NULL));

    do{
        system("cls");
        Menu();
        scanf("%d",&op);
        while(op>8 || op<1){
            puts("------------------------------------");
            puts("¡Opción no valida, intente de nuevo!");
            puts("------------------------------------");
            printf("Elegir opción: ");
            scanf("%d",&op);
        }
        switch(op){
            case 1:
                if(res==1){
                    system("cls");
                    agregarCliente();
                }else{
                    system("cls");
                    puts("¡Lea las restricciones antes!");
                    puts("------------------------------------");
                    system("pause");
                }
                break;
            case 2:
                if(res==1){
                    system("cls");
                    verFila(Inicio);
                }else{
                    system("cls");
                    puts("¡Lea las restricciones antes!");
                    puts("------------------------------------");
                    system("pause");
                }
                break;
            case 3:
                if(res==1){
                    system("cls");
                    modificarCantidades(Inicio);
                }else{
                    system("cls");
                    puts("¡Lea las restricciones antes!");
                    puts("------------------------------------");
                    system("pause");
                }
                break;
            case 4:
                if(res==1){
                    system("cls");
                    verFilaRapida(InicioRapida);
                }else{
                    system("cls");
                    puts("¡Lea las restricciones antes!");
                    puts("------------------------------------");
                    system("pause");
                }
                break;
            case 5:
                if(res==1){
                    system("cls");
                    atenderCajaRapida(InicioRapida);
                }else{
                    system("cls");
                    puts("¡Lea las restricciones antes!");
                    puts("------------------------------------");
                    system("pause");
                }
                break;
            case 6:
                if(res==1){
                    system("cls");
                    verFilaComun(InicioComun);
                }else{
                    system("cls");
                    puts("¡Lea las restricciones antes!");
                    puts("------------------------------------");
                    system("pause");
                }
                break;
            case 7:
                if(res==1){
                    system("cls");
                    atenderCajaComun(InicioComun);
                }else{
                    system("cls");
                    puts("¡Lea las restricciones antes!");
                    puts("------------------------------------");
                    system("pause");
                }
                break;
            case 8:
                system("cls");
                puts("Nada");
                system("pause");
                res = 1;
                break;
            case 9:
                system("cls");
                puts("¿Está seguro que desea salir?\n1.Si\n2.No");
                puts("-----------------");
                printf("Elegir opción: ");
                scanf("%d",&op3);
                while(op3>2 || op3<1){
                    puts("------------------------------------");
                    puts("¡Opción no valida, intente de nuevo!");
                    puts("------------------------------------");
                    printf("Elegir opción: ");
                    scanf("%d",&op3);
                }
                switch(op3){
                case 1:
                    system("cls");
                    puts("Saliendo del programa...");
                    sleep(2);
                    break;
                case 2:
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(2);
                    op=1;
                    break;
                }
                break;
        }
    }while(op!=9);

    return 0;
}
