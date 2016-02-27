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
#define M 150000
#define TREE 1000000
#define oo 1000000000

int menor[TREE], op[TREE];
int cont;
int n;
int num[M];
vector<Ponto> lista;

int build(int no, int x, int y){
	op[no] = 0;
	
	if(x == y){
		menor[no] = num[x];
	}else{
		int meio = (x+y) / 2;
		int esq = no << 1, dir = esq | 1;
		build(esq, x, meio);
		build(dir, meio + 1, y);
		menor[no] = min(menor[esq], menor[dir] );
	}
	
	return no;
}

void ajeitar(int no){
	menor[no] -= op[no];
	int esq = no << 1, dir = esq | 1;
	op[esq] += op[no];
	op[dir] += op[no];
	op[no] = 0;
}

void dec(int no, int ini, int fim, int x, int y, int amount){
	ajeitar(no);
	if( y < ini || x > fim ) return;
	
	if( x <= ini && y >= fim ){
		op[no] += amount;
		ajeitar(no);
	}else{
		int meio = (ini+fim) /2;
		int esq = no << 1, dir = esq | 1;
		dec(esq, ini, meio, x, y, amount);
		dec(dir, meio+1, fim, x, y, amount);
		
		menor[no] = min( menor[esq], menor[dir] );
	}
}

int pilha[M], sp;
Ponto aux[M];

int get(int no, int ini, int fim, int x, int y){
	sp = 0;
	pilha[sp] = no;
	aux[sp].X = ini;
	aux[sp].Y = fim;
	++sp;
	int resp = oo;
	
	while(sp--){
		no = pilha[sp];
		ini = aux[sp].X;
		fim = aux[sp].Y;
		
		ajeitar(no);
		if(y < ini || x > fim ) continue;
		if(x <= ini && y >= fim){
			resp = min( resp, menor[no] );
		}else{
			int meio = (ini+fim)/2;
			pilha[sp] = no << 1;
			aux[sp].X = ini; aux[sp].Y = meio;
			++sp;
			
			pilha[sp] = (no << 1) | 1;
			aux[sp].X = meio + 1, aux[sp].Y = fim;
			++sp;
		}
	}
	return resp;
}

int main(){
	scanf( "%d", &n );
	for( int i = 0; i < n; ++i )
		scanf( "%d", num + i );
	cont = 0;
	int root = build(1, 0, n - 1);
	
	for( int i = 0; i < n; ++i ){
		int val = get(root, 0, n - 1, i, i );
		int fim = n - 1;
		while( val ){
			int ini = i + 1, best = i;
			while(ini <= fim){
				int meio = (ini+fim) / 2;
				if(get(root, 0, n - 1, i, meio )){
					best = meio;
					ini = meio + 1;
				}else
					fim = meio - 1;
			}
			fim = best;
			
			if(best == i){
				while(val){
					lista.pb( mp(i,i) );
					--val;
				}
				dec(root,0, n-1, i, i, val);
			}else{
				lista.pb(mp(i, best));
				dec(root, 0, n-1, i, best, 1);
				--val;
			}
		}			
	}
	
	printf( "%d\n", lista.size() );
	for( int i = 0; i < lista.size(); ++i ){
		printf( "%d %d\n", lista[i].X  + 1, lista[i].Y + 1 );
	}
	
}

