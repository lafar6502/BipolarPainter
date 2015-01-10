#ifndef VECT_H_INCLUDED_
#define VECT_H_INCLUDED_
#include <math.h>
#define MAXDIM 4

template<class T> class Vect
{
	private:
		T _v[MAXDIM];
		int _len;
	public:
		Vect<T>(int len) {
			_len = len;
		};
		Vect<T>(T* arr, int len) {
			if (len > MAXDIM) len = MAXDIM;
			_len = len;
			for (int i=0; i < _len; i++) {
				_v[i] = arr[i];
			}
		};
		Vect<T>(T x, T y) {
			_len = 2;
			_v[0] = x;
			_v[1] = y;
		};
		Vect<T>(T x, T y, T z) {
			_len = 3;
			_v[0] = x;
			_v[1] = y;
			_v[2] = z;
		};
		
		Vect<T>(const Vect<T>& rhs) {
			_len = rhs._len;
			memcpy(_v, rhs._v, MAXDIM * sizeof(T));
		};
		
		int Size() {
			return _len;
		};
		double GetAbsLength() {
			double sum = 0;
			for(int i=0; i<_len; i++) {
				sum += _v[i] * _v[i];
			};
			return sqrt(sum);
		};
		Vect<T>& add(const Vect<T>& rhs) {
			for (int i=0; i < _len; i++) {
				_v[i] += rhs._v[i];
			}
			return *this;
		};
		
		Vect<T>& subtract(const Vect<T>& rhs) {
			for (int i=0; i < _len; i++) {
				_v[i] -= rhs._v[i];
			}
			return *this;
		};
		
		Vect<T>& multiply(double d) {
			for (int i=0; i < _len; i++) {
				_v[i] *= d;
			}
			return *this;
		};
		
		Vect<T>& multiply(int d) {
			for (int i=0; i < _len; i++) {
				_v[i] *= d;
			}
			return *this;
		};
		
		Vect<T>& operator+=(const Vect<T>& rhs) {
			return add(rhs);
		};
		
		Vect<T>& operator-=(const Vect<T>& rhs) {
			return subtract(rhs);
		};
		
		Vect<T>& operator*=(double d) {
			return multiply(d);
		};
		
		Vect<T>& operator*=(int d) {
			return multiply(d);
		};
		
		Vect<T>& operator+(const Vect<T>& rhs) {
			Vect<T> r(*this);
			return r.add(rhs);
		};
		
		Vect<T>& operator-(const Vect<T>& rhs) {
			Vect<T> r(*this);
			return r.subtract(rhs);
		};
		
		Vect<T>& operator*(double v) {
			Vect<T> r(*this);
			return r.multiply(v);
		};

		
		T operator[](int idx) {
			return _v[idx];	
		};
		
		const T* GetData() {
			return _v;
		};
		
		
};


#endif
