#define IDNTIFIER 300
#define INT_CONST 301
#define FLO_CONST 302

#define PLUS      312
#define MINUS     313
#define MULT      314
#define DIV       315
#define PERCENT   303
#define PLUS_PLUS 304
#define MINUS_MINUS 305

#define EQ        311
#define PLUS_EQ   316
#define MINUS_EQ  317
#define MULT_EQ   318
#define DIV_EQ    319

#define EQ_EQ     306
#define LESSER    307
#define LESS_EQ   308
#define GREATER   309
#define GREAT_EQ  310

#define L_SQUARE  414
#define R_SQUARE  415
#define L_PARAEN  416
#define R_PARAEN  417
#define L_CBRACE  418
#define R_CBRACE  419
#define COMMA     420
#define SEMICOL   421

#define SHORT     422
#define INT       423
#define FLOAT     424
#define DOUBLE    425
#define BOOL      426
#define CHAR      427
#define SIGNED    428
#define UNSIGNED  429
#define FOR       430
#define WHILE     431
#define DO        432
#define RETURN    433
#define STRUCT    434
#define CONST     435
#define VOID      436
#define SWITCH    437
#define BREAK     438
#define CASE      439
#define CONTINUE  440
#define GOTO      441
#define LONG      442
#define STATIC    443
#define UNION     444
#define DEFAULT   445
#define IF        475
#define ELSE      476

#define NOTOK     -1


#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;
#include "def.h"  // Include your header file def.h
#include <limits>

unordered_map<string, int> symbolTable;
// unordered_map<string,int>symbolTable;

enum StringValue { plus_plus,minus_minus,eq_eq,less_eq,great_eq,plus_eq, minus_eq,mult_eq, div_eq };

map<std::string, StringValue> s_mapStringValues;

void Initialize()
{
  s_mapStringValues["++"] = plus_plus;
  s_mapStringValues["--"] = minus_minus;
  s_mapStringValues["=="] = eq_eq;
  s_mapStringValues["<="] = less_eq;
  s_mapStringValues[">="] = great_eq;
  s_mapStringValues["+="] = plus_eq;
  s_mapStringValues["-="] = minus_eq;
  s_mapStringValues["*="] = mult_eq;
  s_mapStringValues["/="] = div_eq;

}

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isOperatorSymbol(char c) {
    // Define the characters that can start an operator
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=' || c == '<' || c == '>';
}

bool isSymbol(char c) {
    // Define the characters that represent symbols
    return c == '(' || c == ')' || c == ',' || c == '[' || c == ']' || c == '{' || c == '}' || c == ';';
}

int IsKeyword(const string &lexeme) {
    // Check if lexeme is a keyword, return corresponding token ID
    // Example:
    if (lexeme == "short") return SHORT;
    if (lexeme == "int") return INT;
    if (lexeme == "float") return FLOAT;
    if (lexeme == "double") return DOUBLE;
    if (lexeme == "bool") return BOOL;
    if (lexeme == "char") return CHAR;
    if (lexeme == "signed") return SIGNED;
    if (lexeme == "unsigned") return UNSIGNED;
    if (lexeme == "for") return FOR;
    if (lexeme == "while") return WHILE;
    if (lexeme == "do") return DO;
    if (lexeme == "return") return RETURN;
    if (lexeme == "struct") return STRUCT;
    if (lexeme == "const") return CONST;
    if (lexeme == "void") return VOID;
    if (lexeme == "switch") return SWITCH;
    if (lexeme == "break") return BREAK;
    if (lexeme == "case") return CASE;
    if (lexeme == "continue") return CONTINUE;
    if (lexeme == "goto") return GOTO;
    if (lexeme == "long") return LONG;
    if (lexeme == "static") return STATIC;
    if (lexeme == "union") return UNION;
    if (lexeme == "default") return DEFAULT;
    if (lexeme == "if") return IF;
    if (lexeme == "else") return ELSE;
    
    return 0;  // Return 0 if not a keyword
}

