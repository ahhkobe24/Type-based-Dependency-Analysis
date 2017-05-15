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
#include <iostream>
#include <fstream>
#include "../Nosqldb/NoSqlDb.h"
class Publisher
{
public:
	Publisher(NoSQLDB::NoSqlDb<std::string>* db1)
	{
		db = db1;
	}
	void constrHtml();
	void constrBody(std::string fielname, std::string filepath);
	std::string addExpand(std::string s);
	void constrHead(std::string s);
	void constrDepend(std::vector<std::string> vec, std::string s);
	void constrEnd(std::string s);
	void setPath(std::string path);
	void setFiles(std::vector<std::string> filepara);
	std::string  replaceSpec(std::string s);
	std::string exeCh(std::string s, int i, std::vector<int>& vec, std::string& index);
	bool  isValid(std::string s);
	void constrIndexHtml(std::vector<std::string> files);
private:
	NoSQLDB::NoSqlDb<std::string>* db;
	std::string dirpath;
	std::vector<std::string> files;
};

void  Publisher::setFiles(std::vector<std::string> filepara)
{
	files.insert(files.end(), filepara.begin(), filepara.end());
}

void Publisher::setPath(std::string path)
{
	dirpath = path;
}

void Publisher::constrHtml()
{
	std::cout << "----------Html files generating....---------" << "\n";
	for (auto tmp : files)
	{
		std::string a = tmp.substr(tmp.find_last_of("\\") + 1);
		constrHead(a);
		constrDepend(db->value(a).children, a);
		constrBody(a,tmp);
		constrEnd(a);
	}
	constrIndexHtml(files);
	std::cout << "----------Html file has been generated in ../Html directory, the main page is Index.html---------" << "\n";
}

void Publisher::constrIndexHtml(std::vector<std::string> vec)
{
	constrHead("Index");
	std::ofstream outhead;
	outhead.open("C:/SU/course/CIS687/proj2/proj2//Html/Index.html", std::ios::app);
	if (vec.size() != 0) {
		outhead
			<< "<div class = \"indent\">" << "\n"
			<< "<h4>Index:</h4>" << "\n";
		for (auto c : vec) {
			std::string a = c.substr(c.find_last_of("\\") + 1);
			outhead << "<a href = \"" << a + ".html" << "\">" + a + "</a>" << "\n";
		}
		outhead << "</div>" << "\n"
			<< "<hr/>" << "\n";
	}
	outhead << "<pre>" << "\n";
	outhead.close();
	constrEnd("Index");
}

void Publisher::constrDepend(std::vector<std::string> vec,std::string s)
{
	std::ofstream outhead;
	outhead.open("C:/SU/course/CIS687/proj2/proj2//Html/" + s+".html", std::ios::app);
	if (vec.size() != 0) {
		outhead
			<< "<div class = \"indent\">" << "\n"
			<< "<h4>Dependencies:</h4>" << "\n";
		for (auto c : vec) {
			outhead << "<a href = \"" << c + ".html" << "\">"+c+"</a>" << "\n";
		}
		outhead << "</div>" << "\n"
			<< "<hr/>" << "\n";
	}
	outhead << "<pre>" << "\n";
	outhead << "<script>"
		<< "function ShowIt(id) {"<<"\n"
		<< "if (id.style.display == \"block\")"<<"\n"
		<< "id.style.display = \"none\";"<<"\n"
		<< "else"<<"\n"
		<< "id.style.display = \"block\";"<<"\n"
		<< "};"<<"\n"
		<< "</script>"<<"\n";
	outhead << "<style>"
		<< "div{ display:inline }"
		<< "</style>";
	outhead.close();
}

