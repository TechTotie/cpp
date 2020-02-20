## Lvalue variables and functions Demystified

This program demonstrates the variables, lvalues, lvalue references used as part of function parameters and return types.

Remember that

***Lvalue is address, anyuthing that is stored in memory***
***Rvalue is data, anything that is stored in CPU registers***

For simplicity I will omit, the explaination of some code like # include, using namespace, int main(int argc, char *argv[]) and return 0.

```c++
#include <iostream>
using namespace std;
```

```c++
int global = 100;
```

Define a ***global variable, that is stored in intialized Data Segment*** and assign it value 100.

Let us define a function that returns a Lvalue reference to the global variable

```c++
int & func_lvalue_ret() {
	cout << "\n\t" << "func_lvalue_ret called" << endl;
	return global;
}
```



Let us define another function that takes a Lvalue reference and changes it

```c++
void func1(int &lref) {
	cout << "\n\t" << "func1 called" << endl;
	cout << "\n\t" << "Before lref: " << lref << " &lref: " << &lref << endl;
	lref++;
	cout << "\n\t" << "After lref: " << lref << " &lref: " << &lref << endl;
}
```



Let us define another function that takes const Lvalue reference (can bind to Rvalue or direct data) and changes it using const_cast

```c++
void func2(const int& rref)
{
	cout << "\n\t" << "func2 called" << endl;
	cout << "\n\t" << "Before rref: " << rref << " &rref: " << &rref << endl;
	int & non_const_ref = const_cast<int &>(rref);
	non_const_ref++;
	cout << "\n\t" << "Before non_const_ref: " << non_const_ref << " &non_const_ref: " << &non_const_ref << endl;
}
```



Now main function

```c++
int main() {
cout << "\n\t" << "Initial global: " << global << " &global: " << &global << endl;
```



```c++
func_lvalue_ret() = 200;
cout << "\n\t" << "Assigned to lvalue by returning from fn call global: " << global << " &global: " << &global << endl;
```

In the above statement, `func_lvalue_ret() = 200`

I am assigning Lvalue to 200.
This function returns address of global variable, so basically it returns reference of an address, i.e., reference of an lvalue.
Here you can see the difference that normal rvalue cannot be assigned to lvalue& (int& ref = 20 //error)
But can be assigned ot const lvalue&.
Here function returns lvalue& but still you can assign the value, i.e. because you already have a memory address available to store the value.
Inside the function you can either create a variable or refer to a global variable and then assign the value and return the same memory back,  which will be used to store the value.
This means compiler will optimize to a greater extent and sees if the end results match and then does the operation meaning in this case.
Compiler on the left hand side requires a memory location to store a value and on the right hand side needs a value to be stored in a memory location.
The function returns an address and LHS is nothing but a memory address and right hand side is value.
***So, it works.***

```c++
func1(func_lvalue_ret());
cout << "\n\t" << "Assigned to lvalue by passing as parameter to fn call global: " << global << " &global: " << &global << endl;
```

In the above statement, `func1(func_lvalue_ret());`

I am passing Lvalue and incrementing it.
This function func1 takes lvalue reference as parameter.
 Here we pass the memory location that is returned by the function func_lvalue_ret.

```c++
func2(func_lvalue_ret());
cout << "\n\t" << "Calling Lvalue reference in Rvalue function global: " << global << " &global: " << &global << endl;

```

In the above statement, `func2(func_lvalue_ret());`

I am passing Lvalue to (const Lvalue reference can directly hold data as const qualifier will allocate it memory, so const lvalue reference can hold direct data or it can be though of as const Lvalue reference can bind to Rvalue) function and parameter is automatically type casted to const int &.
The function func2 takes an const lvalue reference. This means we can pass direct data to this function, which is as shown in the next statement `func2(200)`.

```c++
// Passing Rvalue to const Lvalue reference function.
func2(200);
cout << "\n\t" << "After Rvalue change no effect to global global: " << global << " &global: " << &global << endl;
}
```

###### *Output of program for reference*

```powershell
        Initial global: 100 &global: 0x472010

        func_lvalue_ret called

        Assigned to lvalue by returning from fn call global: 200 &global: 0x472010

        func_lvalue_ret called

        func1 called

        Before lref: 200 &lref: 0x472010

        After lref: 201 &lref: 0x472010

        Assigned to lvalue by passing as parameter to fn call global: 201 &global: 0x472010

        func_lvalue_ret called

        func2 called

        Before rref: 201 &rref: 0x472010

        Before non_const_ref: 202 &non_const_ref: 0x472010

        Calling Lvalue reference in Rvalue function global: 202 &global: 0x472010

        func2 called

        Before rref: 200 &rref: 0x70fe0c

        Before non_const_ref: 201 &non_const_ref: 0x70fe0c

        After Rvalue change no effect to global global: 202 &global: 0x472010

```



## ***TakeAways***

Lvalues references can be returned from functions.

Lvalue references can be assigned values.

Compiler will optimize and generate code so that if lvalue references are assigned values then it does not throw compiler error due to type mismatch like LHS is lvalue reference (non const) and RHS is rvalue. Rather it just assigns the value to the memory location returned.

const lvalue reference can refer to rvalues. (as const qualifier helps store variable in memory).

