// Lvalue and Rvalue reference function param and return demonstration
#include <iostream>

using namespace std;

// Lvalue is address
// Rvalue is data

int global = 100;

// Returns a Lvalue reference to the global variable
int & func_lvalue_ret() {
	cout << "\n\t" << "func_lvalue_ret called" << endl;
	return global;
}

// Takes a Lvalue reference and changes it
void func1(int &lref) {
	cout << "\n\t" << "func1 called" << endl;
	cout << "\n\t" << "Before lref: " << lref << " &lref: " << &lref << endl;
	lref++;
	cout << "\n\t" << "After lref: " << lref << " &lref: " << &lref << endl;
}

// Takes const Lvalue reference (can bind to Rvalue or direct data) and changes it using const_cast
void func2(const int& rref)
{
	cout << "\n\t" << "func2 called" << endl;
	cout << "\n\t" << "Before rref: " << rref << " &rref: " << &rref << endl;
	int & non_const_ref = const_cast<int &>(rref);
	non_const_ref++;
	cout << "\n\t" << "Before non_const_ref: " << non_const_ref << " &non_const_ref: " << &non_const_ref << endl;
}

int main() {

	cout << "\n\t" << "Initial global: " << global << " &global: " << &global << endl;

	// Assigning Lvalue to 200
	// This function returns address of global variable, so basically it returns reference of an address, i.e., reference of an lvalue
	// Here you can see the difference that normal rvalue cannot be assigned to lvalue& (int& ref = 20 //error)
	// But can be assigned ot const lvalue&
	// Here function returns lvalue& but still you can assign the value, i.e. because you already have a memory address available to store the value
	// Inside the function you can either create a variable or refer to a global variable and then assign the value and return the same memory back, 
	// which will be used to store the value.
	// This means compiler will optimize to a greater extent and sees if the end results match and then does the operation meaning
	// in this case
	// Compiler on the left hand side requires a memory location to store a value and on the right hand side needs a value to be stored in a memory location
	// function returns an address and LHS is nothing but a memory address and right hand side is value
	// So, it works.
	func_lvalue_ret() = 200;
	cout << "\n\t" << "Assigned to lvalue by returning from fn call global: " << global << " &global: " << &global << endl;
	
	// Passing Lvalue and incrementing it
	// This function func1 takes lvalue reference as parameter.
	// Here we pass the memory location that is returned by the function func_lvalue_ret
	func1(func_lvalue_ret());
	cout << "\n\t" << "Assigned to lvalue by passing as parameter to fn call global: " << global << " &global: " << &global << endl;
	
	// Passing Lvalue to (const Lvalue reference can directly hold data as const qualifier will allocate it memory,
	// so const lvalue reference can hold direct data or it can be though of as const Lvalue reference can bind to Rvalue) function 
	// and parameter is automatically type casted to const int &
	// The function func2 takes an const lvalue reference. This means we can pass direct data to this function
	// 
	func2(func_lvalue_ret());
	cout << "\n\t" << "Calling Lvalue reference in Rvalue function global: " << global << " &global: " << &global << endl;

	// Passing Rvalue to const Lvalue reference function.
	func2(200);
	cout << "\n\t" << "After Rvalue change no effect to global global: " << global << " &global: " << &global << endl;

}
