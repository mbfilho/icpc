#include <cstdio>
#include <algorithm>
#include <list>
#include <vector>
#include <cmath>
using namespace std;

int ma[ 15 ][ 15 ], par[ 15 ][ 15 ], mud[ 15 ][ 15 ];
int n;

int change( int mask ){
    int pot = 1;

    for( int i = 0; i < n; ++i ){
        if( mask & pot )
            mud[ 0 ][ i ] = 1;
        else
            mud[ 0 ][ i ] = 0;
        pot *= 2;
    }

    for( int i = 0; i < n; ++i ){
        par[ 0 ][ i ] = 0;
        if( i && mud[ 0 ][ i - 1 ] == 1 )
            ++par[ 0 ][ i ];
        if( i < n - 1 && mud[ 0 ][ i + 1 ] == 1 )
            ++par[ 0 ][ i ];
    }

    int temp;
    for( int i = 1; i < n; ++i ){
        for( int j = 0; j < n; ++j ){
            temp = par[ i - 1 ][ j ] % 2;
            par[ i ][ j ] = 0;
            if( mud[ i - 1 ][ j ] == 1 ) ++par[ i ][ j ];
            if( j && mud[ i ][ j - 1 ] == 1 ) ++par[ i ][ j ];

            if( temp == 0 ){
                mud[ i ][ j ] = 0;
            }else{
                mud[ i ][ j ] = 1;

                if( j )
                    ++par[ i ][ j - 1 ];
            }
        }
    }

    int qtd = 0;
    for( int i = 0; i < n; ++i ){
        for( int j = 0; j < n; ++j ){
            if( ma[ i ][ j ] != mud[ i ][ j ] ){
                if( ma[ i ][ j ] == 1 ) return 0x7fffffff;
                ++qtd;
            }
        }

    }

    return qtd;
}

int main(){
    int casos;
    scanf( "%d", &casos );

    for( int c = 1; c <= casos; ++c ){
        scanf( "%d", &n );
        for( int i = 0; i < n; ++i ){
            for( int j = 0; j < n; ++j )
                scanf( "%d", &ma[ i ][ j ] );
        }

        int menor = 0x7fffffff;
        for( int mask = 0; mask < ( 1 << n ); ++mask ){
          //  if( mask == 2 ) printf( "A: %d\n", change( mask ) );

            menor = min( menor, change( mask ) );
            if( menor == 0 ) break;
        }

        printf( "Case %d: ", c );
        if( menor == 0x7fffffff )
            printf( "-1\n" );
        else
            printf( "%d\n", menor );
    }
}


