#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define pb push_back

map<string,int> mapa;

void mapeia(vector<string> keys){
	sort(keys.begin(), keys.end());
	
	rep(i, (1<<keys.size())){
		if(!i) continue;
		string ha = "";
				
		rep(j, keys.size()){
			if(i & (1<<j))
				ha += "#" + keys[j];
		}
		++mapa[ha];
	}
}

int main(){
	int n;
	scanf("%d", &n);
	char buf[1000];
	
	rep(i, n){
		int k;
		scanf("%d", &k);
		vector<string> keys;
		rep(j, k) scanf("%s", buf), keys.pb(buf);
		mapeia(keys);
	}
	
	int q;
	scanf("%d", &q);
	while(q--){
		int k;
		vector<string> keys;
		scanf("%d", &k);
		while(k--) scanf("%s", buf), keys.pb(buf);
		sort(keys.begin(), keys.end());
		string ha = "";
		rep(i, keys.size()) ha += "#" + keys[i];
		printf("%d\n", mapa[ha]);
	}
}

