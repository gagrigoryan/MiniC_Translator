#ifndef PROJECT_MICRIC_TOKEN_H
#define PROJECT_MICRIC_TOKEN_H

#include <string>
using namespace std;


enum class LexemType {
	num, chr, str, id, lpar, rpar, lbrace, rbrace, lbracket, rbracket,
	semicolon, comma, colon, opassign, opplus, opminus, opmult, opinc, opeq, opne, oplt,
	opgt, ople, opnot, opor, opand, kwint, kwchar, kwif, kwelse, kwswitch, kwcase, kwwhile,
	kwfor, kwreturn, kwin, kwout, eof, error
};

string lexemToString(LexemType type);


class Token {
private:
	LexemType _type;
	int _value = 0;
	string _str;
public:
	Token();
	Token(LexemType type);
	Token(int value);
	Token(LexemType type, const string& str);
	Token(char c);

	LexemType type();
	int value();
	string str();
	string toInput();
	void print(ostream& stream);
};


#endif