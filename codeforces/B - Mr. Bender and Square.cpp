#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define each(it, m) for(__typeof(m.begin()) it = m.begin(); it != m.end(); ++it)
#define db if(0)
typedef long long ll;

int n;
int x, y;


ll total(ll t){
	if(!t) return 1;
	return 1 + 2*t*t + 2*t;
}

ll soma(ll meio){//triangulo
	if(meio <= 0) return 0;
	return (1 + meio) * meio - meio;
}

ll dist(ll a, ll b){
	return abs(a-x) + abs(b-y);
}


ll getFolga(ll a, ll b, ll t){//area excluida 2 vezes
	ll d = dist(a,b), folga = t - d + 1;
	
	if(folga <= t && folga > 0)
		return ((1 + folga) * folga)/2;
	return 0;
}

ll getArea(ll t){
	ll area = total(t);
	area -= soma(x + t - n + 1);
	area -= soma(y + t - n + 1);
	area -= soma(- (x-t));
	area -= soma(- (y-t));
	area += getFolga(-1,-1, t);
	area += getFolga(n, n, t);
	area += getFolga(-1, n, t);
	area += getFolga(n, -1, t);
	return area;
}

int main(){
	ll c;
	
	cin >> n >> x >> y >> c;
	--x; --y;
	ll ini = 0, fim = 2000000000LL, resp = -1;
	while(ini <= fim){
		ll t = (ini+fim)/2;
		ll area = getArea(t);
		
		if(area >= c){
			resp = t;
			fim = t - 1;
		}else ini = t + 1;
	}
	
	cout << resp << endl;
}




