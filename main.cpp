#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

string ReadFile(string);
void parseCode(vector <string> &,string);

int main(){

    //store the content of the Sample text file into variable code
    string code = ReadFile("SampleFile.txt");

    cout << code << endl;

    vector <string> codeVector; //this vector holds the variable of all the contents of the file
    
    parseCode(codeVector,"SampleFile.txt");


    //Print out the code line by line
    int i = 0;
    while(i < codeVector.size()){
        cout << codeVector[i] << endl;
        i++;
    }
    



    return 0; 
}


/*
* string ReadFile(filename) will read a file and store the contents of the 
* file into a string and the function will return 
* the code into main
*/
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


/*
* parseCode() will read a file and store each line of the sameple text 
* file to a vector 
*
*/
void parseCode(vector <string> &codeVec, string filename){
    string code; 

    ifstream File;

    File.open(filename);

    if(File.fail()){
        cout << "Error: unable to read file\n";
        return;
    }

    while(!File.eof()){
        getline(File,code);

        //If the line contains empty strings then skip to the next line
        if(code != ""){
         codeVec.push_back(code);
        }
    }
    File.close();
}