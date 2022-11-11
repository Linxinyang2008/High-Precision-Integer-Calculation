//exint.h
#ifndef EXINT_H
#define EXINT_H_

#include <iostream>
#include <cstring>
#include <string>

//typedef int T;

template<class T> class exint{
	private:
		bool sign;
		T *num;
		T len;
		static T process_char(const char *s, bool &sign, T *&num);
		static bool unsign_gt(const T *a, const T lena, const T *b, const T lenb);
		static bool unsign_gte(const T *a, const T lena, const T *b, const T lenb);
		static T unsign_plus(const T *a, T lena, const T *b, T lenb, T *&result);
		static T unsign_minus(const T *a,T lena,const T *b,T lenb,T *&result);
		static T multiply_base(const T *a, const T lena, T n, T *&result);
		static T unsgin_multiply(const T *a, const T lena, const T *b, const T lenb, T *&result);
		static bool divide_gte(const T *a, T end, const T *b, T lenb);
		static T unsign_divide(const T *a, const T lena, const T *b, const T lenb, T *&result);
		static T unsign_mod(const T *a, const T lena, const T*b, const T lenb, T *&result);
	public:
		
//constructor
		exint();
		exint(const char * s);
		exint(const std::string & str);
		exint(T n);
		exint(const exint &b);
		
//destructor
		~exint();
		
//calc
		bool operator == (const exint &b) const;
		bool operator > (const exint &b) const;
		bool operator >= (const exint &b) const;
		bool operator < (const exint &b) const;
		bool operator <= (const exint &b) const;
		exint operator - ()const{
			exint b = *this;
			b.sign = !b.sign;
			return b;
		}
		
		/*Added operator '++' here.*/
		exint operator ++ () const{
			return *this + 1;
		}
		exint operator -- () const{
			return *this - 1;
		}
		/*Added operator '++' here.*/
		
		exint operator + (const exint &b) const{
			exint sum;
			delete[] sum.num;
			if(sign)//a >= 0
				if(b.sign){//a > 0 && b > 0
					sum.sign = true;
					sum.len = unsign_plus(num, len, b.num, b.len, sum.num);
				}
				else if(unsign_gte(num,len,b.num,b.len)){// a > 0,b < 0,|a| >= |b|
					sum.sign = true;
					sum.len = unsign_minus(num, len, b.num, b.len, sum.num);
				}
				else{// a > 0,b < 0,|a| < |b|
					sum.sign = false;
					sum.len = unsign_minus(b.num,b.len,num,len,sum.num);
				}
			else{//a < 0
				if(!b.sign){// a < 0, b < 0
					sum.sign = false;
					sum.len = unsign_plus(num,len,b.num,b.len,sum.num);
				}
				else if(unsign_gte(b.num,b.len,num,len)){// a < 0,b > 0,|a| <= |b|
					sum.sign = true;
					sum.len = unsign_minus(b.num,b.len,num,len,sum.num);
				}
				else{//a < 0 b > 0 , |a| > |b|
					sum.sign = false;
					sum.len = unsign_minus(num,len,b.num,b.len,sum.num);
				}
			}
			return sum;
		}
		exint operator - (const exint &b) const{
			return *this + (-b);
		}
		exint operator * (const exint &b)const{
			exint product;
			if(sign == b.sign)
				product.sign = true;
			else
				product.sign = false;
			delete[] product.num;
			product.len = unsgin_multiply(num, len, b.num, b.len, product.num);
			return product;
		}
		exint operator / (const exint<T>& b) const{
			exint consult;
			if(sign == b.sign)
				consult.sign = true;
			else
				consult.sign = false;
			delete[] consult.num;
			consult.len = unsign_divide(num,len,b.num,b.len,consult.num);
			if(consult[0] == 0)//avoid "-0"
				consult.sign = true;
			return consult;
		}
		exint operator % (const exint<T>& b)const{
			exint modulo;
			delete[] modulo.num;
			modulo.sign = sign;
			modulo.len = unsign_mod(num, len, b.num, b.len, modulo.num);
			return modulo;
		}
		
//others/io
		friend std::ostream& operator << (std::ostream &os, const exint <T> &a){
			if(!a.sign)os << '-';
			for(T i = 0;i < a.len;++i)
				os << a.num[i];
			fflush(stdout);
			return os;
		}
		/*
			There should be a function declaration of :
				friend std::istream& operator >> (std::istream &is, exint <T> &a);
			* Delete for some Errors when I was testing I/O functions.
			* It is stored in istream.txt
		*/
		/*  The replacement of 
				friend std::istream& operator >> (std::istream &is, exint <T> &a);
			is 
				exread_string(FILE* buf = stdin);
			Declared here as function, because 'cin' could only read one exint-type data.
				(Maybe my coding skill is too clumsy.)
		*/
		friend std::istream& operator >> (std::istream &is, exint <T> &a){
			delete[] a.num;
			std :: string str;
			is >> str;
			a = str;
			fflush(stdin);
			//Without this line, this function would only read one exint-type data.
			return is;
		}
		
		T& operator[](const T sub) const;
		
		exint operator = (const exint &b){
			if(this == &b) return *this;
			else{
				len = b.len;
				sign = b.sign;
				delete[] num;
				num = new T[len];
				memcpy(num, b.num, sizeof(T) * len);
				return *this;
			}
		}
		exint operator = (const char *s){
			delete[] num;
			len = process_char(s, sign, num);
			return *this;
		}
		exint operator = (const std::string &str){
			delete[] num;
			len = process_char(str.data(), sign, num);
			return *this;
		}
		exint operator = (T p){
			delete[] num;T i = 1;
			while(p > i) i *= 10, len++;
			num = new T[len];--len;
			
			i = len - 1;
			while(p){
				num[i--] = p % 10;
				p /= 10;
			}
			
			return *this;
		}
		
		T size(){ return len; }
		bool IsNatural() const { return sign; }
};

