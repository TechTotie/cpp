## Lvalue Variables and References Demystified

This program demonstrates the variables, lvalues and lvalue references.

For simplicity I will omit, the explaination of some code like # include, using namespace, int main(int argc, char *argv[]) and return 0.

```c++
#include <iostream>
using namespace std;

int main(int argc, char** argv)  {
```

Let us declare a variable `x` and assign `10` to it.

```c++
int x = 10;
```

#### *Some basics about Lvalues and Variables*

Whenever variables are created, memory is allocated for variables and the value is stored directly in these memory locations.

Lvalue is stored in memory.

```c++
cout << "\n\t" << " x: " << x << " &x: " << &x << endl;
```

##### Lvalue reference

Lvalue reference can assigned only lvalues and not rvalues. This is because during assignment compiler does a typecheck, if both are of the same type, or is there any implicit conversion possible or is there any explicit conversion operator or constructor present, and then compiler does an assignment.
According to the above conditions only same types can be assigned or different types can be typecasted and assigned or there is a need to provide a conversion operator or a constructor that does explicit conversion.

So, lvalue reference can only hold lvalues as it is a reference to lvalue.

To make it more clear,
 ***lvalues are nothing but address and rvalues are nothing but data***

```c++
int & xref = x;
xref++;
cout << "\n\t" << " xref: " << xref << " &xref: " << &xref << endl;
```

#### Rvalue (temporary and data)

Rvalues are nothing but data, and assigning a memory to a data reference will not work.
Data reference can hold only data and address references can hold only addresses.
If we try to assign address to a data reference, or data to a address reference, compiler will not allow as the types do not match.
So, below line will not compile as we are trying to assign data to an addrress reference.
This is beacuse 20 is a temporary constant value that is not stored in memory and will be temporarily stored in CPR registers to be copied to operand on LHS
Always rvalues are stored in CPU general purpose registers which are temporary storage locations as they will be overwritten
But LHS is an address reference that is expecting an address and CPU register is holding value, not address and CPU registers themselves cannot be treated as addresses.
Mostly, the temporary variables will be stored in CPU registers so that they can be immediately copied or assigned to a proper memory location.
So, we cannot assign a register/register's address to reference expecting memory address. 

```c++
// int & ref = 20; //error
```

But adding a const will make it work as constants are stored in Initialized Data Segment or Text Segment depending on the compiler, due to const qualifier.
Once the variable is stored in these segments, it will have a valid address, so we can assign this address to the addresss reference 
This const object gets a place to be stored in code segment


```c++
const int & rref = 20;
cout << "\n\t" << " rref: " << rref << " &rref: " << &rref << endl;
```
Value of a Rvalue can be changed by casting it using const_cast
Casting will allow to temporarily change the value stored in the code segment.

```c++
int & tref = const_cast<int &>(rref);
tref++;
cout << "\n\t" << " tref: " << tref << " &tref: " << &tref << endl;
```

```c++
return 0;
}
```

###### *Output of the program for reference*

```powershell
         x: 10 &x: 0x70fdf0

         xref: 11 &xref: 0x70fdf0

         rref: 20 &rref: 0x70fdf4

         tref: 21 &tref: 0x70fdf4
```



## ***TakeAways***

Lvalues are values stored in memory and can be access by addresses.

Rvalues are direct data and are stored temporarily in CPU registers.

Lvalues references can refer to lvalues only. (i.e., memory locations only).

const lvalue reference can refer to rvalues. (as const qualifier helps store variable in memory).