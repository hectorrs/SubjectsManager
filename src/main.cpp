#include<cstdio>
#include<cstdlib>

const int MAXPRUEBAS=7;
    /** Es el numero maximo permitido de pruebas */

const int MAXSEMANAS=15;
    /** Es el numero maximo permitido de semanas */

const int MAXASIGNATURAS=5;
    /** Es el numero maximo permitido de asignaturas que se pueden dar de alta */

struct Puntuables {
    float datos[MAXPRUEBAS];
    int num;
    };

typedef int Baremo[2];
    /** La posicion 0 almacena el peso de las pruebas parciales y la posicion 1, el peso de los entregables */

typedef int Tiempo[MAXSEMANAS];

struct Calificaciones {
    Puntuables parciales;
    Puntuables entregables;
    };

struct Asignatura {
    int codigo;
    char nombre[15];
    Baremo peso;
    Calificaciones notas;
    Tiempo dedicacion;
};

struct Curso {
    Asignatura lista[MAXASIGNATURAS];
    int numAsignaturas;
    };

void menu(int &op);
    /** Nos permite realizar cualqiera de las aplicaciones que se hayan en el. Tiene como parametro de entrada un entero, que
        es la opcion que deseamos realizar */

int busqueda(const Curso &c, int codigo);
    /** Busca el código de una asignatura dentro del vector y devuelve su posición o -1 en el caso de no encontrarlo. Tiene como
        parametro de entrada la matriz c donde se almacenan todos los datos y el codigo que buscamos */

void altaAsignatura(Curso &c);
    /** Pide al usuario que introduzca los datos para crear una nueva asignatura. Tiene como parametro de entrada la matriz c donde
        se almacenan todos los datos*/

void mostrarAsignatura (const Curso &c, int pos);
    /** Muestra los datos de una asignatura que se encuentra en la posición pos del vector. Tiene como parametro de entrada la
        matriz c donde se almacenan todos los datos y la posicion, que es un entero, de la asignatura que queremos mostrar */

void consulta(const Curso &c);
    /** Muestra los datos de una asignatura. Tiene como parametro de entrada la matriz c donde se almacenan todos los datos */

void listado(const Curso &c);
    /** Muestra los datos de todas las asignaturas. Tiene como parametro de entrada la matriz c donde se almacenan todos los datos */

void bajaAsignatura (Curso &c);
    /** Solicita al usuario el codigo de la asignatura y lo busca. Si el codigo no existe, se muestra un mensaje. Si no,
        muestra los datos de la asignatura, pregunta al usuario si son correctos y, si lo son, elimina esa asignatura. Tiene como
        parametro de entrada la matriz c donde se almacenan todos los datos */

void altaDedicacionSemanal(Curso &c);
    /** Solicita al usuario el codigo de la asignatura y lo busca. Si no existe muestra un mensaje indicandolo. En caso contrario,
        solicitara al usuario el numero de la semana y la dedicacion en minutos de esa semana. Tiene como parametro de entrada la
        matriz c donde se almacenan todos los datos */

void consultaDedicacionSemanal (Curso &c);
    /** Solicita al usuario el codigo de la asignatura y lo busca. Si no existe muestra un mensaje indicandolo. Si no, muestra la
        dedicacion en minutos de la seamana. Tiene como parametro de entrada la matriz c donde se almacenan todos los datos */

void altaCalificacionesPruebas(Curso &c);
    /** Solicita al usuario el codigo de la asignatura y lo busca. Si no existe muestra un mensaje indicandolo. En caso contrario,
        se solicitara el numero del parcial y la nota obtenida en ese parcial. Tiene como parametro de entrada la matriz c donde
        se almacenan todos los datos */

void altaCalificacionesEntregables (Curso &c);
    /** Solicita al usuario el codigo de la asignatura y lo busca. Si no existe muestra un mensaje indicandolo. En caso contrario,
        solicita el numero del entregable y la nota obtenida en ese entregable. Tiene como parametro de entrada la matriz c donde
        se almacenan todos los datos */

