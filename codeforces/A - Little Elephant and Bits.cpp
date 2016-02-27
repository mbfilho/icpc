#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 100100

char buf[N];

int main(){
	ios::sync_with_stdio(false);
	cin >> buf;
	int tam = strlen(buf);
	
	int msb = -1;
	rep(i, tam){
		if(buf[i] == '0'){
			msb = i;
			break;
		}
	}
	
	if(~msb){
		buf[msb] = 0;
		cout << buf;
		if(buf[msb+1]) cout << (buf+msb+1);
		cout << endl;
	}else{
		buf[tam-1] = 0;
		if(tam == 1) cout << 0 << endl;
		else cout << buf << endl;
	}
}