template<class T>
T exint<T> ::process_char(const char *s, bool &sign, T *&num){
	T len = strlen(s);
	if(!len){//len == 0
		sign = true;
		num = new T[1];
		num[0] = 0;
		len = 1;
	}
	else
		switch(s[0]){
			case '+':
				sign = true;
				--len;
				num = new T[len];
				for(T i = 0;i < len;++i)
					num[i] = s[i + 1] - '0';
				break;
			case '-':
				sign = false;
				--len;
				num = new T[len];
				for(T i = 0;i < len;++i)
					num[i] = s[i + 1] - '0';
				break;
			default:
				sign = true;
				num = new T[len];
				for(T i = 0;i < len;++i)
					num[i] = s[i] - '0';
				break;
		}
	return len;
}

template<class T>
bool exint<T> ::unsign_gt(const T *__a, const T lena, const T *__b, const T lenb){
	if(lena < lenb)
		return false;
	else if(lena > lenb)
		return true;
	else{
		for(T i = 0;i < lena;++i)
			if(__a[i] < __b[i])return false;
			else if(__a[i] > __b[i])return true;
		return false;
	}
}

template<class T>
bool exint<T> ::unsign_gte(const T *__a, const T lena, const T *__b, const T lenb){
	if(lena < lenb)
		return false;
	else if(lena > lenb)
		return true;
	else
	{
		for(T i = 0;i < lena;++i)
			if(__a[i] < __b[i])return false;
			else if(__a[i] > __b[i])return true;
		return true;
	}
} 

template<class T>
T exint<T> ::unsign_plus(const T *__a, T lena, const T *__b, T lenb, T *&result){
	T rem;
	if(lenb > lena){
		const T *temp = __a;
		__a = __b;
		__b = temp;
		rem = lena;
		lena = lenb;
		lenb = rem;
	}
	T len = lena + 1;
	result = new T[len];
	T sub = lena;
	rem = 0;
	--lena;
	--lenb;
	while(lenb >= 0){
		rem += __a[lena--] + __b[lenb--];
		result[sub--] = rem % 10;
		rem /= 10;
	}
	while(lena >= 0){
		rem += __a[lena--];
		result[sub--] = rem %10;
		rem /= 10;
	}
	if(rem > 0)
		result[sub] = rem;
	else{
		--len;
		T *p = new T[len];
		memcpy(p, result + 1, sizeof(T)*len);
		delete[] result;
		result = p;
	}
	return len;
}

template<class T>
T exint<T> ::unsign_minus(const T *__a, T lena, const T *__b, T lenb, T *&result){//a was requested to be greater than b
	T len = lena;
	result = new T[len];
	memcpy(result, __a, sizeof(T)*len);//const T *a can't be modified
	--lenb;
	--lena;
	while(lenb >= 0){
		if(__a[lena] >= __b[lenb])
			result[lena] -= __b[lenb];
		else{
			result[lena] += 10 - __b[lenb];
			--result[lena -1];
		}
		--lena;
		--lenb;
	}
	while(lena>=0){
		if(result[lena] < 0){
			result[lena] += 10;
			--result[lena - 1];
			--lena;
		}
		else break;
	}
	T zero = 0;
	while(zero < len)
		if(result[zero] == 0) ++zero;
		else break;
	if(zero == len){
		delete[] result;
		result = new T[1]{0};
		len = 1;
	}
	else if(zero != 0){
		len -= zero;
		T *p = new T[len];
		memcpy(p,result + zero,sizeof(T)*len);
		delete[] result;
		result = p;
	}
	return len;
}

