// remove all the sanity checks, as sir already told to assume, and in testcases,
 // he would use appropiately, which may not pass ur checks...
// so, REMOVE SANITY CHECKS.
//remove int main()


// RECURSION, RECURSION andd RECURSION!
// base case for all functions  is           if(!top_left) blah...

//major flaw, if we revert the changes, children are not deleted....write a function regulate()???
// wrote regulate() for this.... DONE.

//DONE shouldn't need to write seperate set_num_1()..... make computatoins at the spot...

#include <iostream>
using namespace std;
#include <string>

long long int ONE = 1;

// tree structure to represent images of size 2^n x 2^n. 256x256 or 1024x1024

// quad_tree is a rooted tree.... every node has 0 or 4 children
// quad tree corresponds to submatrix of size 2^i x 2^i...
// root node is entire matrix.
// image pixel entries are either 0 or 1. CLIP-ART ??


class quad_tree {

	quad_tree *top_left = NULL; 
	quad_tree *top_right = NULL; 
	quad_tree *bottom_right = NULL; 
	quad_tree *bottom_left = NULL; 
	int value; //0 or 1
	int n = 0; // which power of 2. does this quad_tree === submatrix refer to..
	// n is height
	// string name = "QTREE";
	long long int  num_1;
	// if adding any new variable, add in copy constructor too!
public:

	void set_num1_leaf(){
		if(top_left){
			cout << "ALERT: misusing set_num1_leaf  : "<<endl;
			return;
		}
		if(value) num_1 = ONE<<(2*n);
		else num_1 = 0;
	}

	void set_num1_node(){
		if(top_left) num_1 = 
			top_left->num_1 + 
			top_right->num_1 + 
			bottom_left->num_1 + 
			bottom_right->num_1 ;

		else cout<<"==ALERT: misusing set_num1_node"<<endl;
	}

	quad_tree (int n){ //n is height of quad_tree.... 20 max.... 2^20 is int range ok.
		value = 0;
		this->n = n;
		num_1 = 0;
	}

	quad_tree (int n, int value){ //value is value
		this->value = value;
		this->n = n;
		set_num1_leaf();
	}

	// quad_tree (int n, int value, string name){ //value is value
	// 	this-> name = name;
	// 	this->value = value;
	// 	this->n = n;
	// 	set_num1_leaf();
	// }


	~quad_tree (){
			// cout << "dectructor called on size = "<<n<<endl;
		if(top_left) {
			// cout << "top_left activated dectructor called on size = "<<n<<endl;
			delete top_left;
			delete top_right;
			delete bottom_left;
			delete bottom_right;
		}
	}

	quad_tree (quad_tree const &Q){ //copy constructor
		value = Q.value;
		n = Q.n;
		num_1 = Q.num_1;
		if(Q.top_left){
			top_left = new quad_tree(*(Q.top_left));
			top_right = new quad_tree(*(Q.top_right));
			bottom_right = new quad_tree(*(Q.bottom_right));
			bottom_left = new quad_tree(*(Q.bottom_left));
		}
	}

	void regulate(){ //to make sure there are no useless childs... hahaha, daddy wants only good kids.
		if(
			!top_left->top_left &&
			!top_right->top_left &&
			!bottom_left->top_left &&
			!bottom_right->top_left &&
			//this makes sure, that every child is a leaf
			top_left->value == top_right->value &&
			top_right->value == bottom_right->value &&
			bottom_right->value == bottom_left->value
			//to check that all four childs are equal
			)
		{
			value = top_right->value;
			if(n != top_left->n + 1) cout<<" Smthing going wrong in regulate"<<endl;

			delete top_left;
			delete top_right;
			delete bottom_left;
			delete bottom_right;

			top_left = NULL;
			top_right = NULL;
			bottom_left = NULL;
			bottom_right = NULL;

			set_num1_leaf();

			//now, our current node is a leaf...awww.
		}
	}

