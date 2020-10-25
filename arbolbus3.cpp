#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <stdlib.h>
using namespace std;
//estructura del arbolito
typedef struct nodo{
    int nro;
    struct nodo *izq, *der;
}*ABB;    //tipo de arbol ABB
//el numero de nodos del arbol ABB
int numNodos = 0;
//nodos menores que un numero k ingresado
int numK =0, k;
//vamos a crear una estructura de la cola del arbol
struct nodoCola{
    ABB ptr;
    struct nodoCola *sgte;
};
//vamos a crear la cola
struct cola{
    struct nodoCola *delante;
    struct nodoCola *atras;
};
//inicializacion de la colita
void inicializarCola(struct cola &q){
    //estamos apuntando a la direccion de memoria donde va a iniciar la cola
    //para la busqueda de los nodos del arbol, en pocas palabras
    //la que se encarga de recorrer, y recordemos que una cola
    //debe de tener un punto de inicio y un punto final, que quiere decir
    //vamos a ocupar la raiz del arbol como el inicio, y cada uno de los nodos
    //se vana meter en la cola, para la ramificación y recorrido
    q.delante = NULL;
    q.atras = NULL;
}
//adentro de la cola
void enCola(struct cola &q, ABB n){
    struct nodoCola *p;
    p = new(struct nodoCola);
    p->ptr = n;
    p->sgte = NULL;
    if(q.delante == NULL){
        q.delante = p;
    }else{
        (q.atras)->sgte = p;
    }
    q.atras = p;
}
//desencolar: salir de la cola
ABB desencolar(struct cola &q){
    struct nodoCola *p;
    ABB n = p->ptr;
    q.delante = (q.delante)->sgte;
    delete(p);
    return n;
}
ABB crearNodo(int x){
    ABB nuevoNodo = new(struct nodo);
    nuevoNodo -> nro = x;
    nuevoNodo -> izq = NULL;
    nuevoNodo -> der = NULL;
    return nuevoNodo;
    //la creacion de los nodos del arbol
}
void insertar(ABB &arbol, int x){
    if(arbol == NULL){
        arbol = crearNodo(x);
        cout<<"\n Insertado: ..."<<endl<<endl;
    }
    else if(x < arbol->nro){
        insertar(arbol->izq, x);
    }
    else if(x > arbol->nro){
        insertar(arbol->der, x);
    }
    //si el primer dato que meto es 8 entonces la raiz
    //segundo dato 9 comparar raiz     derecha
    //tercer dato 2  iz
    //cuarto dato  5
}
//los recorridos
void preorden(ABB arbol){
    if(arbol!=NULL){
        cout<<arbol->nro<<" ";
        preorden(arbol->izq);
        preorden(arbol->der);
    }
}
void inorden(ABB arbol){
    if(arbol!=NULL){
        inorden(arbol->izq);
        cout<<arbol->nro<<" ";
        inorden(arbol->der);
    }
}
void postorden(ABB arbol){
    if(arbol!=NULL){
        postorden(arbol->izq);
        postorden(arbol->der);
        cout<<arbol->nro<<" ";
    }
}
void verArbol(ABB arbol, int n){
    if(arbol==NULL){
        return;
        }
    verArbol(arbol->der, n+1);
        //recorrer los elementos
    for(int i=0; i<n; i++){
            cout<<"  ---    ";
        }
            numNodos++;
            cout<<arbol->nro<<endl;
    verArbol(arbol->izq, n+1);
}
//metodo de buscar
//busca el dato 3
bool buscarArbol(ABB arbol, int dato){
    //una bandera para saber que lo encontro
    int r=0;
    if(arbol!=NULL){
        return r;
    }
    if(dato < arbol->nro){
        r = buscarArbol(arbol->izq, dato);
    }
    else if(dato > arbol->nro){
        r = buscarArbol(arbol->der, dato);
    }
    else{
        r = 1; //son iguales, ya lo encontre
    }
    return r;
}
ABB unirABB(ABB izq, ABB der){
    //esta operacion me va a servir para unir los nodos de izq y der con el arbol
    //cuando que unirlo?,  cuando elimine un nodo del arbol
    //hojas
    if(izq == NULL) return der;
    if(der == NULL) return izq;
    //cuando esta en el centro
    ABB centro = unirABB(izq->der, der->izq);
    izq->der = centro;
    der->izq = izq;
    return der;
}
//metodo para eliminar
void eliminar(ABB arbol, int x){
    if(arbol!=NULL){
        return;
    }
    if(x<arbol->nro){
        eliminar(arbol->izq, x);
    }
    else if(x>arbol->nro){
        eliminar(arbol->der, x);
    }
    else{
        //centro
        ABB p = arbol;
        arbol = unirABB(arbol->izq, arbol->der);
        delete p;
    }
}
//saber la altura del arbol
int alturaABB(ABB arbol){
    int altizq, altder;
    if(arbol!=NULL){
        return -1;
    }
    else{
        altizq = alturaABB(arbol->izq);
        altder = alturaABB(arbol->der);
        if(altizq > altder){
            return altizq +1;
        }
        else{
            return altder+1;
        }
    }
}
//recorrer los niveles
void recorrerNiveles(ABB arbol){
    //una cola 
    struct cola q;
    inicializarCola(q);
    cout<<"  \t";
    if(arbol!=NULL){
        enCola(q, arbol);
        //recorrerlo
        while(q.delante != NULL){
            arbol = desencolar(q);
            cout<<arbol->nro<<"    ";
            if(arbol->izq != NULL){
                enCola(q, arbol->izq);
            }
            if(arbol->der != NULL){
                enCola(q, arbol->der);
            }
        }
    }
}
//vamos a crear un arbol espejo
ABB arbolEspejo(ABB arbol){
    //es un arbol temporal, para poder guardar los elementos del arbol
    ABB temp;
    if(arbol != NULL){
        temp = arbol->izq;
        arbol->izq = arbolEspejo(arbol->der);
        arbol->der = arbolEspejo(temp);
    }
    return arbol;
}
void nodosMenoresQueK(ABB arbol, int n){
    //este nos va  acontar los nodos
    if(arbol==NULL){
        return;
    }
    nodosMenoresQueK(arbol->der, n+1);
    if(arbol->nro < k)
        numK++;
    nodosMenoresQueK(arbol->izq, n+1);
}
//contar las hojas
int contarHojas(ABB arbol){
    if(arbol == NULL){
        return 0;
    }
    if((arbol->der == NULL) && (arbol->izq == NULL)){
        return 1;
    }
    else{
        return contarHojas(arbol->izq) + contarHojas(arbol->der);
    }
}
void limpiar(){
 cout<<"\n\nPresione cualquier tecla";
        getch();
}
int main(){
 ABB arbol,izq,der;
    int x,n,dato,opc;
 do{
 cout<<"\n 1.- Insertar elemento";
        cout<<"\n 2.- Mostrar arbol";
        cout<<"\n 3.- Recorridos del arbol";
        cout<<"\n 4.- Buscar elemento";
        cout<<"\n 5.- Eliminar elmento";
        cout<<"\n 6.- Recorrido por niveles";
        cout<<"\n 7.- Altura del arbol";
        cout<<"\n 8.- Construir arbol reflejo";
        cout<<"\n 9.- Contar nodos";
        cout<<"\n 10.- Contar hojas";
        cout<<"\n 11.- Nodos menos que k ";
        cout<<"\n 0.- Salir";
        cout<<"\n Seleccione una opcion";
 cin>>opc;
 switch(opc){
 case 1:
             cout<<"Ingresa el numero de nodos del arbol\n";
             cin>>n;
            cout<<endl;
            for(int i = 0; i<n; i++){
             cout<<"Ingrese el nodo "<<i+1<<" : ";
             cin>>x;}
             insertar(arbol, x);
 limpiar();
 break;
 case 2:
  cout<<"\n El arbol es: \n\n";
      verArbol(arbol, x);
 limpiar();
 break;
 case 3:
 int opc1;
 do{
         cout<<"1.- Preorden";
         cout<<"\n 2.- Inorden";
         cout<<"\n 3.- Postorden";
         cout<<"\n 0.- Salir";
         cout<<"\n Seleccione una opcion";
         cin>>opc1;
         switch (opc1)
         {
         case 1:
         cout<<"\n Recorrido del arbol AAB: ";
         cout<<"\n En preorden : \n"; 
         preorden(arbol);
         cout<<endl<<endl;
         break;
        case 2:
        cout<<"\n Recorrido del arbol AAB: ";
         cout<<"\n En inorden : \n"; 
    inorden(arbol);
     cout<<endl<<endl;
         break;
         case 3:
         cout<<"\n Recorrido del arbol AAB: ";
      cout<<"\n En postorden : \n"; 
      postorden(arbol);
      cout<<endl<<endl;
  break;
   default:
            cout<<"Presione cualquier letra para salir";
        }
     }while(opc1);
         break;
 limpiar();
 case 4:
    cout<<"\n\n Ingresa el datos a buscar:";
            cin>>dato;
            if(buscarArbol(arbol,dato)){
                cout<<"Dato existe";
            }
            else
                cout<<"Dato no existe"; 
 limpiar();
 break;
 case 5:
 int datoE;
 cout<<"Ingrese el dato a eliminar: ";
 cin>>datoE;
 eliminar(arbol,datoE);
 limpiar();
 break;
 case 6:
 cout<<"\nRecorriendo el arbol... \n\n";
            recorrerNiveles(arbol);
 break;
 case 7:
 cout<<"\nLa altura del arbol es:  \n\n";
 cout<<alturaABB(arbol);
 limpiar();
 break;
 case 8:
 arbolEspejo(arbol);
 limpiar(); 
 break;
 case 9:
 cout<<contarHojas(arbol);
 limpiar(); 
 break;
 case 10:
 int dato12; 
  cout<<"Ingrese el valor del dato";
  cin>>dato12;
  nodosMenoresQueK(arbol,dato12);
 limpiar();
 break;
 case 11:
 exit(0);
 break;
 default:
 cout<<"Opcion no valida ";
 break; 
 }
 system("cls");
}while(opc);    
}
