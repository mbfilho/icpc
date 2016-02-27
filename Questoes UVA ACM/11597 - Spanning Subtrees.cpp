#include <cstdio>

int main(){
    int caso = 0, temp;
    int array[ 401 ];
    
    for( int i = 2; i <= 400; i += 2 )
         *( array + i ) = (i >> 1);   
         
    scanf( "%d", &temp );
    while( temp ){
           printf( "Case %d: %d\n", ++caso, array[ temp ] );
           scanf( "%d", &temp );
    }
}
