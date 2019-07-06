//
// Created by 苏畅 on 2019/5/12.
//

#include<iostream>
#include "interface.h"
#include "text.h"
int main()
{
   auto s1=  StdFormula("9010+5.4=905.4");
    auto s2=  StdFormula("5.4+9010=905.4");
    auto s3 = GetAllStdFormulaWithSub("5.4+9010=905.4");
    auto s4 = StdFormula("5.4+9010");
    return 0;

}//
// Created by 苏畅 on 2019/5/12.
//

