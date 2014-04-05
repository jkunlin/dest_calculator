#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include <string>
#include <iostream>
using std::string; using std::istream;


enum class Kind : char {
	name, number, end,
	plus = '+', minus = '-', mul = '*', div = '/', print = ';', assign = '=', lp = '(', rp = ')'
};

struct Token {
	Kind kind;
	string string_value;
	double number_value;
};

class Token_stream {
private:
	void close() { if (owns) delete ip; }

	istream *ip;
	bool owns;
	Token ct;
public:
	Token_stream(istream &s) : ip{ &s }, owns{ false }, ct{ { Kind::end } }{}
	Token_stream(istream *p) : ip{ p }, owns{ true }, ct{ { Kind::end } }{}

	~Token_stream() { close(); }

	Token get();
	const Token& current() { return ct; }

	void set_input(istream &s) { close(); ip = &s; owns = false; }
	void set_input(istream *p) { close(); ip = p; owns = true; }
};

#endif