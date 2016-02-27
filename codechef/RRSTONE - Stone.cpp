#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define _(n) rep(i, n)
#define pb push_back
#define ft first
#define sd second
#define mp make_pair
#define SIZE(x) int(x.size())
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long hash;
#define N 100100

int n, k;
vector<ll> input;

vector<ll> doIt(vector<ll> tmp){
	ll best = *max_element(tmp.begin(), tmp.end());
	for(ll& e : tmp) e = best - e;
	return tmp;
}

void print(vector<ll>& tmp){
	cout << tmp[0];

	fr(i, 1, SIZE(tmp)) cout << " " << tmp[i];
	cout << "\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin >> n >> k;
	input.resize(n);

	_(n) cin >> input[i];

	if(!k) print(input);
	else{
		vector<ll> tmp[2];
		tmp[0] = doIt(input), tmp[1] = doIt(tmp[0]);
		print(tmp[(k-1)&1]);
	}
}