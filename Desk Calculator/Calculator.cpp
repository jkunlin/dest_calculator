#include "Token_stream.h"
#include <iostream>
#include <map>
using std::map;

extern Token_stream ts;
map<string, double> table;

int no_of_errors;
int error(const string& s) {
	++no_of_errors;
	std::cerr << "error:" << s << std::endl;
	return 1;
}

double expr(bool get);

double prim(bool get) {
	if (get) ts.get();
	switch (ts.current().kind) {
	case Kind::number:
	{
						 double v = ts.current().number_value;
						 ts.get();
						 return v;
	}
	case Kind::name:
	{
					   double &v = table[ts.current().string_value];
					   if (ts.get().kind == Kind::assign) v = expr(true);
					   return v;
	}
	case Kind::minus:
	{
						return -prim(true);
	}
	case Kind::lp:
	{
					 auto e = expr(true);
					 if (ts.current().kind != Kind::rp)
						 return error("'(' expected");
	}
	default:
		return error("primary expected");
	}
}

double term(bool get) {
	double left = prim(get);

	for (;;) {
		switch (ts.current().kind) {
		case Kind::mul:
			left *= prim(true);
			break;
		case Kind::div:
			if (auto d = prim(true)) {
				left /= d;
				break;
			}
			return error("divide by 0");
		default:
			return left;
		}
	}
}

double expr(bool get) {
	double left = term(get);

	for (;;) {
		switch (ts.current().kind)
		{
		case Kind::plus:
			left += term(true);
			break;
		case Kind::minus:
			left -= term(true);
			break;
		default:
			return left;
		}
	}
}

void calculate() {
	table["pi"] = 3.1415926535897932385;
	table["e"] = 2.718281828459052354;
	for (;;) {
		ts.get();
		if (ts.current().kind == Kind::end) break;
		if (ts.current().kind == Kind::print) continue;
		std::cout << expr(false) << std::endl;
	}
}