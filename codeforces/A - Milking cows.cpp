#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define pb push_back
typedef long long ll;
#define oo 1000000000

vector<int> Left, Right;
int ini, n;

int main(){
	scanf("%d", &n);
	rep(i, n){
		int dir;
		scanf("%d", &dir);
		if(dir) Right.pb(i);
		else Left.pb(i);
	}
	ll ans = 0;
	ini = 0; //do right!
	
	while(Left.size() && ini != Right.size()){
		int L = oo, R = oo;
		
		int idx = lower_bound(Left.begin(), Left.end(), Right[ini]) - Left.begin();
		R = Left.size() - idx;
		
		idx = lower_bound(Right.begin() + ini, Right.end(), Left.back()) - Right.begin();
		L = idx;
						
		if(L < R) ans += L, Left.pop_back();
		else ans += R, ++ini;

	}
	cout << ans << endl;
}
