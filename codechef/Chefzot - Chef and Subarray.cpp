#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define _(n) rep(i, n)
#define mp make_pair
#define ft first
#define sd second
#define pb push_back
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long hash;

int main(){
	ios::sync_with_stdio(false);
	int n;
	cin >> n;

	int best = 0, last = -1;
	_(n){
		int input;
		cin >> input;
		if(input && last == -1) last = i;

		if(input) best = max(best, i - last + 1);
		else last = -1;
	}

	cout << best << endl;


}
