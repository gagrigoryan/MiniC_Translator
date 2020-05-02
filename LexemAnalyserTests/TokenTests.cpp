#include "pch.h"
#include "../LexemAnalyser/Token.h"

TEST(TokenTests, EmptyToken) {
	ostringstream outStream;
	Token token(LexemType::eof);
	token.print(outStream);
	ASSERT_EQ("[eof]", outStream.str());
	ASSERT_EQ(LexemType::eof, token.type());
	ASSERT_EQ(0, token.value());
	ASSERT_EQ("", token.str());
}

TEST(TokenTests, StrToken) {
	ostringstream outStream;
	Token token(LexemType::id, "test");
	token.print(outStream);
	ASSERT_EQ("[id, \"test\"]", outStream.str());
	ASSERT_EQ(LexemType::id, token.type());
	ASSERT_EQ(0, token.value());
	ASSERT_EQ("test", token.str());
	outStream.str("");

	Token token2(LexemType::error, "какая-то строковая ошибка!");
	token2.print(outStream);
	ASSERT_EQ("[error, \"какая-то строковая ошибка!\"]", outStream.str());
	ASSERT_EQ(LexemType::error, token2.type());
	ASSERT_EQ(0, token2.value());
	ASSERT_EQ("какая-то строковая ошибка!", token2.str());
}

TEST(TokenTests, CharToken) {
	ostringstream outStream;
	Token token('c');
	token.print(outStream);
	ASSERT_EQ("[chr, 'c']", outStream.str());
	ASSERT_EQ(LexemType::chr, token.type());
	ASSERT_EQ('c', token.value());
	ASSERT_EQ("c", token.str());
}

TEST(TokenTests, IntToken) {
	ostringstream outStream;
	Token token(33);
	token.print(outStream);
	ASSERT_EQ("[num, 33]", outStream.str());
	ASSERT_EQ(LexemType::num, token.type());
	ASSERT_EQ(33, token.value());
	ASSERT_EQ("", token.str());
}