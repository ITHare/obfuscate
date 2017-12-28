// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "..\..\src\obfuscate.h"

using namespace obf;

template<class T, size_t N>
class ObfBitUint {
private:
	T val;
	static constexpr T mask = ((T)1 << N) - (T)1;
	static_assert(N < sizeof(T) * 8);
public:
	ObfBitUint() : val() {}
	ObfBitUint(T x) { val = x&mask; }
	operator T() const { assert((val&mask) == val); return val & mask; }
	ObfBitUint operator *(ObfBitUint x) const { return ObfBitUint(val * x.val); }
	ObfBitUint operator +(ObfBitUint x) { return ObfBitUint(val + x.val); }
	ObfBitUint operator -(ObfBitUint x) { return ObfBitUint(val - x.val); }
	ObfBitUint operator %(ObfBitUint x) { return ObfBitUint(val%x.val);/*TODO: double-check*/ }
	ObfBitUint operator /(ObfBitUint x) { return ObfBitUint(val / x.val); /*TODO: double-check*/ }
};

#ifndef NDEBUG
#define DBGPRINT
#endif

NOINLINE OBF6(int64_t) factorial(
	OBF6(size_t) x) {
#ifdef DBGPRINT
	static bool xPrinted = false;
	if (!xPrinted) {
		std::cout << "x:" << std::endl;
		x.dbgPrint(1);
	}
	xPrinted = true;
#endif
	OBF3(int64_t) ret = 1;
#ifdef DBGPRINT
	static bool retPrinted = false;
	if (!retPrinted) {
		std::cout << "ret:" << std::endl;
		ret.dbgPrint(1);
	}
	retPrinted = true;
#endif
	for (OBF3(size_t) i = 1; i <= x; ++i) {
#ifdef DBGPRINT
		static bool iPrinted = false;
		if (!iPrinted) {
			std::cout << "i:" << std::endl;
			i.dbgPrint(1);
		}
		iPrinted = true;
#endif
		ret *= i;
	}
	return ret;
}

int main(int argc, char** argv) {
#ifndef NDEBUG
	freopen("ConsoleApplication1.log", "w", stdout);
#endif
	obf_init();
	/*ObfBitUint<size_t, 31> x = 12832197;
	auto y = obf_mul_inverse_mod2n(x);
	assert(y*x == 1);
	using Lit0 = obf_literal < size_t, 123, OBFUSCATE_SEED+0, 500>;
	Lit0::dbgPrint();
	Lit0 c;
	//using inj = obf_injection_with_constant<uint32_t, OBFUSCATE_SEED, 8>;
	//printf("%d, %d, %d\n",inj::C, inj::injection(123,inj::C), inj::surjection(inj::injection(123,inj::C),inj::C));
	//std::cout << c.value() << std::endl;
	//constexpr static const char* loc = OBF_LOCATION;
	//std::cout << loc;
	//constexpr static OBFSEED seed = obf_seed_from_file_line(LOCATION, 0);
	//obf_var<size_t, 0, obf_exp_cycles(OBFSCALE + 0)> var(c.value());
	//OBFCYCLES c0 = obf_exp_cycles(0);
	OBF0(size_t) var(c.value());
	var.dbgPrint();
	OBF0(size_t) var2(c.value());
	var2.dbgPrint();
	var = var.value() + 1;
	std::cout << var.value() << std::endl;
	return 0;*/
	//int n = obf_mul_inverse_mod2n(0x66666667U);
	//std::cout << std::hex << n << std::endl;
	std::cout << argc / 5 << std::endl;

	obf_dbgPrint();
	if (argc <= 1)
		return 0;
	int x = atoi(argv[1]);
	auto f = factorial(x);
#ifdef DBGPRINT
	static bool fPrinted = false;
	if (!fPrinted) {
		std::cout << "f:" << std::endl;
		f.dbgPrint(1);
	}
	fPrinted = true;
#endif
	int64_t ff = f;
	std::cout << "factorial(" << x << ") = " << ff << std::endl;

	return 0;
}
