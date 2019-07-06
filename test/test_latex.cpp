//
// Created by 苏畅 on 2019/5/12.
//

#include<iostream>
#include "interface.h"
#include "text.h"
int main()
{
//   auto s1=  StdFormula("900+5.4=905.4");
//    auto s2=  StdFormula("5.4+900=905.4");
    auto s7=  StdFormula("900+5.4=905.4");
    auto s8=  StdFormula("5.4+900=905.4");
    auto s3 = GetAllStdFormulaWithSub("5.4+900=905.4");
    auto s4 = StdFormula("5.4+900");
    auto s10 = GetAllStdFormulaWithSub("1 \\div 9");
    auto s11 = GetAllStdFormulaWithSub("9 \\div 1");
    auto res1 = QueryComm("$5.4+900$", 4);
    auto res2 = QueryComm("$900+5.4=905.4$", 4);
    auto res3 = QueryComm("$5.4+900=905.4$", 4);
    return 0;

}//
// Created by 苏畅 on 2019/5/12.
//

