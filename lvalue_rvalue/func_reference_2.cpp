// Lvalue and Rvalue reference function param and return demonstration
#include <iostream>

using namespace std;

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

// Takes Rvalue reference and changes it using const_cast
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
	func_lvalue_ret() = 200;
	cout << "\n\t" << "Assigned to lvalue by returning from fn call global: " << global << " &global: " << &global << endl;
	
	// Passing Lvalue and incrementing it
	func1(func_lvalue_ret());
	cout << "\n\t" << "Assigned to lvalue by passing as parameter to fn call global: " << global << " &global: " << &global << endl;
	
	// Passing Lvalue to Rvalue reference function and parameter is automatically type casted to const int &
	func2(func_lvalue_ret());
	cout << "\n\t" << "Calling Lvalue reference in Rvalue function global: " << global << " &global: " << &global << endl;

	// Passing Rvalue to Ravlue reference function.
	func2(200);
	cout << "\n\t" << "After Rvalue change no effect to global global: " << global << " &global: " << &global << endl;

}
