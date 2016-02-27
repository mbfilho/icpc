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
#define N 100100

int w[N], n;

int main(){
	ios::sync_with_stdio(false);
	int t;
	cin >> t;

	while(t--){
		cin >> n;
		rep(i, n) cin >> w[i];
		int at = 0;

		rep(i, n) if(at - i < w[i]) at = w[i] + i;
		cout << at << endl;
	}

}
