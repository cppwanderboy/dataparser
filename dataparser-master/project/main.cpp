// #define CHECK_TIME
#include"szData_parser.h"

#include<stdlib.h>

#include<iostream>

using namespace parser;

int main(){
    system("mkdir deal;mkdir order");
    szDataParser parser{};
    parser.main_run("20210709_91401215.szdata");
    return 0;
}