void consultaCalificaciones (Curso &c);
    /** Solicita al usuario el codigo de la asignatura y lo busca. Si no existe, muestra un mensaje indicandolo. Si no, muestra las
        notas de los parciales y las notas de los entregables y calcula y muestra la nota final respecto de los pesos asignados a
        cada uno anteriormente. Tiene como parametro de entrada la matriz c donde se almacenan todos los datos */

int main()
{
    int op;
    Curso c;

    c.numAsignaturas=0;

    do{
        menu(op);

        switch (op){
        case 1: altaAsignatura(c);
            break;
        case 2: consulta(c);
            break;
        case 3: bajaAsignatura(c);
            break;
        case 4: altaDedicacionSemanal(c);
            break;
        case 5: consultaDedicacionSemanal(c);
            break;
        case 6: altaCalificacionesPruebas(c);
            break;
        case 7: altaCalificacionesEntregables(c);
            break;
        case 8: consultaCalificaciones(c);
            break;
        case 9: listado(c);
            break;
        case 0:
            break;
        }
    }while(op!=0);
}

void menu(int &op)
{
    system("cls");

    printf("Introduzca una opcion de la lista: \n\n");
    printf("\t ------------------------------------------------------------------\n");
    printf("\t 1: Alta asignatura\n");
    printf("\t 2: Consulta de datos de una asignatura\n");
    printf("\t 3: Baja asignatura\n");
    printf("\t 4: Alta dedicacion semanal de una asignatura\n");
    printf("\t 5: Consulta dedicacion semanal de una asignatura\n");
    printf("\t 6: Alta calificaciones de las pruebas de una asignatura\n");
    printf("\t 7: Alta calificaciones de los entregables de una asignatura\n");
    printf("\t 8: Consulta calificaciones\n");
    printf("\t 9: Listado de todas las asignaturas\n");
    printf("\t 0: Salir\n");
    printf("\t ------------------------------------------------------------------\n");

    do{
        printf("\t");
        scanf("%d", &op);
        if ((op<0) or (op>9))
            printf("Error. Introduzca otro numero\n\n");
    }while ((op<0) or (op>9));
}

int busqueda(const Curso &c, int codigo)
{
    int pos;
    int i;

    i=0;

    while ((i<c.numAsignaturas-1) and (c.lista[i].codigo!=codigo)){
        i=i+1;
    }

    if (c.lista[i].codigo==codigo)
        pos=i;
    else
        pos=-1;

    return pos;
}

void mostrarAsignatura (const Curso &c, int pos)
{
     printf("\tLos datos de la asignatura son: \n\n");
     printf("\tCodigo: %d\n", c.lista[pos].codigo);
     printf("\tNombre: %s\n", c.lista[pos].nombre);
     printf("\tNumero de parciales: %d\n", c.lista[pos].notas.parciales.num);
     printf("\tNumero de entregables: %d\n", c.lista[pos].notas.entregables.num);
     printf("\tPeso de las pruebas parciales: %d\n", c.lista[pos].peso[0]);
     printf("\tPeso de los entregables: %d\n\n", c.lista[pos].peso[1]);

     system("pause");
}

