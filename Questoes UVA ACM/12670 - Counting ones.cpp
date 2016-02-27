#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,ll> pll;
#define ft first
#define sd second
#define N 65

pll pd[N];

pll memo(ll lim, int i, int s, bool tight){
	if(i == -1) return mp(1,0);
	if(!tight && pd[i].ft != -1) return pd[i];

	ll pos = 1LL << i;
	
	//0
	pll ans = memo(lim, i-1, s, tight && (lim & pos) == 0);
	
	//1
	if(!tight || (lim & pos)){
		pll tmp = memo(lim, i-1, s, tight && (lim&pos));
		ans.ft += tmp.ft;
		ans.sd += tmp.ft + tmp.sd;
	}
	
	if(!tight) pd[i] = ans;
	return ans;		
}


ll wrap(ll num){
	if(!num) return 0;
	
	int s = 0;
	ll tmp = num;
	
	while(num) ++s, num >>= 1;
	
	pll ans = memo(tmp, s - 1, s, true);
	return ans.sd;
	
}

int main(){
	ios::sync_with_stdio(false);
	rep(i, N) pd[i] = mp(-1, -1);
	ll a, b;			
	
	while(cin >> a >> b){
		cout << wrap(b) - wrap(a-1) << endl;
	}
}