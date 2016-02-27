#include <cstdio>
#include <algorithm>
#include <list>
#include <vector>
using namespace std;
#define mp( x, y) make_pair( x, y )

struct No{
    vector< pair<int,int> > adj;
    int maior;
    bool mark;
}agpm[ 4000 ];


struct Aresta{
    int u, v, peso;

    bool operator<( const Aresta& a  ) const{
        return peso < a.peso;
    }
}ares[ 200000 ];

int n, m, rest;


int conj[ 4000 ];

int fila[ 4000 ], prt;

int find( int a ){
    if( a != conj[ a ] )
        return conj[ a ] = find( conj[ a ] );

    return conj[ a ];
}

void unir( int a, int b ){
    conj[ find( a ) ] = find( b );
}

void kruskal(){
    for( int i = 0; i <= n; ++i ){
        agpm[ i ].adj.clear();
    }

    for( int i = 1; i <= n; ++i )
        conj[ i ]= i;
    sort( ares, ares + m );


    rest = 0;
    for( int i = 0; i < m; ++i ){
        if( rest == n - 1 ) break;

        if( find( ares[ i ].v ) != find( ares[ i ].u ) ){
            unir( ares[ i ].u, ares[ i ].v );
            agpm[ ares[ i ].u ].adj.push_back( mp( ares[ i ].v, ares[ i ].peso ) );
            agpm[ ares[ i ].v ].adj.push_back( mp( ares[ i ].u, ares[ i ].peso ) );
            ++rest;
        }
    }
}


int busca( int ini, int fim ){
    for( int i = 0; i <= n; ++i ){
        agpm[ i ].mark = false;
        agpm[ i ].maior = 0;
    }

    prt = 1;
    fila[ 0 ] = ini;
    agpm[ ini ].mark = true;

    int temp, next;
    while( prt ){
        temp = fila[ --prt ];

        for( int i = agpm[ temp ].adj.size() - 1; i >= 0; --i ){
            next = agpm[ temp ].adj[ i ].first;
            if( agpm[ next ].mark ) continue;

            fila[ prt++ ] = next;
            agpm[ next ].mark = true;
            agpm[ next ].maior = max( agpm[ temp ].maior, agpm[ temp ].adj[ i ].second );
        }
    }

    return agpm[ fim ].maior;
}

int main(){
    int caso = 1, casos;

   scanf( "%d", &casos );
    while( casos-- ){
        scanf( "%d %d", &n, &m );
        int u, v, p;

        for( int i = 0; i < m; ++i ){
            scanf( "%d %d %d", &u, &v, &p );
            ares[ i ].u = u;
            ares[ i ].v = v;
            ares[ i ].peso = p;
        }

        kruskal();

        int q;
        scanf( "%d", &q );
        printf( "Case %d\n", caso++ );

        while( q-- ){
            scanf( "%d %d", &u, &v );
            printf( "%d\n", busca( u, v ) );
        }
        printf( "\n" );
    }


}

