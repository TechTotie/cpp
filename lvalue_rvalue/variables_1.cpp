// Lvalue Rvalue Demonstration Program
#include <iostream>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

int main(int argc, char** argv) {

	// Lvalue stored in memory
	// Whenever variables are created, memory is allocated for variables and the value is stored directly in these memory locations.
	int x = 10;
	cout << "\n\t" << " x: " << x << " &x: " << &x << endl;
	
	// Lvalue reference
	int & xref = x;
	xref++;
	cout << "\n\t" << " xref: " << xref << " &xref: " << &xref << endl;
	
	// Rvalue temporary
	// Will not compile without const as it thinks the reference value will change which has no memory location.
	// Always rvalues are stored in CPU general purpose registers which are temporary storage locations as they will be overwritten
	// int & ref = 20; //error
	
	// Adding constant will create a temporary object that is it creates a mmeory location in code segment due to const qualifier
	// and then it assigns the value to this memory location
	// This const object gets a place to be stored in code segment
	const int & rref = 20;
	cout << "\n\t" << " rref: " << rref << " &rref: " << &rref << endl;
	
	// Value of a Rvalue can be changed by casting it using const_cast
	int & tref = const_cast<int &>(rref);
	tref++;
	cout << "\n\t" << " tref: " << tref << " &tref: " << &tref << endl;

	return 0;
}
