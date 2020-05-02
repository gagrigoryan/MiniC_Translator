#include <iostream>
#include <string>
#include <fstream>
#include "Token.h"
#include "Scaner.h"

using namespace std;

int main() {
	ofstream fout("out.txt");
	ifstream fin("test.txt");
	Scanner scanner(fin);

	for (;;) {
		Token currentLexem = scanner.getNextLexem();
		currentLexem.print(cout);
		currentLexem.print(fout);
		cout << endl;
		fout << endl;
		if (currentLexem.type() == LexemType::error
			|| currentLexem.type() == LexemType::eof) {
			break;
		}
	}

	fout.close();
	fin.close();

	return 0;
}