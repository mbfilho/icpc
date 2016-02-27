#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <list>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;

typedef long long ll;

#define lowbit(a) (a & (-a))
#define maxi 1000015
struct par{
	int id;
	ll val;
	
	bool operator<( const par& a ) const{
		return val < a.val;
	}
}a[ maxi ];

int cont;
ll tree1[ maxi ], tree2[ maxi ];

ll pares( int id ){
	ll soma = 0;
	
	while( id > 0 ){
		soma += tree1[ id ];
		id -= lowbit( id );
	}
	
	return soma;
}

ll triplas( int id ){
	ll soma = 0;
	
	while( id > 0 ){
		soma += tree2[ id ];
		id -= lowbit( id );
	}
	
	return soma;
}

void change( ll *ar, int id, ll val ){
	while( id <= cont ){
		ar[ id ] += val;
		id += lowbit( id );
	}
}

int main(){

	scanf( "%d", &cont );
//	fill( tree1, tree1 + cont + 1, 0 );
//	fill( tree2, tree2 + cont + 1, 0 );
	
	for( int i = 1; i <= cont; ++i ){
		cin >> a[ i ].val;
		a[ i ].id = i;
	}
	
	sort( a + 1, a + cont + 1 );
	
	ll par, tri;
	ll resp = 0;
	for( int i = cont; i > 0; --i ){
		par = pares( a[ i ].id );
		change( tree1, a[ i ].id, 1 );
		
		tri = triplas( a[ i ].id );
		change( tree2, a[ i ].id, par );
		
		resp += tri;
	}
	
	cout << resp << endl;
}