	void set (int x1, int y1, int x2, int y2, int b){ //V_2 is possible

		if( x1<0 || x2<0 || y1<0 || y2<0) { //failsafes
			cout <<endl <<"this should'nt be happening; error in set function"<<endl;
			return;
		}
		if( x1>=1<<n || x2>=1<<n || y1>=1<<n || y2>=1<<n) { //failsafes
			cout <<endl <<"this should'nt be happening; error in set function"<<endl;
			return;
		}

		// cout << "Set function called:" << endl;
		// printf("n is %d, x1 is %d, x2 is %d, y1 is %d, y2 is %d \n",n,x1,x2,y1,y2);

		if(!top_left){

			if (b == value) return; //one basecase

			if ( (x1 == 0) && (y1 == 0) && (x2 == (1<<n)-1) && (y2 == (1<<n)-1)){ 
				//another base case.
				value = b;
				set_num1_leaf();

				// printf("SWAPPED: value is swapped, size n= %d \n",n);
				return;
			}

			top_left = new quad_tree(n-1, value);
			top_right = new quad_tree(n-1, value);
			bottom_left = new quad_tree(n-1, value);
			bottom_right = new quad_tree(n-1, value);
			// cout << "children created for size n= "<<n<<endl;
		}

		bool x1_r = ( 0<=x1 && (x1<(1<<(n-1))) );
		bool x2_r = ( 0<=x2 && (x2<(1<<(n-1))) );
		bool y1_r = ( 0<=y1 && (y1<(1<<(n-1))) );
		bool y2_r = ( 0<=y2 && (y2<(1<<(n-1))) );

		int mid_left = (1<<(n-1))-1;
		int mid_right = (1<<(n-1));

		if (x1_r && x2_r && y1_r && y2_r) {
			top_left->set(x1, y1, x2, y2, b );
		}
		if (!x1_r && !x2_r && y1_r && y2_r) {
			top_right->set(x1-mid_right, y1, x2-mid_right, y2, b );
		}
		if (x1_r && x2_r && !y1_r && !y2_r) {
			bottom_left->set(x1, y1-mid_right, x2, y2-mid_right, b );
		}
		if (!x1_r && !x2_r && !y1_r && !y2_r) {
			bottom_right->set(x1-mid_right, y1-mid_right, x2-mid_right, y2-mid_right, b );
		}
		if (x1_r && x2_r && y1_r && !y2_r) {
			top_left->set(x1, y1, x2, mid_left, b );
			bottom_left->set(x1, 0, x2, y2-mid_right, b );
		}
		if (x1_r && !x2_r && y1_r && y2_r) {
			top_left->set(x1, y1, mid_left, y2, b );
			top_right->set(0, y1, x2-mid_right, y2, b );
		}
		if (!x1_r && !x2_r && y1_r && !y2_r) {
			top_right->set(x1-mid_right, y1, x2-mid_right, mid_left, b );
			bottom_right->set(x1-mid_right, 0, x2-mid_right, y2-mid_right, b );
		}
		if (x1_r && !x2_r && !y1_r && !y2_r) {
			bottom_left->set(x1, y1-mid_right, mid_left, y2-mid_right, b );
			bottom_right->set(0, y1-mid_right, x2-mid_right, y2-mid_right, b );
		}
		if (x1_r && !x2_r && y1_r && !y2_r) {
			top_left->set(x1, y1, mid_left, mid_left, b );
			top_right->set(0, y1, x2-mid_right, mid_left, b );
			bottom_left->set(x1, 0, mid_left, y2-mid_right, b );
			bottom_right->set(0, 0, x2-mid_right, y2-mid_right, b );
		}
		//deleting useless childrens....
		regulate();
		if(top_left) set_num1_node() ;

		return;
	}

