#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define NH 200100
#define pb push_back
#define mp make_pair
#define altura second
#define pilares first
typedef long long ll;
vector<ll> alt;
//qtd, alt
pair<ll,ll> casa[ NH ];
int nh, np;
ll a, b, c, e, f, g, h, I, j;

void gerar(){
	alt.clear();
	alt.pb( c % 10000 + 1 );
	alt.pb( ( a * alt[ 0 ] + c ) % 10000 + 1 );
	
	for( int i = 2; i < np; ++i )
		alt.pb( ( a * alt[ i - 1 ] + b * alt[ i - 2 ] + c ) % 10000 + 1 );
	
	casa[ 0 ].altura = g % 10000 + 1;
	casa[ 0 ].pilares = j % 100000 + 1;
	
	for( int i = 1; i < nh; ++i ){
		casa[ i ].altura = ( e * casa[ i - 1 ].altura + f * casa[ i - 1 ].pilares + g ) % 10000 + 1;
		casa[ i ].pilares = ( h * casa[ i - 1 ].pilares + I * casa[ i - 1 ].altura + j ) % 100000 + 1;
	}
}


int bs( int num ){
	int ini = 0, fim = np - 1, resp = -1;
	
	while( ini <= fim ){
		int meio = ( ini + fim ) / 2;
		
		if( alt[ meio ] < num )
			ini = meio + 1;
		else{
			resp = meio;
			fim = meio - 1;
		}
	}
	
	return resp;
}

int contar(){		
	sort( alt.begin(), alt.end() );
	sort( casa, casa + nh );
	
	int cont = 0;
	for( int i = 0; np && i < nh; ++i ){
		int ind = bs( casa[ i ].altura );
		if( ind == -1 ) continue;
		if( np - ind < casa[ i ].pilares ) continue;
		++cont;
		alt.erase( alt.begin() + ind, alt.begin() + ind + casa[ i ].pilares );
		np -= casa[ i ].pilares;
	}
	
	return cont;
}

int main(){
	int casos;
	scanf( "%d", &casos );
	
	for( int caso = 1; caso <= casos; ++caso ){
		scanf( "%d %d", &np, &nh );
		scanf( "%lld %lld %lld %lld %lld %lld %lld %lld %lld", &a, &b, &c, &e, &f, &g, &h, &I, &j );
		
		gerar();
		printf( "Case %d: %d\n", caso, contar() );
	}
}