template<class T>
bool exint<T> ::divide_gte(const T *__a, const T end, const T *__b, const T lenb){
	T begin = 0;
	while(__a[begin] == 0)++begin;
	
	if(end - begin  + 1 < lenb)	return false;
	else if(end - begin + 1 > lenb)	return true;
	else {
		for(T i = 0;i < lenb; ++begin, ++i)
			if(__a[begin] > __b[i])	return true;
			else if(__a[begin] < __b[i]) return false;
		return true;
	}
}

template<class T>
T exint<T> ::multiply_base(const T *__a, T lena, const T n, T * &result){//the first member may be 0
	T len = lena + 1;
	result = new T[len];
	T rem = 0;
	T sub = lena;
	--lena;
	while(lena >= 0){
		rem += n * __a[lena];
		result[sub] = rem % 10;
		rem /= 10;
		--lena;
		--sub;
	}
	if(rem > 0) result[sub] = rem;
	else result[sub] = 0;
	
	return len;
}

template<class T>
T exint<T> ::unsgin_multiply(const T *__a, const T lena, const T *__b, const T lenb, T *&result){//a on the top
	T len = lena + lenb;
	result = new T[len]{0};
	T *MultiplyTemp;
	T MultiplyBit = lenb - 1;//the subscript of number in the b to be multiplied
	while(MultiplyBit >= 0){
		T MultiplyTempSub = multiply_base(__a, lena, __b[MultiplyBit], MultiplyTemp);
		//plus
		T rem = 0;
		T sub = len - (lenb - MultiplyBit);//the bit when result begin plus
		--MultiplyTempSub;
		while(MultiplyTempSub >= 0){
			rem += result[sub] + MultiplyTemp[MultiplyTempSub];
			result[sub] = rem % 10;
			rem /= 10;
			--sub;
			--MultiplyTempSub;
		}
		if(rem > 0)
			result[sub] += rem;
		--MultiplyBit;
		delete[] MultiplyTemp;
	}
	T zero = 0;
	while(zero < len)
		if(result[zero] == 0)
			++zero;
		else break;
	if(zero == len){
		delete[] result;
		result = new T[1]{0};
		return 1;
	}
	else if(zero != 0){
		len -= zero;
		T *p = new T[len];
		memcpy(p,result + zero,sizeof(T)*len);
		delete[] result;
		result = p;
	}	
	return len;
}

template<class T>
T exint<T> ::unsign_divide(const T *__a, const T lena, const T *__b, const T lenb, T *&result){
	if(lena < lenb){
		result = new T[1]{0};
		return 1;
	}
	//Judge the first bit
	T CurrentBit = lenb - 1;//the current number on the consult
	T len;
	if(!divide_gte(__a, CurrentBit, __b, lenb) )
		if(CurrentBit + 1== lena){//lena == lenb && a < b
			result = new T[1]{0};
			return 1;
		}
		else{
			++CurrentBit;
			len = lena - lenb;
			result = new T[len];
		}
	else{
		len = lena - lenb + 1;
		result = new T[len];
	}
	//copy
	T *A = new T[lena];
	memcpy(A, __a, sizeof(T) * lena);
	T sub = 0;//sub = CurrentBit - (lena - lenb)，too much calc
	while(CurrentBit < lena){
		result[sub] = 0;
		do{
			//minus
			T Asub = CurrentBit;
			for(T i = lenb - 1;i >= 0;--Asub,--i)
				if(A[Asub] >= __b[i])
					A[Asub] -= __b[i];
				else{
					A[Asub] += 10 - __b[i];
					--A[Asub - 1];
				}
			while(Asub >= 0)
				if(A[Asub] < 0){
					A[sub] += 10;
					--A[Asub - 1];
					--Asub;
				}
				else
					break;
			++result[sub];
		}while(divide_gte(A, CurrentBit, __b, lenb));
		
		if(++sub, ++CurrentBit == lena)break;
		while(!divide_gte(A, CurrentBit, __b, lenb)){
			result[sub] = 0;
			if(++sub, ++CurrentBit == lena)break;
		}
	}
	delete[]A;
	return len;
}

