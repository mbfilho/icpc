#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define oo 0x7fffffff
#define X first
#define Y second
#define relax(no) (menor[no] = min( menor[no<<1], menor[(no<<1) | 1]))

priority_queue<int, vector<int>, greater<int> > filas[1001];
int mapa[1000100], seg[1000100];
int n, k;

int menor[10000];

int pilha[10000];
pair<int,int> inter[10000];



inline int query(int ini, int fim){
	int no = 1, x = 0, y = k, sp = 0;
	int resp = oo;
	
	pilha[sp++] = 1;
	
	while(sp--){
		no = pilha[sp];
		x = inter[no].X;
		y = inter[no].Y;

		if( ini > y || fim < x || menor[no] == oo) continue;
		
		if( ini <= x && fim >= y ){
			resp = min( resp, menor[no] );
		}else{
			pilha[sp++] = no<<1;
			pilha[sp++] = (no<<1)|1;
		}
	}
	return resp;
}

void build(){
	int no = 1, x = 0, y = k, sp = 0;
	pilha[sp++] = 1;
	inter[1].X = x;
	inter[1].Y = y;
	
	while(sp--){
		no = pilha[sp];
		menor[no] = oo;
		x = inter[no].X;
		y = inter[no].Y;
		if( x != y ){
			int meio = (x+y)>>1;
		
			inter[no<<1].X = x;
			inter[no<<1].Y = meio;
			pilha[sp++] = no<<1;
		
			inter[(no<<1)|1].X = meio+1;
			inter[(no<<1)|1].Y = y;
			pilha[sp++] = (no<<1)|1;
		}else{
			seg[x] = no;
		}
	}
}

bool getInt( int& x ){
	x = 0;
	char ch = getchar_unlocked();
	
	while( !(ch >= '0' && ch <= '9') ){
		if( ch == EOF ) return false;
		ch = getchar_unlocked();
	}
	
	
}

int main(){
	bool ft = true;
	int casos;
	while(scanf( "%d%d", &k, &n ) != EOF ){
		if( ft ) ft = false;
		else printf( "\n" );
		for( int i = 0; i <= k; ++i ){
			while(!filas[i].empty()) filas[i].pop();
		}
		
		build();
		long long soma = 0, cont = 0;
		char buf[10];

		while(n){
			scanf( "%s", buf );

			if( buf[0] == 'b' ){
				int times, carga;
				scanf( "%d %d", &times, &carga );
				
				while( times-- ){
					soma += carga;
					--n;
					int indice = query(carga,k);
					if( indice == oo ){
						++cont;
//						push(cont,k-carga);
						int no = seg[k-carga];
//						printf( ">>>> %d %d\n", no, k-carga );
						filas[k-carga].push(cont);
						mapa[cont] = k-carga;
						menor[no] = filas[k-carga].top();
						no >>= 1;
						while( no > 0 ){
							relax(no);
							no >>= 1;
						}
//						printf( "sim\n");
						
					}else{
//						printf("****\n");
						int valor = mapa[indice];
						int no = seg[valor];
						filas[valor].pop();
						if( filas[valor].empty() ) menor[no] = oo;
						else menor[no] = filas[valor].top();
						no >>= 1;
						while(no > 0){
							relax(no);
							no >>= 1;
						}
						
						no = seg[valor-carga];
						filas[valor-carga].push(indice);
						mapa[indice] = valor-carga;
						menor[no] = filas[valor-carga].top();
						no >>= 1;
						while( no > 0 ){
							relax(no);
							no >>= 1;
						}
//						printf( "yes\n");
//						pop(valor);
////						printf( "#(%d)->%d [%d]\n", indice, valor, menor[1]);
//						
//						if(valor!=carga)
//							push(indice,valor-carga);
					}
				}
			}else{
				--n;
				int carga;
				sscanf( buf, "%d", &carga );
				
				soma += carga;
				int indice = query( carga, k );
//				printf( "Qury %d\n", indice );
				if( indice == oo ){
					++cont;
//					push(cont, k - carga);
					int no = seg[k-carga];
					filas[k-carga].push(cont);
					mapa[cont] = k - carga;
					menor[no] = filas[k-carga].top();
					no >>= 1;
					
					while(no > 0){
						relax(no);
						no >>= 1;
					}
				}else{
					int valor = mapa[indice];
//					pop(valor);
//					if(valor!=carga)
//						push(indice,valor-carga);					
					int no = seg[valor];
					filas[valor].pop();
					if( filas[valor].empty() ) menor[no] = oo;
					else menor[no] = filas[valor].top();
					no >>= 1;
					while(no > 0){
						relax(no);
						no >>= 1;
					}
					
					no = seg[valor-carga];
					filas[valor-carga].push(indice);
					mapa[indice] = valor-carga;
					menor[no] = filas[valor-carga].top();
					no >>= 1;
					while( no > 0 ){
						relax(no);
						no >>= 1;
					}
				}
			}
		}
		
		printf( "%lld %lld\n", cont, cont * k - soma );
		
	}
}


