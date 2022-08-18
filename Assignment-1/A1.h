#include<vector>
#include<iostream>
using namespace std;


long long int gcd(long long int a, long long int b){
    if (a == 0) return b;  
    return gcd(b%a, a);  
}    
// Function to return LCM of two long long numbers  
long long int lcm(long long int a, long long int b){ 
    return (a*b)/gcd(a, b);  
}  
//////////////////////////////////////////////////

class permutation{

	int *a;  //equal to some new int[n]
	int n;
	vector<int> * loop; //array of vectors.
	vector<vector<int>> size_count;
	long long int perm_index=1;

////////////////////////////////// private methods
	void do_perm_index(){  //works!
		for(int i=1; i<size_count.size(); i++){
			if(size_count[i].size() > 0) perm_index = lcm( perm_index, i );
		}
		return;
	}

	void form_loop(){    //works!
		size_count.clear();
		vector<vector<int>> aqwe(n+1);
		size_count=aqwe;		

		loop = new vector<int> [n];
		for(int i=0; i<n; i++){
			loop[i].push_back(i);
			int next = a[i];
			while(next!=i){
				if(next<i){
					loop[i].clear();
					break;
				}
				loop[i].push_back(next);
				next=a[next];
			}
			size_count[loop[i].size()].push_back(i);
		}
		this->do_perm_index();
	return;
	}

///////////////////////////////////////////
	permutation(int n, vector<int> * loop, vector<vector<int>> &size_count){
		this->n=n;
		int *b = new int[n];
		
		for(int lp_size=1; lp_size<n+1; lp_size++){
				
				for(int index=0; index<size_count[lp_size].size(); index++){
					int lp=size_count[lp_size][index];
					for(int lp_index=0; lp_index < lp_size-1; lp_index++){
						b[loop[lp][lp_index]]=loop[lp][lp_index+1];
					}
					b[loop[lp][lp_size-1]]=loop[lp][0];
				}
		}
		a=b;
		this->form_loop();
	}


public:
	permutation(int n, int a[]) {  //i<=n<=100
		this->n = n;
		int *b = new int[n];
		for (int i=0; i<n; i++)
			b[i]=a[i];
		this->a = b;

		this->form_loop();
	}

	permutation (permutation const &q){
		n=q.n;
		int *b = new int[n];
		for (int i=0; i<n; i++)
			b[i]=q.a[i];
		a=b;
		this->form_loop();
	}

	~permutation(){
		delete[] a; 
		delete[] loop;  //no memory leak da.
	}

	permutation const operator= (permutation const &q){ //q might hav different size. account for it!!
		n=q.n;
		delete[] a;

		int *b = new int[n];
		for (int i=0; i<n; i++)
			b[i]=q.a[i];
		a=b;
		this->form_loop();
		return *this;
	}

	int size() const{
		return n;
	}

	int* to_array() const{
		int *b = new int[n];
		for(int i=0; i<n; i++) b[i]=a[i];
		return b;
	}

	permutation const operator-() const{ //given inverse function   works!!
		int b[n];
		for(int i=0; i<n; i++) 	
			b[a[i]]=i;
		class permutation I(n,b);
		return I;
	}

	permutation const operator* (permutation const &q) const{  //works!
		int b[n];
		for (int i=0; i<n; i++)
			b[i]=a[q.a[i]];
		class permutation P(n,b);
		return P;	
	}

	permutation const square_root() const{ //return identity p(i)=i if no squareroot  //works!
		int bqw[n];
		for (int i=0; i<n; i++)bqw[i]=i;
		permutation IDENTITY(n,bqw);

		for(int SIZE=2; SIZE<n; SIZE+=2){
			if(size_count[SIZE].size()%2 == 1) return IDENTITY;
		}

		int b[n];
		
		for(int lp_size=1; lp_size<n+1; lp_size++){  //optimized!
			
			if(lp_size%2 == 1){    //loop of size 5
				for(int index=0; index<size_count[lp_size].size(); index++){ //maybe 2 such loops r there
					int lp=size_count[lp_size][index];    //loop's index in loop[].
					for(int lp_index=0; lp_index < lp_size; lp_index++){  //index of elem in the loop
						b[loop[lp][lp_index]] = loop[lp][(lp_index + ((lp_size+1)/2))%lp_size];
					}
				}
			}

			else{															//loop of size 6	
				for(int index=0; index<size_count[lp_size].size(); index+=2){ //8 such loops are there
					int lp1=size_count[lp_size][index];    //first loop
					int lp2=size_count[lp_size][index+1];  // second loop
					for(int lp_index=0; lp_index < lp_size-1; lp_index++){
						b[loop[lp1][lp_index]]=loop[lp2][lp_index];
						b[loop[lp2][lp_index]]=loop[lp1][lp_index+1];
					}
					b[loop[lp1][lp_size-1]]=loop[lp2][lp_size-1];
					b[loop[lp2][lp_size-1]]=loop[lp1][0];
				}
			}

		}
		permutation f(n,b);
		return f;
	}

	permutation const operator^ (long long int power) const{ //mind the long long! //works!

		int b[n];
		for (int i=0; i<n; i++)b[i]=i;
		permutation IDENTITY(n,b);

		if(power==0) return IDENTITY;

		power = power%perm_index;

		if(power<=100) return (*this)*((*this)^power-1);

		permutation f=IDENTITY;
		f.loop= new vector<int> [n];
		f.size_count.clear();
		vector<vector<int>> aqwe(n+1);
		f.size_count=aqwe;

		
		for(int lp_size=1; lp_size<n+1; lp_size++){   //size can be 5
			int clock_size=lp_size;
			int skip=(power%clock_size);
			int gcd_both = gcd(clock_size, skip);
			
			for(int index=0; index<size_count[lp_size].size(); index++){ //say 4 pieces are there in lp_length==5
				int lp=size_count[lp_size][index];  //lp is loop index in loop[]
				// int b[lp_size];

				for(int lp_index=0; lp_index < lp_size; lp_index++){ //index inside loop[]
					// b[lp_index]=loop[lp][lp_index];
					int ref=loop[lp][lp_index];
					f.loop[ref].push_back(ref);
					int next=loop[lp][(lp_index+skip)%lp_size];

					for(int zx=1; zx< clock_size/gcd_both; zx++){
						if(next < ref){
							f.loop[ref].clear();
							break;
						} 
						f.loop[ref].push_back(next);
						next = loop[lp][(lp_index+(skip*(1+zx)))%lp_size];
					}
					f.size_count[f.loop[ref].size()].push_back(ref);
				}
			}
		}


		permutation ans(n,f.loop,f.size_count);
		return ans;
	}

	bool is_power(permutation const &q) const{ //working
		permutation qtemp=q^0;
		if(n!=q.n) return 0;

		for(long long int i=1; i<=q.perm_index; i++){
			bool equal=1;
			for(int qa=0; qa<n; qa++){
				if(a[qa]!=qtemp.a[qa]) {equal=0;break;}
			}
			if(equal) return 1;
			qtemp=qtemp*q;
		}
		return 0;
	}

	int log(permutation const &q) const{ //find smallest value i, if it exists. Compute to modulo 10^9+7.
											// reutrn -1, if no such i.
		permutation qtemp=q^0;
		if(n!=q.n) return -1;

		for(long long int i=1; i<=q.perm_index; i++){
			bool equal=1;
			for(int qa=0; qa<n; qa++){
				if(a[qa]!=qtemp.a[qa]) {equal=0;break;}
			}
			if(equal) return (i-1)%(1000000007);
			qtemp=qtemp*q;
		}
		return -1;
	}
};

