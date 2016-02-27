#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)

int main(){
	ios_base::sync_with_stdio(false);
	string str;
	
	cin >> str;
	int mod = 0;
	rep(i, str.size()){
		mod = (mod + str[i] - '0') % 3;
	}
	
	if(!mod){
		cout << "2\n";
	}else{
		cout << "1\n" << mod << "\n";
		
	}
}

