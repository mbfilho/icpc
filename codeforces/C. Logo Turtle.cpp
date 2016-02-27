#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
typedef long long ll;
#define mp make_pair
#define pb push_back

char ins[ 110 ];
int total;
int memo[ 110 ][ 55 ][ 2 ][ 400 ];
bool dist[ 110 ];

void rec( int ind, int qtd, int dir, int x ){
	if( !ins[ ind ] && !qtd ) dist[ abs( x ) ] = true;
	if( !ins[ ind ] ) return;
	
	int aux = 0;
	if( dir < 0 ) aux = 1;
	if( memo[ ind ][ qtd ][ aux ][ 110 + x ] ) return;	
	memo[ ind ][ qtd ][ aux ][ 110 + x ] = true;

	bool turn = ( ins[ ind ] == 'T' );
		
	for( int k = 0; k <= qtd; ++k ){
		if( !turn ){
			rec( ind + 1, qtd - k, dir, x + dir * 1 );
		}else
			rec( ind + 1, qtd - k, -dir, x );
		turn = !turn;
	}
}

int main(){
	scanf( "%s %d", ins, &total );
	memset( memo, false, sizeof memo );
	memset( dist, false, sizeof dist );
	rec( 0, total, 1, 0 );
	
	int tmp = 0;
	for( tmp = 110; tmp >= 0; --tmp ){
		if( dist[ tmp ] ) break;
	}
	printf( "%d\n", tmp );
}


