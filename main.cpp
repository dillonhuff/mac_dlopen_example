#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

#include <cstdio>

#include <dlfcn.h>

using namespace std;

// int myFunc(int i) {
//   return 12 + i;
// }

//extern "C" int myFunc(int i);

int main() {
  ofstream out("./prog.cpp");
  // out << "#define EXPORT __attribute__((visibility(\"default\")))\n"
  //   "EXPORT\n"
  //   "int myFunc(int i) {\n"
  //   "\treturn 12 + i;\n"
  //   "}\n" << endl;

  out <<
    "#include <iostream>\n"
    "using namespace std;\n"
    "int myFunc(int i) {\n"
    "\treturn 12 + i;\n"
    "}\n"
    "int main() {\n"
    "\tcout << \"Im the other main! I print out 12!\" << endl;\n"
    "}\n" << endl;
  
  int ret =
    system("clang++ -std=c++11 ./prog.cpp -o ./prog");

  cout << "clang call ret = " << ret << endl;

  void* myLibHandle = dlopen("./prog", RTLD_NOW);

  if (myLibHandle == nullptr) {
    printf("dlsym failed: %s\n", dlerror());
    return -1;
  }

  cout << "lib handle = " << myLibHandle << endl;

  void* mainFunV = dlsym(myLibHandle, "main");

  if (mainFunV == nullptr) {
    printf("dlsym failed: %s\n", dlerror());
    return -1;
  }

  int (*otherMain)() =
    reinterpret_cast<int (*)()>(mainFunV);

  otherMain();

  // if (myFunV == nullptr) {
  //   printf("dlsym failed: %s\n", dlerror());
  //   return -1;
  // }
  // cout << "myFunV func = " << myFunV << endl;

  // int (*myFunc)(int) =
  //   static_cast<int (*myFunc)(int)>( dlsym(myLibHandle, "myFunc") );

  // cout << "myFunc = " << myFunc(12) << endl;
}
