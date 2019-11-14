/*******************************************************************************
E ->  TQ
Q -> +TQ | -TQ | ε
T ->  FR
R -> *FR | ε
F -> (E) | id
*******************************************************************************/

#include <iostream>
#include <ctype.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

//FROM THE TEXTBOOK:
// Global variable tokenPtr indexes the input string. If the current token is
// in a follow set, then it is not used up. Next time a function examines a
// token, we must give it the same token again. This is done by moving the
// tokenPtr back one character -> backup().

string ReadFile(string);
string SplitOffStart(string codeSnip);
string ParseEndLines(string &codeSnip);
void SyntacticalAnalyzer(string codeToCheck);

bool E();
bool Q();
bool T();
bool R();
bool F();
void forward();
void backup();
int tokenPtr;
ofstream outputFile;
string testString = "a + b";
string snip;

int main() {

    outputFile.open("output.txt");
    //store the content of the Sample text file into variable code
    string code = ReadFile("SampleFile.txt");
    code = SplitOffStart(code);

    tokenPtr = 0;
    snip = ParseEndLines(code);
    snip = snip + '$';
    while(code.length() > 0) {

        //run the analyzer on each line of code (snip)
        SyntacticalAnalyzer(snip);

        tokenPtr = 0;
        snip = ParseEndLines(code);
        snip = snip + '$';
    }
    //run the analyzer on the last line of code
    SyntacticalAnalyzer(snip);

    return 0;
}


void forward() {
  if(tokenPtr < snip.size()) {
    tokenPtr += 1;
    while(snip[tokenPtr] == ' ') {
      tokenPtr += 1;
    }
  }
}

void backup() {
  if(tokenPtr > 0) {
    tokenPtr -= 1;
    while(snip[tokenPtr] == ' ') {
      tokenPtr -= 1;
    }
  }
}

bool E() {
  if( T() ) {
    if( Q() ) {
      cout << "E -> TQ\n";
      outputFile << "E -> TQ\n";
      return true;
    }
  }
}

bool Q() {
  char cc = snip[tokenPtr];
  forward();
  if( cc == '+' || cc == '-') {
    if ( T() ) {
      if ( Q() ) {
        cout << "Q -> +TQ\n";
        outputFile << "Q -> +TQ\n";
        return true;
      }
    }
  } else {
    if( cc == ')' || '$') {
      backup();
      cout << "Q -> eps\n";
      outputFile << "Q -> eps\n";
      return true;
    }
  }
}

bool T() {
  if( F() ) {
    if( R() ) {
      cout << "T -> FR\n";
      outputFile << "T -> FR\n";
      return true;
    }
  }
}

bool R() {
  char cc = snip[tokenPtr];
  forward();
  if( cc == '*') {
    if( F() ) {
      if( R() ) {
        cout << "R -> *FR\n";
        outputFile << "R -> *FR\n";
        return true;
      }
    }
  } else {
    if( cc == '+' || ')' || '$' ) {
      backup();
      cout << "R -> eps\n";
      outputFile << "R -> eps\n";
      return true;
    }
  }
}

bool F() {
  char cc = snip[tokenPtr];
  forward();
  if( isalpha(cc) ) {
    cout << "F -> id\n";
    outputFile << "F -> id\n";
    return true;
  } else {
    if( cc == '(') {
      if( E() ) {
        if( cc == ')' ) {
          cout << "F -> (E)\n";
          outputFile << "F -> (E)\n";
          return true;
        }
      }
    }
  }
}

void SyntacticalAnalyzer(string codeToCheck) {
    cout << codeToCheck << endl;
    outputFile << codeToCheck << endl;
    if( E() && codeToCheck[tokenPtr] == '$' ) {
    cout << "success\n\n";
    outputFile << "success\n\n";
    } else {
    cout << "failure\n";
    cout << codeToCheck << endl;
    cout << "^" << tokenPtr <<  " " << codeToCheck[tokenPtr] << " ---error\n\n";
    outputFile << "failure\n";
    outputFile << codeToCheck << endl;
    outputFile << "^" << tokenPtr <<  " " << codeToCheck[tokenPtr] << " ---error\n\n";
    }
}

string ReadFile(string filename){
    string code = ""; 
    string temp;

    ifstream File;

    File.open(filename);

    if(File.fail()){
        cout << "Error: unable to read file\n";
        return "";
    }

    while(!File.eof()){
        getline(File,temp);
        code += temp;
    }

    File.close();

    return code;
}

string SplitOffStart(string codeSnip) {
    int found = codeSnip.find_last_of("%%");
    string snipped = codeSnip.substr(found+1);
    return snipped;
}

string ParseEndLines(string &codeSnip) {
    int endLine = codeSnip.find_first_of(';');
    string snip = codeSnip.substr(2,endLine-2);
    codeSnip.erase(0,endLine+1);
    return snip;   
}