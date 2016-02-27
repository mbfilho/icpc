#include <cstdio>
#include <algorithm>
#include <map>
#include <string>
#include <set>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define mp make_pair
map<int,string> mapa;

void pre(){

	fr(x, 2, 101){
		set<int> mods;
		string tmp = "";
		int num = 1;
		
		while(1){
			if(!mods.insert(num).second) break;
			if(!num) break;
			if(num < x){
				num *= 10;
				if(!mods.insert(num).second) break;
			}
			if(num < x){
				tmp += "0";
				num *= 10;
			}else{
				char buf[100];
				sprintf(buf, "%d", num / x);
				num %= x;
				tmp += buf;
			}
		}
		mapa[x] = tmp;
	}
}

int main(){
	int n, k;
	pre();
	while(scanf("%d%d", &n, &k) == 2){
		int c = 0;
		while(n > 1){
			string tmp = mapa[n];
			rep(i, tmp.size()) if(tmp[i] - '0' == k) ++c;
			--n;
		}
		printf("%d\n", c);
	}
}

