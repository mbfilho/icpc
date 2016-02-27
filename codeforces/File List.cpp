#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <cmath>
#include <queue>
using namespace std;
typedef unsigned long long hash;
typedef long long ll;
typedef pair<int,int> Ponto;
#define mp make_pair
#define X first
#define Y second
#define pb push_back
#define M 500000

char s[M];
int len;
vector<Ponto> lista;


int main(){
	scanf( "%s", s );
	len = strlen(s);
	
	int prt = 0;
	int ini = 0, fim = 0;
	bool dm = false;
	
	while(ini < len){
		fim = ini;
//		printf( "%d\n", ini );
		while(fim < len && s[fim] != '.') ++fim;
		if(s[fim] != '.' || fim - ini > 8 || fim - ini < 1){
			dm = true;
//			printf( "Aki[%d %d %d]\n", s[fim] != '.', fim - ini > 8, fim - ini < 1);
//			printf( "%d\n", lista.size());
			break;
		}
		
		for( prt = fim + 1; prt < len && s[prt] != '.'; ++prt );
		int left = 1;
		if(s[prt] != '.') left = 0;
		
		int qtd = min( (prt - fim - 1) - left, 3 );
		if( qtd < 1 ){
			dm = true;
//			printf( "Ake\n");
			break;
		}
		
		lista.pb( mp(ini, fim + qtd + 1) );
//		printf( ">>> %d %d\n", ini, fim + qtd + 1);
		ini = fim + qtd + 1;
	}
	
	if(dm) printf("NO\n");
	else{
		printf("YES\n");
		
		for( int i = 0; i < lista.size(); ++i ){
			char ch = 0;
			swap(ch, s[lista[i].Y]);
			printf( "%s\n", s + lista[i].X );
			swap(ch, s[lista[i].Y]);
		}
	}
	
	
}

