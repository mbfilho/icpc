#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
#include <queue>
using namespace std;
#define N 100100

char rmq[ N ][ 17 ];
char seq[ N ];
int n, d;


void calc(){
	for( int i = 0; i < n; ++i )
		rmq[ i ][ 0 ] = i;
	
	for( int xp = 1, t = 1; ( 1 << xp ) <= n; t *= 2, ++xp ){
		for( int i = 0; i + t < n; ++i ){
			if( seq[ rmq[i][xp-1] ] > seq[ rmq[i+t][xp-1] ] )
				rmq[i][xp] = rmq[i][xp-1];
			else if( seq[ rmq[i][xp-1] ] < seq[ rmq[i+t][xp-1] ] )
				rmq[i][xp] = rmq[i+t][xp-1]; 
			else
				rmq[i][xp] = min( rmq[i][xp-1], rmq[i+t][xp-1] );
		}
	}
}

int query( int a, int b ){
	int l = int( log( b - a + 1 ) );
	if( seq[ rmq[a][l] ] > seq[ rmq[1 + b - (1<<l)][l] ] )
		return rmq[a][l];
	else if( seq[ rmq[a][l] ] < seq[ rmq[1 + b - (1<<l)][l] ] )
		return rmq[1 + b - (1<<l)][l];
	else
		return min( rmq[a][l], rmq[1 + b - (1<<l)][l] );
}

int main(){

	while( scanf( "%d %d", &n, &d ) && n ){
		scanf( "%s", seq );
		priority_queue< pair<char,int> > heap;
		//calc();
		
		/*
		int ind = 0, fim = d;
		for( int i = 0; i < n - d; ++i ){
			ind = query( ind, fim );
			//resul[ i ] = seq[ ind ];
			printf( "%c", seq[ ind ] );
			++ind;
			++fim;
		}
		*/
		int qtd = 0, ini = 0, fim = d;
		for( int i = 0; i <= d; ++i ){
		//	printf( "Coloquei %c\n", seq[i] );
			heap.push( make_pair( seq[i], -i ) );
		}
			
		while( qtd < n - d ){
			while( -heap.top().second < ini )
				heap.pop();
			printf( "%c", heap.top().first );
			ini = -heap.top().second;
			heap.pop();
			++fim;
			heap.push( make_pair( seq[fim], -fim ) );
			++qtd;
			
		}
		printf( "\n" );		
	}
}