void altaAsignatura(Curso &c)
{
    int pos;
    int codigo;
    int j;
    int k;

    system("cls");

    printf("\n\t\t\t\tALTA ASIGNATURA\n");
    printf("\t------------------------------------------------------------------\n");

    printf("\n\tIntroduzca el codigo de la asignatura: \n");

    do{
        printf("\t");
        scanf("%d", &codigo);
        pos=busqueda(c,codigo);
        if (pos!=-1)
            printf("\tEl codigo ya existe.Vuelve a introducir otro\n");
    }while (pos!=-1);

    c.lista[c.numAsignaturas].codigo=codigo;

    fflush(stdin);

    printf("\tIntroduzca el nombre de la asignatura: \n\t");
    gets(c.lista[c.numAsignaturas].nombre);
    do{
        printf("\tIntroduzca el numero de parciales: \n\t");
        scanf("%d", &c.lista[c.numAsignaturas].notas.parciales.num);
        if ((c.lista[c.numAsignaturas].notas.parciales.num<=0) or (c.lista[c.numAsignaturas].notas.parciales.num>MAXPRUEBAS))
            printf("\tError. El rango de los parciales es de 1 a 7\n");
    }while ((c.lista[c.numAsignaturas].notas.parciales.num<=0) or (c.lista[c.numAsignaturas].notas.parciales.num>MAXPRUEBAS));
    do{
        printf("\tIntroduzca el numero de entregables: \n\t");
        scanf("%d", &c.lista[c.numAsignaturas].notas.entregables.num);
        if ((c.lista[c.numAsignaturas].notas.entregables.num<=0) or (c.lista[c.numAsignaturas].notas.entregables.num>MAXPRUEBAS))
            printf("\tError. El rango de los entregables es de 1 a 7\n");
    }while ((c.lista[c.numAsignaturas].notas.entregables.num<=0) or (c.lista[c.numAsignaturas].notas.entregables.num>MAXPRUEBAS));

    for (j=0;j<=c.lista[c.numAsignaturas].notas.parciales.num-1;j++){
            c.lista[c.numAsignaturas].notas.parciales.datos[j]=0;}

    for (k=0;k<=c.lista[c.numAsignaturas].notas.entregables.num-1;k++){
            c.lista[c.numAsignaturas].notas.entregables.datos[k]=0;}

    for (j=0;j<=MAXSEMANAS-1;j++){
            c.lista[c.numAsignaturas].dedicacion[j]=-1;}

    do{
        do{
            printf("\tIntroduzca el peso en tanto por ciento de la calificacion de las pruebas\tparciales: \n\t");
            scanf("%d", &c.lista[c.numAsignaturas].peso[0]);
        }while((c.lista[c.numAsignaturas].peso[0]<0)or(c.lista[c.numAsignaturas].peso[0]>100));

        do{
            printf("\tIntroduzca el peso en tanto por ciento de la calificacion de los\t\tentregables: \n\t");
            scanf("%d", &c.lista[c.numAsignaturas].peso[1]);
        }while((c.lista[c.numAsignaturas].peso[1]<0) or (c.lista[c.numAsignaturas].peso[1]>100));

        if(c.lista[c.numAsignaturas].peso[0]+c.lista[c.numAsignaturas].peso[1]!=100)
            printf("\tError.Los pesos tienen que sumar 100.\n\tIntroduzca los pesos de nuevo: \n\n");
    }while (c.lista[c.numAsignaturas].peso[0]+c.lista[c.numAsignaturas].peso[1]!=100);

    c.numAsignaturas++;

    system("pause");
}

void consulta(const Curso &c)
 {
     int cod;
     int pos;

     system("cls");

     printf("\n\t\t\tCONSULTA DE ASIGNATURAS\n");
     printf("\t------------------------------------------------------------------\n");

     printf("\n\tIntroduzca el codigo de la asignatura: \n\t");

     do{
        scanf("%d", &cod);
        pos=busqueda(c,cod);
        if (pos==-1)
            printf("\tError. El codigo no existe. Introduzca un codigo nuevo.\n");
     }while (pos==-1);

     mostrarAsignatura(c,pos);
 }

void listado(const Curso &c)
{
    int i;

    system("cls");

    printf("\n\t\t\tLISTADO DE LAS ASIGNATURAS\n");
    printf("\t------------------------------------------------------------------\n\n");

    for(i=0;i<=c.numAsignaturas-1;i++){
        mostrarAsignatura(c,i);}
}

void bajaAsignatura (Curso &c)
{
    int pos;
    int codigo;
    char respuesta;
    int i;

    system("cls");

    printf("\n\t\t\tBAJA ASIGNATURA\n");
    printf("\t------------------------------------------------------------------\n\n");

    do{
        printf("\tIntroduzca el codigo de la asignatura: \n\t");
        scanf("%d", &codigo);
        pos=busqueda(c,codigo);
        if (pos==-1)
            printf("\tEl codigo no existe.Introduce otro:\n");
    }while (pos==-1);

    mostrarAsignatura(c,pos);

    do{
        printf("\tSon correctos los datos a borrar: S/N\n\t");
        fflush(stdin);
        scanf("%c", &respuesta);
    }while((respuesta!='S') and (respuesta!='s') and (respuesta!='N') and (respuesta!='n'));

    if ((respuesta=='S') or (respuesta=='s')) {
        for(i=pos;i<=c.numAsignaturas-1;i++)
            c.lista[i]=c.lista[i+1];}

    c.numAsignaturas--;
}

