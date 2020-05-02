
#include <map>
#include <istream>
#include "Token.h"

using namespace std;

static map<char, LexemType> punctuation{ {'[', LexemType::lbracket},
											 {']', LexemType::rbracket},
											 {'(', LexemType::lpar},
											 {')', LexemType::rpar},
											 {'{', LexemType::lbrace},
											 {'}', LexemType::rbrace},
											 {';', LexemType::semicolon},
											 {',', LexemType::comma},
											 {':', LexemType::colon} };
static map<string, LexemType> keywords{ {"return", LexemType::kwreturn},
												 {"int",    LexemType::kwint},
												 {"char",   LexemType::kwchar},
												 {"if",     LexemType::kwif},
												 {"else",   LexemType::kwelse},
												 {"switch", LexemType::kwswitch},
												 {"case",   LexemType::kwcase},
												 {"while",  LexemType::kwwhile},
												 {"for",    LexemType::kwfor},
												 {"in",     LexemType::kwin},
												 {"out",    LexemType::kwout} };

class Scanner {
private:
	int intValue = 0;
	char charValue = '\0';
	string stringValue = "";
	int currentState = 0;
	char currentChar = '\0';
	bool stopped = false;
	bool currentStop = false;
	bool negative = false;
	Token TokenStop = Token(LexemType::eof);
	istream& inputStream;
public:
	Scanner(istream& inputStream);

	bool isDigit(char c);

	bool isChar(char c);

	int charToInt(char c);

	Token getNextLexem();
};

Scanner& operator>>(Scanner& scanner, Token& token);