int IsIdentifier(const string &lexeme) {
    // Check if lexeme is a valid identifier, return corresponding token ID
    // Example:
    if (isLetter(lexeme[0]) || lexeme[0] == '_') {
        if(lexeme[1] == '_'){
            return 0;
        }
        for (char c : lexeme) {
            if (!(isLetter(c) || isDigit(c) || c == '_')) {
                return 0;  // Invalid identifier
            }
        }
        return IDNTIFIER;
    }
    return 0;  // Not an identifier
}

int IsIntegerConstant(const string &lexeme) {
    // Check if lexeme is a valid integer constant, return corresponding token ID
    // Example:
    if (isDigit(lexeme[0]) || (lexeme[0] == '-' && isDigit(lexeme[1])) || (lexeme[0] == '+' && isDigit(lexeme[1]))){
        // Check for valid digits
        for (size_t i = 1; i < lexeme.size(); ++i) {
            if (!isDigit(lexeme[i])) {
                return 0;  // Invalid integer constant
            }
        }
        return INT_CONST;
    }
    return 0;  // Not an integer constant
}

int IsFloatConstant(const string &lexeme) {
    // Check if lexeme is a valid float constant, return corresponding token ID
    // Example:
    if (isDigit(lexeme[0]) || (lexeme[0] == '-' && isDigit(lexeme[1])) || (lexeme[0] == '+' && isDigit(lexeme[1]))){
        size_t dotCount = 0;
        for (char c : lexeme) {
            if(c == '+' || c == '-'){
                continue;
            }
            if (isDigit(c)) continue;
            if (c == '.') {
                dotCount++;
                continue;
            }
            return 0;  // Invalid float constant
        }
        if (dotCount == 1) {
            return FLO_CONST;
        }
        return 0;
    }
    return 0;  // Not a float constant
}

int isOperator(const std::string &lexeme) {
    // Check if lexeme is a valid operator, return corresponding token ID
    if (lexeme.size() == 1) {
        switch (lexeme[0]) {
            case '+': return PLUS;
            case '-': return MINUS;
            case '*': return MULT;
            case '/': return DIV;
            case '%': return PERCENT;
            case '=': return EQ;
            default : return 0;
        }
    } else if (lexeme.size() == 2) {
        switch (s_mapStringValues[lexeme]) {
            case plus_plus : return PLUS_PLUS;
            case minus_minus : return MINUS_MINUS;
            case eq_eq: return EQ_EQ;
            case less_eq: return LESS_EQ;
            case great_eq: return GREAT_EQ;
            case plus_eq: return PLUS_EQ;
            case minus_eq: return MINUS_EQ;
            case mult_eq: return MULT_EQ;
            case div_eq: return DIV_EQ;              
            default : return 0; // Not a valid operator
        }
    }
    return 0;  // Not a valid operator
}

int getSymbolTokenID(char symbol) {
    switch (symbol) {
        case '(': return L_PARAEN;
        case ')': return R_PARAEN;
        case ',': return COMMA;
        case '[': return L_SQUARE;
        case ']': return R_SQUARE;
        case '{': return L_CBRACE;
        case '}': return R_CBRACE;
        case ';': return SEMICOL;
        default: return 0;  // Not a valid symbol
    }
}

