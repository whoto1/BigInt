#include <vector>
#include <iostream>
#include <string>
#include <string.h>
#include <tuple>
#include <bitset>
#include <sstream>
#include <list>
class BigInt {
public:std::string num;
	  int sign;// 0 - "+"      1 - "-"
public:
	BigInt();  //done
	BigInt(int); //done
	BigInt(std::string); //done
	BigInt(const BigInt&);//done
	~BigInt();//done

	BigInt& operator=(const BigInt&);  // done

	BigInt operator~() const; //done

	BigInt& operator++(); //done
	const BigInt operator++(int) const; //done
	BigInt& operator--(); //done
	const BigInt operator--(int) const; //done

	BigInt& operator+=(const BigInt&); //done
	BigInt& operator*=(const BigInt&); //done
	BigInt& operator-=(const BigInt&); //done
	BigInt& operator/=(const BigInt&); //done
	BigInt& operator^=(const BigInt&); //done
	BigInt& operator%=(const BigInt&); //done
	BigInt& operator&=(const BigInt&); //done
	BigInt& operator|=(const BigInt&); //done

	BigInt operator+() const;  // unary + done
	BigInt operator-() const;  // unary - done

	bool operator==(const BigInt&) const; //done
	bool operator!=(const BigInt&) const; //done
	bool operator<(const BigInt&) const; //done
	bool operator>(const BigInt&) const; //done
	bool operator<=(const BigInt&) const; //done
	bool operator>=(const BigInt&) const; //done

	operator int() const; //done
	operator std::string() const; //done

	size_t size() const;  // size in bytes //done
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);

std::ostream& operator<<(std::ostream& o, const BigInt& i);


std::vector<bool> bin(BigInt a) {
	std::vector<bool> binary;

	int n = a.num.size();
	std::string temp = a.num;
	for (int i = 0;i < n / 2;i++) std::swap(temp[i], temp[n - i - 1]);



	int nf = 0;
	BigInt myNumbers(a);
	std::vector<bool> conver_myNumbers;

	while (myNumbers.num != "0") {
		if (myNumbers % BigInt(2) == BigInt(0)) conver_myNumbers.push_back(false);
		else conver_myNumbers.push_back(true);
		myNumbers /= BigInt(2);
	}
	
	if (a.sign == 1) {
		bool flag = true;
		conver_myNumbers.flip();
		for (int i = 0;i < conver_myNumbers.size();i++) {
			if (conver_myNumbers[i] == flag)
			{
				flag = true;
				conver_myNumbers[i] = false;
			}
			else {
				flag = false;
				conver_myNumbers[i] = true;
				break;
			}
		}
	}
	conver_myNumbers.push_back(false);
	return conver_myNumbers;
}
BigInt bin_reverse(std::vector<bool> a, int sign) {

	bool flag = true;
	std::vector<int> myNumbers(1, 0);
	if (sign == 1) {
		a.flip();
		for (int i = 0;i < a.size();i++) {
			if (a[i] == flag)
			{
				flag = true;
				a[i] = false;
			}
			else {
				flag = false;
				a[i] = true;
				break;
			}
		}
	}

	for (int i = 0;i < a.size();i++) {
		if (a[i] == true)		 myNumbers[0] += pow(2, i);
	}
	std::string cov;
	cov = std::to_string(myNumbers[0]);
	BigInt c(cov);
	return c;
}
void strip_leading_zeroes(std::string& num) {
	int i;

	for (i = num.size() - 1; i > 0; i--)
		if (num[i] == '0')
			num.pop_back();
		else break;
}
bool is_power_of_10(const std::string& num) {

	if (num[num.size() - 1] != '1')
		return false;
	for (int i = num.size() - 2; i >= 0; --i)
		if (num[i] != '0')
			return false;

	return true;    // first digit is 1 and the following digits are all 0
}
std::tuple<BigInt, BigInt> divide(const BigInt& dividend, const BigInt& divisor) {
	BigInt quotient, remainder, temp;

	temp = divisor;
	quotient = 1;
	while (temp < dividend) {
		++quotient;
		temp += divisor;
	}
	if (temp > dividend) {
		--quotient;
		remainder = dividend - (temp - divisor);
	}

	return std::make_tuple(quotient, remainder);
}
BigInt::BigInt() { this->num = ""; this->sign = 0; }
BigInt::BigInt(int val) {
	sign = 0;
	if (val < 0)
		sign = 1;
	if (sign == 0)
	{
		do {
			this->num.push_back(val % 10 + '0');
			val /= 10;
		} while (val);
	}
	else
	{
		std::string str = std::to_string(val);
		int n = str.size();
		for (int i = n - 1;i > 0;--i)
		{
			this->num.push_back(str[i]);
		}
	}
}
BigInt::BigInt(std::string val)
{
	sign = 0;
	int n = val.size();
	for (int i = n - 1; i >= 0;i--) {
		if (!isdigit(val[i]))
		{
			if (val[i] == '-')
			{
				sign = 1;
				continue;
			}
			throw("ERROR"); // бросать исключение std::invalid_argument при ошибке
		}

		this->num.push_back(val[i]);
	}
}
BigInt::BigInt(const BigInt& a) {
	num = a.num;
	sign = a.sign;
}
BigInt::~BigInt() { this->num = ""; this->sign = 0; }

