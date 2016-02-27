#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;
#define pb push_back
#define mp make_pair
#define X first
#define Y second
#define N 200100

struct No{
	int x, y;
	int esq, dir, pai;
	int id;
	
	void set(int a){
		id = a;
		pai = -1;
		y = rand();
		x = a;
		esq = dir = -1;
	}
}nos[N];

int count(int no){
	int c = 0;
	if(nos[no].esq != -1) c = nos[nos[no].esq].x;
	
	return c;
}

void ajeitar( int no ){
	int esq = 0, dir = 0;
	if( nos[no].esq != -1 ) esq = nos[ nos[no].esq ].x;
	if( nos[no].dir != -1 ) dir = nos[ nos[no].dir ].x;
	
	nos[no].x = esq + dir + 1;
}

void setPai(int no){
	if(nos[no].esq != -1) nos[ nos[no].esq ].pai = no;
	if(nos[no].dir != -1) nos[ nos[no].dir ].pai = no;
}

void split( int t, int x, int& l, int& r ){
	if(~l)
		nos[l].pai = -1;
	if(~r)
		nos[r].pai = -1;
	
	if( t == -1 ) r = l = -1;
	else{
		int qtd = 1;
		if( nos[ t ].esq != -1 ) qtd = nos[ nos[t].esq ].x + 1;
		
		
		if( x == qtd ){
			l = t;
			r = nos[t].dir;
			
			nos[l].dir = -1;
			
		}else if( x < qtd ){
			split( nos[t].esq, x,  l, nos[t].esq );
			r = t;
		}else{
			split( nos[t].dir, x - qtd, nos[t].dir, r );
			l = t;
		}
		
		setPai(t);
		ajeitar( t );
	}
}

int merge( int& l, int& r ){
	if( l == -1 ) return r;
	if( r == -1 ) return l;
	
	if( nos[l].y > nos[r].y ){
		nos[r].esq = merge( l, nos[r].esq );
		ajeitar( r );
		setPai(r);
		return r;
	}else{
		nos[l].dir = merge( nos[l].dir, r );
		ajeitar( l );
		setPai(l);
		return l; 
	}
}

int add( int t, int nw ){
	if( t == -1 || nos[t].y > nos[nw].y ){
		split( t, nos[nw].x, nos[nw].esq, nos[nw].dir );
		ajeitar( nw );
		setPai(nw);
		nos[nw].pai = -1;
		return nw;
	}
	
	int qtd = 1;
	if( nos[t].esq != -1 ) qtd = nos[ nos[t].esq ].x + 1;
	
	if( nos[nw].x < qtd ){
//		nos[nw].x -= 1;
		nos[t].esq = add( nos[t].esq, nw );
	}else{
		nos[nw].x -= qtd;
		nos[t].dir = add( nos[t].dir, nw );
	}
	
	ajeitar( t );
	setPai(t);
	return t;
}


void dfs(int no, int pai){
	if(no != -1){
		printf( "No %d Pai esperado %d Pai atual %d\n", nos[no].id, pai, nos[no].pai );
		printf("esq: ");
		dfs(nos[no].esq, no); printf("\n");
		printf("dir: ");
		dfs(nos[no].dir, no); printf("\n");
	}
}

int getIndex(int no, int son){
	if(no == -1) return 0;
	
	if(son == nos[no].esq) return getIndex(nos[no].pai, no);
	
	return count(no) + getIndex(nos[no].pai, no) + 1;
}

int n, q;
int main(){
	int casos;
	scanf( "%d", &casos );
	long long var = time(0);
	srand(var);
	while(casos--){
//		printf( "%lld\n", var );
		int root = -1;
		scanf( "%d %d", &n, &q );
		
		for(int i = 1; i <= n; ++i){
			nos[i].set(i);
			root = add(root, i);
		}
//		dfs(root, -1);
//		for(int i = 1; i <= n; ++i){
//			printf("[%d] = %d\n", i, getIndex(i, -2));
//		}

		for(int i = 0; i < q; ++i){
			if(i) printf( " " );
			int tmp;
			scanf( "%d", &tmp );
			int index = getIndex(tmp, -2);
			
			printf( "%d", index - 1);
			int a = -1, b = -1, c = -1;
			split(root, index - 1, b, c);
//			printf( "Primeira parte\n" );
//			dfs(b, -1);
//			printf( "----------" );
//			dfs(c, -1);
//			printf( "###########\n" );
			split(c, 1, a, c);
			
//			printf( "Segunda parte\n");
//			dfs(a,-1);
//			printf("__________\n");
//			dfs(c,-1);
//			printf( "########\n" );
			a = merge(a, b);
//			printf( "After merge1\n");
//			dfs(a, -1);
			
			root = merge(a, c);
//			printf( "After marge2\n");
//			dfs(root, -1);
			
//			for(int i = 1; i <= n; ++i){
//				printf("[%d] = %d\n", i, getIndex(i, -2));
//			}
		}
		printf( "\n" );
	}
}


