////////////////////////////////////////////////////////////////////////////////
// DependAnal.cpp - Define a class to do the dependency analysis and          //
//                save it to Nosqldb                                          //
// Ver 1.0                                                                   //
// Application: CSE687 Pr#2, Spring 2017                                     //
// Platform:    Win 10 Pro, Visual Studio 2015                              //
// Author:      Xia Hua                                                    //
//              xhua02@syr.edu                                            //  
////////////////////////////////////////////////////////////////////////////


#include "DependAnal.h"
#include "../TypeTable/TypeTable.h"


#ifdef TEST_DepemdA
int main()
{
	Scanner::DepAnalsis dpa;
	CodeAnalysis::TypeElement te1;
	te1.filepath = "text1.h";
	te1.name = "aaa";
	te1.type = "decleration";
	CodeAnalysis::TypeElement te2;
	te2.filepath = "text2.h";
	te2.name = "bbb";
	te2.type = "decleration";
	CodeAnalysis::TypeTable tt;
	tt.insert(te1.name , te1);
	tt.insert(te2.name, te2);
	dpa.isDepend(tt);
	return 0;
}
#endif