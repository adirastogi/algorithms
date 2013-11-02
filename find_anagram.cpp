/*
*
* Program to find the anagrams of a string
*/



#include<iostream>
#include<string>
#include<map>
using namespace std;



long long hashfun(char * s){

	int l = strlen(s);
	long long hashval = 1;
	for(int i=0;i<l;i++)
		hashval *= s[i];
	return hashval;

}

void print_anagrams(char** str, int LEN){

	typedef multimap<long long,int> hashtable;
	hashtable h;
	for(int i=0;i<LEN;i++)
		h.insert(pair<long long,int>(hashfun(str[i]),i));

	hashtable::iterator it;
	pair<hashtable::iterator,hashtable::iterator> keyit;

	for(it=h.begin();it!=h.end();++it){
		if(h.count((*it).first)>1){
			cout<<"\nanagrams: hash: "<<(*it).first<<"->";
			keyit = h.equal_range((*it).first);
			for(hashtable::iterator jt = keyit.first;jt!=keyit.second;++jt){
				cout<<"\t"<<str[(*jt).second];
			}
		}
	}

}

int main(){

	char* strings[6] = {"hello", "olleh","tyua","dadas","tayu","llohe"};
	print_anagrams(strings,6);
	return 0;
}