void Publisher::constrHead(std::string s)
{
	std::ofstream outhead;
	
	outhead.open("C:/SU/course/CIS687/proj2/proj2//Html/"+s + ".html");
	//std::string sourcefile;
	outhead << "<html>" << "\n" << "<head>" << "\n" << "<style>" << "\n"
		<< "body{" << "\n"
		<< "margin: 20px;" << "\n"
		<< "color: black;" << "\n"
		<< "background - color: #eee;" << "\n"
		<< "font - family: Consolas;" << "\n"
		<< "font - weight: 600;" << "\n"
		<< "font - size: 110 % ;}" << "\n";

	outhead << ".indent{ margin - left: 20px; margin - right: 20px;}" << "\n";
	outhead << "h4{margin - bottom: 3px;margin - top: 3px;}" << "\n";
	outhead << "</style>" << "\n";
	outhead << "</head>" << "\n";
	outhead << "<body>" << "\n";
	outhead << "<h3>"<<s<<"</h3>" << "\n" << "<hr/>" << "\n";
	outhead.close();
}

void Publisher::constrEnd(std::string s)
{
	std::ofstream outend;
	outend.open("C:/SU/course/CIS687/proj2/proj2//Html/" + s + ".html", std::ios::app);
	outend << "</pre>" << "\n"
		<< "</body>" << "\n"
		<< "</html>" << "\n";
	outend.close();
}
void Publisher::constrBody(std::string fielname,std::string filepath)
{
	
	std::ifstream in;
	//std::cout << dirpath +"1/"+ s << "\n";
	in.open(filepath);
	std::string sourcefile;
	std::ofstream out;
	out.open("C:/SU/course/CIS687/proj2/proj2//Html/"+ fielname +".html", std::ios::app);
	
	while (!in.eof())
	{
	
		char arrstr[2048];
		in.getline(arrstr,2000);
		sourcefile.append(arrstr);
		sourcefile += '\n';
	}
	std::string nospec = replaceSpec(sourcefile);
	//std::cout << nospec;
	//std::cout << "\n" << fielname << "****************\n";
	std::string finalstr = addExpand(nospec);

	out << finalstr;
	out.close();
	in.close();
	
}

/*{{{{{{{{{{*/
//{{{{
std::string Publisher::addExpand(std::string s)
{
	std::string index = "a"; bool isSpec = false; bool isFirstdouble = false; bool isFirstsingle = false; std::vector<int> vec; //vec.resize(500);
	std::string s1; bool isFirstcomm = false; bool isFirstlinecomm = false;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '/'&&s[i + 1] == '/'&&isFirstdouble == false && isFirstsingle == false&& isFirstcomm == false && isFirstlinecomm==false)
		{isSpec = true; s1 += s[i]; isFirstlinecomm = true; continue;}
		if (s[i] == '\n'&&isFirstdouble == false && isFirstsingle == false && isFirstcomm == false && isFirstlinecomm == true)
		{isSpec = false; s1 += s[i]; isFirstlinecomm = false; continue;}
		if (s[i] == '/'&&s[i +1] == '*'&&isFirstdouble == false && isFirstsingle == false&& isFirstcomm==false)
		{isSpec = true; s1 += s[i];  isFirstcomm = true; continue;}
		if (s[i] == '*'&&s[i + 1] == '/'&&isFirstdouble == false && isFirstsingle == false&&isFirstcomm==true)
		{isSpec = false; s1 += s[i]; isFirstcomm = false; continue;}
		if (s[i] == '\''&&s[i-1] != '\\' && isFirstdouble == false && isFirstcomm == false && isFirstlinecomm == false)
		{
			if (isFirstsingle == false)
			{isFirstsingle = true;isSpec = true;}else
			{isFirstsingle = false;isSpec = false;}
			s1 += s[i];
			continue;
		}
		if (s[i] == '\''&&s[i - 1] == '\\'&&s[i - 2] == '\\'&&isFirstdouble == false && isFirstsingle == true && isFirstcomm == false && isFirstlinecomm == false)
		{
			isFirstsingle = false;isSpec = false;s1 += s[i];continue;
		}
		if (s[i] == '"'&&s[i - 1] != '\\'&& isFirstsingle==false && isFirstcomm == false && isFirstlinecomm == false)
       {
			if (isFirstdouble == false) {isFirstdouble = true;isSpec = true;}else
			{ isFirstdouble = false;isSpec = false;}
			s1 += s[i];
			continue;
		}
		if (s[i] == '"'&&s[i - 1] == '\\'&&s[i - 2] == '\\'&&isFirstdouble == true && isFirstsingle == false && isFirstcomm == false && isFirstlinecomm == false)
		{
			isFirstdouble = false;isSpec = false;s1 += s[i];continue;
		}
		if (isSpec == false)
		{
			s1 += exeCh(s, i, vec, index);
			continue;
		}
		s1 += s[i];
	}
	return s1;
}

