#include <iostream>
using namespace std;
#include <vector>

// typedef long long int long long int; 

int main(){

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int level_f=-1;
	int k; cin >> k;//k is from 1 to 6;
	// characters are the first k characters in a,b,c,d,e,f.

	vector<char*> words[k]; //2D array to store strings 
	vector<long long int> sizes[k];  //2D array to store sizes of strings
	string f; //the bakra string to store cin values.

	for(int i=0; i<k; i++){
		char* spare=new char[1];
		spare[0]='a'+i;
		sizes[i].push_back(1);
		words[i].push_back(spare);
		level_f=0;

		cin>>f;  //each f length is atmost 20.
		char *spam=new char[f.size()];
		for(int j=0; j<f.size(); j++) spam[j]=f[j];
		sizes[i].push_back(f.size());
		words[i].push_back(spam);
		level_f=1;
	}


	NOW YOU NEED TO UPDATE THE 2D-ARRAYS OF STRINGS AND SIZES, TO DYNAMICAlong long intY STORE SHIT AND REPORT ANSWERS FOR PART-1 AND 2.


	long long int t; cin >> t; //testcases count

	int id;
	for(long long int i=0; i<t; i++){
		cin>>id;

		if(id==0){
			int n; cin >> n;
			if(level_f<n){
				for(XXXXXXXXXXXXXXXX)
			}

			//do function 1 or 2
		}
		else if(id==1) {
			long long int 

		}
		else if(id==2){
			string s; cin >> s;
			//do function 3 or 4
		}
		else if(id==3){

		}
	}



}