BigInt& BigInt::operator=(const BigInt& a) {
	this->num = a.num;
	this->sign = a.sign;
	return *this;
}

BigInt BigInt::operator~() const {
	int n = this->num.size();
	BigInt c;
	std::vector<bool> conv_a;
	conv_a = bin(*this);
	conv_a.flip();

	if (this->sign == 0) c.sign = 1;
	else c.sign = 0;
	c = bin_reverse(conv_a, c.sign);
	if (this->sign == 0) c.sign = 1;
	else c.sign = 0;
	return c;
}

BigInt& BigInt::operator++() {
	BigInt c(1);
	*this = *this + c;
	return *this;

}
const BigInt BigInt::operator++(int a) const {
	BigInt c = *this;
	c += 1;
	return c;
}
BigInt& BigInt::operator--() {
	*this -= 1;
	return *this;
}
const BigInt BigInt::operator--(int) const {
	BigInt c = *this;
	c -= 1;
	return c;
}

BigInt& BigInt::operator+=(const BigInt& a) {
	*this = (*this) + a;
	return *this;
}
BigInt& BigInt::operator*=(const BigInt& a) {
	*this = (*this) * a;
	return *this;
}
BigInt& BigInt::operator-=(const BigInt& a) {
	*this = (*this) - a;
	return *this;
}
BigInt& BigInt::operator/=(const BigInt& a) {
	*this = *this / a;
	return *this;
}
BigInt& BigInt::operator%=(const BigInt& a) {
	*this = *this % a;
	return *this;
}
BigInt& BigInt::operator^=(const BigInt& a) {
	*this = *this ^ a;
	return *this;
}
BigInt& BigInt::operator&=(const BigInt& a) {
	*this = *this & a;
	return *this;
}
BigInt& BigInt::operator|=(const BigInt& a) {
	*this = *this | a;
	return *this;
}

BigInt BigInt::operator+() const { return *this; }
BigInt BigInt::operator-() const {
	BigInt temp;

	temp.num = num;
	if (num != "0") {
		if (sign == 0)
			temp.sign = 1;
		else
			temp.sign = 0;
	}
	return temp;
}

