#ifndef VECT_H_INCLUDED_
#define VECT_H_INCLUDED_
#include <math.h>
#include <string.h>
#include <stdio.h>

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
			rhs.Print("rhs");
			Print("copy");
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
		
		Vect<T>& divide(T d) {
			for (int i=0; i < _len; i++) {
				_v[i] /= d;
			}
			return *this;
		};
		
		Vect<T>& operator=(const Vect<T>& rhs) {
			_len = rhs._len;
			memcpy(_v, rhs._v, MAXDIM * sizeof(T));
			return *this;
		}
		
		Vect<T>& operator+=(const Vect<T>& rhs) {
			return add(rhs);
		};
		
		Vect<T>& operator-=(const Vect<T>& rhs) {
			return subtract(rhs);
		};
		
		Vect<T>& operator*=(double d) {
			return multiply(d);
		};
		
		Vect<T>& operator/=(T d) {
			return divide(d);
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
			r.Print("orig");
			r.multiply(v);
			r.Print("mul");
			return r;
		};
		
		Vect<T>& operator/(T v) {
			Vect<T> r(*this);
			return r.divide(v);
		};

		int MaxValueIndex() {
			int mv = 0;
			for (int i=1; i<_len; i++) {
				if (_v[i] > _v[mv]) {
					mv = i;
				}
			}
			return mv;
		};
		
		int MaxAbsValueIndex() {
			int mv = 0;
			T c = abs(_v[0]);
			for (int i=1; i<_len; i++) {
				T c2 = abs(_v[i]);
				if (c2 > c) {
					mv = i;
					c = c2;
				}
			}
			return mv;
		};
		
		int MinValueIndex() {
			int mv = 0;
			for (int i=1; i<_len; i++) {
				if (_v[i] < _v[mv]) {
					mv = i;
				}
			}
			return mv;
		};
		
		T operator[](int idx) {
			return _v[idx];	
		};
		
		const T* Data() {
			return _v;
		};
		
		void ToString(char* buf, int bufLen) const {
			char* b = buf;
			int rem = bufLen;
			int r = snprintf(b, rem, "[");
			b += r;
			rem -= r;
			for (int i=0; i<_len; i++) {
				r = snprintf(b, rem, i > 0 ? ", %f" : "%f", _v[i]);
				rem -= r;
				b += r;
				if (rem <= 0) return;
			};
			snprintf(b, rem, "]");
		};
		
		void Print(const char* f = NULL) const {
			char buf[100];
			ToString(buf, sizeof(buf));
			if (f == NULL) {
				printf("%s\n", buf);
			}
			else {
				printf("%s: %s\n", f, buf);
			}
		}
		
};


#endif
