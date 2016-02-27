#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

struct caixa{
	double b, h, w, d;
};
typedef struct caixa C;

struct pos{
	int p;
	char c;
};
typedef struct pos P;

C m[ 100 ];

double u, v;
bool comp( const P &a, const P &b ){
	if( a.c == 'c' )
		u = m[ a.p ].b;
	else
		u = m[ a.p ].b + m[ a.p ].h;
		
		
	if( b.c == 'c' )
		v = m[ b.p ].b;
	else
		v = m[ b.p ].b + m[ b.p ].h;	
		
		
	if( u <= v )
		return true;
	return false;
}



int main(){
	freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );
	
	int casos, q, k;
	double base, total, alt, s, v;
	P a[ 200 ];
	cin >> casos;
	for( int i=0; i<casos; i++ ){
		cin >> q;
		
		k = 0;
		for( int j=0; j<q; j++ ){
			cin >> m[j].b >> m[j].h >> m[j].w >> m[j].d;
			a[ k ].p = j;
			a[ k ].c = 'c';
			
			a[ k + 1 ].p = j;
			a[ k + 1 ].c = 't';
			
			k += 2;
		}
		cin >> total;
		sort( a, a + k, comp );
		bool over = true;
		
		base = m[ a[ 0 ].p ].w * m[ a[ 0 ].p ].d;
		alt = m[ a[ 0 ].p ].b;
		for( int j=1; j<k; j++ ){
			if( a[j].c == 'c' )
				s = m[ a[j].p ].b - alt;
			else if( a[j].c == 't' )
				s = m[ a[j].p ].b + m[ a[j].p ].h - alt;
			
			v = s * base;
			
			if( v >= total ){
				alt += total / base;
				over = false;
				break;
			}else{
				alt += s;
				if( a[j].c == 'c' )
					base += m[ a[j].p ].w * m[ a[j].p ].d;
				else if( a[j].c == 't' )
					base -= ( m[ a[j].p ].w * m[ a[j].p ].d );
					
				total -= v;
			}
		}
		
		if( over == false ){
			printf( "%.2lf\n", alt );
		}else
			cout << "OVERFLOW" << endl;
			
		if( i != casos - 1 )
			printf( "\n" );
	}	
}
