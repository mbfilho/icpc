#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 200000
#define EPS 1e-8

struct No{
	int v, m, id;
	
	bool operator<( const No& a ) const{
		if( m != a.m )
			return m < a.m;
		return v < a.v;
	}
}nos[N];

int n, k, h;
int at[N], melhor[N];

bool pode(double tempo){
	int prt = 0;
	
	for( int i = 1;i <= k; ++i ){
		while( prt < n && ((double(i) * double(h)) / double(nos[prt].v)) > tempo ) ++prt;
		if(prt == n) return false;
		at[i] = nos[prt++].id;
	}
	return true;
}

int main(){
	scanf( "%d %d %d", &n, &k, &h );
	
	for( int i = 0; i < n; ++i )
		scanf( "%d", &nos[i].m );
		
	for( int i = 0; i < n; ++i ){
		scanf( "%d", &nos[i].v );
		nos[i].id = i + 1;
	}
	
	sort( nos, nos + n );
	double ini = 0, fim = 1e12;
	
	for( int i = 0; i < 300; ++i ){
		double meio = (ini+fim) / 2;
		
		if(pode(meio)){
//			printf( ">>> %lf\n", meio );
			for( int i = 0; i <= k; ++i ) melhor[i] = at[i];
			fim = meio;
		}else
			ini = meio;
	}
	
	printf( "%d", melhor[1]);
	for( int i = 2; i <= k; ++i ) 
		printf( " %d", melhor[i]);
	printf( "\n" );
	
	
	
	
}