int main() {
    string inputFileName;
    cout<<"Enter Input File Name : ";
    getline(cin, inputFileName);
    string outputFileName1;
    cout<<"Enter Output File Name for TokenID and Attribute Value : ";
    getline(cin, outputFileName1);
    string outputFileName2;
    cout<<"Enter Output File Name for Keyword and Identifier : ";
    getline(cin, outputFileName2);
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        cerr << "Unable to open input file." << endl;
        return 1;
    }

    Initialize();

    string buffer;
    string lexeme;
    char c;
    
    while (inputFile.get(c)) {
        // Process the characters in the input
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            // Skip whitespaces
            continue;
        }
        else if (c == '/' && inputFile.peek() == '*') {
            // Ignore comments enclosed within /* */
            inputFile.ignore(numeric_limits<streamsize>::max(), '*');
            inputFile.ignore(numeric_limits<streamsize>::max(), '/');
            continue;
        }
        else if (isLetter(c) || c == '_') {
            // Handle identifiers and keywords
            lexeme.clear();
            lexeme += c;
            while (inputFile.get(c) && (isLetter(c) || isDigit(c) || c == '_')) {
                lexeme += c;
            }
            inputFile.unget();  // Put back the character not part of the identifier
            int tokenID = IsKeyword(lexeme);
            if (tokenID == 0) {
                tokenID = IsIdentifier(lexeme);
            }
            // Process the token and update symbol table
            symbolTable.insert({lexeme,tokenID});
            // ...
        }
        else if (isDigit(c) || c == '-' || c == '+') {
            // Handle integer and float constants
            lexeme.clear();
            lexeme += c;
            while (inputFile.get(c) && (isDigit(c) || c == '.')) {
                lexeme += c;
            }
            inputFile.unget();  // Put back the character not part of the constant
            int tokenID = IsIntegerConstant(lexeme);
            if(tokenID!=0){
                symbolTable.insert({lexeme,tokenID});
            }
            if (tokenID == 0) {
                tokenID = IsFloatConstant(lexeme);

                if(tokenID!=0){
                    symbolTable.insert({lexeme,tokenID});
                }
                if (isOperatorSymbol(c)) {
                lexeme.clear();
                lexeme += c;
                while (inputFile.get(c) && isOperatorSymbol(c)) {
                    lexeme += c;
                }
                inputFile.unget();  // Put back the character not part of the operator

                // Check if lexeme is a valid operator and get the token ID
                int tokenID = isOperator(lexeme);
                if (tokenID != 0) {
                // Process the operator token
                symbolTable.insert({lexeme,tokenID});
                // ...
                    }
                }
            }
            // Process the token
            // symbolTable.insert({tokenID,lexeme});

            // ...
        }
        else if (isOperatorSymbol(c)) {
            lexeme.clear();
            lexeme += c;
            while (inputFile.get(c) && isOperatorSymbol(c)) {
                lexeme += c;
            }
            inputFile.unget();  // Put back the character not part of the operator

            // Check if lexeme is a valid operator and get the token ID
            int tokenID = isOperator(lexeme);
            if (tokenID != 0) {
                // Process the operator token
                symbolTable.insert({lexeme,tokenID});
                // ...
            }
        }
        else if (isSymbol(c)) {
            lexeme.clear();
            lexeme += c;
            int tokenID = getSymbolTokenID(c);
            if (tokenID != 0) {
                // Process the symbol token
                symbolTable.insert({lexeme,tokenID});
                // ...
            }
        }
        else{
            cout<<c<<endl;
            cout<<"The character in not recogised"<<endl;
            inputFile.close();
            return 0;
        }
    }

    ofstream outputFile(outputFileName1);
    if (!outputFile.is_open()) {
        cerr << "Error opening output.txt" << std::endl;
        return 1;
    }
    outputFile<<"TokenID"<<"\t\t"<<"Value"<<endl;
    for (const auto& pair : symbolTable) {
        outputFile << pair.second << "\t\t\t" << pair.first << endl;
    }

    outputFile.close();

    ofstream outputFile1(outputFileName2);
    if (!outputFile1.is_open()) {
        cerr << "Error opening output.txt" << std::endl;
        return 1;
    }
    outputFile1<<"Attribute Value"<<"\t\t"<<"0->Keyword 1->Identifier"<<endl;
    for (const auto& pair : symbolTable) {
        if(pair.second == 300){
            outputFile1<<pair.first << "\t\t\t\t"<<"1"<<endl;
        }
        else if(pair.second>=422 && pair.second<=476){
            outputFile1 << pair.first << "\t\t\t\t" << "0"<< endl;
        }
        
    }

    outputFile1.close();
    inputFile.close();
    return 0;
}
