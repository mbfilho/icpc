#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
typedef long long ll;
#define mp make_pair

string F[200];
int cnt;

ll pd[101];
pair<string,string> memo[101];

void pre(){
	F[0] = "0"; F[1] = "1";
	cnt = 2;
	while(cnt < 28){
		F[cnt] = F[cnt-1] + F[cnt-2];
		++cnt;
	}
}

int n;
string str;

string pref(string& tmp, int size){
	return tmp.substr(0, size);
}

string suf(string& tmp, int size){
	return tmp.substr(tmp.size() - size, size);
}

int fail[100100];

void fazFail(){
	int k = -1;
	fail[0] = -1;
	int size = str.size();
	fr(i, 1, size){
		while(k != -1 && str[i] != str[k+1]) k = fail[k];
		if(str[i] == str[k+1]) ++k;
		fail[i] = k;
	}
}

int contar(string tmp){
	int cont = 0;
	int k = -1;
	int txt = tmp.size(), pat = str.size();
	
	rep(i, txt){
		while(k != -1 && tmp[i] != str[k+1]) k = fail[k];
		if(tmp[i] == str[k+1]) ++k;
		if(k == pat-1){
			++cont;
			k = fail[k];
		}
	}
	
	return cont;
}


int main(){
	pre();
	cin.sync_with_stdio(false);
	int caso = 0;
	
	while(cin >> n >> str){
		printf("Case %d: ", ++caso);
		fazFail();
		
		if(n < cnt){
			printf("%d\n", contar(F[n]));
		}
		else{
			memo[cnt-1] = mp(pref(F[cnt-1], str.size()-1), suf(F[cnt-1], str.size()-1));
			memo[cnt-2] = mp(pref(F[cnt-2], str.size()-1), suf(F[cnt-2], str.size()-1));
			fr(i, cnt, n+1)
				memo[i] = mp(memo[i-1].first, memo[i-2].second);
			pd[cnt-1] = contar(F[cnt-1]);
			pd[cnt-2] = contar(F[cnt-2]);
			
			fr(i, cnt, n+1){
				pd[i] = pd[i-1] + pd[i-2];
				pd[i] += contar(memo[i-1].second + memo[i-2].first);
			}
			
			printf("%lld\n", pd[n]);
		}
	}
}





