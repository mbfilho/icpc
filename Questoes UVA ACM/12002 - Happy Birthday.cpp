#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 510
#define V 1010
#define oo 0x3f3f3f3f

//Cada pilha é especificada como um par (up,down). 
//Pense cada tamanho de sequencia como tendo uma lista
//de quais pilhas terminam com aquele tamanho.

//Para cada numero da entrada, ele pode aumentar
//uma sequencia sendo colocado como novo 'down' ou
//novo 'up'. Imagine que ele será o novo down. 
//Para cada tamanho só existe no máximo um par ótimo para ser
//aumentado: deve ter old_down <= down e, dentre esses,
//o maior up possível. Pra descobrir quem eh esse cara
//use uma bit (na idéia de um array que guarda o maximo
//acumulado da pos i até o final).
//Pensamento semelhante caso o numero seja posto no topo da pilha.

int seq[N];
int bits[N][2][V];

int query(int* bit, int idx){
	int maior = -oo;
	
	for(int i = idx; i > 0; i -= i & -i) maior = max(maior, bit[i]);
	return maior;
}

void update(int* bit, int idx, int v){
	for(int i = idx; i <= V; i += i & -i) bit[i] = max(bit[i], v);
}

int n;

int main(){
	while(scanf("%d", &n) == 1 && n){
		rep(i, n) scanf("%d", seq + i);
		int l = 0;
		
		rep(i, n+1) rep(k,2) rep(j, V) bits[i][k][j] = -oo;
		
		rep(i, n){
			for(int s = l - 1; s >= 0; --s){
				//update down
				int up = query(bits[s][0], seq[i]);
				if(up > -oo){
					if(s == l-1) ++l;
					update(bits[s+1][0], seq[i], up), update(bits[s+1][1], V - up, -seq[i]);
				}
				
				//update up
				int down = query(bits[s][1], V - seq[i]);
				if(down > -oo){
					if(s == l-1) ++l;
					update(bits[s+1][0], -down, seq[i]), update(bits[s+1][1], V-seq[i], down);
				}
			}
			
			if(!l) ++l;
			update(bits[0][0], seq[i], seq[i]), update(bits[0][1], V-seq[i], -seq[i]);
		}
		
		printf("%d\n", l);
	}
}

