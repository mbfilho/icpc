#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;
#define mp make_pair
#define N 200000

struct No{
	int x, y, z;	
	
	bool operator<( const No& c ) const{
		return z < c.z;
	}
}nos[ N ];

set< pair<int,int> > conj;
int n;

int main(){
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d", &n );
		for( int i = 0; i < n; ++i ) scanf( "%d %d %d", &nos[ i ].x, &nos[ i ].y, &nos[ i ].z );
		
		sort( nos, nos + n );
		conj.clear();
	
		int resp = 1;
		conj.insert( mp( nos[0].x, nos[0].y ) );
		pair<int,int> p;
		set< pair<int,int> >::iterator it;
		vector< pair<int,int> > temp;
		
		for( int i = 1; i < n; ++i ){
			p.first = nos[ i ].x;
			p.second = nos[ i ].y;
		
			it = conj.lower_bound( p );
		
			if( it != conj.begin() && p.second > (*(--it)).second ) continue;
			temp.clear();
			++resp;
		
			for( it = conj.lower_bound( p ); it != conj.end(); ++it ){
				if( (*it).second > p.second ) temp.push_back( *it );
				else break;
			}
			
			for( int i = 0; i < temp.size(); ++i )
				conj.erase( conj.find( temp[i] ) );
				
			conj.insert( p );
		}	
	
		printf( "%d\n", resp );
	}
}

