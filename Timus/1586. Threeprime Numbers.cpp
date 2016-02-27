#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <string>
#include <iostream>
using namespace std;
typedef long long ll;

const ll mod = (1000000000 + 9);

bool crivo[ 2000 ];
int cont, n;

ll pd[ 10001 ][ 10 ][ 10 ];
int primos[ 200 ];

int gerar(){
    fill( crivo, crivo + 1001, true );

    for( int i = 4; i < 1000; i += 2 )
        crivo[ i ] = false;

    for( int i = 3; i * i < 1000; i += 2 ){
        if( crivo[ i ] == false ) continue;
        for( int j = i * i; j < 1000; j += 2 * i )
            crivo[ j ] = false;
    }

    cont = 0;
    for( int i = 101; i < 1000; i += 2 ){
        if( crivo[ i ] ){
            primos[ cont++ ] = i;
        }
    }

    return cont;
}

bool bs( int val ){
    int ini = 0, fim = cont - 1, meio;

    while( ini <= fim ){
        meio = ( ini + fim ) / 2;
        if( primos[ meio ] == val ) return true;

        if( primos[ meio ] > val )
            fim = meio - 1;
        else
            ini = meio + 1;
    }

    return false;
}

int contar( int pos, int x2, int x1 ){
    if( pos == 0 ) return 1;

    ll &ret = pd[ pos ][ x2 ][ x1 ];
    if( ret != -1 ) return ret;

    int num;
    ret = 0;
    for( int i = 0; i < 10; ++i ){
        num = x2 * 100 + x1 * 10 + i;
        if( bs( num ) )
            ret = ( ret + contar( pos - 1, x1, i ) ) % mod;
    }

    return ret;
}

int main(){
    gerar();

    for( int i = 1; i <= 10000; ++i ){
        for( int j = 0; j < 10; ++j ){
            for( int k = 0; k < 10; ++k ){
                pd[ i ][ j ][ k ] = -1;
            }
        }
    }

    while( scanf( "%d", &n ) != EOF ){
        ll cont = 0;
        for( int i = 1; i < 10; ++i ){
            for( int j = 0; j < 10; ++j )
                cont = ( cont + contar( n - 2, i, j ) ) % mod;
        }
        printf( "%lld\n", cont );
    }
}
