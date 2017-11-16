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
  string targetBinary = "./libprog.dylib";
  //string targetBinary = "./prog.o";
  ofstream out("./prog.cpp");

  out << //"#define EXPORT __attribute__((visibility(\"default\")))\n"
    //"EXPORT\n"
    "int myFunc(int i) {\n"
    "\treturn 12 + i;\n"
    "}\n" << endl;

  // out <<
  //   "#include <iostream>\n"
  //   "using namespace std;\n"
  //   "int myFunc(int i) {\n"
  //   "\treturn 12 + i;\n"
  //   "}\n" << endl;
    // "int main() {\n"
    // "\tcout << \"Im the other main! I print out 12!\" << endl;\n"
    // "}\n" << endl;
  
  int ret =
    system(("clang++ -std=c++11 -fPIC -dynamiclib ./prog.cpp -o " + targetBinary).c_str());

  cout << "clang call ret = " << ret << endl;

  void* myLibHandle = dlopen(targetBinary.c_str(), RTLD_LOCAL);

  if (myLibHandle == nullptr) {
    printf("dlsym failed: %s\n", dlerror());
    return -1;
  }

  cout << "lib handle = " << myLibHandle << endl;

  void* myFuncFunV = dlsym(myLibHandle, "myFunc"); //__Z6myFunci"); //myFunc");
  if (myFuncFunV == nullptr) {
    printf("dlsym failed: %s\n", dlerror());
  } else {
    printf("FOUND\n");
  }

  myFuncFunV = dlsym(myLibHandle, "__Z6myFunci"); //myFunc");
  if (myFuncFunV == nullptr) {
    printf("dlsym failed: %s\n", dlerror());
  } else {
    printf("FOUND\n");
  }

  myFuncFunV = dlsym(myLibHandle, "_Z6myFunc"); //myFunc");
  if (myFuncFunV == nullptr) {
    printf("dlsym failed: %s\n", dlerror());
  } else {
    printf("FOUND\n");
  }
  
  myFuncFunV = dlsym(myLibHandle, "myFunci");
  if (myFuncFunV == nullptr) {
    printf("dlsym failed: %s\n", dlerror());
  } else {
    printf("FOUND\n");
  }

  myFuncFunV = dlsym(myLibHandle, "_myFunc");
  if (myFuncFunV == nullptr) {
    printf("dlsym failed: %s\n", dlerror());
  } else {
    printf("FOUND\n");
  }

  myFuncFunV = dlsym(myLibHandle, "__myFunc");
  if (myFuncFunV == nullptr) {
    printf("dlsym failed: %s\n", dlerror());
  } else {
    printf("FOUND\n");
  }

  myFuncFunV = dlsym(myLibHandle, "_myFunci");
  if (myFuncFunV == nullptr) {
    printf("dlsym failed: %s\n", dlerror());
  } else {
    printf("FOUND\n");
  }

  myFuncFunV = dlsym(myLibHandle, "_Z6myFunci");
  if (myFuncFunV == nullptr) {
    printf("dlsym failed: %s\n", dlerror());
  } else {
    printf("FOUND\n");
  }

  int (*myFuncCall)(int) =
    reinterpret_cast<int (*)(int)>(myFuncFunV);

  cout << "myFunc = " << myFuncCall(12) << endl;
    
  
  dlclose(myLibHandle);

  // void* mainFunV = dlsym(myLibHandle, "main");

  // if (mainFunV == nullptr) {
  //   printf("dlsym failed: %s\n", dlerror());
  //   return -1;
  // }

  // int (*otherMain)() =
  //   reinterpret_cast<int (*)()>(mainFunV);

  //otherMain();

}
