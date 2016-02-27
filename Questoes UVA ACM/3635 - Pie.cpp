#include <cstdio>
#include <algorithm>
#include <list>
#include <vector>
#include <cmath>
using namespace std;
const double pi = 4 * atan(1);

int f, t;
double menor;
double vol[ 10003];
int tortas[ 10003 ];

int cont( double arg ){
    int ret = 0;

    for( int i = 0; i < t; ++i ){
        ret += int( vol[ i ] / arg );
    }

    return ret;
}

double busca(){
    double ini = 0.0001, fim = pi * 100000001, resp = -5000;
    int qtd;

    while( ini <= fim ){
        double meio = ( ini + fim ) / 2;
        qtd = cont( meio );

     //   printf( "%lf %d\n", meio, qtd );
        if( qtd >= f + 1 ){
            resp = meio;
            ini = meio + 0.0001;
        }else
            fim = meio - 0.0001;
    }

    return resp;
}

int main(){

    int casos;
    scanf( "%d", &casos );

    while( casos-- ){
        scanf( "%d %d", &t, &f );
        menor = 999999999.0;

        for( int i = 0; i < t; ++i ){
            scanf( "%d", tortas + i );
            vol[ i ] = pi * tortas[ i ] * tortas[ i ];
        }


        printf( "%.4lf\n", busca() );
    }
}
