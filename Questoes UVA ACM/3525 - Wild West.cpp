#include <cstring>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <cassert>
using namespace std;
#define mp make_pair
typedef long long ll;
#define X first
#define Y second
#define N 100100

struct No{
	int x, y, z;
	
	bool operator<( const No& n ) const{
		if( z != n.z )
			return z < n.z;
		else if( x != n.x )
			return x < n.x;
		else
			return y < n.y;
	}
}nos[ N ];

set< pair<int,int> > conj;
int n, m;
ll area;

//A ideia é manter no set as bordas da area. 
//Quando um ponto for ser inserido, remove-se as areas dos pontos que serão cobertos por ele.
//Isso para poder atualizar a área que ele vai cobrir.
void calc( int x, int y ){
	pair<int,int> p = mp( x, y );
	set< pair<int,int> >::iterator it = conj.lower_bound( p );

	if( it != conj.end() && (*it).Y >= y ) return;
	
	//Apagar td mundo que eu vou cobrir
	while( !conj.empty() ){
		it = conj.lower_bound( p );
		if( it == conj.begin() ) break; // Nao vou cobrir ngm
		
		ll ly;
		if( it == conj.end() ) ly = 0;
		else ly = (*it).Y;
		
		--it;
		ll mx = (*it).X, my = (*it).Y;
		if( my > y ) break;
		
		if( it == conj.begin() ){
			area -= mx * ( my - ly );
		}else{
			--it;
			area -= ( mx - (*it).X ) * ( my - ly );
			++it;
		}
		
		conj.erase( it );	
	}
	
	it = conj.lower_bound( p );
	if( it != conj.end() && (*it).Y >= y ) return;
	ll ly;
	if( conj.empty() || it == conj.end() ){
		ly = 0;
	}else{
		ly = (*it).Y;
	}
	
	if( it == conj.begin() || conj.empty() )
		area += x * ( y - ly );
	else{
		--it;
		area += ( x - (*it).X ) * ( y - ly );
	}
	
	conj.insert( p );
}

int main(){
	while( scanf( "%d %d", &n, &m ) == 2 && ( n | m  ) ){
		conj.clear();

		area = 0;
		
		for( int i = 0; i < n; ++i )
			scanf( "%d %d %d", &nos[ i ].x, &nos[ i ].y, &nos[ i ].z );
			
		sort( nos, nos + n );
		
		ll resp = 0;
		int prt = n - 1;
		for( int line = m; line > 0; --line ){
			while( prt >= 0 && nos[ prt ].z == line ){
				calc( nos[ prt ].x, nos[ prt ].y );
				--prt;
			}
			resp += ll( m ) * ll( m )  - area;
		}
		
		printf( "%lld\n", resp );
	}
}




