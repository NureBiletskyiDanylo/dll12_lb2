// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the DLL12_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// DLL12_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef DLL12_EXPORTS
#define DLL12_API __declspec(dllexport)
#else
#define DLL12_API __declspec(dllimport)
#endif

#include <iostream> // Include the necessary header for std::cout, std::endl

#include <vector>;
#include <set>
using namespace std;
// This class is exported from the dll
DLL12_API void primefiller();


DLL12_API void setkeys();


DLL12_API  vector<int> encoder(string message);
DLL12_API  string decoder(vector<int> encoded);
