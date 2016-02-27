#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)


string in, out;

int main(){
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	cin >> in;
	
	
	out = "";
	
	int i = 0;
	if(in[0] == 'f'){
		out += "ftp://";
		i += 3;
	}else{
		out += "http://";
		i += 4;
	}
	
	bool tem = false;
	while(in[i] != 'r' || in[i+1] != 'u' || !tem){
		tem = true;
		out += in[i];
		++i;
	}
	out += ".ru";
	i += 2;
	if(i != in.size()){
		out += "/";
		while(i != in.size()){
			out += in[i];
			++i;
		}
	}
	cout << out << endl;
}


