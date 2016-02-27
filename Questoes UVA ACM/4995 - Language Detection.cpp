#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <list>
using namespace std;
typedef long long ll;

int main(){
	string temp;
	int caso = 1;
	while( cin >> temp && temp != "#" ){
		cout << "Case " << caso++ << ": ";
		if( temp == "HELLO" )
			cout << "ENGLISH\n";
		else if ( temp == "HOLA" )
			cout << "SPANISH\n";
		else if( temp == "BONJOUR" )
			cout << "FRENCH\n";
		else if( temp == "CIAO" )
			cout << "ITALIAN\n";
		else if( temp == "ZDRAVSTVUJTE" )
			cout << "RUSSIAN\n";
		else if( temp == "HALLO" )
			cout << "GERMAN\n";
		else
			cout << "UNKNOWN\n";
	}
}
