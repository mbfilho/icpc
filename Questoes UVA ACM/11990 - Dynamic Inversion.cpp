#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <vector>
using namespace std;
typedef long long ll;
#define N 200100
#define SQ 500

int n, m;
int input[N];
int mapa[N];

struct No{
	int dir, esq;
	vector<int> ord;
	vector<int> bit;
}nos[2*N];
int prt;

void update( vector<int>& bit, int ind, int val ){
	for( int i = ind; i < bit.size(); i += i & -i )
		bit[i] += val;
}

int soma( vector<int>& bit, int ind ){
	int ret = 0;
	
	for( int i = ind; i > 0; i -= i & -i )
		ret += bit[i];
		
	return ret;
}

void update( int* bit, int ind, int val ){
	for( int i = ind; i <= n; i += i & -i )
		bit[i] += val;
}

int soma( int* bit, int ind ){
	int ret = 0;
	
	for( int i = ind; i > 0; i -= i & -i )
		ret += bit[i];
		
	return ret;
}

int build( int no, int ini, int fim ){
	if( ini == fim ){
		nos[no].dir = nos[no].esq = -1;
		nos[no].ord.resize(1);
		nos[no].bit.resize(2);
		nos[no].bit[1] = 1;
		nos[no].ord[0] = input[ini];
	}else{
		int meio = ( ini + fim ) / 2;
		nos[no].esq = build( prt++, ini, meio );
		nos[no].dir = build( prt++, meio + 1, fim );
		nos[no].ord.resize( fim - ini + 1 );
		nos[no].bit.resize( fim - ini + 2 );
		fill( nos[no].bit.begin(), nos[no].bit.end(), 0 );
		
		for( int i = 0; i < fim - ini + 1; ++i )
			update( nos[no].bit, i + 1, 1 );
		
		int esq = nos[no].esq, dir = nos[no].dir;
		merge( nos[esq].ord.begin(), nos[esq].ord.end(), nos[dir].ord.begin(), nos[dir].ord.end(), nos[no].ord.begin() );
	}

	return no;
}

int lower( vector<int>& ord, int ini, int fim, int val ){
	int meio, resp = fim + 1;
	//O primeiro maior
	
	while( ini <= fim ){
		meio = ( ini + fim ) / 2;
		if( ord[meio] >= val ){
			resp = meio;
			fim = meio - 1;
		}else
			ini = meio + 1;
	}
	
	return resp;
}

int menores( int no, int ini, int fim, int x, int y, int val ){
	if( x > fim || y < ini ) return 0;
	
	if( x <= ini && y >= fim ){
		int tmp = lower( nos[no].ord, 0, nos[no].ord.size() - 1, val );
		
		return soma( nos[no].bit, tmp - 1 + (1) );
	}else{
		int meio = ( ini + fim ) / 2;
		
		int ret = 0, esq = nos[no].esq, dir = nos[no].dir;
		if( ~esq ) ret = menores( esq, ini, meio, x, y, val );
		if( ~dir ) ret += menores( dir, meio + 1, fim, x, y, val );
		
		return ret;
	}
}

int maiores( int no, int ini, int fim, int x, int y, int val ){
	if( x > fim || y < ini ) return 0;

	if( x <= ini && y >= fim ){
		int tmp = lower( nos[no].ord, 0, nos[no].ord.size() - 1, val );
		return soma( nos[no].bit, nos[no].bit.size() - 1 ) - soma( nos[no].bit, tmp - 1 + (1) );
	}else{
		int meio = ( ini + fim ) / 2;
		int ret = 0, esq = nos[no].esq, dir = nos[no].dir;
		if( ~esq ) ret = maiores( esq, ini, meio, x, y, val );
		if( ~dir ) ret += maiores( dir, meio + 1, fim, x, y, val );
		
		return ret;
	}
}

void excluir( int no, int ini, int fim, int val ){
	int tmp = lower( nos[no].ord, 0, nos[no].ord.size() - 1, val );
	update( nos[no].bit, 1 + tmp, -1 );
	assert( nos[no].ord[tmp] == val );
	
	if( ini != fim ){
		int meio = ( ini + fim ) / 2;
		if( mapa[val] >= ini && mapa[val] <= meio ) excluir( nos[no].esq, ini, meio, val );
		else excluir( nos[no].dir, meio + 1, fim, val );
	}
}

int getInt(){
	int ret = 0;
	char ch;
	
	while(1){
		ch = getchar_unlocked();
		if( ch >= '0' && ch <= '9' ) break;
	}
	
	do{
		ret = ret * 10 + ch - '0';
		ch = getchar_unlocked();
	}while( ch >= '0' && ch <= '9' );
	
	return ret;
}

int bit[N];
ll total;
int main(){
	while( scanf( "%d %d", &n, &m ) != EOF ){
		for( int i = 0; i < n; ++i ){
			input[i] = getInt();
			mapa[input[i]] = i;
		}
		
		total = 0;
		for( int i = 0; i <= n; ++i ) bit[i] = 0;

		for( int i = n - 1; i >= 0; --i ){
			total += soma( bit, input[i] );
			update( bit, input[i], 1 );
		}		
		
		prt = 0;
		int root = build( prt++, 0, n - 1 );
		
		while( m-- ){
			int aux;
			aux = getInt();
			printf( "%lld\n", total );
			
			int men = menores( root, 0, n - 1, mapa[aux] + 1, n - 1, aux );
			int mai = maiores( root, 0, n - 1, 0, mapa[aux] - 1, aux );
			total -= men + mai;
			excluir( root, 0, n - 1, aux );
		}
	}
}
	