template<class T>
T exint<T> ::unsign_mod(const T *__a, const T lena, const T *__b, const T lenb, T *&result){
	T len = lena;
	result = new T[len];
	memcpy(result,__a,sizeof(T)*len);
	if(lena < lenb)
		return len;
	//Judge the first bit
	T CurrentBit = lenb - 1;//the current number on the consult
	if(!divide_gte(result, CurrentBit, __b, lenb)){
		if(CurrentBit + 1== len)//lena == lenb && a < b
			return len;
		else ++CurrentBit;
	}
	while(CurrentBit < len){
		do{
			//minus
			T sub = CurrentBit;
			for(T i = lenb - 1;i >= 0;--sub,--i)
				if(result[sub] >= __b[i])	result[sub] -= __b[i];
				else{
					result[sub] += 10 - __b[i];
					--result[sub - 1];
				}
			while(sub >= 0)
				if(result[sub] < 0){
					result[sub] += 10;
					--result[sub - 1];
					--sub;
				}
				else break;
		}while(divide_gte(result, CurrentBit, __b, lenb));
		
		while(++CurrentBit != len)
			if(divide_gte(result, CurrentBit, __b, lenb)) break;
	}
	T zero = 0;
	while(zero < len)
		if(result[zero] == 0) ++zero;
		else break;
	if(zero == len){
		delete[] result;
		result = new T[1]{0};
		len = 1;
	}
	else if(zero != 0){
		len -= zero;
		T *p = new T[len];
		memcpy(p, result + zero, sizeof(T)*len);
		delete[] result;
		result = p;
	}
	return len;
}
//constructor

template<class T>
exint<T> ::exint(){
	sign = true;
	num = new T[1];
	num[0] = 0;
	len = 1;
}

template<class T>
exint<T> ::exint(const char *s){
	len = process_char(s,sign,num);
}

template<class T>
exint<T> ::exint(const std::string &str){
	const char *s = str.data();
	new (this)exint(s); 
}

template<class T>
exint<T> ::exint(T n){
	if(n < 0) sign = false;
	else sign = true;
	
	if(n == 0){
		len = 1;
		num = new T[1]{0};
		return;
	}
	len = 0;
	T N = n;
	while(n > 0){
		n /= 10;
		++len;
	}
	num = new T[len];
	for(T i = len;i > 0;--i){
		num[i - 1] = N % 10;
		N /= 10;
	}
}

template<class T>
exint<T> ::exint(const exint &b){
	sign = b.sign;
	len =  b.len;
	num = new T[len];
	memcpy(num, b.num, sizeof(T) * len);
}

//destructor
template<class T>
exint<T> ::~exint(){ delete[] num; }

//calculate
template<class T>
bool exint<T> ::operator == (const exint &b) const{
	if(len != b.len)return false;
	else if(sign != b.sign)return false;
	else{
		for(T i = 0;i < len;++i)
			if(num[i] != b.num[i])
				return false;
		return true;
	}
}

template<class T>
bool exint<T> ::operator > (const exint &b) const{
	if(sign)
		if(b.sign) return unsign_gt(num, len, b.num, b.len);
		else return true;
	else
		if(b.sign) return false;
		else return !unsign_gt(num,len,b.num,b.len);
}

template<class T>
bool exint<T> ::operator >= (const exint &b)const{
	if(sign)
		if(b.sign) return unsign_gte(num,len,b.num,b.len);
		else return true;
	else
		if(b.sign) return false;
		else return !unsign_gte(num,len,b.num,b.len);
}

template<class T>
bool exint<T> ::operator < (const exint &b) const{
	return !(*this >= b);
}

template<class T>
bool exint<T> ::operator <= (const exint &b) const{
	return !(*this > b);
}

//others/io

template<class T>
T & exint<T> ::operator[](const T sub) const{
	return num[len - 1 - sub];
}

#endif

#ifdef Ex_io	
	template<class T>
	T exread_string(exint<T> t){
		std :: string Temp_Str;
		std :: cin >> Temp_Str;
		t = Temp_Str;
		return t.size();
	}
#endif

#define ValueNameToString(name)  (#name)

#endif
/*
Copyright Declaration:
	This header file is quoted from
		https://www.cnblogs.com/h-hg/p/8366142.html (Author: h_hg)
	Appreciate for the resources.
	
	I modified some value names and value type, to make sure auto-matching can work, and 
		let the value names won't be duplicated.
	
	Modified: 
		* All elements : "template<class T>"
		* exint :: istream& operator : 
			" c >= '0' && c <= '9' " -> " isdigit(c) "
		* Other grammercial and algorithmic optimization and improvement
	Added:
		* exint :: istream& operator : 
			Line 153 : 	fflush(stdin);
		* exint :: operator ++ () const;
		* exint :: operator -- () const;
		* exread()
		* ValueNameToString() //Declared by preprocesser
*/
