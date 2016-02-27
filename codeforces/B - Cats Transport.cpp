#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 100100
typedef long long ll;
ll d[N], h[N], t[N], pd[N][2];
int p[N], n, K, m;
int fila[N];

bool cmp(int a, int b){
	return t[a] < t[b];
}

bool best(int i, int j, ll a, int k){
	return (pd[i][k] + h[i]) - (pd[j][k] + h[j]) < a * (i - j);
}

int main(){
	cin >> n >> m >> K;
	fr(i, 2, n+1) cin >> d[i], d[i] += d[i-1];
	fr(i, 1, 1+ m){
		int hill;
		cin >> hill >> t[i]; 
		t[i] -= d[hill];
	}
	fr(i, 1, 1+m) p[i] = i;
	sort(p+1, p+m+1, cmp);
	fr(i, 1, 1+m) h[i] = t[p[i]] + h[i-1];
	
	memset(pd, 0x3f, sizeof pd);
	pd[0][0] = pd[0][1] = 0;
	int at = 1;
	
	fr(k, 1, K+1){
		int ini = 0, fim = 1;
		fila[0] = 0;
		int last = 1 - at;
		
		fr(i, 1, m+1){
			while(fim - ini >= 2 && best(fila[ini+1], fila[ini], t[p[i]], last)) ++ini;
			pd[i][at] = pd[fila[ini]][last] + (i-fila[ini]) * t[p[i]] - (h[i] - h[fila[ini]]);
			
			while(fim - ini >= 2
			&& (pd[i][last] + h[i] - pd[fila[fim-1]][last]-h[fila[fim-1]]) * (fila[fim-1] - fila[fim-2])  
			<= (pd[fila[fim-1]][last] + h[fila[fim-1]] - pd[fila[fim-2]][last] - h[fila[fim-2]]) * (i - fila[fim-1]) 
			) --fim;
			
			fila[fim++] = i;
		}
		at = 1 - at;	
	}
	at = 1 - at;
	cout << pd[m][at] << endl;
	
	
	
}

