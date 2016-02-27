#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define inc kjshdfkjsd
#define pb push_back
#define N 60
#define oo 10000000

int ma[N][N];
map<string,int> mapa;
int cont;

int pega(string arg){
	map<string,int>::iterator it = mapa.find(arg);
	if(it != mapa.end()) return it -> second;
	mapa[arg] = cont++;
	return cont - 1;
}

int main(){
	int n, r, caso = 0;
	ios::sync_with_stdio(false);
	while(cin >> n >> r && (n|r)){
		cont = 0;
		mapa.clear();
		rep(i, N){
			rep(j, N) ma[i][j] = oo;
			ma[i][i] = 0;
		}
		while(r--){
			int u[2];
			string tmp;
			rep(i, 2){
				cin >> tmp;
				u[i] = pega(tmp);
			}
			
			if(u[0] != u[1])			
				ma[u[0]][u[1]] = ma[u[1]][u[0]] = 1;
		}

		rep(k, n){
			rep(i, n){
				rep(j, n){
					ma[i][j] = min(ma[i][k] + ma[k][j], ma[i][j]);
					ma[j][i] = ma[i][j];
				}
			}
		}

		int resp = -1;
		rep(i, n){
			rep(j, n){
				resp = max(resp, ma[i][j]);
			}
		}

		cout << "Network " << (++caso) << ": "; 
		if(resp >= oo) cout << "DISCONNECTED";
		else cout << resp;
		cout << endl << endl;
	}
}
