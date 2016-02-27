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

pii pts[N];
int mk[N], caso;

int n;

struct No{
	int coord, priCoef, secCoef, idx;

	No(){}
	No(int a, int b, int c, int d):coord(a), priCoef(b), secCoef(c), idx(d){}
};

int get(pii& pt, int c){
	return c == 0 ? pt.ft : pt.sd;
}

int getMost(int coord, int priCoef, int secCoef){
	int ret = 0;

	rep(i, n) {
		if(get(pts[i], coord) * priCoef > get(pts[ret], coord) * priCoef ||
			(get(pts[i], coord) * priCoef ==  get(pts[ret], coord) * priCoef 
				&& get(pts[i], 1-coord) * secCoef >= get(pts[ret], 1-coord) * secCoef)){
			ret = i;
		}
	}

	return ret;
}

string getString(No& at){
	string ret = "";

	//x
	if(at.coord == 0){
		if(at.secCoef == 1) ret = "S";
		else ret = "N";

		if(at.priCoef == 1) ret += "W";
		else ret += "E";
	} else { //y
		if(at.priCoef == 1) ret = "S";
		else ret = "N";

		if(at.secCoef == 1) ret += "W";
		else ret += "E";
	}

	return ret;
}

int main(){
	int t;
	ios::sync_with_stdio(false);

	cin >> t;
	memset(mk, 0, sizeof mk);
	caso = 0;

	while(t--){
		cin >> n;
		rep(i, n) cin >> pts[i].ft >> pts[i].sd;
		vector<No> extreme;

		rep(coord, 2){
			int aux[] = {-1, 1};
			rep(p, 2) rep(s, 2) {
				int ret = getMost(coord, aux[p], aux[s]);
				extreme.pb(No(coord, aux[p], aux[s], ret));
			}
		}

		vector<No> ans;
		fr(msk, 1, (1 << extreme.size())){
			bool dm = false;
			vector<No> light;

			rep(i, extreme.size()) if(msk & (1<<i)){
				rep(j, light.size()) if(light[j].idx == extreme[i].idx) dm = true;

				light.pb(extreme[i]);
			}

			if(dm || (ans.size() && light.size() >= ans.size())) continue;
			++caso;
			int cnt = 0;

			rep(i, light.size()){
				No at = light[i];
				pii lPt = pts[at.idx];

				rep(j, n){
					if(get(lPt, 1-at.coord) * at.secCoef >= get(pts[j], 1-at.coord) * at.secCoef) if(mk[j] != caso){
						mk[j] = caso;
						++cnt;
					}
				}
			}

			if(cnt == n){
				ans = light;

				// rep(i, light.size()){
				// 	cout << light[i].coord << " " << light[i].priCoef << " " <<light[i].secCoef << " " << light[i].idx << endl;
				// }
			}
		}

		cout << ans.size() << endl;

		rep(i, ans.size()) {
			cout << ans[i].idx + 1 << " " << getString(ans[i]) << endl;
		}

	}
}
