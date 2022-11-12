# exint - A High-Precision-Integer-Calculation Header File.

### Particially edited and devoloped for numerical calculations greater than 10^38(Max__int128_t) in C++ language.

## Installation:
> #1. Call as a local header file by preprocessor:
```cpp
#define Ex_io // If you need to use function ' T exread_string(exint<T> t) '
#include "exint.hpp"
```

> #2. Call as a standard header file:
```cpp
// Drop into the path where standard header files were stroed.
// For example: " \Dev-Cpp\TDM-GCC-64\lib\gcc\x86_64-w64-mingw32\9.2.0\include\c++\tr1\ "
#define Ex_io
#include <exint.hpp>
```

## Copyright Declaration:
### This header file is quoted from
		  https://www.cnblogs.com/h-hg/p/8366142.html (Author: h_hg)
### Appreciate for the resources.
	
#### I have modified some value names and value type, to make sure auto-matching can work, and let the value names won't be duplicated.
```python
## Modified: 
		* All elements : "template<class T>"
		* exint :: istream& operator : 
			" c >= '0' && c <= '9' " -> " isdigit(c) "
		* Other grammercial and algorithmic optimization and improvement
## Added:
		* exint :: istream& operator : 
			Line 153 : 	fflush(stdin);
		* exint :: operator ++ () const;
		* exint :: operator -- () const;
		* exread()
		* ValueNameToString() //Declared by preprocesser
```
###### Maybe my coding skill is too ~~Clumsy~~

* Author : Linxinyang2008 from Golden Apple Jincheng No.1 Seconday School Chengdu , PRC

```cpp
2022.11.11 Submit to GitHub
2022.11.11 Updated ReadMe.md
2022.11.11 Complied from exint.h to exint.h.gch

2022.11.12 Updated test.cpp ( Added operator calling test and corrected preprocessor calling
	mistakes that got into the way of compiling)
```