std::string  Publisher::exeCh(std::string s, int i, std::vector<int>& vec, std::string& index)
{
	std::string s2;
	switch (s[i]) {
	case '{':
	{
		std::string prefix;
		for (int a = i - 50; a < i; a++)
		{
			prefix += s[a];
		}
		if ( isValid(prefix))
		{
			if (vec.size() == 0) {
				s2 += "<div class = \"wrapper\">";
				s2 += "<span  style=\"width:30px; height:20px; color:red;\"  onclick=\"ShowIt(" + index + ")\">+</span>";
				s2 += "</div><section id = \"" + index + "\">";
				s2 += s[i];index += "a";vec.push_back(1);
			}
			else if(vec.back() == 0) {
					vec.push_back(0);s2 += s[i];
				}
			else if (vec.back() == 1) {
				s2 += "<div class = \"wrapper\">";
				s2 += "<span  style=\"width:30px; height:20px; color:red;\"  onclick=\"ShowIt(" + index + ")\">+</span>";
				s2 += "</div><section id = \"" + index + "\">";
				s2 += s[i];index += "a";vec.push_back(1);
			}
		}
		else {
			vec.push_back(0);s2 += s[i];
		}
		break;
	}
	case '}':
	{
		s2 += s[i];
		if (vec.back() == 1) s2 += "</section>";
		if(vec.size()>0)vec.pop_back();
		break;
	}
	default:
		s2 += s[i];
	}
	return s2;
}

std::string  Publisher::replaceSpec(std::string s)
{
	std::string s3;
	for (int i = 0; i < s.length(); i++)
	{
		switch (s[i]) {
		case '<':
			s3 += "&lt;";
			break;
		case '>':
			s3 += "&gt;";
			break;
		default:
			s3 += s[i];
		}
	}
	return s3;
}

bool  Publisher::isValid(std::string s)
{
	//if (s.find("for") < 25)
	//{
	//	int i = s.find("for");
	//	if (s[i-1] == ' ' || s[i-1] == '\n' || s[i-1] == '\t')
	//	{
	//		return false;
	//	}
	//}
	//else if(s.find("while") < 25)
	//{
	//	int i = s.find("while");
	//	if (s[i-1] == ' ' || s[i-1] == '\n' || s[i-1] == '\t')
	//		return false;
	//}
	//else if (s.find("try") < 25)
	//{
	//	int i = s.find("try");
	//	if (s[i-1] == ' ' || s[i-1] == '\n' || s[i-1] == '\t')
	//		return false;
	//}
	//else if (s.find("catch") < 25)
	//{
	//	int i = s.find("catch");
	//	if (s[i - 1] == ' ' || s[i - 1] == '\n' || s[i - 1] == '\t')
	//		return false;
	//}
	//else if (s.find("do") < 25 )
	//{
	//	int i = s.find("do");
	//	if (s[i - 1] == ' ' || s[i - 1] == '\n' || s[i - 1] == '\t')
	//		return false;
	//}
	//else if (s.find("if") < 25)
	//{
	//	int i = s.find("if");
	//	if (s[i - 1] == ' ' || s[i - 1] == '\n' || s[i - 1] == '\t')
	//		return false;
	//}
	//else if (s.find("switch") < 25 )
	//{
	//	int i = s.find("switch");
	//	if (s[i - 1] == ' ' || s[i - 1] == '\n' || s[i - 1] == '\t')
	//		return false;
	//}
	//else if (s.find("case") < 25)
	//{
	//	int i = s.find("case");
	//	if (s[i - 1] == ' ' || s[i - 1] == '\n' || s[i - 1] == '\t')
	//		return false;
	//}
	if(s.find("for") > 200 && s.find("catch") > 200 && s.find("enum") > 200 && s.find("if") > 200 && s.find("while") > 200 && s.find("=") > 200 && s.find("try")>200 && s.find("else")>200 && s.find("do")>200)
	{
			return true;
	}
	return false;
}