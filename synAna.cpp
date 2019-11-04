/*******************************************************************************
E ->  TQ
Q -> +TQ | ε
T ->  FR
R -> *FR | ε
F -> (E) | id
*******************************************************************************/

#include <iostream>
#include <ctype.h>

using namespace std;

//FROM THE TEXTBOOK:
// Global variable tokenPtr indexes the input string. If the current token is
// in a follow set, then it is not used up. Next time a function examines a
// token, we must give it the same token again. This is done by moving the
// tokenPtr back one character -> backup().

bool E();
bool Q();
bool T();
bool R();
bool F();
int tokenPtr;
string testString = "a + b";

void forward() {
  if(tokenPtr < testString.size()) {
    tokenPtr += 1;
    while(testString[tokenPtr] == ' ') {
      tokenPtr += 1;
    }
  }
}

void backup() {
  if(tokenPtr > 0) {
    tokenPtr -= 1;
    while(testString[tokenPtr] == ' ') {
      tokenPtr -= 1;
    }
  }
}

bool E() {
  if( T() ) {
    if( Q() ) {
      cout << "E -> TQ\n";
      return true;
    }
  }
}

bool Q() {
  char cc = testString[tokenPtr];
  forward();
  if( cc == '+' ) {
    if ( T() ) {
      if ( Q() ) {
        cout << "Q -> +TQ\n";
        return true;
      }
    }
  } else {
    if( cc == ')' || '$') {
      backup();
      cout << "Q -> eps\n";
      return true;
    }
  }
}

bool T() {
  if( F() ) {
    if( R() ) {
      cout << "T -> FR\n";
      return true;
    }
  }
}

bool R() {
  char cc = testString[tokenPtr];
  forward();
  if( cc == '*') {
    if( F() ) {
      if( R() ) {
        cout << "R -> *FR\n";
        return true;
      }
    }
  } else {
    if( cc == '+' || ')' || '$' ) {
      backup();
      cout << "R -> eps\n";
      return true;
    }
  }
}

bool F() {
  char cc = testString[tokenPtr];
  forward();
  if( isalpha(cc) ) {
    cout << "F -> id\n";
    return true;
  } else {
    if( cc == '(') {
      if( E() ) {
        if( cc == ')' ) {
          cout << "F -> (E)\n";
          return true;
        }
      }
    }
  }
}

int main() {

  string inputStr;

  testString = testString + '$'; //Append end marker
  tokenPtr = 0;

  cout << testString << endl;
  cout << testString[tokenPtr] << endl;

  if( E() && testString[tokenPtr] == '$' ) {
    cout << "success\n";
  } else {
    cout << "failure\n";
    cout << testString << endl;
    cout << "^" << tokenPtr << " ---error\n";
  }

  return 0;
}
