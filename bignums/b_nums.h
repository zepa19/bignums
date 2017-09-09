#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <tuple>

namespace BigNumbers {

	class excepT : public std::exception {
		virtual const char* what() const throw() {
			return "This is not an integer number.";
		}
	};

	typedef std::vector<long long> bn_container;

	struct b_num {
		bn_container number;
		bool isNeg = false;
	};

	class b_int {

	private:
		static const int cell_size_power = 9;				// 10^cell_size_power
		static const int cell_size_val = 1000000000;		// 10^cell_size_power
		excepT badParam;
		b_num bigNum;

	public:
		b_int();
		b_int(const char*);
		b_int(long long int); // TODO: unsigned long long int
		b_int(b_num);

		b_int b_int::operator-() const;

		b_int& operator++();	//pre
		b_int& operator--();	//pre
		b_int operator++(int);	//post
		b_int operator--(int);	//post

		b_int& b_int::operator+=(const b_int&);

		b_int& b_int::operator-=(const b_int&);

		friend bool operator<(const b_int&, const b_int&);
		friend bool operator>(const b_int&, const b_int&);
		friend bool operator<=(const b_int&, const b_int&);
		friend bool operator>=(const b_int&, const b_int&);
		friend bool operator==(const b_int&, const b_int&);
		friend bool operator!=(const b_int&, const b_int&);

		friend std::ostream& operator<<(std::ostream&, const b_int&);

		operator std::string() const;

		void printvec(bn_container, bool);

	};

}