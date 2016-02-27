#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
#define N 2000

int n[2], s[2][N];
int fim[2*N];
map<int,int> mapa;
int pd[N][N];

int faz(int i, int a, int b){
	if(~pd[a][b]) return pd[a][b];
	if(i == n[0] + n[1] && a == n[0] && b == n[1]) return true;
	
	int& resp = pd[a][b];
	
	resp = 0;
	if(a < n[0] && fim[i] == s[0][a]){
		resp = faz(i+1, a+1, b);
	}
	
	if(resp) return resp;
	
	if(b < n[1] && fim[i] == s[1][b]){
		resp = faz(i+1, a, b+1);
	}
	
	return resp;
}


int main(){
	while(scanf( "%d %d", n, n + 1) != EOF && (n[0] | n[1])){
		mapa.clear();
		int prt = 0;
		
		for(int k = 0; k < 2; ++k){
			for(int i = 0; i < n[k]; ++i){
				int tmp;
				scanf( "%d", &tmp );
				if(!mapa.count(tmp)) mapa[tmp] = prt++;
				s[k][i] = mapa[tmp];
			}
		}

		bool dm = false;
		for(int i = 0; i < n[0] + n[1]; ++i){
			int tmp;
			scanf( "%d", &tmp );
			if(!mapa.count(tmp)) dm = true;
			fim[i] = mapa[tmp];
		}

		if(dm) printf( "not possible\n");
		else{
			memset(pd, -1, sizeof pd);
			int resp = faz(0,0,0);
			if(resp) printf("possible\n");
			else printf("not possible\n");
		}
	}
}

