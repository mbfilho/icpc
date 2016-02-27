#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define Fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) Fr(i,0,n)
#define N 60
#define V 11000

int n, m;
int ma[N][N];

int primos[V], A[V], contp;
int qtd[V];

void pre(){
	rep(i,V) A[i] = -1, qtd[i] = 0;
	contp = 0;
		
	Fr(i, 2, V){
		if(A[i] == -1){
			A[i] = contp;
			primos[contp++] = i;	
			qtd[i] = 1;
		}
		
		Fr(j, 0, contp){
			if(primos[j] * i >= V) break;
			A[primos[j]*i] = j;
			qtd[primos[j]*i] = 1 + qtd[i];
		}
	}
}

int main(){
	pre();
	int t;
	scanf("%d", &t);
	
	rep(cas, t){
		scanf("%d%d", &n, &m);
		
		int soma = 0;
		rep(i, n){
			int tmp = 0;
			rep(j, m){
				scanf("%d", &ma[i][j]);
				tmp += qtd[ma[i][j]];
			}
			soma ^= tmp;
		}
		
		printf("Case #%d: ", cas + 1);
		if(soma) printf("YES\n");
		else printf("NO\n");	
	}
	
}







