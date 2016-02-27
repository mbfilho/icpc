#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define _(n) rep(i, n)
#define reps(i, str) for(int i = 0; str[i]; ++i)
#define mp make_pair
#define ft first
#define sd second
#define pb push_back
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long hash;
#define S 1100000

int n;
char s[S], mapping[300];

int main(){
	ios::sync_with_stdio(false);
	int t;
	cin >> t;

	while(t--){
		cin >> n;
		_(300) mapping[i] = i;

		_(n) {
			char a[10], b[10];
			cin >> a >> b;
			mapping[a[0]] = b[0];
		}
		cin >> s;

		reps(i, s) s[i] = mapping[s[i]];

		char* str = s;
		while(*str == '0') ++str;
		bool temPonto = false;
		reps(i, str) temPonto |= (str[i] == '.');

		int size = strlen(str);
		if(temPonto){
			while(str[size-1] == '0') --size;
			if(str[size-1] == '.') --size;
			str[size] = 0;
		}
		if(!size) cout << "0\n";
		else cout << str << endl;
	}
}