	int get (int x1, int y1) const {

		if( x1<0 || y1<0 ) { //failsafes
			cout <<endl <<"this should'nt be happening; error in get function"<<endl;
			return 0;
		}
		if( x1>=1<<n || y1>=1<<n ) { //failsafes
			cout <<endl <<"this should'nt be happening; error in get function"<<endl;
			return 0;
		}

		if(!top_left) return value;
		else {

			bool x1_r = ( 0<=x1 && (x1<(1<<(n-1))) );
			bool y1_r = ( 0<=y1 && (y1<(1<<(n-1))) );
			int mid_right = (1<<(n-1));

			if(x1_r && y1_r ) return top_left->get(x1, y1);
			if(!x1_r && y1_r ) return top_right->get(x1-mid_right, y1);
			if(x1_r && !y1_r ) return bottom_left->get(x1, y1-mid_right);
			if(!x1_r && !y1_r ) return bottom_right->get(x1-mid_right, y1-mid_right);
		}
		return -1;
	}

	int size() const {
		return n;
	}

	void overlap (quad_tree const &Q){

		// if(n!=Q.n) { //sanity check
		// 	cout<<"Something's wrong in overlap function, sizes dont match"<<endl;
		// 	return;
		// }

		if(!Q.top_left){

			if(Q.value == 1){
				value = 1;
				num_1 = ONE<<(2*n);
				if(top_left){
					delete top_left;
					delete top_right;
					delete bottom_left;
					delete bottom_right;
					top_left = NULL;
					top_right = NULL;
					bottom_left = NULL;
					bottom_right = NULL;
				}
				return;
			}
			else{
				return;
			}
		}

		else {

			if (!top_left) {
				if(value==1){
					return;
				}
				else{  //now, *this equals Q after overlap
					value = Q.value;
					num_1 = Q.num_1;
					top_left = new quad_tree(*(Q.top_left));
					top_right = new quad_tree(*(Q.top_right));
					bottom_left = new quad_tree(*(Q.bottom_left));
					bottom_right = new quad_tree(*(Q.bottom_right));
					return;
				}
			}
			else{
				top_left->overlap( *(Q.top_left));
				top_right->overlap( *(Q.top_right));
				bottom_left->overlap( *(Q.bottom_left));
				bottom_right->overlap(*(Q.bottom_right));

				regulate();
				if(top_left) set_num1_node();

				return;

			}
		}

	}

	void intersect (quad_tree const &Q){

		// if(n!=Q.n) { //sanity check
		// 	cout<<"Something's wrong in intersect function, sizes dont match"<<endl;
		// 	return;
		// }

		if(!Q.top_left){

			if(Q.value == 0){
				value = 0;
				num_1 = 0;
				if(top_left){
					delete top_left;
					delete top_right;
					delete bottom_left;
					delete bottom_right;
					top_left = NULL;
					top_right = NULL;
					bottom_left = NULL;
					bottom_right = NULL;
				}
				return;
			}
			else{
				return;
			}
		}

		else {

			if (!top_left) {
				if(value == 0){
					return;
				}
				else{  //now, *this equals Q after intersect
					value = Q.value;
					num_1 = Q.num_1;
					top_left = new quad_tree(*(Q.top_left));
					top_right = new quad_tree(*(Q.top_right));
					bottom_left = new quad_tree(*(Q.bottom_left));
					bottom_right = new quad_tree(*(Q.bottom_right));
					return;
				}
			}
			else{
				top_left->intersect( *(Q.top_left));
				top_right->intersect( *(Q.top_right));
				bottom_left->intersect( *(Q.bottom_left));
				bottom_right->intersect(*(Q.bottom_right));

				regulate();
				if(top_left) set_num1_node();

				return;

			}
		}

	}

	void complement (){

		if( !top_left ){
			value = 1-value ;
		}
		else {
			top_left->complement();
			top_right->complement();
			bottom_left->complement();
			bottom_right->complement();
		}

		num_1 = (ONE<<(2*n)) - num_1;
	}

