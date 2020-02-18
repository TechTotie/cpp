#include <iostream>
#include <unistd.h>
#include <vector>

using namespace std;

using cb_fnptr = void(*)(void *);
class Callback {
	public:
		Callback(cb_fnptr fnptr, void* data)
		: m_cbptr(fnptr), m_data(data) {
		}
		cb_fnptr m_cbptr;
		void * m_data;
};

std::vector<Callback> vec_cb_fns;

void RegisterFunc(const Callback &callbackfn) {
	vec_cb_fns.push_back(std::move(callbackfn));
}

void ExecuteCallback() {
	for(auto& fn : vec_cb_fns) {
		fn.m_cbptr(fn.m_data);
	}
}

void LoopCallback() {
	while(1) {
		ExecuteCallback();
		sleep(1);
	}
}

// Test Code
//using cb_fnptr = void(*)(void *);
void func1(int * x) {
	cout << "x: " << *x << endl;
}
void func2(int * y) {
	cout << "y: " << *y << endl;
}


int main()
{
	int x =20;
	int y = 50;
	// Typecast functions to cb_fnptr and data to void *
	RegisterFunc(Callback((cb_fnptr)func1, (void *)&x));
	RegisterFunc(Callback((cb_fnptr)func2, (void *)&y));
	LoopCallback();
}
