/*

Copyright (c) 2018, ITHare.com
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

//TEST GENERATOR. Generates randomized command lines for a testing session
//  Using C++ to avoid writing the same logic twice in *nix .sh and Win* .bat

#include "../../kscope/test/randomtestgen.h"

class ObfTestEnvironment : public KscopeTestEnvironment {
	public:
	virtual std::string testSrcFolder() override { return  srcDirPrefix + "../../../kscope/test/"; }
	virtual std::string alwaysDefine() override {//relative to kscope/test
#ifdef __GNUC__ //includes clang
#ifdef __apple_build_version__
		return "-DITHARE_KSCOPE_TEST_EXTENSION=\"../../obf/src/kscope_extension_for_obf.h\"";//no -latomic needed or possible for Apple Clang
#else
		return "-DITHARE_KSCOPE_TEST_EXTENSION=\"../../obf/src/kscope_extension_for_obf.h\" -latomic";
#endif
#elif defined(_MSC_VER)
		return "/DITHARE_KSCOPE_TEST_EXTENSION=\"../../obf/src/kscope_extension_for_obf.h\"";
#else
#error
#endif
	}
	
#if defined(__APPLE_CC__) || defined(__linux__)
	virtual std::string checkExe(int nseeds) override {//very weak heuristics, but still better than nothing
		bool obfuscated = nseeds != 0;
		std::string cmp = std::string("strings testapp | grep Negative");//referring to string "Negative value of factorial()" 
		//return cmp + "\n" + exitCheck(cmp,!obfuscated);
		return "";//TODO! - reinstate
	}
#endif //nothing for Windows at the moment, sorry :-(
};

int main(int argc, char** argv) {
	ObfTestEnvironment kenv;
	KscopeTestGenerator kgen(kenv);
	return almost_main(kenv,kgen,argc,argv);
}
