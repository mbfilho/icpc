#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <cmath>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> Ponto;
#define W first
#define H second
#define mp make_pair
#define pb push_back

ll n;
Ponto best;

bool troca(ll w, ll h){
	if(best.W == -1 || h * w < best.W * best.H) return true;
	if(h*w == best.W * best.H && abs(best.W - best.H) > abs(h-w)) return true;
	
	return false;
}


int main(){
	int casos;
	scanf("%d", &casos);
	
	while(casos--){
		scanf("%lld", &n);
		ll raiz = 10 + ll(sqrt(double(n)));
		best = mp(-1,-1);
		
		//i numa linha
		for(int i = 1; i <= raiz; ++i){
			ll w = 40LL * i + (i + 1) * 4;
			ll linhas = (n + 5*i-1)/(5*i);
			ll h = 8 * linhas + (linhas + 1) * 2;
			
			if(troca(w,h)){
				best.W = w;
				best.H = h;
			}
		}
		
		
		//i linhas
		for(int i = 1; i <= raiz; ++i){
			ll pilhas = (n+i*5-1) / i*5;
			ll w = 40LL * pilhas + (pilhas + 1) * 4;
			ll h = 8 * i + (i+1) * 2;
			
			if(troca(w,h)){
				//printf(">");
				best.W = w;
				best.H = h;
			}
		}
		
		printf( "%lld X %lld = %lld\n", max(best.W, best.H), min(best.W, best.H), best.W * best.H); 
		
	}
}


