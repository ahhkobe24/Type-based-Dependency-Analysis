#pragma once
#pragma once
///////////////////////////////////////////////////////////////////
// DependAnal - Define a class to do the dependency analysis and//
//                save it to Nosqldb                              //
// Ver 1.0                                                       //
// Application: CSE687 Pr#2, Spring 2017                         //
// Platform:    Dell XPS 2720, Win 10 Pro, Visual Studio 2015   //
// Author:      Xia Hua                                         //
//              xhua02@syr.edu                                  //
/////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package is to define DepAnalsis class, it has to do the dependency analysis and save it to Nosqldb.
*
Class
---------------------------------
* DepAnalsis

improtant functions
---------------------------------
//--------keys or key operation
bool isDepend(CodeAnalysis::TypeTable typetable); ------extract data from typetable and analysis dependency, save the result to Nosqldb 
bool construcGragh();                            -------call function in class Graph , to construct graph
void displayNosql();                              ---------display the Nosqldb 
void showGraph();                                     -------call function in class Graph , to display graph
void findSsc();                                   -------call function in class Graph , to find scc in graph
void dispalySsc();                                   -------call function in class Graph , to display scc in graph
void saveScc();                              -----------save Scc to Nosqldb, element in Nosqldb have the same category are in the same ssc
void savetoXml();                            -------save to xml file
void setFiles(std::vector<std::string> filepara);  -------set files
void setPath(std::string path);                   -----------set path

* Required Files:
* ---------------
*   - TypeTable.h  -NoSqlDb.h
*   - Persist.h    -Display.h
*   - Graph.h
* Maintenance History:
* --------------------
* ver 1.0 : 4 March 2017
* - First release
*
*/
#include"../TypeTable/TypeTable.h"
#include <iostream>
#include <functional>
#include "../Nosqldb/NoSqlDb.h"
#include "../Nosqldb/Persist.h"
#include "../Nosqldb/Display.h"

#include <sstream>



namespace Scanner
{
	class DepAnalsis
	{
	public:
		bool isDepend(CodeAnalysis::TypeTable typetable);
		void displayNosql();
		
		void setFiles(std::vector<std::string> filepara);
		void setPath(std::string path);
		NoSQLDB::NoSqlDb<std::string>* getDb();
	private:
		Toker toker;
		std::string dirpath;
		NoSQLDB::NoSqlDb<std::string> db;
		std::unordered_map<int, std::vector<int>> component;
		std::vector<std::string> files;

		
	};

	NoSQLDB::NoSqlDb<std::string>* DepAnalsis::getDb()
	{
		return &db;
	}
	//----< set path >---------------------
	void DepAnalsis::setPath(std::string path)
	{
		dirpath = path;
	}

	//----< set files >---------------------
	void DepAnalsis::setFiles(std::vector<std::string> filepara)
	{
		files.insert(files.end(), filepara.begin(), filepara.end());
	}

	//----< extract data from typetable and analysis dependency, save the result to Nosqldb >------------------------------------
	bool DepAnalsis::isDepend(CodeAnalysis::TypeTable typetable)
	{
		try
		{
			std::cout << "\n\n"; std::cout << "\n --------------------Displaying dependency relationship--------------------";std::vector<std::string> keysall = typetable.keys();
			for (auto tmp : files)
			{
				std::string data; NoSQLDB::Element<std::string> elemdb;std::string a = tmp.substr(tmp.find_last_of("\\") + 1); elemdb.name = a;
				for (auto b : keysall)
				{
					if (typetable.value(b).filepath == a)
					{data = data + typetable.value(b).name + ", ";}
				}
				elemdb.data = data; db.saveRecord(elemdb.name, elemdb);
			}
			for (auto c : files) {
				std::string tmp = c.substr(c.find_last_of("\\") + 1);bool find = false; std::ifstream in(c);
				if (!in.good())
				{
					std::cout << "\n  can't open " << c << "\n\n";return 1;
				}
				{toker.returnComments();
				toker.attach(&in);
				do
				{
					std::string tok = toker.getTok();
					if (tok == "include")
					{
						std::string nexttok = toker.getTok();std::vector<std::string> vec = db.keys();
						for (size_t i = 0; i < vec.size(); i++)
						{
							if (nexttok.find(db.value(vec[i]).name) < 10)
							{
								std::cout << "\n" << tmp << " depend on " << db.value(vec[i]).name;db.value(tmp).saveChild(db.value(vec[i]).name);
								break;
							}
						}
					}

				} while (in.good());
				}
			}
		}
			catch (std::logic_error& ex)
			{std::cout << "\n  " << ex.what();}
			std::cout << "\n\n";return 0;
	}

	void  DepAnalsis::displayNosql()
	{
		std::cout << "\n\n -------------Displaying Nosqldb-------------  ";
		std::cout << "\n -----The same catagory means that these element in the same strong component---------  ";
		std::cout << "\n -----data means its global element and child means files depend on---------  ";
		NoSQLDB::Display<std::string> display(db);
			std::vector<std::string> ikeys = db.keys();
			for (auto key : ikeys)
			{
				std::cout << "\n  " << key << ":";
				std::cout << db.value(key).show();
			}
	}



}