	// void set_num_1(){
	// 	if(!top_left) {
	// 		if(value) num_1 = ONE<<(2*n);
	// 		else num_1 = 0;
	// 		return;
	// 	}

	// 	else{
	// 		top_left->set_num_1();
	// 		top_right->set_num_1();
	// 		bottom_left->set_num_1();
	// 		bottom_right->set_num_1();
	// 		num_1 = top_left->num_1 + top_right->num_1 + bottom_left->num_1 + bottom_right->num_1 ;
	// 		return;
	// 	}
	// }

	void resize (int m) {
		if(n == m) return;

		if(m > n){
			if(!top_left){
				num_1 = num_1 * (ONE<<(2*(m-n)));
				n = m;
				return;
			}
			else{
				num_1 = num_1 * (ONE<<(2*(m-n)));
				n = m;
				top_left->resize(m-1);
				top_right->resize(m-1);
				bottom_left->resize(m-1);
				bottom_right->resize(m-1);
			}
			return;
		}

		if(m < n){

			if(!top_left){
				n = m;
				set_num1_leaf();
				//no need of regulation
				return;
			}

			if(m==0){

				// set_num_1();

				if(num_1 >= (ONE<<(2*n - 1))) value = 1;
				else value = 0;

				n = m;
				// regulation, to delete useless childs without mercy
				if(top_left){
					delete top_left;
					delete top_right;
					delete bottom_left;
					delete bottom_right;
					top_left = NULL;
					top_right = NULL;
					bottom_left = NULL;
					bottom_right = NULL;
				}
				set_num1_leaf();
			}

			else{
				n=m;
				top_left->resize(m-1);
				top_right->resize(m-1);
				bottom_left->resize(m-1);
				bottom_right->resize(m-1);
				regulate();
				if(top_left)set_num1_node();
			}

			return;
		}
	}

	void extract (int x1, int y1, int m){ //daffa code!!!
		// cout<<"nahanasd"<<endl;
		if(m == n) return;

		if(!top_left) {
			n = m;
			set_num1_leaf();
			return;
		}

		quad_tree *ans = extract_tree(x1, y1, m);


		// for(int x=0; x < (1<<m); x++)
		// 	for(int y=0; y < (1<<m); y++){
		// 		// cout << x <<" , "<<y<<endl;
		// 		ans->set(x, y, x, y, get(x+x1, y+y1));
		// 		// ans->print();
		// 		// ans->print_tree();
		// 		// cout<<endl;
		// 	}

		if(top_left){    //making *this as a brand-new quadtree...
			delete top_left;
			delete top_right;
			delete bottom_left;
			delete bottom_right;
			top_left = NULL;
			top_right = NULL;
			bottom_left = NULL;
			bottom_right = NULL;
		}

		n = ans->n;
		if(n!=m){
			cout<<"Somthing wrong with height of extract_tree"<<endl;
			return;
		}
		value = ans->value;
		num_1 = ans->num_1;

		if(ans->top_left){
			top_left = ans->top_left;
			top_right = ans->top_right;
			bottom_left = ans->bottom_left;
			bottom_right = ans->bottom_right;
			ans->top_left = NULL;
			ans->top_right = NULL;
			ans->bottom_left = NULL;
			ans->bottom_right = NULL;
		}
		delete ans;
	}

