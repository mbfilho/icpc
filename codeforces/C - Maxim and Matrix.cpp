#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
typedef long long ll;
#define N 64
#define pb push_back

ll lines[N];
ll size[N][N];

void pre(){
	lines[0] = 1;
	size[0][0] = 1;
	
	fr(i, 1, N){
		lines[i] = lines[i-1] + 1 + lines[i-1];
		
		rep(j, N){
			size[i][j] = size[i-1][j] + (j ? size[i-1][j-1] : 0);
		}
		++size[i][0];
	}
}

ll t, n;
ll resp[N];
vector<ll> count(ll limite, int tam){
	if(!limite) return vector<ll>(N,0);
	if(lines[tam] == limite){
		vector<ll> resp;
		rep(i, N) resp.pb(size[tam][i]);
		return resp;
	}
	
	vector<ll> resp = vector<ll>(N, 0);
	ll val = limite - lines[tam-1] - 1;
	if(val < 0){
		tam = 0;
		while(lines[tam] < limite) ++tam;
		return count(limite, tam);
	}
	else{
		rep(i, N) resp[i] = size[tam-1][i];
		++resp[0];
		vector<ll> tmp = count(val, tam);
		fr(i, 1, N) resp[i] += tmp[i-1];
		return resp;
	}
}

int bits(ll mask){
	int c = 0;
	while(mask){
		++c;
		mask -= mask & -mask;
	}
	return c;
}

int pote(ll mask){
	int c = -1;
	while(mask){
		++c;
		mask >>= 1;
	}
	return c;
}

int main(){
	pre();
	cin >> n >> t;
	++n;
	int tam = 0;
	while(lines[tam] < n) ++tam;
//	cout << "Tam " << tam << " " << pote(t) << endl;
	vector<ll> resp = count(n, tam);
	if(t == 1) --resp[0];
	if(bits(t) != 1) cout << "0\n";
	else cout << resp[pote(t)] << endl;
}






