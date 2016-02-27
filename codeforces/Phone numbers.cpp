 #include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

int main(){
	int dig;
	
	cin >> dig;
	
	string nome;	
	cin >> nome;
	
	if( dig % 2 == 0 ){
		cout << nome[0] << nome[1];
		for( int i = 2; i < nome.size(); i += 2 ){
			cout << "-" << nome[i] << nome[i + 1];
		}
		cout << endl;
	}else{
		cout << nome[0] << nome[1];
		for( int i = 2; i < nome.size() - 1; i += 2 ){
			cout << "-" << nome[i] << nome[i + 1];
		}
		cout << nome[nome.size() - 1];
		cout << endl;		
	}

}