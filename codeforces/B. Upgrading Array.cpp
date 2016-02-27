#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <iostream>
using namespace std;
typedef long long ll;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
#define ft first
#define sd second
#define N 6000
#define LIM 100100


int A[LIM], P[LIM], contp;
set<int> bad;
int acc[N], input[N];

void pre(){
	contp = 0;
	memset(A, -1, sizeof A);

	fr(i, 2, LIM){
		if(A[i] == -1){
			A[i] = contp;
			P[contp++] = i;
		}

		rep(j, A[i]+1){
			ll tmp = ll(i) * P[j];
			if(tmp >= LIM) break;
			A[tmp] = j;
		}
	}
}

vector<pii> fat(int num){
	int tmp = num;
	vector<pii> ans;
	if(num == 1 || num == 0) return ans;

	rep(i, contp){
		ll p = P[i];
		if(p*p > num) break;
		pii f = mp(P[i], 0);

		while(tmp % P[i] == 0){
			tmp /= P[i];
			++f.sd;
		}
		ans.pb(f);
	}
	if(tmp != 1) ans.pb(mp(tmp, 1));
	return ans;
}

int gcd(int a, int b){
	return b ? gcd(b, a%b) : a;
}

int F(int num){
	if(num == 1) return 0;

	int ans = 0;
	vector<pii> guy = fat(num);
	rep(i, guy.size()){
		if(bad.find(guy[i].ft) != bad.end()) ans -= guy[i].sd;
		else ans += guy[i].sd;
	}

	return ans;
}

int main(){
	ios::sync_with_stdio(false);
	pre();
	int n, m;
	cin >> n >> m;

	rep(i, n) cin >> input[i];
	acc[0] = input[0];
	fr(i, 1, n) acc[i] = gcd(input[i], acc[i-1]);

	rep(i, m){
		int tmp; 
		cin >> tmp;
		bad.insert(tmp);
	}

	int ans = 0, mdc = 1;

	for(int i = n - 1; i >= 0; --i){
		acc[i] /= mdc;

		int fg = F(acc[i]);
		// cout << acc[i] << " " << fg << endl;

		if(fg < 0) mdc *= acc[i];

		ans += F(input[i] / mdc);
		// cout << "Pra calc " << input[i]/mdc << endl;
		// cout << "To ans " << F(input[i] / mdc) << endl;
	}

	cout << ans << endl;

}