#include <bits/stdc++.h>
using namespace std;

    int main (){
        ///
        /// github https://gist.github.com/Briaares/17b99d969b569c5c4242
        /// N es la cantidad de secuencia.
        /// M seria 0 si es una secuencia saltarina
        /// y si no es la secuencia saltarina
        /// m seria el numero menor que no cumple la condicion
        /// para ser la secuencia slatarina.
        /// USO es un ayudante
        /// J y I son iteradores
        ///
        ///

        int n,m=0,uso,j,i;

        cin>>n; /// Recibe la cantidad de la secuencia.

        int v[n],v2[n],v3[n]; /// int array de n cantidad.

        ///
        /// v tendra la secuencia
        /// v2 tendra los valores absolutos de las diferencias
        /// entre elementos sucesivos.
        /// v3 tendra los valores que debe tener como los valores de
        /// las diferencias, para ser la secuencia saltarina.
        ///

        for(i=1,uso=1;i<=n;i++){ /// inicia i y uso a 1; no usa 0. Y repite n veces.
            cin>>v[i];
            if(i>1){

                // assigna la diferencia entre los valores sucesivos
                // despues de calcular el numero mayor y menor entre dos numeros.
                v2[uso]=max(v[i],v[i-1])-min(v[i],v[i-1]);
                uso++;
            }

            // repite 1 a n
            if(i<n){
                // assigna todos los valores para la condicion
                v3[i]=i;
            }
        }

        // mueve v3
        for(i=1;i<n;i++){

            uso=0;

            // mu4eve v2, repite hasta encontrar un numero igual en v3(la condicion)
            for(j=1;j<n;j++){


                if(v3[i]==v2[j]){
                    uso++;
                }
            }

            // si es 0, quire decir que no encontro
            if(uso==0){
                m=v3[i];
                i=n;
            }
        }
        cout << m << "";
    }
