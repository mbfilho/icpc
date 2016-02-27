#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

struct slot{
	int lin, col, dir;
	
	bool operator<( const slot& s ) const{
		if( lin != s.lin )
			return lin < s.lin;
		return col < s.col;
	}
}slots[ 200 ];

int ma[ 20 ][ 20 ], cont[ 20 ][ 20 ], n;
bool marc[ 200 ];
//ehSeta[ 20 ][ 20 ];
string words[ 200 ];

set<int> solutions;

void retirar( int lin, int col, int lini, int coli, int dir ){
	if( dir == 'D' ){
		for(; lin >= lini; --lin ){
			if( cont[ lin ][ coli ] == 1 )
				ma[ lin ][ coli ] = 0;
			--cont[ lin ][ coli ];
		}
	}else{
		for(; col >= coli; --col ){
			if( cont[ lini ][ col ] == 1 )
				ma[ lini ][ col ] = 0;
			--cont[ lini ][ col ];
		}
	}
}

bool inserir( string& pal, int lini, int coli, int dir ){
	int lin = lini, col = coli, tam = pal.size();
	
	if( dir == 'D' ){
		if( lini + tam - 1 > 10 ) return false;
		if( lini + tam <= 10 && ( ma[ lini + tam ][ coli ] > 0 ) ) return false;
		
		for( int i = 0; i < tam; ++i ){
			if( ma[ lin ][ coli ] == 0 || ( ma[ lin ][ coli ] == pal[ i ] ) ){
				ma[ lin ][ coli ] = pal[ i ];
				++cont[ lin ][ coli ];
				++lin;
			}else{
				retirar( lin - 1, coli, lini, coli, dir );
				return false;
			}
		}
		
	}else{
		if( coli + tam - 1 > 10 ) return false;
		if( coli + tam <= 10 && ( ma[ lini ][ coli + tam ] > 0 ) ) return false;
		
		for( int i = 0; i < tam; ++i ){
			if( ma[ lini ][ col ] == 0 || ( ma[ lini ][ col ] == pal[ i ] ) ){
				ma[ lini ][ col ] = pal[ i ];
				++cont[ lini ][ col ];
				++col;
			}else{
				retirar( lini, col - 1, lini, coli, dir );
				return false;
			}
		}
		
	}
	
	return true;
}

void rec( int s ){
	if( s == n ){
		for( int i = 0; i <= n; ++i ){
			if( marc[ i ] == false ){
				solutions.insert( i );
				return;
			}
		}
	}
	
	int antes, tam;
	for( int p = 0; p <= n; ++p ){
		if( marc[ p ] ) continue;
		if( inserir( words[ p ], slots[ s ].lin, slots[ s ].col, slots[ s ].dir ) ){
			tam = words[ p ].size();
			if( slots[ s ].dir == 'D' ){
				antes = ma[ slots[ s ].lin + tam ][ slots[ s ].col ];
				ma[ slots[ s ].lin + tam ][ slots[ s ].col ] = -1;
			}else{
				antes = ma[ slots[ s ].lin ][ slots[ s ].col + tam ];
				ma[ slots[ s ].lin ][ slots[ s ].col + tam ] = -1;
			}
			
			marc[ p ] = true;
			rec( s + 1 );
			marc[ p ] = false;
			if( slots[ s ].dir == 'D' ){
				retirar( slots[s].lin + tam - 1, slots[s].col, slots[s].lin, slots[s].col, slots[s].dir );
				ma[ slots[ s ].lin + tam ][ slots[ s ].col ] = antes;
			}else{
				ma[ slots[ s ].lin ][ slots[ s ].col + tam ] = antes;
				retirar( slots[s].lin, slots[s].col + words[p].size() - 1, slots[s].lin, slots[s].col, slots[s].dir );
			}
		}
	}
}

int main(){
	int trial = 1;
	
	while( scanf( "%d", &n ) && n ){
		for( int i = 0; i <= 10; ++i ){
			for( int j = 0; j <= 10; ++j )
				ma[ i ][ j ] = cont[ i ][ j ] = 0;
		}
		
		int a, b; 
		char dir;
		for( int i = 0; i < n; ++i ){
			scanf( "%d %d %c", &a, &b, &dir );
			if( dir == 'D' )
				ma[ a - 1 ][ b ] = -1;
			else
				ma[ a ][ b - 1 ] = -1;
		//	ehSeta[ a ][ b ] = true;
			slots[ i ].lin = a;
			slots[ i ].col = b;
			slots[ i ].dir = dir;
		}
		sort( slots, slots + n );
		
		for( int i = 0; i <= n; ++i )
			cin >> words[ i ];
		
		fill( marc, marc + n + 1, false );
		solutions.clear();
		rec( 0 );
		
		printf( "Trial %d:", trial++ );
		if( solutions.empty() )
			printf( " Impossible\n\n" );
		else{

			for( set<int>::iterator it = solutions.begin(); it != solutions.end(); ++it )
				cout << " " << words[ *it ];
			cout << endl << endl;
		}
	}
}

