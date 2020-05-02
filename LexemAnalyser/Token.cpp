
#include "Token.h"
#include <iostream>
#include <string>


Token::Token() {
	_type = LexemType::error;
}

Token::Token(LexemType type) {
	_type = type;
}

Token::Token(int value) {
	_type = LexemType::num;
	_value = value;
}

Token::Token(LexemType type, const string& str) {
	_type = type;
	_str = str;
}

Token::Token(char c) {
	_type = LexemType::chr;
	_value = int(c);
	string s(1, c);
	_str = s;
}

LexemType Token::type() {
	return _type;
}

int Token::value() {
	return _value;
}

string Token::str() {
	return _str;
}

string Token::toInput() {
	switch (_type) {
	case LexemType::num:
		return lexemToString(_type) + ", " + to_string(_value);
	case LexemType::chr:
		return lexemToString(_type) + ", " + "'" + _str + "'";
	case LexemType::eof:
		return lexemToString(_type);
	case LexemType::id:
		return lexemToString(_type) + ", " + "\"" + _str + "\"";
	default:
		if (!_str.empty()) {
			return lexemToString(_type) + ", " + "\"" + _str + "\"";
		}
		else {
			return lexemToString(_type);
		}
	}
}

void Token::print(ostream& stream) {
	stream << "[" << toInput() << "]";
}


string lexemToString(LexemType type) {

	switch (type) {
	case LexemType::num:
		return "num";
	case LexemType::chr:
		return "chr";
	case LexemType::str:
		return "str";
	case LexemType::id:
		return "id";
	case LexemType::lpar:
		return "lpar";
	case LexemType::rpar:
		return "rpar";
	case LexemType::lbrace:
		return "lbrace";
	case LexemType::rbrace:
		return "rbrace";
	case LexemType::lbracket:
		return "lbracket";
	case LexemType::rbracket:
		return "rbracket";
	case LexemType::semicolon:
		return "semicolon";
	case LexemType::comma:
		return "comma";
	case LexemType::colon:
		return "colon";
	case LexemType::opassign:
		return "opassign";
	case LexemType::opplus:
		return "opplus";
	case LexemType::opminus:
		return "opminus";
	case LexemType::opmult:
		return "opmult";
	case LexemType::opinc:
		return "opinc";
	case LexemType::opeq:
		return "opeq";
	case LexemType::opne:
		return "opne";
	case LexemType::ople:
		return "ople";
	case LexemType::oplt:
		return "oplt";
	case LexemType::opgt:
		return "opgt";
	case LexemType::opnot:
		return "opnot";
	case LexemType::opor:
		return "opor";
	case LexemType::opand:
		return "opand";
	case LexemType::kwint:
		return "kwint";
	case LexemType::kwchar:
		return "kwchar";
	case LexemType::kwif:
		return "kwif";
	case LexemType::kwswitch:
		return "kwswitch";
	case LexemType::kwcase:
		return "kwcase";
	case LexemType::kwwhile:
		return "kwwhile";
	case LexemType::kwfor:
		return "kwfor";
	case LexemType::kwreturn:
		return "kwreturn";
	case LexemType::kwin:
		return "kwin";
	case LexemType::kwout:
		return "kwout";
	case LexemType::kwelse:
		return "kwelse";
	case LexemType::eof:
		return "eof";
	case LexemType::error:
		return "error";
	}
}

