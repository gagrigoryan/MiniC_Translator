#include "pch.h"
#include "../LexemAnalyser/Token.h"
#include "../LexemAnalyser/Scaner.h"


TEST(ScannerTests, EmptyFile) {
	istringstream inputStream("");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ErrorChar) {
	istringstream inputStream("ошибка");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::error, token.type());
}

TEST(ScannerTests, CountTest) {
	istringstream inputStream("0");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(0, token.value());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}


TEST(ScannerTests, NumberTest) {
	istringstream inputStream("33");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(33, token.value());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, NumbersTest) {
	istringstream inputStream("4;64");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(4, token.value());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(64, token.value());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, CharTest) {
	istringstream inputStream("'с'");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::chr, token.type());
	ASSERT_EQ("с", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ErrorCharTest) {
	istringstream inputStream("'ab'");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::error, token.type());
}

TEST(ScannerTests, EmptyCharTest) {
	istringstream inputStream("''");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::error, token.type());
}

TEST(ScannerTests, CharsTest) {
	istringstream inputStream("'a';'b'");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::chr, token.type());
	ASSERT_EQ("a", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::chr, token.type());
	ASSERT_EQ("b", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, KeywordTest) {
	istringstream inputStream("return;");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwreturn, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, IdTest) {
	istringstream inputStream("let");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("let", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, KeywordIdTest) {
	istringstream inputStream("return let;");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwreturn, token.type());
	scanner >> token;
	token.print(cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("let", token.str());
	scanner >> token;
	token.print(cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	scanner >> token;
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, StringTest) {
	istringstream inputStream("\"Hello, world!\"");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::str, token.type());
	ASSERT_EQ("Hello, world!", token.str());
	scanner >> token;
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ErrorStringTest) {
	istringstream inputStream("\"Error string, not end");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::error, token.type());
}

TEST(ScannerTests, MinusOperTest) {
	istringstream inputStream("-");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::opminus, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, MinusNumTest) {
	istringstream inputStream("-4");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(-4, token.value());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, MinusTwoNumTest) {
	istringstream inputStream("12 - 19");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(12, token.value());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::opminus, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(19, token.value());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, MinusTwoNum2Test) {
	istringstream inputStream("12 + (-19)");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(12, token.value());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::opplus, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(-19, token.value());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, NotTest) {
	istringstream inputStream("!");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::opnot, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, NeqTest) {
	istringstream inputStream("!=");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::opne, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, LtTest) {
	istringstream inputStream("<");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::oplt, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, LeTest) {
	istringstream inputStream("<=");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::ople, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, PlusTest) {
	istringstream inputStream("+");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::opplus, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, IncTest) {
	istringstream inputStream("5++");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::opinc, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, OrTest) {
	istringstream inputStream("||");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::opor, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ErrorOrTest) {
	istringstream inputStream("|'a'");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::error, token.type());
}

TEST(ScannerTests, AndTest) {
	istringstream inputStream("&&");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::opand, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ErrorAndTest) {
	istringstream inputStream("&-");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::error, token.type());
}

TEST(ScannerTests, IfTest) {
	istringstream inputStream("if");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwif, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, IfExprTest) {
	istringstream inputStream("if (a==10);");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwif, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("a", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::opeq, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(10, token.value());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ForTest) {
	istringstream inputStream("for");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwfor, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ForExprTest) {
	istringstream inputStream("for (i=0;i<10;i++)");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwfor, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("i", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::opassign, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(0, token.value());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("i", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::oplt, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(10, token.value());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("i", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::opinc, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, SwitchTest) {
	istringstream inputStream("switch");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwswitch, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, SwitchExprTest) {
	istringstream inputStream("switch (a*2);");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwswitch, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("a", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::opmult, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(2, token.value());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, OutTest) {
	istringstream inputStream("out");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwout, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, OutNumTest) {
	istringstream inputStream("out(42);");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwout, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(42, token.value());
	token = scanner.getNextLexem();
	token.print(cerr);;
	ASSERT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, Out2Test) {
	istringstream inputStream("out(res);");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwout, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("res", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, OutWordTest) {
	istringstream inputStream("out(\"Hello, world!\");");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwout, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::str, token.type());
	ASSERT_EQ("Hello, world!", token.str());
	scanner >> token;
	token.print(cerr);
	ASSERT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, InTest) {
	istringstream inputStream("in");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwin, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, WhileTest) {
	istringstream inputStream("while");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwwhile, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, WhileExprTest) {
	istringstream inputStream("while (a<=111);");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwwhile, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("a", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::ople, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(111, token.value());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, CaseTest) {
	istringstream inputStream("case");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwcase, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ElseTest) {
	istringstream inputStream("else");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwelse, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, BracketTest) {
	istringstream inputStream("[]");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::lbracket, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::rbracket, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ColonTest) {
	istringstream inputStream(":");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::colon, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, CommaTest) {
	istringstream inputStream(",");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::comma, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ParTest) {
	istringstream inputStream("()");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::lpar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::rpar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, BraceTest) {
	istringstream inputStream("{}");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::lbrace, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::rbrace, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, IntTest) {
	istringstream inputStream("int a;");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwint, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("a", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ManyIntsTest) {
	istringstream inputStream("int a=3,b=4,c=5;");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwint, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("a", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::opassign, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(3, token.value());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::comma, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("b", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::opassign, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(4, token.value());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::comma, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("c", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::opassign, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(5, token.value());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, Char2Test) {
	istringstream inputStream("char b;");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwchar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("b", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ManyCharsTest) {
	istringstream inputStream("char a,b,c;");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwchar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("a", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::comma, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("b", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::comma, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("c", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, SignTest) {
	istringstream inputStream("=");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::opassign, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, CharExprTest) {
	istringstream inputStream("char b=17;");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwchar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("b", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::opassign, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(17, token.value());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, IntArrTest) {
	istringstream inputStream("int a[19];");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwint, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("a", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::lbracket, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(19, token.value());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::rbracket, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, CharArrTest) {
	istringstream inputStream("char buf[] = \"Hello world!\";");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::kwchar, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("buf", token.str());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::lbracket, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::rbracket, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::opassign, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::str, token.type());
	ASSERT_EQ("Hello world!", token.str());
	scanner >> token;
	token.print(cerr);
	ASSERT_EQ(LexemType::semicolon, token.type());
	token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}

TEST(ScannerTests, ExpressionTest) {
	istringstream inputStream("12+20<!a");
	Scanner scanner(inputStream);
	Token token = scanner.getNextLexem();
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(12, token.value());
	scanner >> token;
	token.print(cerr);
	ASSERT_EQ(LexemType::opplus, token.type());
	scanner >> token;
	token.print(cerr);
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(20, token.value());
	scanner >> token;
	token.print(cerr);
	ASSERT_EQ(LexemType::oplt, token.type());
	scanner >> token;
	token.print(cerr);
	ASSERT_EQ(LexemType::opnot, token.type());
	scanner >> token;
	token.print(cerr);
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ("a", token.str());
	scanner >> token;
	token.print(cerr);
	ASSERT_EQ(LexemType::eof, token.type());
}
