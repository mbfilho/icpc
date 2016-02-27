#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
#define Fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) Fr(i,0,n)
#define N 110000
#define Q 51000
#define SQR 400

int n, q;

int start[SQR], end[SQR], grupos, s;
vector<int> lista[SQR];
int val[N];

int main(){
	while(scanf("%d%d", &n, &q) == 2){
		s = (int) sqrt(n);
		grupos = (n + s -1)/s;
		rep(i, n)
			scanf("%d", val + i);
		
		int tmp = 0;
		rep(g, grupos){
			start[g] = tmp;
			lista[g].clear();
			
			rep(k, s){
				if(tmp + k >= n) break;
				lista[g].push_back(val[tmp+k]);
			}
			sort(lista[g].begin(), lista[g].end());
			end[g] = min(n, tmp + s);
			tmp += s;
		}
		
		char buf[10];
		rep(i, q){
			scanf("%s", buf);
			
			if(buf[0] == 'M'){
				int i, m;
				scanf("%d%d", &i, &m);
				--i;
				
				int old = val[i], g = i/s;
				lista[g].erase(lower_bound(lista[g].begin(), lista[g].end(), old));
				lista[g].insert(lower_bound(lista[g].begin(), lista[g].end(), m), m);
				val[i] = m;
			}else{
				int i, j, x, soma = 0;
				scanf("%d%d%d", &i, &j, &x);
				--i; --j;
				int gi = i/s, gf = j/s;
				
				Fr(k, i, min(end[gi], j+1)){
					if(val[k] <= x) ++soma;
				}
				
				Fr(g, gi+1, gf){
					int qtd = upper_bound(lista[g].begin(), lista[g].end(), x) - lista[g].begin();
					soma += qtd;
				}
				
				if(gf != gi){
					Fr(k, start[gf], j+1){
						if(val[k] <= x) ++soma;
					}
				}
				printf("%d\n", soma);
			}	
		}
	}
}








