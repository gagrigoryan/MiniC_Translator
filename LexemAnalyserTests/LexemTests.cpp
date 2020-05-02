#include "pch.h"
#include "../LexemAnalyser/Token.h"


TEST(LexemTests, LexemTypeTest) {
	EXPECT_EQ("num", lexemToString(LexemType::num));
	EXPECT_EQ("chr", lexemToString(LexemType::chr));
	EXPECT_EQ("str", lexemToString(LexemType::str));
	EXPECT_EQ("id", lexemToString(LexemType::id));
	EXPECT_EQ("lpar", lexemToString(LexemType::lpar));
	EXPECT_EQ("rpar", lexemToString(LexemType::rpar));
	EXPECT_EQ("lbrace", lexemToString(LexemType::lbrace));
	EXPECT_EQ("rbrace", lexemToString(LexemType::rbrace));
	EXPECT_EQ("lbracket", lexemToString(LexemType::lbracket));
	EXPECT_EQ("rbracket", lexemToString(LexemType::rbracket));
	EXPECT_EQ("semicolon", lexemToString(LexemType::semicolon));
	EXPECT_EQ("comma", lexemToString(LexemType::comma));
	EXPECT_EQ("colon", lexemToString(LexemType::colon));
	EXPECT_EQ("opassign", lexemToString(LexemType::opassign));
	EXPECT_EQ("opplus", lexemToString(LexemType::opplus));
	EXPECT_EQ("opminus", lexemToString(LexemType::opminus));
	EXPECT_EQ("opmult", lexemToString(LexemType::opmult));
	EXPECT_EQ("opinc", lexemToString(LexemType::opinc));
	EXPECT_EQ("opeq", lexemToString(LexemType::opeq));
	EXPECT_EQ("opne", lexemToString(LexemType::opne));
	EXPECT_EQ("oplt", lexemToString(LexemType::oplt));
	EXPECT_EQ("opgt", lexemToString(LexemType::opgt));
	EXPECT_EQ("ople", lexemToString(LexemType::ople));
	EXPECT_EQ("opnot", lexemToString(LexemType::opnot));
	EXPECT_EQ("opor", lexemToString(LexemType::opor));
	EXPECT_EQ("opand", lexemToString(LexemType::opand));
	EXPECT_EQ("kwint", lexemToString(LexemType::kwint));
	EXPECT_EQ("kwchar", lexemToString(LexemType::kwchar));
	EXPECT_EQ("kwif", lexemToString(LexemType::kwif));
	EXPECT_EQ("kwelse", lexemToString(LexemType::kwelse));
	EXPECT_EQ("kwswitch", lexemToString(LexemType::kwswitch));
	EXPECT_EQ("kwcase", lexemToString(LexemType::kwcase));
	EXPECT_EQ("kwwhile", lexemToString(LexemType::kwwhile));
	EXPECT_EQ("kwfor", lexemToString(LexemType::kwfor));
	EXPECT_EQ("kwreturn", lexemToString(LexemType::kwreturn));
	EXPECT_EQ("kwin", lexemToString(LexemType::kwin));
	EXPECT_EQ("kwout", lexemToString(LexemType::kwout));
	EXPECT_EQ("eof", lexemToString(LexemType::eof));
	EXPECT_EQ("error", lexemToString(LexemType::error));
}