void altaDedicacionSemanal(Curso &c)
{
    int cod;
    int semana;
    char respuesta;
    int pos;

    system("cls");

    printf("\n\t\t\tALTA DE LA DEDICACION SEMANAL\n");
    printf("\t------------------------------------------------------------------\n\n");

    printf("\tIntroduzca el codigo de la asignatura: \n\t");
    scanf("%d", &cod);

    pos=busqueda(c,cod);

    if (pos==-1)
        printf("\tEl codigo no existe.\n");
    else
        do{
            do{
                printf("\tIntroduce el numero de la semana\n\t");
                scanf("%d", &semana);
                if ((semana<=0) or (semana>MAXSEMANAS))
                    printf("Error.El rango de la semana es de 1 a 15\n");
            }while ((semana<=0) or (semana>MAXSEMANAS));

            do{
                printf("\tIntroduzca el numero de minutos\n\t");
                scanf("%d", &c.lista[pos].dedicacion[semana-1]);
                if (c.lista[pos].dedicacion[semana-1]<=0)
                    printf("Error.Los minutos tienen que ser positivos.\n");
            }while (c.lista[pos].dedicacion[semana-1]<=0);

            do{
                printf("\tDesea continuar: S/N\n\t");
                fflush(stdin);
                scanf("%c", &respuesta);
                if ((respuesta!='S') and (respuesta!='s') and (respuesta!='N') and (respuesta!='n'))
                    printf("\tEse caracter no es valido\n\t");
            }while ((respuesta!='S') and (respuesta!='s') and (respuesta!='N') and (respuesta!='n'));
        }while ((respuesta=='S') or (respuesta=='s'));

        system("pause");
}

void consultaDedicacionSemanal (Curso &c)
{
    int cod;
    int pos;
    int i;

    system("cls");

    printf("\n\t\t\tCONSULTA DE LA DEDICACION SEMANAL\n");
    printf("\t------------------------------------------------------------------\n\n");

    printf("\tIntroduzca el codigo de la asignatura: \t");
    scanf("%d", &cod);

    pos=busqueda(c,cod);

    if (pos==-1)
        printf("\tEl codigo no existe.\n\t");
    else{
        printf("\n\tLa dedicacion semanal de la asignatura %d es: \n", cod);
        for (i=0;i<=MAXSEMANAS-1;i++)
            printf("\tLa dedicacion de la semana %d es: %d\n", i+1,c.lista[pos].dedicacion[i]);
    }

    system("pause");
}

void altaCalificacionesPruebas(Curso &c)
{
    int cod;
    int pos;
    int num;
    char respuesta;

    system("cls");

    printf("\n\t\tALTA DE LAS CALIFICACIONES DE LAS PRUEBAS PARCIALES\n");
    printf("\t------------------------------------------------------------------\n\n");

    printf("\tIntroduzca el codigo de la asignatura: \n\t");
    scanf("%d", &cod);

    pos=busqueda(c,cod);

    if (pos==-1)
        printf("\tEl codigo no existe.\n\t");
    else
        do{
            do{
                printf("\tIntroduzca el numero del parcial: \n\t");
                scanf("%d", &num);
            }while ((num<=0) or (num>c.lista[pos].notas.parciales.num));

            do{
                printf("\tIntroduzca la nota del parcial: \n\t");
                scanf("%f", &c.lista[pos].notas.parciales.datos[num-1]);
                if ((c.lista[pos].notas.parciales.datos[num-1]<0) or (c.lista[pos].notas.parciales.datos[num-1]>10))
                    printf("Error. El rango de la nota es de 0 a 10");
            }while ((c.lista[pos].notas.parciales.datos[num-1]<0) or (c.lista[pos].notas.parciales.datos[num-1]>10));

            do{
                printf("\tDesea continuar: S/N\n\t");
                fflush(stdin);
                scanf("%c", &respuesta);
                if ((respuesta!='S') and (respuesta!='s') and (respuesta!='N') and (respuesta!='n'))
                    printf("\tEse caracter no es valido\n");
            }while ((respuesta!='S') and (respuesta!='s') and (respuesta!='N') and (respuesta!='n'));
        }while ((respuesta=='S') or (respuesta=='s'));
        system("pause");
}

