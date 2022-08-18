#include <bits/stdc++.h>
using namespace std;


int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int k;
	cin >> k;

	if((k>=1) && (k<=6)){

		vector<string> f;

		for (int i = 0; i < k; ++i){
			string o;
			cin >> o;
			f.push_back(o);
		}

		int num_testcases;

		cin >> num_testcases;

		vector<unsigned long long int> fn[k]; //fn is a array of vectors.
		for (int i = 0; i < k; ++i){
			fn[i].push_back(1);
		}


		for (int u = 0; u < num_testcases; ++u){

			int id;
			cin >> id;
			if(id==0){
				int n;
				cin >> n;
				int a = fn[0].size(); //a is f_level
				for (int i = a; i < n+1 ; ++i){
					for (int j = 0; j < k; ++j){
						long long int d=0;
						for (int I = 0; I < f[j].length(); ++I){
								d=d+fn[f[j][I]-'a'][i-1];
						}
						fn[j].push_back(d);
					}
				}
				cout<<fn[0][n]<<endl;
			}
			if(id==1){
				unsigned long long int n;
				cin>>n;
				while(n>=fn[0][fn[0].size()-1]){
					for (int j = 0; j < k; ++j){
						long long int d=0;
						for (int I = 0; I < f[j].length(); ++I){
								d=d+fn[f[j][I]-'a'][fn[j].size()-1];
						}
						fn[j].push_back(d);
					}
				}
				int a=fn[0].size()-1;
				int I=0;
				while(a>1){
					for (int i = 0; i < f[I].length(); ++i){
						if (n<fn[I][a-1]){
							I=f[I][i]-'a';
							break;
						}
						else{
							n=n-fn[f[I][i]-'a'][a-1];
						}
					}
					a=a-1;
				}
				cout<<f[I][n]<<endl;
			}
		}
	}
}