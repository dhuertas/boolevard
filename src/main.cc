/*
 * Boolean expression evaluator in C++.
 * Based on https://ruslanspivak.com/lsbasi-part7/
 *
 * @author: Dani Huertas
 */
#include <iostream>
#include <string>

#include <unistd.h>

#include "main.hh"

#include "Parser.hh"
#include "Number.hh"
#include "String.hh"
#include "Boolean.hh"
#include "List.hh"
#include "Interpreter.hh"

const char *exprStr_ = NULL;

int logLevel_ = LOG_INFO;

void usage(char *name) {

    char fmt[] = "Usage: %s [options] 'expression'\n"
        "Options:\n"
        "\t-v: verbose\n"
        "\t-e: expression\n"
    "\n";

  printf(fmt, name);
  exit(0);
}

int getOptions(int argc, char *argv[0]) {

    int c;

    opterr = 0;

    while ((c = getopt (argc, argv, "e:hv")) != -1) {

        switch (c) {

            case 'h': usage(argv[0]); exit(0);
            case 'v': logLevel_++; break;
            case 'e': exprStr_ = optarg; break;
            default:
                abort();
        }
    }

    if (not exprStr_) {
        exprStr_ = argv[optind];
    }

  return 0;
}

int main(int argc, char *argv[]) {

    int res = getOptions(argc, argv);

    if (res < 0) {
        std::cerr << "Error parsing arguments" << std::endl;
        return -1;
    }

    std::string expression(exprStr_);

    Lexer lexer(expression);
    Parser parser(lexer);
    Interpreter interpreter(parser);

    bool result = interpreter.interpret();

    std::cout << (result ? "true" : "false") << std::endl;

    return 0;
}