	quad_tree* extract_tree(int x1, int y1, int m){ //verify whether num_1 is updated neatly
		// should create a copy, and not point to the same thing....
		quad_tree* ans = NULL;

		if(m == n) {
			ans = new quad_tree(*this);
			return ans;
		}

		if(!top_left) {
			ans = new quad_tree(m, value);
			return ans;
		}

		int x2 = x1 + (1<<m)-1;
		int y2 = y1 + (1<<m)-1;

		if(x2>=(1<<n)) {
			cout<<"Something wrong in extract_tree"<<endl;
			return ans;
		}
		if(y2>=(1<<n)) {
			cout<<"Something wrong in extract_tree"<<endl;
			return ans;
		}

		int mid_right = (1<<(n-1));

		bool x1_r = ( 0<=x1 && x1 < mid_right );
		bool x2_r = ( 0<=x2 && x2 < mid_right );
		bool y1_r = ( 0<=y1 && y1 < mid_right );
		bool y2_r = ( 0<=y2 && y2 < mid_right );

		if (x1_r && x2_r && y1_r && y2_r) {
			ans = top_left->extract_tree(x1, y1, m);
		}
		else if (!x1_r && !x2_r && y1_r && y2_r) {
			ans = top_right->extract_tree(x1-mid_right, y1, m);
		}
		else if (x1_r && x2_r && !y1_r && !y2_r) {
			ans = bottom_left->extract_tree(x1, y1-mid_right, m);
		}
		else if (!x1_r && !x2_r && !y1_r && !y2_r) {
			ans = bottom_right->extract_tree(x1-mid_right, y1-mid_right, m);
		}
		else {
			ans = new quad_tree(m);
			ans->top_left = extract_tree(x1, y1, m-1);
			ans->top_right = extract_tree(x1 + (1<<(m-1)), y1, m-1);
			ans->bottom_left = extract_tree(x1, y1 + (1<<(m-1)), m-1);
			ans->bottom_right = extract_tree(x1 + (1<<(m-1)), y1 + (1<<(m-1)), m-1);
			//deleting useless childrens....
			ans->regulate(); //regulate sets the num_1 also...
			if(ans->top_left) ans->set_num1_node() ;
		}

		return ans;

	}

	void print(){
		for( int y=0; y<(1<<n); y++){
			for(int x=0; x<(1<<n); x++){
				cout << this->get(x,y)<< " ";
			}
			cout<<endl;
		}
		cout<<"=================================="<<endl;
	}

	void print_num1(){
		cout << "NUM of 1's in Image: " << num_1 << endl; 
		// printf("NUM of 1's in Image: %d\n", num_1);
	}

	void print_tree(){

		if(!top_left){
			cout << " ("<<   value   <<") ";
		}
		else{
		cout<<" ( ";
		top_left->print_tree();
		top_right->print_tree();
		bottom_left->print_tree();
		bottom_right->print_tree();
		cout<<" ) ";
		}
	}

};


int main(int argc, char const *argv[]){

	quad_tree P(2);
	P.set(0,0,2,2,1);
	P.print_tree();cout<<endl;

	// cout<< P.get(1,1)<<endl;
	P.print();
	P.resize(4);
	quad_tree Q(4,0);
	Q.set(2,0,3,3,1);
	Q.print();
	P.overlap(Q);
	P.print();
	cout<<"ovelrpa"<<endl;
	// P.complement();
	P.resize(6);
	// P.print();
	P.resize(2);
	P.print();
	P.print_num1();
	P.complement();
	P.print();
	P.print_num1();
	P.resize(4);
	P.print();
	cout << "size is "<<P.size()<<endl;
	// P.complement();
	P.print_num1();
	P.resize(0);
	P.print();
	cout<<"<<<    checkmark     >>>"<<endl;
	// P.set(0,0,0,0,0);
	// P.set(1,1,1,1,0);
	// P.set(2,2,2,2,0);
	// P.set(3,3,3,3,0);
	// P.set(5,4,5,4,0);
	P.complement();
	P.print();
	P.print_num1();
	// cout<<"\n\n\n\n";
	// P.extract(2,2,2);
	P.print();
	P.print_tree();
	P.print_num1();

	// long long int a = 12;
	// a = (ONE<<(35)) - a;
	// cout<<a<<endl;

	// quad_tree* a= NULL;
	// a->print();

	cout << "\nDon't forget to delete main-function finally"<<endl;

}






