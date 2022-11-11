# Copyright Declaration:
### This header file is quoted from
		  https://www.cnblogs.com/h-hg/p/8366142.html (Author: h_hg)
### Appreciate for the resources.
	
## I modified some value names and value type, to make sure auto-matching can work, and let the value names won't be duplicated.

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

###### Maybe my coding skill is too ~~Clumsy~~

# Author : Linxinyang2008 from Golden Apple Jincheng No.1 Seconday School Chengdu , PRC
