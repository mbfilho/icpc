#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
typedef long long ll;
#define pb push_back

vector<ll> seq[12];

void faz(){
	seq[1].pb(0); seq[1].pb(1); seq[1].pb(2);
	
	ll passo = 3;
	for( int i = 2; i <= 11; ++i ){
		
		for( int j = 0; j < 3; ++j ){
			for( int k = 0; k < seq[i-1].size(); ++k )
				seq[i].pb( seq[i-1][k] );
		}
		
		int ini = 0, mid = 1, fim = 2;
		
		for( int j = 0; j < seq[i-1].size(); ++j ){
			seq[i][j] = seq[i][j] * 3 + ini;
			seq[i][j+passo] = seq[i][j+passo] * 3 + mid;
			seq[i][j+2*passo] = seq[i][j+2*passo] * 3 + fim;
			
			ini++; ini%=3;
			mid++; mid%=3;
			fim++; fim%=3;
		}
		
		passo *= 3;
	}
}

void print( ll num, int tam ){
	char buf[tam+10];
	
	for( int i = 0; i < tam; ++i ){
		buf[i] = num % 3 + '0';
		num /= 3;
	}
	buf[tam] = 0;
	
	printf( "%s\n", buf );
}

int main(){
	faz();
	
	#ifndef X
	freopen( "antigray.in", "r", stdin );
	freopen( "antigray.out", "w", stdout );
	#endif
	
	int t;
	scanf( "%d", &t );
	for( int i = 0; i < seq[t].size(); ++i ){
		print( seq[t][i], t );
	}
	
}


