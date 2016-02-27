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

struct Ponto{
    int x, y, id;

    Ponto( int a, int b ){
        x = a;
        y = b;
    }

    Ponto(){}

    int operator%( const Ponto& p ) const{
        return ( x * p.y - y * p.x );
    }

    Ponto operator-( const Ponto& p ) const{
        return Ponto( x - p.x, y - p.y );
    }

    int operator!() const{
        return ( x * x + y * y );
    }
}pivot;

bool comp( const Ponto& a, const  Ponto& b ){
    Ponto aa = a - pivot, bb = b - pivot;
    int prod = aa % bb;

    if( prod != 0 )
        return prod > 0;
    else
        return !aa < !bb;
}

Ponto pts[ 4000 ];
int n;


int main(){
    int casos;

    scanf( "%d",&casos );

    while( casos-- ){
        scanf( "%d", &n );

        for( int i = 0; i < n; ++i ){
            scanf( "%d %d", &pts[ i ].x, &pts[ i ].y );
            pts[ i ].id = i;
        }

        pivot = pts[ 0 ];
        int ind = 0;

        for( int i = 1; i < n; ++i ){
            if( pts[ i ].y < pivot.y ){
                pivot = pts[ i ];
                ind = i;
            }else if( pts[ i ].y == pivot.y && pts[ i ].x < pivot.x ){
                pivot = pts[ i ];
                ind = i;
            }
        }

        sort( pts, pts + n, comp );

        int k = n - 2;
        while( ( ( pts[ k ] - pivot ) % ( pts[ n - 1 ] - pivot ) ) == 0 ){
           // if( k == 0 ) cout << "dm" << endl;
            --k;
        }

        reverse( pts + k + 1, pts + n );

        printf( "%d", pts[ 0 ].id );
        for( int i = 1; i < n; ++i ){
            printf( " %d", pts[i].id );
        }

        printf( "\n" );
    }
}
