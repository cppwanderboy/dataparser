// #define CHECK_TIME
#include"szData_parser.h"

#include<iostream>

using namespace parser;

int main(){
    szDataParser parser{};
    parser.main_run("20210709_91401215.szdata");
    gettimeofday(&endtimes, NULL);
    return 0;
}