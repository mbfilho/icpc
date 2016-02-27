#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define N 510

int n, m, ma[N][N];

int main(){
	ios::sync_with_stdio(false);
	
	while(cin >> n >> m && (n|m)){
		rep(i, n) rep(j, m) cin >> ma[i][j];
		int q;
		cin >> q;
		
		while(q--){
			int u, l;
			cin >> l >> u;
			
			int best = 0;
			rep(i, n){
				int ind = lower_bound(ma[i], ma[i] + m, l) - ma[i];
				if(ind == m) continue;
				
				int ini = max(1, best), fim = min(n - i, m - ind);
				while(ini <= fim){
					int mid = (ini+fim)>>1;
					if(ma[i+mid-1][ind+mid-1] <= u) ini = mid + 1;
					else fim = mid - 1;
				}
				
				if(ini-1 > best) best = ini - 1;
			}
			
			cout << best << endl;
		}
		
		cout << "-" << endl;
	}
}


