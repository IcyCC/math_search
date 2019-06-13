//
// Created by 苏畅 on 2019/5/12.
//

#include<iostream>
#include "interface.h"
#include "text.h"
int main()
{
   auto s1=  StdFormula("a+1 = 2 +  5");
   auto s2=  StdFormula("1+a = 5 +  2");

   assert(s1==s2);

    s1=  StdFormula("a^n");
    s2=  StdFormula("n^a");
   return 0;

}//
// Created by 苏畅 on 2019/5/12.
//

