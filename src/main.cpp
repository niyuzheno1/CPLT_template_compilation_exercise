//create hello world program
#include "tree_sitter/api.h"
#include <iostream>
using namespace std;
extern "C" {  TSLanguage *tree_sitter_cpp();}
const char * testDescription ="";
int main()
{
    TSParser *tsParser = ts_parser_new();
    ts_parser_set_language(tsParser, tree_sitter_cpp());
    TSTree const *tree = ts_parser_parse_string(
        tsParser,
        nullptr,
        testDescription,
        strlen(testDescription));
    TSNode root =  ts_tree_root_node(tree);
    return 0;
}