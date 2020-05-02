#include "Scaner.h"

Scanner::Scanner(istream& stream)
	:inputStream(stream) {}

Scanner& operator>>(Scanner& scanner, Token& token) {
	token = scanner.getNextLexem();
	return scanner;
}

bool Scanner::isDigit(char c) {
	return '0' <= c && c <= '9';
}

int Scanner::charToInt(char c) {
	return c - '0';
}

bool Scanner::isChar(char c) {
	return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_';
}


Token Scanner::getNextLexem() {
	if (stopped) {
		return TokenStop;
	}
	while (true) {
		if (!currentStop || inputStream.eof()) {
			currentChar = inputStream.get();
			if (inputStream.eof() && currentState == 0) {
				stopped = true;
				TokenStop = Token(LexemType::eof);
				return TokenStop;
			}
			else if (inputStream.eof() &&
				(currentState == 3 || currentState == 4 || currentState == 11 || currentState == 12)) {
				stopped = true;
				TokenStop = Token(LexemType::error, "eof");
				return TokenStop;
			}
		}
		currentStop = false;
		
		if (currentState == 0) {
			if (isDigit(currentChar)) {
				currentState = 1;
				intValue = charToInt(currentChar);
				continue;
			}
			else if (currentChar == '*') {
				return Token(LexemType::opmult);
			}
			else if (punctuation.find(currentChar) != punctuation.end()) {
				Token out(punctuation.find(currentChar)->second);
				return out;
			}
			else if (currentChar == ' ' || currentChar == '\n') {
				continue;
			}
			else if (currentChar == '\'') {
				currentState = 2;
				continue;
			}
			else if (currentChar == '!') {
				currentState = 7;
				continue;
			}
			else if (currentChar == '<') {
				currentState = 8;
				continue;
			}
			else if (currentChar == '=') {
				currentState = 9;
				continue;
			}
			else if (currentChar == '+') {
				currentState = 10;
				continue;
			}
			else if (currentChar == '|') {
				currentState = 11;
				continue;
			}
			else if (currentChar == '&') {
				currentState = 12;
				continue;
			}
			else if (currentChar == '"') {
				currentState = 4;
				continue;
			}
			else if (isChar(currentChar)) {
				currentState = 5;
				stringValue += currentChar;
				continue;
			}
			else if (currentChar == '-') {
				currentState = 6;
				continue;
			}
			else if (currentChar == '>') {
				return Token(LexemType::opgt);
			}
		}
		else if (currentState == 1) {
			if (isDigit(currentChar)) {
				if (negative) {
					intValue = intValue * 10 - charToInt(currentChar);
				}
				else {
					intValue = intValue * 10 + charToInt(currentChar);
				}
				continue;
			}
			else {
				Token out(intValue);
				currentState = 0;
				intValue = 0;
				negative = false;
				currentStop = true;
				return out;
			}
		}
		else if (currentState == 2) {
			if (currentChar == '\'') {
				stopped = true;
				return Token(LexemType::error, "empty chr");
			}
			else {
				currentState = 3;
				charValue = currentChar;
				continue;
			}
		}
		else if (currentState == 3) {
			if (currentChar == '\'') {
				Token out(charValue);
				currentState = 0;
				return out;
			}
			else {
				stopped = true;
				TokenStop = Token(LexemType::error, "invalid chr");
				return TokenStop;
			}
		}
		else if (currentState == 4) {
			if (currentChar == '"') {
				Token out(LexemType::str, stringValue);
				currentState = 0;
				stringValue = "";
				return out;
			}
			else {
				stringValue += currentChar;
				continue;
			}
		}
		else if (currentState == 5) {
			if (isChar(currentChar) || isDigit(currentChar)) {
				stringValue += currentChar;
				continue;
			}
			else if (keywords.find(stringValue) != keywords.end()) {
				Token out(keywords.find(stringValue)->second);
				stringValue = "";
				currentState = 0;
				currentStop = true;
				return out;
			}
			else {
				Token out(LexemType::id, stringValue);
				stringValue = "";
				currentState = 0;
				currentStop = true;
				return out;
			}
		}
		else if (currentState == 6) {
			if (isDigit(currentChar)) {
				intValue = (-1) * charToInt(currentChar);
				currentState = 1;
				negative = true;
				continue;
			}
			else {
				Token out(LexemType::opminus);
				currentState = 0;
				currentStop = true;
				return out;
			}
		}
		else if (currentState == 7) {
			if (currentChar == '=') {
				Token out(LexemType::opne);
				currentState = 0;
				return out;
			}
			else {
				Token out(LexemType::opnot);
				currentState = 0;
				currentStop = true;
				return out;
			}
		}
		else if (currentState == 8) {
			if (currentChar == '=') {
				Token out(LexemType::ople);
				currentState = 0;
				return out;
			}
			else {
				Token out(LexemType::oplt);
				currentState = 0;
				currentStop = true;
				return out;
			}
		}
		else if (currentState == 9) {
			if (currentChar == '=') {
				Token out(LexemType::opeq);
				currentState = 0;
				return out;
			}
			else {
				Token out(LexemType::opassign);
				currentState = 0;
				currentStop = true;
				return out;
			}
		}
		else if (currentState == 10) {
			if (currentChar == '+') {
				Token out(LexemType::opinc);
				currentState = 0;
				return out;
			}
			else {
				Token out(LexemType::opplus);
				currentState = 0;
				currentStop = true;
				return out;
			}
		}
		else if (currentState == 11) {
			if (currentChar == '|') {
				Token out(LexemType::opor);
				currentState = 0;
				return out;
			}
			else {
				stopped = true;
				TokenStop = Token(LexemType::error, "unfamiliar char: |");
				return TokenStop;
			}
		}
		else if (currentState == 12) {
			if (currentChar == '&') {
				Token out(LexemType::opand);
				currentState = 0;
				return out;
			}
			else {
				stopped = true;
				TokenStop = Token(LexemType::error, "unfamiliar char: &");
				return TokenStop;
			}
		}
		stopped = true;
		string text = "unfamiliar : ";
		text += currentChar;
		TokenStop = Token(LexemType::error, text);
		return TokenStop;
	}
}