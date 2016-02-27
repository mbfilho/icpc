#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define pb push_back
#define mp make_pair
#define N 100100
typedef unsigned long long hash;
#define B 93

int freq[N], n;
string in[N];
char buf[1000];
vector<pair<hash,int> > prefs[16];
bool cmp(pair<hash,int> a, pair<hash,int> b){
	if(a.first != b.first) return a.first < b.first;
	if(freq[a.second] != freq[b.second]) return freq[a.second] > freq[b.second];
	return in[a.second] < in[b.second];
}

int V(char ch){
	return ch - 'a' + 1;
}

bool sohHash(const pair<hash,int>& a, const pair<hash,int>& b){
	return a.first < b.first;
}

int main(){
	scanf("%d", &n);
	rep(i, n) scanf("%s %d", buf, freq+i), in[i] = buf;

	rep(i, n){
		hash ha = 0;
		rep(j, in[i].size()){
			ha = ha * B + V(in[i][j]);
			prefs[j].pb(mp(ha,i));
		}
	}

	rep(i, 16) sort(prefs[i].begin(), prefs[i].end(), cmp);
	
	
	int q;
	scanf("%d", &q);
	
	rep(x, q){
		if(x) printf("\n");
		
		scanf("%s", buf);
		hash ha = 0;
		int tam = strlen(buf);
		rep(i, tam)	ha = ha * B + V(buf[i]);
		int ini = lower_bound(prefs[tam-1].begin(), prefs[tam-1].end(), mp(ha, 0), sohHash) - prefs[tam-1].begin();
		int fim = upper_bound(prefs[tam-1].begin(), prefs[tam-1].end(), mp(ha, 0), sohHash) - prefs[tam-1].begin();
		
		fr(i, ini, min(ini+10,fim)){
			if(prefs[tam-1][ini].first != ha) throw 1;
			printf("%s\n", in[prefs[tam-1][i].second].c_str());
		}
	}
}