bool BigInt::operator==(const BigInt& a) const {
	if (this->sign == a.sign && this->num.size() == a.num.size())
	{
		int n = a.num.size();
		for (int i = n - 1; i >= 0;i--)
		{
			if (this->num[i] != a.num[i])
				return false;
		}
		return true;
	}
	else return false;
}
bool BigInt::operator!=(const BigInt& a) const { return !(*this == a); }
bool BigInt::operator<(const BigInt& a) const {

	if (sign == a.sign) {
		if (sign == 0) {
			if (this->size() == a.size())
			{
				for (int i = this->size() - 1;i >= 0;--i)
				{
					if (num[i] < a.num[i]) return true;
					else if (num[i] > a.num[i]) return false;
				}
				return false;
			}
			else
			{
				if (a.size() > this->size()) return true;
				else return false;
			}
		}
		else
			return  (-(*this) > -a);
	}
	else
		return sign == 1;
}
bool BigInt::operator>(const BigInt& a) const { return !((*this < a) || (*this == a)); }
bool BigInt::operator<=(const BigInt& a) const { return (*this < a) || (*this == a); }
bool BigInt::operator>=(const BigInt& a) const { return (*this > a) || (*this == a); }

BigInt::operator int() const {
	int n = this->size();
	std::string temp = this->num;
	for (int i = 0;i < n / 2;i++) std::swap(temp[i], temp[n - i - 1]);
	return (this->sign == 1 ? (std::stoi(temp) * (-1)) : std::stoi(temp));
}
BigInt::operator std::string() const {

	std::string temp = this->num;
	if (this->sign == 1) temp.push_back('-');
	int n = temp.size();
	for (int i = 0;i < n / 2;i++) std::swap(temp[i], temp[n - i - 1]);
	return temp;
}
size_t BigInt::size() const { return this->num.size(); }