void altaCalificacionesEntregables (Curso &c)
{
    int cod;
    int pos;
    int num;
    char respuesta;

    system("cls");

    printf("\n\t\tALTA DE LAS CALIFICACIONES DE LOS ENTREGABLES\n");
    printf("\t------------------------------------------------------------------\n\n");

    printf("\tIntroduzca el codigo de la asignatura: \n\t");
    scanf("%d", &cod);

    pos=busqueda(c,cod);

    if (pos==-1)
        printf("\tEl codigo no existe.\n\t");
    else
        do{
            do{
                printf("\tIntroduzca el numero del entregable: \n\t");
                scanf("%d", &num);
            }while ((num<=0) or (num>c.lista[pos].notas.entregables.num));

            do{
                printf("\tIntroduzca la nota del entregable: \n\t");
                scanf("%f", &c.lista[pos].notas.entregables.datos[num-1]);
                if ((c.lista[pos].notas.entregables.datos[num-1]<0) or (c.lista[pos].notas.entregables.datos[num-1]>10))
                    printf("Error. El rango de la nota es de 0 a 10");
            }while ((c.lista[pos].notas.entregables.datos[num-1]<0) or (c.lista[pos].notas.entregables.datos[num-1]>10));

            do{
                printf("\tDesea continuar: S/N\n\t");
                fflush(stdin);
                scanf("%c", &respuesta);
                if ((respuesta!='S') and (respuesta!='s') and (respuesta!='N') and (respuesta!='n'))
                    printf("\tEse caracter no es valido.\n");
            }while ((respuesta!='S') and (respuesta!='s') and (respuesta!='N') and (respuesta!='n'));
        }while ((respuesta=='S') or (respuesta=='s'));
        system("pause");
}

void consultaCalificaciones (Curso &c)
{
    int cod;
    int pos;
    int i;
    float sumaParciales;
    float sumaEntregables;
    float  notaFinal;

    system("cls");

    printf("\n\t\t\tLISTADO DE LAS ASIGNATURAS\n");
    printf("\t------------------------------------------------------------------\n\n");

    printf("\tIntroduzca el codigo de la asignatura: \n\t");
    scanf("%d", &cod);

    pos=busqueda(c,cod);

    if (pos==-1)
        printf("\tEl codigo no existe.\n\t");
    else{
        printf("\tLas notas de los parciales son: \n");

        for(i=0;i<=c.lista[pos].notas.parciales.num-1;i++)
            printf("\tLa nota del parcial %d es: %.2f\n\n", i+1,c.lista[pos].notas.parciales.datos[i]);
            printf("\tLas notas de los entregables son: \n");

        for(i=0;i<=c.lista[pos].notas.entregables.num-1;i++)
            printf("\tLa nota del entregable %d es: %.2f\n\n", i+1,c.lista[pos].notas.entregables.datos[i]);

        system("pause");

        sumaParciales=0;

        for(i=0;i<=c.lista[pos].notas.parciales.num-1;i++)
            sumaParciales=sumaParciales+c.lista[pos].notas.parciales.datos[i];

        for(i=0;i<=c.lista[pos].notas.entregables.num-1;i++)
            sumaEntregables=sumaEntregables+c.lista[pos].notas.entregables.datos[i];

        notaFinal=(sumaParciales/c.lista[pos].notas.parciales.num)*c.lista[pos].peso[0]/100+(sumaEntregables/c.lista[pos].notas.entregables.num)*c.lista[pos].peso[1]/100;


        printf("\tLos pesos de los parciales y entregables son respectivamente: %d y %d", c.lista[pos].peso[0], c.lista[pos].peso[1]);
        printf("\n\tLa nota final es: %.2f\n\t", notaFinal);}


        system("pause");
}
