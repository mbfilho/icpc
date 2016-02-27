#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
using namespace std;
#define N 2000

char input[N];
int prt;
string P(int);
string F(int);

string E(){
	string ret = P(0);
	
	if(input[prt] == '+'){
		ret += "+";
		++prt;
		ret += E();
	}
	return ret;
}

string P(int m){
	string ret = F(m);
	
	if((input[prt] >= 'a' && input[prt] <= 'z') || input[prt] == '('){
		ret += P(1);
	}
	return ret;
}

string F(int m){
	string ret = "";
	if(input[prt] >= 'a' && input[prt] <= 'z'){
		char aux[10];
		sprintf(aux, "%c", input[prt++]);
		ret += aux;
	}else{
		++prt;
		ret += E();
		++prt;
		bool soma = false;
		int c = 0;
		for(int i = 0; i < ret.size() && !soma; ++i){
			if(!c && ret[i] == '+') soma = true;
			if(ret[i] == '(') ++c;
			if(ret[i] == ')') --c;
		}
		
		if(soma&&(m || input[prt] == '(' || (input[prt] >= 'a' && input[prt] <= 'z')) ){
			ret = "(" + ret + ")";
		}
	}
	
	return ret;
}

int main(){
	while(scanf( "%s", input) != EOF ){
		prt = 0;
		string expr = E();
		printf( "%s\n", expr.c_str());
		if(input[prt]) throw 1;
	}
}

