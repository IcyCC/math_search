#include "cmd.h"
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>

using namespace std;


void HandleTex(vector<TextBlock> &vec, std::string outpath){
		vector<TextBlock> nature;
		vector<TextBlock> concept;
		vector<TextBlock> exercise;
		vector<TextBlock> text;
		vector<TextBlock> example;
	
		for(auto v: vec){
			if(v.type==TextBlock::BlockType::NATURE){
				nature.push_back(v);
			}

			else if(v.type==TextBlock::BlockType::CONCEPT){
				concept.push_back(v);
			}

			else if(v.type==TextBlock::BlockType::EXERCISES){
				exercise.push_back(v);
			}

			else if(v.type==TextBlock::BlockType::TEXT){
				text.push_back(v);
			}

			else if(v.type==TextBlock::BlockType::EXAMPLE){
				example.push_back(v);
			}

		}

		
		NatureStore nature_;
		nature_.data=nature;
		nature_.Save(outpath);

		ConceptStore concept_;
		concept_.data=concept;
		concept_.Save(outpath);
	
		ExercisesStore exercise_;
		exercise_.data=exercise;
		exercise_.Save(outpath);		

		TextStore text_;
		text_.data=text;
		text_.Save(outpath);		

		ExampleStore example_;
		example_.data=example;
		example_.Save(outpath);

}

/*
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
				
				vector<TextBlock> t;
				t=ParseFromLatex(inpath);
				vec.insert(vec.end(), t.begin(), t.end());

        }
		HandleTex(outpath);

}
*/


void DirList(std::string inpath, std::string outpath){
		vector<string> file=GetAllFilenames(inpath);
		auto vec = vector<TextBlock>();
		for(auto f: file){
				vector<TextBlock> t;
                t=ParseFromLatex(f);
                vec.insert(vec.end(), t.begin(), t.end());
		}
		HandleTex(vec, outpath);
}
 
void RunSpliteLatex(std::string inpath, std::string outpath){
		DirList(inpath, outpath);
}


void RunKeyWords(AbcStore *s, std::string outpath){
		KeyWordToFile(s,outpath);
}


