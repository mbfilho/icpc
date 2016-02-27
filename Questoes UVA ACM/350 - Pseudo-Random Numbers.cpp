#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <iostream>
using namespace std;
typedef long long ll;

int z, i, m, l;

int main(){
	int caso = 1, cont;
	set<int> seq;

	while( scanf( "%d %d %d %d", &z, &i, &m, &l ) && ( z | i | m | l ) ){
		seq.clear();
		cont = 0;
		l = l % m;
		
		while( true ){
			ll aux = ( ll( z * l ) + i ) % m;
			if( seq.find( aux ) == seq.end() ){
				++cont;
				l = aux;
				seq.insert( aux );
			}else
				break;
		}
					
		printf( "Case %d: %d\n", caso++, cont );
	}
}

