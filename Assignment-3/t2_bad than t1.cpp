// remove all the sanity checks, as sir already told to assume, and in testcases,
 // he would use appropiately, which may not pass ur checks...
// so, REMOVE SANITY CHECKS.
//remove int main()


// RECURSION, RECURSION andd RECURSION!
// base case for all functions  is           if(!top_left) blah...

//major flaw, if we revert the changes, children are not deleted....write a function regulate()???
// wrote regulate() for this.... DONE.

//shouldn't need to write seperate set_num_1()..... make computatoins at the spot...

#include <iostream>

using namespace std;

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
	long long int  num_1;
	// if adding any new variable, add in copy constructor too!
public:

	void set_num1_leaf(){
		if(top_left){
			cout << "ALERT: misusing set_num1_leaf"<<endl;
			return;
		}
		if(value) num_1 = 1<<(2*n);
		else num_1 = 0;
	}

	void set_num1_node(){
		if(top_left) num_1 = 
			top_left->num_1 + 
			top_right->num_1 + 
			bottom_left->num_1 + 
			bottom_right->num_1 ;

		else cout<<"==ALERT: You r misusing set_num1_node"<<endl;

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

	~quad_tree (){
			// cout << "dectructor called on size = "<<n<<endl;
		if(top_left) {
			// cout << "top_left activated dectructor called on size = "<<n<<endl;
			delete top_left;
			// cout<<"top_left deleted for size of "<<n<<endl;
			delete top_right;
			// cout<<"top_right deleted for size of "<<n<<endl;
			delete bottom_left;
			// cout<<"bottom_left deleted for size of "<<n<<endl;
			delete bottom_right;
			// cout<<"top_left deleted for size of "<<n<<endl;
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

			set_num1_leaf();

			delete top_left;
			delete top_right;
			delete bottom_left;
			delete bottom_right;

			top_left = NULL;
			top_right = NULL;
			bottom_left = NULL;
			bottom_right = NULL;

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

				printf("SWAPPED: value is swapped, size n= %d \n",n);
				return;
			}

			top_left = new quad_tree(n-1, value);
			top_right = new quad_tree(n-1, value);
			bottom_left = new quad_tree(n-1, value);
			bottom_right = new quad_tree(n-1, value);
			cout << "children created for size n= "<<n<<endl;
		}

		bool x1_r = ( 0<=x1 && (x1<(1<<(n-1))) );
		bool x2_r = ( 0<=x2 && (x2<(1<<(n-1))) );
		bool y1_r = ( 0<=y1 && (y1<(1<<(n-1))) );
		bool y2_r = ( 0<=y2 && (y2<(1<<(n-1))) );

		int mid_left = (1<<(n-1))-1;
		int mid_right = (1<<(n-1));

		if (x1_r && x2_r && y1_r && y2_r) {
			top_left->set(x1, y1, x2, y2, b );
			// cout << "set called on top-left"<<endl;
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

	int get (int x1, int y1) const {//FLAW: if again reverting, u will still have the children, but u shouldnt have na...

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

		if(n!=Q.n) { //sanity check
			cout<<"Something's wrong in overlap function, sizes dont match"<<endl;
			return;
		}

		if(!Q.top_left && Q.value == 1 ){ //wooo! big improvement...
			value = 1;
			num_1 = 1<<(2*n);

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

		if( !top_left && !Q.top_left ){
			value = value|Q.value;
			set_num1_leaf();
		}
		else if (top_left && !Q.top_left){
			top_left->overlap( quad_tree(n-1, Q.value));
			top_right->overlap( quad_tree(n-1, Q.value));
			bottom_left->overlap( quad_tree(n-1, Q.value));
			bottom_right->overlap( quad_tree(n-1, Q.value));
			regulate();
			if(top_left) set_num1_node();
		}

		else {

			if (!top_left) {
				top_left = new quad_tree(n-1, value);
				top_right = new quad_tree(n-1, value);
				bottom_left = new quad_tree(n-1, value);
				bottom_right = new quad_tree(n-1, value);
			}

			top_left->overlap( *(Q.top_left));
			top_right->overlap( *(Q.top_right));
			bottom_left->overlap( *(Q.bottom_left));
			bottom_right->overlap(*(Q.bottom_right));
			regulate();
			if(top_left) set_num1_node();

		}

		// else {
		// 	top_left->overlap( *(Q.top_left));
		// 	top_right->overlap( *(Q.top_right));
		// 	bottom_left->overlap( *(Q.bottom_left));
		// 	bottom_right->overlap(*(Q.bottom_right));
		// }

	}

	void intersect (quad_tree const &Q){

		if(n!=Q.n) { //sanity check
			cout<<"Something's wrong in intersect function, sizes dont match"<<endl;
			return;
		}

		if(!Q.top_left && Q.value == 0 ){//wooo! big improvement...
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

		if( !top_left && !Q.top_left ){
			value = value & Q.value;
			set_num1_leaf();
		}
		else if (top_left && !Q.top_left){
			top_left->intersect( quad_tree(n-1, Q.value));
			top_right->intersect( quad_tree(n-1, Q.value));
			bottom_left->intersect( quad_tree(n-1, Q.value));
			bottom_right->intersect( quad_tree(n-1, Q.value));
			regulate();
			if(top_left) set_num1_node();

		}
		else {
			if (!top_left) {
				top_left = new quad_tree(n-1, value);
				top_right = new quad_tree(n-1, value);
				bottom_left = new quad_tree(n-1, value);
				bottom_right = new quad_tree(n-1, value);
			}

			top_left->intersect( *(Q.top_left));
			top_right->intersect( *(Q.top_right));
			bottom_left->intersect( *(Q.bottom_left));
			bottom_right->intersect(*(Q.bottom_right));

			regulate();
			if(top_left) set_num1_node();
		}

		// else {
		// 	top_left->intersect( *(Q.top_left));
		// 	top_right->intersect( *(Q.top_right));
		// 	bottom_left->intersect( *(Q.bottom_left));
		// 	bottom_right->intersect(*(Q.bottom_right));
		// }

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
		num_1=(1<<(2*n))-num_1;
	}

	void set_num_1(){
		if(!top_left) {
			if(value) num_1 = 1<<(2*n);
			else num_1 = 0;
			return;
		}

		else{
			top_left->set_num_1();
			top_right->set_num_1();
			bottom_left->set_num_1();
			bottom_right->set_num_1();
			num_1 = top_left->num_1 + top_right->num_1 + bottom_left->num_1 + bottom_right->num_1 ;
			return;
		}
	}

	void resize (int m) {
		if(n == m) return;

		if(m > n){
			if(!top_left){
				n = m;
				return;
			}
			else{
				n=m;
				top_left->resize(m-1);
				top_right->resize(m-1);
				bottom_left->resize(m-1);
				bottom_right->resize(m-1);
			}
			return;
		}

		if(m < n){
			if(!top_left){
				n=m;
				//no need of regulation
				return;
			}
			if(m==0){
				set_num_1();
				n=m;
				// maybe delete childerens and set to null????
				if(num_1 >= 1<<n) value = 1;
				else value = 0;
				// regulation, to delete useless childs
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

			}
			else{
				n=m;
				top_left->resize(m-1);
				top_right->resize(m-1);
				bottom_left->resize(m-1);
				bottom_right->resize(m-1);
				regulate();
			}

			return;
		}
	}

	// void extract (int x1, int y1, int m){

	// }

	void print(){
		for( int y=0; y<(1<<n); y++){
			for(int x=0; x<(1<<n); x++){
				cout << this->get(x,y)<< " ";
			}
			cout<<endl;
		}
		cout<<"=================================="<<endl;
	}



};


int main(int argc, char const *argv[]){

	quad_tree P(2);
	P.set(0,0,2,2,1);

	// cout<< P.get(1,1)<<endl;
	P.print();
	quad_tree Q(2,0);
	Q.set(2,0,3,3,1);
	Q.print();
	P.overlap(Q);
	P.print();
	// P.complement();
	P.resize(6);
	// P.print();
	P.resize(2);
	P.print();





	cout << "Don't forget to delete main-function finally"<<endl;
}