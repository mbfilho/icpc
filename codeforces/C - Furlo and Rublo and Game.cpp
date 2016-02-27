#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
typedef long long ll;
#define LIM 900000
typedef pair<int,int> pii;
#define X first
#define Y second
#define mp make_pair
#define G 4
#define LIM2 777777779777LL
vector<ll> raiz, quarta;
int grundy[LIM];

pii limites(ll num){
	pii resp = mp(0,0);
	resp.X = lower_bound(quarta.begin(), quarta.end(), num) - quarta.begin();
	resp.Y = upper_bound(raiz.begin(), raiz.end(), num) - raiz.begin();
	--resp.Y;
	return resp;
}
int soma[LIM][G];

void pre(){
	for(ll i = 0; i*i < LIM2; ++i) raiz.push_back(i*i);
	for(ll i = 0; i*i*i*i < LIM2; ++i) quarta.push_back(i*i*i*i);
	int greatest = 0;
	
	fr(k, 2, LIM){
		pii inter = limites(k);

		if(inter.X <= inter.Y){
			grundy[k] = -1;
			rep(i, G){
				if(!(soma[inter.Y][i] - soma[inter.X-1][i])){
					grundy[k] = i;
					break;
				}
			}
			if(grundy[k] == -1) throw 123;
		}
		
		rep(i, G)
			soma[k][i] = soma[k-1][i] + (grundy[k] == i);
	}
}

int number(ll num){
	if(num < LIM) return grundy[num];
	pii inter = limites(num);
	
	rep(i, G){
		if(soma[inter.Y][i] - soma[inter.X-1][i] == 0){
			return i;
		}
	}
	
	throw 1;
}

int main(){
	ios::sync_with_stdio(false);
	pre();
	int nim = 0, n;
	ll tmp;
	cin >> n;
	rep(i, n){
		cin >> tmp;
		nim ^= number(tmp);
	}
	
	if(nim)
		cout << "Furlo" << endl;
	else
		cout << "Rublo" << endl;
	
	
	
}



