#include <cstdio>
#include <cstdlib>

int main(){
    int lados, soma;
       
    scanf( "%d", &lados );
    
    while( lados != 0 ){
           
           if( lados == 1 )
               printf( "%d\n", 1 );
           else{
              soma = lados * lados + 1;
           
             int sub;
             for( sub = 2; sub < lados; ++sub )
                     soma += ((lados - sub + 1) * (lados - sub + 1));
           
             printf( "%d\n", soma );
           
           }

           scanf( "%d", &lados ); 
           
    }
    
}

