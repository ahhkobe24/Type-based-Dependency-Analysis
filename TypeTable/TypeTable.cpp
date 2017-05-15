////////////////////////////////////////////////////////////////////////////////
// DependAnal.cpp - Define a class to do the dependency analysis and          //
//                save it to Nosqldb                                          //
// Ver 1.0                                                                   //
// Application: CSE687 Pr#2, Spring 2017                                     //
// Platform:    Win 10 Pro, Visual Studio 2015                              //
// Author:      Xia Hua                                                    //
//              xhua02@syr.edu                                            //  
////////////////////////////////////////////////////////////////////////////


#include "TypeTable.h"
#include "../AbstractSyntaxTree/AbstrSynTree.h"


#ifdef TEST_TypeTable
int main()
{
	CodeAnalysis::TypeTable tt;
	CodeAnalysis::ASTNode* pst1 = new CodeAnalysis::ASTNode();
	CodeAnalysis::ASTNode* pst2 = new CodeAnalysis::ASTNode();
	pst1->name_ = "node1";
	pst2->name_ = "node2";
	pst1->children_[0] = pst1;
	tt.DFS(pst1);
	tt.doDisplay();
	return 0;
}
#endif