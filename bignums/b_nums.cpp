#include "stdafx.h"
#include "b_nums.h"
#include <Windows.h>

namespace BigNumbers {

	void b_int::printvec(bn_container tmp, bool sgn) {
		std::cout << "Sign: ";
		if (sgn)
			std::cout << "-\n";
		else
			std::cout << "+\n";
		std::cout << "[";
		bn_container::iterator t = tmp.begin();
		for (; t != tmp.end(); ++t) {
			std::cout << *t;
			if (t != tmp.end() - 1)
				std::cout << ", ";
		}
		std::cout << "]\n";
	}

	b_int::b_int() {
		bigNum.number.push_back(0);
		bigNum.isNeg = false;
	}

	b_int::b_int(const char* rhs) {
		int strt = 0, end = 0, coef = 1, in = 0;

		if (*rhs == '-')
			strt = 1;

		// Check if it is a correct number and go to the end of the number(end variable)
		for (end = strt; *(rhs + end); end++)
			if (*(rhs + end) < '0' || *(rhs + end) > '9')
				throw badParam;

		if (strt == 1)
			bigNum.isNeg = true;

		while (--end >= strt) {

			in += static_cast<long int>(*(rhs + end) - 48)*coef;
			coef *= 10;

			if (coef == cell_size_val || end == strt) {
				bigNum.number.push_back(in);
				coef = 1;
				in = 0;
			}
		}

	}

	b_int::b_int(long long int rhs) {
		b_int r = std::to_string(rhs).c_str();
		bigNum.number.resize(r.bigNum.number.size());
		copy(r.bigNum.number.begin(), r.bigNum.number.end(), bigNum.number.begin());
		bigNum.isNeg = r.bigNum.isNeg;

	}

	b_int::b_int(b_num rhs) {
		bigNum.number.resize(rhs.number.size());
		copy(rhs.number.begin(), rhs.number.end(), bigNum.number.begin());
		bigNum.isNeg = rhs.isNeg;
	}

	b_int b_int::operator-() const {
		b_int tmp = bigNum;
		tmp.bigNum.isNeg = !tmp.bigNum.isNeg;
		return tmp;
	}

	b_int& b_int::operator++() {
		*this += 1;
		return *this;
	}

	b_int& b_int::operator--() {
		*this -= 1;
		return *this;
	}

	b_int b_int::operator++(int) {
		b_int tmp(*this);
		*this += 1;
		return tmp;
	}

	b_int b_int::operator--(int) {
		b_int tmp(*this);
		*this -= 1;
		return tmp;
	}

	b_int& b_int::operator+=(const b_int& rhs) {
		
		if (bigNum.isNeg == rhs.bigNum.isNeg) {

			if (bigNum.number.size() <= rhs.bigNum.number.size())
				bigNum.number.resize(rhs.bigNum.number.size() + 1, 0);
			
			bn_container::iterator lit = bigNum.number.begin();
			bn_container::const_iterator rit = rhs.bigNum.number.begin();

			for (; lit != bigNum.number.end()-1; ++lit) {

				if (rit != rhs.bigNum.number.end()) {
					*lit += *rit;
					++rit;
				}

				*(lit + 1) += *lit / cell_size_val;
				*lit %= cell_size_val;

			}

			if (bigNum.number.at(bigNum.number.size() - 1) == 0)
				bigNum.number.erase(bigNum.number.end() - 1);

		}
		else {
			*this -= -rhs;
		}

		return *this;
	}

	b_int& b_int::operator-=(const b_int& rhs) {

		if (bigNum.isNeg == rhs.bigNum.isNeg) {

			if (*this == rhs) {
				bigNum.number.clear();
				bigNum.number.push_back(0);
				bigNum.isNeg = false;
				return *this;
			}

			b_int grt, low;

			if (*this > rhs && !bigNum.isNeg || *this < rhs && bigNum.isNeg) {
				grt = *this;
				low = rhs;
			}
			else {
				grt = rhs;
				low = *this;
			}

			if (*this > rhs) {
				grt.bigNum.isNeg = false;
				low.bigNum.isNeg = false;
			}
			else {
				grt.bigNum.isNeg = true;
				low.bigNum.isNeg = true;
			}

			if (grt.bigNum.number.size() > low.bigNum.number.size())
				low.bigNum.number.resize(grt.bigNum.number.size(), 0);

			bn_container::iterator git = grt.bigNum.number.begin();
			bn_container::iterator lit = low.bigNum.number.begin();

			for (; git != grt.bigNum.number.end(); ++git, ++lit) {
				*git -= *lit;

				if (*git < 0) {
					*git += cell_size_val;
					*(git + 1) -= 1;
				}

			}

			bigNum.number.resize(grt.bigNum.number.size());
			copy(grt.bigNum.number.begin(), grt.bigNum.number.end(), bigNum.number.begin());
			bigNum.isNeg = grt.bigNum.isNeg;

		}
		else {
			*this += -rhs;
		}

		return *this;
	}

	bool operator<(const b_int& lhs, const b_int& rhs) {

		if(lhs.bigNum.isNeg == rhs.bigNum.isNeg && lhs.bigNum.isNeg)
			return std::tie(std::string(rhs)) < std::tie(std::string(lhs));

		return std::tie(std::string(lhs)) < std::tie(std::string(rhs));

	}

	bool operator>(const b_int& lhs, const b_int& rhs) {
		return rhs < lhs;
	}

	bool operator<=(const b_int& lhs, const b_int& rhs) {
		return !(lhs > rhs);
	}

	bool operator>=(const b_int& lhs, const b_int& rhs) {
		return !(lhs < rhs);
	}

	bool operator==(const b_int& lhs, const b_int& rhs) {

		return std::tie(std::string(lhs)) == std::tie(std::string(rhs));

	}

	bool operator!=(const b_int& lhs, const b_int& rhs) {
		return !(lhs == rhs);
	}

	std::ostream& operator<<(std::ostream& os, const b_int& rhs) {

		b_num r = rhs.bigNum;

		bn_container::reverse_iterator rit = r.number.rbegin();
		int lenn;

		if (r.isNeg)
			os << "-";

		os << *rit;
		rit++;

		for (; rit != r.number.rend(); ++rit) {

			lenn = b_int::cell_size_power - std::to_string(*rit).length();
			for (int i = 0; i < lenn; i++) os << '0';
			os << *rit;

		}

		return os;
	}

	b_int::operator std::string() const{
		
		b_num r = bigNum;
		bn_container::reverse_iterator rit = r.number.rbegin();
		int lenn;
		std::string tmp = "";

		if (r.isNeg)
			tmp += "-";

		tmp += std::to_string(*rit);
		rit++;

		for (; rit != r.number.rend(); ++rit) {

			lenn = b_int::cell_size_power - std::to_string(*rit).length();
			for (int i = 0; i < lenn; i++) tmp += "0";
			tmp += std::to_string(*rit);

		}

		return tmp;
	}
}