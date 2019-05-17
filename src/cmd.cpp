#include "cmd.h"
#include "store.h"
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>

using namespace std;


void DirList(std::string inpath, std::string outpath){
        string temp;
        temp=(char *)malloc(sizeof(char)*50);
        int j;
        for(int i=6;i<112;i=i+5){
                j=i+5;
                ostringstream ostr;
                ostr << inpath << "/book" << i << "-" << i+5 << ".tex";
                temp=ostr.str();
                //cout << temp << endl;
                //const char *p=temp.data();
				
				HandleTex(temp, outpath);
        }
}
    std::vector<int> src;
    std::vector<int> dest;
    dest.insert(dest.end(), src.begin(), src.end());

void HandleTex(std::string inpath, std::string outpath){
		AbcStore temp=new AbcStore();
		temp.data=ParseFromLatexCRE(inpath);
		
		//temp.Save(outpath);
}


void RunSpliteLatex(std::string inpath, std::string outpath){
		DirList(inpath, outpath);
}

