#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define each(it, m) for( __typeof(m.begin()) it = m.begin(); it != m.end(); ++it)
#define N 1010

double prob[N][N];//prob de i vir antes de j

int p[N];
int a[N], b[N];
int n, m;

int main(){
	scanf("%d%d", &n, &m);
	rep(i, n) scanf("%d", p+i);
	rep(i, m) scanf("%d%d", a+i, b+i), --a[i], --b[i];
	
	rep(i, n){
		fr(j, i+1, n)
			prob[i][j] = 1.0;
	}
	
	for(int k = m - 1; ~k; --k){
//	rep(k, m){
		int u = a[k], v = b[k];
		
		prob[u][v] = prob[v][u] = 0.5;
		rep(i, n){
			if(i != u && i != v){
				prob[i][v] = prob[i][u] = (prob[i][u] + prob[i][v]) * 0.5;
				prob[u][i] = prob[v][i] = 1 - prob[i][v];
			}
		}
		
	}
	
	double res = 0;
	rep(i, n){
		fr(j, 0, n){
			if(p[i] > p[j])
				res += prob[i][j];
		}
	}
	
	printf("%.7lf\n", res);
	
}



