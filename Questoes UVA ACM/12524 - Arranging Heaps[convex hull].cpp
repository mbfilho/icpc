#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define N 1100
typedef long long ll;
//http://wcipeg.com/wiki/Convex_hull_trick -> n ajudou muito =/

//{ Ajudou bastante
//http://codeforces.com/blog/entry/7785
//http://codeforces.com/contest/311/submission/3779559
//http://codeforces.com/contest/311/standings
//}

ll pd[N][2], w[N], p[N];
int n, K;

ll h[N], s[N];

int fila[N], ini, fim;

int main(){
	w[0] = h[0] = s[0] = p[0] = 0;
	
	while(scanf("%d%d", &n, &K) == 2){
		fr(i, 1, 1+n) scanf("%lld%lld", p + i, w + i), s[i] = w[i] + s[i-1], h[i] = w[i] * p[i] + h[i-1];
		
		memset(pd, 0x3f, sizeof pd);
		pd[0][0] = pd[0][1] = 0;
		int at = 1;
		
		fr(x, 1, K+1){
			ini = fim = 0;
			fila[fim++] = 0;
			int last = 1 - at;
			fr(i, 1, 1+ n){
				while(ini < fim){
					int k1 = fila[ini+1], k2 = fila[ini];
					if(ini < fim && (pd[k1][last] + h[k1] - (pd[k2][last] + h[k2]) <= p[i] * (s[k1] - s[k2]))) ++ini;
					else break;
				}
				int j = fila[ini];
				pd[i][at] = pd[j][last] + p[i] * (s[i] - s[j]) - (h[i] - h[j]);
				while(ini<fim){
					int k1 = fila[fim], k2 = fila[fim - 1];
					if(ini<fim && 
						(
							( (pd[k1][last] + h[k1] - (pd[k2][last] + h[k2])) * (s[i] - s[k1]) ) 
								>=
							((pd[i][last] + h[i] - (pd[k1][last] + h[k1])) * (s[k1] - s[k2]))
						)
					) --fim;
					else break;
				}
				fila[++fim] = i;
			}
			at = 1 - at;
		}

		printf("%lld\n", pd[n][1-at]);
	}
}

