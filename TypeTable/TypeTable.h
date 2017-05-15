#pragma once
#pragma once
///////////////////////////////////////////////////////////////////
// TypeTable - Define a class to store global types declerated in files  //
//                                                                       //
// Ver 1.0                                                               //
// Application: CSE687 Pr#2, Spring 2017                                //
// Platform:    Dell XPS 2720, Win 10 Pro, Visual Studio 2015           //
// Author:      Xia Hua                                                 //
//              xhua02@syr.edu                                         //
/////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package is to define Define a class to store global types declerated in files.
*
Class
---------------------------------
* TypeTable

improtant functions
---------------------------------
using SPtr = std::shared_ptr<ASTNode*>;       
std::vector<std::string> keys();                      -----------return keys in tyetable
TypeTable();                                          -----------constructor
void doTypeAnal();                                    -----------start denpend analysis
TypeElement value(std::string key);                   ------------return the value of the key
std::string getPath();                                --------------get path
bool insert(std::string key, TypeElement elem);      -------------insert element into tyeptable
void doDisplay();                                     -----------display tyeptable
void DFS(ASTNode* pNode);                           -----------Scan ASTtree ,extract data and store in tyetable

* Required Files:
* ---------------
*   - ActionsAndRules.h
* Maintenance History:
* --------------------
* ver 1.0 : 4 March 2017
* - First release
*
*/

#include "../Parser/ActionsAndRules.h"
#include <iostream>
#include <functional>

#pragma warning (disable : 4101)  // disable warning re unused variable x, below
namespace CodeAnalysis
{

	struct TypeElement
	{
		std::string name;
		std::string type;
		std::string filepath;
	};

  class TypeTable
  {
  public:
    using SPtr = std::shared_ptr<ASTNode*>;
	std::vector<std::string> keys();
	TypeTable();
    void doTypeAnal();
	TypeElement value(std::string key);
	std::string getPath();
	bool insert(std::string key, TypeElement elem);
	void doDisplay();
	void DFS(ASTNode* pNode);
  private:

    AbstrSynTree& ASTref_;
    ScopeStack<ASTNode*> scopeStack_;
    Scanner::Toker& toker_;
	using Item = std::pair<std::string, TypeElement>;
	std::unordered_map<std::string, TypeElement> store;
	std::string path;
  };

  //----< Using Repository to initialize TypeTable >---------------------
  inline TypeTable::TypeTable() :
    ASTref_(Repository::getInstance()->AST()),
    scopeStack_(Repository::getInstance()->scopeStack()),
    toker_(*(Repository::getInstance()->Toker()))
  {
    std::function<void()> test = [] { int x; };  // This is here to test detection of lambdas.
  }                                              // It doesn't do anything useful for dep anal.

  std::vector<std::string> TypeTable::keys()
  {
	  std::vector<std::string> keys;
	  for (Item item : store)
	  {
		  keys.push_back(item.first);
	  }
	  return keys;
  }


  //----< return the value of key >---------------------
  TypeElement TypeTable::value(std::string key)
  {
	  if (store.find(key) != store.end())
		  return store[key];
	  return TypeElement();
  }
  //----< display the tyeptable >---------------------
  void TypeTable::doDisplay()
  {
	  std::vector<std::string> keysall = keys();
	  for (size_t i = 0; i < keysall.size(); i++)
	  {
		  TypeElement elem = value(keysall[i]);
		  std::cout << "\n" << elem.name << " , " << elem.type << " , " << elem.filepath;
	  }
  }

  //----< return path >---------------------
  std::string TypeTable::getPath()
  {
	  return path;
  }

  //----< insert element into typetable >---------------------
  bool TypeTable::insert(std::string key, TypeElement elem)
  {
	  if (store.find(key) != store.end())
	  {
		  store[key].filepath += "+" + elem.filepath;
	  }
	  store[key] = elem;
	  //std::cout << "Element " << elem.name << " has been inserted!!" << "\n";
	  return true;
  }

  //----< Scan ASTtree ,extract data and store in tyetable >---------------------
  inline void TypeTable::DFS(ASTNode* pNode)
  {
	  int i = 1;
	TypeElement elem0;
	elem0.name = pNode->name_;
	elem0.type = pNode->type_;

	insert(elem0.name, elem0);
	  for (auto c : pNode->decl_)
	  {
		  TypeElement elemdec;
		  elemdec.name = c.name;
		  elemdec.type = "decleration";
		  elemdec.filepath = c.package_;
		  insert(elemdec.name, elemdec);
		  i++;
	  }
	  for (auto b : pNode->children_)
	  {
		  TypeElement elemchild;
		  elemchild.name =b->name_;
		  elemchild.type = b->type_;
		  elemchild.filepath = b->package_;
		/*  std::cout << b->name_ << "&&&&&&&&&&&&&&&&\n";
		  for (size_t i = 0; i < b->statements_.size(); i++)
		  {
			  std::cout << b->statements_[i]<<"888888888888888888888\n";
		  }*/
		  insert(elemchild.name, elemchild);
		  i++;
	 }
  }

  //----< start type analysis >---------------------
  inline void TypeTable::doTypeAnal()
  {
    //std::cout << "\n  starting type analysis:\n";
    //std::cout << "\n  scanning AST and displaying TypeTable:";
    //std::cout << "\n -----------------------------------------------";
    ASTNode* pRoot = ASTref_.root();
    DFS(pRoot);
	//doDisplay();
  }
}