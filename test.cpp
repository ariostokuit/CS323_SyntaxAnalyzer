#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

string ReadFile(string);
string SplitOffStart(string codeSnip);
string ParseEndLines(string &codeSnip);

int main(){

    //store the content of the Sample text file into variable code
    string code = ReadFile("SampleFile.txt");
    string snip;
    
    
    code = SplitOffStart(code);
    
    while(code.length() > 0) {
        snip = ParseEndLines(code);
        cout << snip << endl;
    }

    return 0; 
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