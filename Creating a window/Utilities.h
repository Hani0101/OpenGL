#pragma once
#include<string>
#include<fstream>
using namespace std;

//a utitility function used to help us extract the name of
// our project (ex: C:BOA/OpenglDemo)
// the function will go and extract "OpenglDemo" and give it to us
//this function can be used to give our window a name instead of writting it manually
static const char* extract_version(const char* full)
{
	string p1 = full;
	static string p2;
	p2.clear();
	p2 = p1.substr(p1.find_last_of("/\\" )+ 1, (p1.length() - p1.find_last_of("/\\")) - (p1.length() - p1.find_last_of(".")) + 1);
	return p2.c_str();
}

#ifdef _DEBUG
static void write_log(const char* msg)
{
	ofstream logs;
	logs.open("our_log.text", ofstream::app | ofstream::out);
	logs << msg;
	logs.close();
}
#else
static void write_log(const char* msg)
{
}
#endif