BigInt operator+(const BigInt& a, const BigInt& b)
{
	int num = 0, n, m, rem = 0;
	BigInt c;
	n = a.num.size();
	m = b.num.size();
	int k = n < m ? m : n;
	if (a.sign == b.sign)
	{
		for (int i = 0;i < k;i++) {

			if (i < m && i < n)
				num = ((a.num[i]) - '0') + (b.num[i] - '0') + rem;
			else if (i >= n) num = (b.num[i] - '0') + rem; //i>m
			else num = (a.num[i] - '0') + rem; //n>m
			rem = num / 10;
			c.num.push_back((num % 10) + '0');
		}
		if (rem)
			c.num.push_back(rem + '0');
		if (a.sign == 1 && b.sign == 1)
			c.sign = 1;
	}
	else
	{
		if (a.sign == 1 && b.sign == 0)
		{
			if (a.num.size() < b.num.size())
				c.sign = 0;
			else if (a.num.size() == b.num.size())
			{
				for (int i = n - 1;i >= 0;i--)
				{
					if (a.num[i] <= b.num[i]) {
						c.sign = 0;
						break;
					}
					else if (a.num[i] > b.num[i]) {
						c.sign = 1;
						break;
					}
				}
			}
			else {
				c.sign = 1;
			}

			c = b -(-a);
		}

		if (a.sign == 0 && b.sign == 1) {
			if (a.num.size() > b.num.size())
				c.sign = 0;
			else if (a.num.size() == b.num.size())
			{
				for (int i = n - 1;i >= 0;i--)
				{
					if (a.num[i] >= b.num[i]) {
						c.sign = 0;
						break;
					}
					else if (a.num[i] < b.num[i]) {
						c.sign = 1;
						break;
					}
				}
			}
			else {
				c.sign = 1;
			}
			c = (-b) - a;
		}
	}
	return c;
}
BigInt operator-(const BigInt& a, const BigInt& b)
{
	int n, m, num = 0, rem = 0;
	std::string large, small;
	BigInt c;
	int flag = 0;
	n = a.num.size();
	m = b.num.size();
	if (a.num.size() > b.num.size()) {
		large = a.num;
		small = b.num;
		if (a.sign == 1) c.sign = 1;
	}
	else if (a.num.size() == b.num.size())
	{
		for (int i = n - 1;i >= 0;i--)
		{
			if (a.num[i] < b.num[i]) {
				if (b.sign == 1)	c.sign = 1;
				else c.sign = 0;
				large = b.num;
				small = a.num;
				flag = 1;
				break;
			}
			else if (a.num[i] > b.num[i]) {
				if (a.sign == 1)	c.sign = 1;
				else c.sign = 0;
				large = a.num;
				small = b.num;
				flag = 1;
				break;
			}

		}
		if (a.sign == 0)	c.sign = 0;
		else c.sign = 1;
		if (flag == 0) {
			large = a.num;
			small = b.num;
		}
		
	}
	else {
		large = b.num;
		small = a.num;
		if (b.sign == 1) c.sign = 0;
		else c.sign = 1;
	}
	n = large.size();
	m = small.size();

	if (a.sign == b.sign) {
		for (int i = 0;i < n;i++)
		{
			if (i < m) {
				num = (large[i] + '0') - (small[i] + '0') + rem;
			}
			else
				num = (large[i] - '0') + rem;
			if (num < 0)
				num += 10,
				rem = -1;
			else
				rem = 0;
			c.num.push_back(num + '0');
		}
	}
	else {
		BigInt d1, d2;
		d1 = a;
		d2 = b;
		d2.sign = d1.sign;
		c = d1 + d2;
		return c;
	}

	strip_leading_zeroes(c.num);

	return c;
}
BigInt operator*(const BigInt& a, const BigInt& b)
{
	int num = 0, n, m, rem = 0;
	BigInt c, duba, dubb;
	if (a.num.size() < b.num.size()) { duba = b; dubb = a; }
	else { duba = a; dubb = b; }

	n = duba.num.size();
	m = dubb.num.size();
	std::vector<int> v(n + m, 0);

	for (int i = 0;i < n;i++)
		for (int j = 0;j < m;j++)
			v[i + j] += (duba.num[i] - '0') * (dubb.num[j] - '0');
	n += m;
	for (int s, i = 0, rem = 0; i < n; i++)
	{
		s = rem + v[i];
		v[i] = s % 10;
		rem = s / 10;
		c.num.push_back(v[i] + '0');
	}

	strip_leading_zeroes(c.num);
	if (a.sign != b.sign)
		c.sign = 1;

	return c;
}
BigInt operator^(const BigInt& a, const BigInt& b) {
	BigInt c;
	std::vector<bool> conv_a;
	std::vector<bool> conv_b;
	std::vector<bool> conv_c;
	conv_a = bin(a);
	conv_b = bin(b);
	
	int n, m;
	bool sign_a, sign_b;
	n = conv_a.size();
	m = conv_b.size();
	
	int k = n < m ? m : n;
	if (a.sign == 0)  sign_a = false;
	else sign_a = true;
	if (b.sign == 0)  sign_b = false;
	else sign_b = true;
	for (int i = 0;i < k;i++) {

		if (i < m && i < n) {
			if (conv_a[i] == conv_b[i]) conv_c.push_back(false);
			else conv_c.push_back(true);
		}
		else if (i >= n) {  //i>m     m>n
			if (conv_b[i] != sign_b) conv_c.push_back(true);
			else conv_c.push_back(false);
		}
		else {
			if (conv_a[i] != sign_a) conv_c.push_back(true);
			else conv_c.push_back(false);
		}  //n>m
	}
	if (a.sign == b.sign) c.sign = 0;
	else {
		c.sign = 1;
	}
	c = bin_reverse(conv_c, c.sign);
	if (a.sign == b.sign) c.sign = 0;
	else {
		c.sign = 1;
	}
	return c;
}
BigInt operator|(const BigInt& a, const BigInt& b) {
	BigInt c;
	std::vector<bool> conv_a;
	std::vector<bool> conv_b;
	std::vector<bool> conv_c;
	conv_a = bin(a);
	conv_b = bin(b);
	int n, m;
	bool sign_a, sign_b;
	n = conv_a.size();
	m = conv_b.size();
	int k = n < m ? m : n;
	if (a.sign == 0)  sign_a = false;
	else sign_a = true;
	if (b.sign == 0)  sign_b = false;
	else sign_b = true;

	for (int i = 0;i < k;i++) {

		if (i < m && i < n) {
			if (conv_a[i] == conv_b[i]) conv_c.push_back(conv_a[i]);
			else conv_c.push_back(true);
		}
		else if (i >= n) {  //i>m     m>n
			if (conv_b[i] == sign_b) conv_c.push_back(conv_b[i]);
			else conv_c.push_back(true);
		}
		else {
			if (conv_a[i] == sign_a) conv_c.push_back(conv_a[i]);
			else conv_c.push_back(true);
		}  //n>m
	}
	if (a.sign == b.sign) c.sign = a.sign;
	else 		c.sign = 1;
	c = bin_reverse(conv_c, c.sign);
	if (a.sign == b.sign) c.sign = a.sign;
	else 		c.sign = 1;
	return c;
}
BigInt operator&(const BigInt& a, const BigInt& b) {
	BigInt c;
	std::vector<bool> conv_a;
	std::vector<bool> conv_b;
	std::vector<bool> conv_c;
	conv_a = bin(a);
	conv_b = bin(b);
	int n, m;
	bool sign_a, sign_b;
	n = conv_a.size();
	m = conv_b.size();
	int k = n < m ? m : n;
	if (a.sign == 0)  sign_a = false;
	else sign_a = true;
	if (b.sign == 0)  sign_b = false;
	else sign_b = true;
	for (int i = 0;i < k;i++) {

		if (i < m && i < n) {
			if (conv_a[i] == conv_b[i]) conv_c.push_back(conv_a[i]);
			else conv_c.push_back(false);
		}
		else if (i >= n) {  //i>m     m>n
			if (conv_b[i] == sign_b) conv_c.push_back(conv_b[i]);
			else conv_c.push_back(false);
		}
		else {
			if (conv_a[i] == sign_a) conv_c.push_back(conv_a[i]);
			else conv_c.push_back(false);
		}  //n>m
	}
	if (a.sign == b.sign) c.sign = a.sign;
	else 		c.sign = 0;
	c = bin_reverse(conv_c, c.sign);
	if (a.sign == b.sign) c.sign = a.sign;
	else 		c.sign = 0;
	return c;
}
BigInt operator/(const BigInt& a, const BigInt& b) {//this - a num - b
	BigInt abs_dividend = a;
	BigInt abs_divisor = b;
	abs_dividend.sign = 0;
	abs_divisor.sign = 0;

	if (b == BigInt(0))
		throw std::logic_error("Attempted division by zero");
	if (abs_dividend < abs_divisor)
		return BigInt(0);
	if (b == BigInt(1))
		return a;
	if (b == BigInt(-1))
		return -(a);

	BigInt quotient;
	if (abs_dividend <= BigInt(LLONG_MAX) && abs_divisor <= BigInt(LLONG_MAX))
		quotient = std::stoll(abs_dividend.num) / std::stoll(abs_divisor.num);
	else if (abs_dividend == abs_divisor)
		quotient = 1;
	else if (is_power_of_10(abs_divisor.num)) { // if divisor is a power of 10 do optimised calculation
		size_t digits_in_quotient = abs_dividend.num.size() - abs_divisor.num.size() + 1;
		quotient.num = abs_dividend.num.substr(abs_dividend.size() - digits_in_quotient, digits_in_quotient);
	}
	else {
		int len_divs = abs_divisor.size();
		int len_divd = abs_dividend.size();
		quotient.num = "0";    // the value is cleared as digits will be appended
		BigInt chunk, chunk_quotient, chunk_remainder, abs_divisor_swap, abs_dividend_swap, chunk_swap;
		int chunk_index = 0;
		chunk_remainder.num = abs_dividend.num.substr(abs_dividend.size() - chunk_index - (abs_divisor.size() - 1), abs_divisor.size() - 1);
		chunk_index = abs_divisor.num.size() - 1;
		for (int i = 0;i < chunk_remainder.size() / 2;i++) std::swap(chunk_remainder.num[i], chunk_remainder.num[chunk_remainder.size() - i - 1]);

		while (chunk_index < abs_dividend.size()) {
			chunk_remainder.num.append(1, abs_dividend.num[abs_dividend.size() - chunk_index - 1]);
			for (int i = 0;i < chunk_remainder.size() / 2;i++) std::swap(chunk_remainder.num[i], chunk_remainder.num[chunk_remainder.size() - i - 1]);
			chunk = chunk_remainder;
			chunk_index++;
			while (chunk < abs_divisor) {
				strip_leading_zeroes(chunk.num);
				quotient.num += "0";
				if (chunk_index < abs_dividend.num.size()) {
					for (int i = 0;i < chunk.size() / 2;i++) std::swap(chunk.num[i], chunk.num[chunk.size() - i - 1]);
					chunk.num.append(1, abs_dividend.num[abs_dividend.size() - chunk_index - 1]);
					for (int i = 0;i < chunk.size() / 2;i++) std::swap(chunk.num[i], chunk.num[chunk.size() - i - 1]);
					chunk_index++;
				}
				else
					break;
			}
			if (chunk == abs_divisor) {
				quotient.num += "1";
				chunk_remainder = 0;
			}
			else if (chunk > abs_divisor) {
				for (int i = 0;i < quotient.size() / 2;i++) std::swap(quotient.num[i], quotient.num[quotient.size() - i - 1]);

				strip_leading_zeroes(quotient.num);
				for (int i = 0;i < quotient.size() / 2;i++) std::swap(quotient.num[i], quotient.num[quotient.size() - i - 1]);

				std::tie(chunk_quotient, chunk_remainder) = divide(chunk, abs_divisor);
				for (int i = 0;i < chunk_remainder.size() / 2;i++) std::swap(chunk_remainder.num[i], chunk_remainder.num[chunk_remainder.size() - i - 1]);
				quotient.num += chunk_quotient.num;
				//chunk_index++;
			}
		}
	}
	for (int i = 0;i < quotient.size() / 2;i++) std::swap(quotient.num[i], quotient.num[quotient.size() - i - 1]);

	strip_leading_zeroes(quotient.num);

	if (a.sign == b.sign)
		quotient.sign = 0;
	else
		quotient.sign = 1;

	return quotient;

}
BigInt operator%(const BigInt& a, const BigInt& b) {
	BigInt abs_dividend = a;
	BigInt abs_divisor = b;
	abs_dividend.sign = 0;
	abs_divisor.sign = 0;
	if (abs_divisor == BigInt(0))
		throw std::logic_error("Attempted division by zero");
	if (abs_divisor == BigInt(1) || abs_divisor == abs_dividend)
		return BigInt(0);

	BigInt remainder;
	if (abs_dividend <= BigInt(LLONG_MAX) && abs_divisor <= BigInt(LLONG_MAX))
		remainder = std::stoll(abs_dividend.num) % std::stoll(abs_divisor.num);
	else if (abs_dividend < abs_divisor)
		remainder = abs_dividend;
	else if (is_power_of_10(b.num)) { 
		size_t no_of_zeroes = b.num.size() - 1;
		remainder.num = abs_dividend.num.substr(abs_dividend.num.size() - no_of_zeroes);
	}
	else {
		BigInt quotient = abs_dividend / abs_divisor;
		remainder = abs_dividend - quotient * abs_divisor;
	}
	strip_leading_zeroes(remainder.num);


	if (a.sign == b.sign) remainder.sign = a.sign;
	else remainder.sign = 1;

	if (remainder.num == "0") remainder.sign = 0;
	if (remainder < BigInt(0))
		remainder = remainder + abs_divisor;
	return remainder;
}
std::ostream& operator<<(std::ostream& out, const BigInt& a)
{
	if (a.sign == 1 && a.num != "0")
		out << '-';
	int n = a.size();
	std::string temp = a.num;
	for (int i = 0;i < n / 2;i++) std::swap(temp[i], temp[n - i - 1]);
	out << temp;

	return out;
}

int main()
{
	BigInt x("-5"); //-5734
	BigInt y("3"), c; //-649
	//BigInt x("-34"), y(4);
	c = x & y;
	std::cout << c;
	return 0;
}