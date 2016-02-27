#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define _(n) rep(i, n)
#define pb push_back
#define ft first
#define sd second
#define mp make_pair
#define SIZE(x) int(x.size())
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pii;
typedef unsigned long long hash;
#define N 42

#define color ft
#define price sd
#define sum sd
#define count ft
pii memo[N][N][N];
int mk[N][N][N], step;

pii B[N];
int n, m;

pii rec(int ind, int lastColor, int colors){
	if(ind == n) return mp(colors >= m, 0);
	pii& pd = memo[ind][lastColor][colors];
	if(mk[ind][lastColor][colors] == step) return pd;
	mk[ind][lastColor][colors] = step;

	pd = rec(ind+1, lastColor, colors);

	pii nt = rec(ind+1, B[ind].color, max(0, colors + (lastColor != B[ind].color)));
	pd.count += nt.count;
	pd.sum += nt.sum + nt.count * B[ind].price;
	return pd;
}

int main(){
	ios::sync_with_stdio(false);
	memset(mk, 0, sizeof mk);
	step = 1;

	int t;
	cin >> t;

	while(t--){
		cin >> n >> m;
		_(n) cin >> B[i].color >> B[i].price;
		sort(B, B + n);
		++step;
		pii pd = rec(0, 0, 0);
		ld ans = pd.sum, tot = pd.count;

		if(tot != 0) cout << setiosflags(ios::fixed) << setprecision(6) << ans / tot << "\n";
		else cout << "0\n";
	}

	
}