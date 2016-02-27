#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define mp make_pair
typedef long long ll;
typedef pair<ll,ll> pll;

int k;

int mk[361160], caso;
ll mmc;
int bfs(ll s, ll t){
	if(s-t > mmc) throw false;
	++caso;
	queue<pll> fila;
	fila.push(mp(s,0LL));
//	mk[s%mmc] = caso;
	
	while(!fila.empty()){
		ll at = fila.front().first;
		int ops = fila.front().second;
		fila.pop();
		
		
		if(at == t) return ops;
		
		fr(i, 2, k+1){
			if(at % i){
				ll nt = at - (at%i);
				if(mk[nt % mmc] != caso){
					mk[nt%mmc] = caso;
					fila.push(mp(nt, ops+1));
				}
			}
		}
		if(at && mk[(at-1) % mmc] != caso){
			mk[(at-1) % mmc] = caso;
			fila.push(mp(at-1, ops+1));
		}
	}
	
	throw 1;
}

ll gcd(ll a, ll b){
	return b ? gcd(b, a%b) : a;
}

ll lcm(ll a, ll b){
	return a * b / gcd(a,b);
}

/*
3 tipos de intervalos de tamanho LCM(2..K):
	o primeiro, o ultimo e os do meio.
	Bfs pra cada tipo, depois so juntar =D
*/

int main(){
	ios::sync_with_stdio(false);
	ll a, b;
	cin >> b >> a >> k;
	
	mmc = 1;
	fr(i, 2, k+1) mmc = lcm(mmc, i);
	ll resp = 0;
	resp = bfs(b, max(b - (b % mmc), a));
	if(b - (b%mmc) > a){
		resp += bfs(a + (mmc - (a%mmc))%mmc, a);
		ll nb = b - (b % mmc), na = a + (mmc - (a%mmc))%mmc;
		
		ll qtd = (nb - na)/mmc;
		if(qtd){
			ll tmp = bfs(2*mmc, mmc);
			resp += tmp * qtd;
		}
	}
	
	cout << resp << endl;
	
}





