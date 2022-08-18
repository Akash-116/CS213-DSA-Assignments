#include <iostream>
using namespace std;
#include <vector>

//1. If space is given in input for f[<char>], urs code blows up.
//2. maybe write up some functions for neat code. instead of humongous for loops.
//check whether the blank string can be valid.....
//3. Blows up for linearly growing sequences.



int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int flevel=-1; 			//f level should be the max n for which, f^n is stored.
	int k; cin >> k;		//k is from 1 to 6;
							// characters are the first k characters in a,b,c,d,e,f.
	string spam;
	vector<long long int> sizes[k];  //2D array to store sizes of strings
	string f[k]; 					 //the f_values string to store cin values.
	getline(cin, f[0]); 			 //some issue between cin and getline. so, need to waste up a getline like this.

	for(int i=0; i<k; i++){
		sizes[i].push_back(1);
		getline(cin, f[i]);  //each f length is atmost 20.
		sizes[i].push_back(f[i].size());
	}
	flevel=1;

	int flevel_needed=13; //since 20^13 is less than 10^18
	for(flevel+=1; flevel <= flevel_needed; flevel++ ){ //to compute till flevel_needed 
		for(int i=0; i<k; i++){ //to compute for all chars.
			long long int next=0;
			for(unsigned int str_idx=0; str_idx<f[i].size(); str_idx++){//to parse the f[current_char]
				next+=sizes[0-'a'+f[i][str_idx]][flevel-1];
			} 
			sizes[i].push_back(next);
		}
	}
	flevel--;

	// for(int i=0; i<19; i++) cout<<sizes[0][i]<<endl;
	// NOW YOU NEED TO UPDATE THE 2D-ARRAYS OF SIZES, TO DYNAMICAY STORE long long int AND REPORT ANSWERS FOR PART-1 AND 2.
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	long long int t; cin >> t; //testcases count
	int id;

	for(long long int i=0; i<t; i++){
		cin>>id;
		getline(cin, spam);

		if(id==0){
			int need_n; cin >> need_n;

			if(flevel<need_n){
				for(flevel+=1; flevel<=need_n; flevel++ ){ 			 //to compute till flevel_needed 
					for(int i=0; i<k; i++){							 //to compute f^n for all chars na!.
						long long int next=0;
						for(unsigned int str_idx=0; str_idx<f[i].size(); str_idx++){//to parse the f[current_char] string and add their f^n-1.
							next+=sizes[0-'a'+f[i][str_idx]][flevel-1];
						} 
						sizes[i].push_back(next);
					}
				}
				flevel--;  //since, one unnecessary increment came.
			}
			cout << sizes[0][need_n]<<endl;
		}
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		else if(id==1) {
			long long int n; cin >> n;//this is char at index==i.
			n++;//this is ith char. in string,so, index+1
			int n_match = flevel;

			if(n==1) {
				cout<<'a'<<endl;
			}
			else{
				while(sizes[0][n_match]>n){  //if needed char is within our storage.
					n_match--;
				}
				if(sizes[0][n_match]!=n) n_match++;  //small technical issue. :)

				while(sizes[0][flevel]<n){   // if needed char is out of our storage, we better our storage.
					n_match=++flevel;
					for(int i=0; i<k; i++){ //to compute for all chars.
						long long int next=0;
						for(unsigned int str_idx=0; str_idx<f[i].size(); str_idx++){//to parse the f[current_char] and add p f^n-1's
							next+=sizes[0-'a'+f[i][str_idx]][flevel-1];
						} 
						sizes[i].push_back(next);
					}
				}
				//////////////////////////////////////Our Storage is developed///////////////////////////////////////////////////
				// if(sizes[0][n_match]<n)cout<<"Something's wrong"<<endl;

				int k_curr=0; //i.e. current initial char under need is 'a'.
				for( ; n_match>0; n_match-- ){ //to move towards base case
					if(n_match==1) {
						cout<<f[k_curr][n-1]<<endl; //since n is not index, it is index+1.
						break;
 					}
					for(unsigned int str_idx=0; str_idx<f[k_curr].size(); str_idx++){ //to check every f^n-1 of f^n , where, the asked element belongs to.
						if(n>sizes[0-'a'+f[k_curr][str_idx]][n_match-1]){
							n-=sizes[0-'a'+f[k_curr][str_idx]][n_match-1];
						}
						else{
							k_curr = 0-'a'+f[k_curr][str_idx];
							break;
						}
					}
				}
				// getline(cin, spam);
			}

		}
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		else if(id==2){
			string s; 
			// cin>>s;
			getline(cin, s);
			// cout<<"substring \""<<s<<"\" substring"<<endl;
			if(s.size()==0) cout<<"0 0"<<endl;
			else cout<<"-1"<<endl;
			//do function 3 or 4
		}
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		else if(id==3){
			string s; 
			// cin>>s;
			getline(cin, s);
			// cout<<"subseq \""<<s<<"\" subseq"<<endl;
			if(s.size()==0) cout<<"0 0"<<endl;
			else cout<<"-1"<<endl;

		}
	}
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


}