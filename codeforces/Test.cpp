#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
typedef unsigned long long ll;

const ll BASE = 31;
ll pot[200001];

int minimo( int a, int b ){
	if( a < b )
		return a;
	return b;
}

void preencher(){
	pot[ 0 ] = 1;
	
	for( int i = 1; i <= 100000; ++i ){
		pot[ i ] = ( pot[ i - 1 ] * BASE ); 		
	}

}

string calc( string& s1, string& s2 ){
	if( s1 == "" )
		return s2;
	if( s2 == "" )
		return s1;
	
	int temp = 0;
	ll h1 = 0, h2 = 0;
	
	int prt = s1.size() - 1;
	const int lim = minimo( s1.size(), s2.size() );
	for( int i = 0; i < lim; ++i ){
		h2 = ( h2 * BASE + s2[ i ] );
		h1 = ( h1 + s1[ prt ] * pot[ i ] );

		if( h2 == h1 )
			temp = i + 1;
		--prt;
	}
	
	return ( s1 + s2.substr( temp ) );
}

bool encontrar( string& a, string& b ){
	if( a.size() == 0 || b.size() == 0 )
		return false;
	if( b.size() > a.size() )
		return false;
		
	ll hb = 0, ha = 0;
	int tam = b.size();

	for( int i = 0; i < tam; ++i ){
		hb = hb * BASE + b[ i ];
		ha = ha * BASE + a[ i ];
	}
	
	if( ha == hb )
		return true;

	ll ex = pot[ tam - 1 ];
		
	for( int i = tam; i < a.size(); ++i ){
		ha = ha - ( a[ i - tam ] ) * ex;
		ha = ha * BASE;
		ha = ha + a[ i ];
		
		if( ha == hb )
			return true;
	}
	
	return false;
	
}

int main(){
	string s[ 3 ], temp;
	int melhor = 0x7fffffff;
	int indices[] = { 0, 1, 2 };

	preencher();
	
	getline( cin, s[ 0 ] );
	getline( cin, s[ 1 ] );
	getline( cin, s[ 2 ] );
		
	if( encontrar( s[ 0 ], s[ 2 ] ) )
		s[ 2 ] = "";
	if( encontrar( s[ 2 ], s[ 0 ] ) )
		s[ 0 ] = "";
		
	if( encontrar( s[ 0 ], s[ 1 ] ) )
		s[ 1 ] = "";
	if( encontrar( s[ 1 ], s[ 0 ] ) )
		s[ 0 ] = "";
		
	if( encontrar( s[ 1 ], s[ 2 ] ) )
		s[ 2 ] = "";
	if( encontrar( s[ 2 ], s[ 1 ] ) )
		s[ 1 ] = "";
	
	
	do{
		temp = calc( s[ indices[ 0 ] ], s[ indices[ 1 ] ] );
		if( temp.size() > melhor )
			continue;
		temp = calc( temp, s[ indices[ 2 ] ] );

		if( temp.size() < melhor )
			melhor = temp.size();
	}while( next_permutation( indices, indices + 3 ) );
	
	cout << melhor << endl;
}


