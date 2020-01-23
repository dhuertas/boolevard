/*
 * Boolean expression evaluator in C++.
 *
 * @author Dani Huertas
 * @email huertas.dani@gmail.com
 *
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <vector>

#include <unistd.h>

#include "main.hh"
#include "Number.hh"
#include "String.hh"
#include "Boolean.hh"
#include "List.hh"
#include "Interpreter.hh"
#include "Parser.hh"

const char *exprStr_ = NULL;

int logLevel_ = LOG_INFO;
bool numeric_ = false;

std::map<std::string, Token> variables_;

std::vector<std::string> invalidVariableNames_ = {
    "sw",
    "ew",
    "contains",
    "not"
};

//------------------------------------------------------------------------------
void usage(char *name) {

    char fmt[] = "Usage: %s [options] 'expression'\n"
        "Options:\n"
        "\t-a: assign variable (name=value)\n"
        "\t-e: expression (useful when expression contains negative numbers)\n"
        "\t-h: this help\n"
        "\t-n: numeric output (0: false, 1: true)\n"
        "\t-v: verbose\n"
    "\n";

  printf(fmt, name);
  exit(0);
}

//------------------------------------------------------------------------------
void assign(char *var) {

    std::string aux(var);

    size_t pos = aux.find('=');

    if (pos == std::string::npos or pos+1 >= aux.size()) {
        std::cerr << "Invalid assignment: " << aux << std::endl;
        exit(-1);
    }

    std::string name = aux.substr(0, pos); 
    std::string value = aux.substr(pos+1, aux.size());

    if (std::find(invalidVariableNames_.begin(), invalidVariableNames_.end(), name) != invalidVariableNames_.end()) {
        std::cerr << "Invalid variable name: " << name << std::endl;
        exit(-1); 
    }

    Lexer l(value);

    variables_[name] = l.getNextToken();

    DEBUG("%s = %s", name.c_str(), variables_[name].toString().c_str());
}

//------------------------------------------------------------------------------
int getOptions(int argc, char *argv[0]) {

    int c;

    opterr = 0;

    while ((c = getopt(argc, argv, "a:e:hnv")) != -1) {

        switch (c) {

            case 'a': assign(optarg); break;
            case 'h': usage(argv[0]); exit(0);
            case 'n': numeric_ = true; break;
            case 'v': logLevel_++; break;
            case 'e': exprStr_ = optarg; break;
            default:
                INFO("Unrecognized option: '%c'", c);
                exit(-1);
        }
    }

    if (not exprStr_) {
        exprStr_ = argv[optind];
    }

  return 0;
}

//------------------------------------------------------------------------------
int main(int argc, char *argv[]) {

    int res = getOptions(argc, argv);

    if (res < 0) {
        std::cerr << "Error parsing arguments" << std::endl;
        return -1;
    }

    if (not exprStr_) {
        std::cerr << "Missing expression" << std::endl;
        std::cerr << std::endl;
        usage(argv[0]);
        return -1;
    }

    std::string expression(exprStr_);

    Lexer lexer(expression);
    lexer.setVariables(variables_);

    Parser parser(lexer);
    Interpreter interpreter(parser);

    bool result = interpreter.interpret();

    if (numeric_) {
        return (result ? 0 /* OK */ : 1 /* not OK */);
    } else {
        std::cout << (result ? "true" : "false") << std::endl;
    }

    return 0;
}
