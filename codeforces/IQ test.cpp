#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;


int main(){
	int qtd;
	
	cin >> qtd;
	int par = 0, imp = 0;
	int idP, idI;
	ll temp;
	
	for( int i = 1; i <= qtd; ++i ){
		cin >> temp;
		if( temp & 1 ){
			++imp;
			idI = i;
		}else{
			idP = i;
			++par;
		}
	}
	
		
	if( par == 1 && imp > 1 ){
		cout << idP << endl;
	}else if( imp == 1 && par > 1 )
		cout << idI << endl;
			
	
}
