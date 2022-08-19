#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "exec_1.hpp"
#include "exec_2.hpp"
//#include "exec_3.hpp"

using namespace std;

int main()
{
    const string command1= "ls -l";
    const vector<string> command2 = {"ls","-al","--color"};
    const string command3 = "ls -al";

    string out="";
    ostringstream oss;

    cout << "Testing exec_1 " << " with command: "<< command1 << endl;
    cout << "executing..." << endl;
    //included in exec_1.hpp
    out = exec_1(command1.c_str());
    cout << "Output:" << endl;
    cout << out << endl;


    for(string s:command2)
        oss << s <<" ";

    cout << "Testing exec_2 " << "with command: " << oss.str() << endl;
    //included in exec_2.hpp
    out = exec_2(command2);
    cout << "Output:" << endl;
    cout << out << endl;
/*
    cout << "Testing exec_3 " << "with command: " << command3 << endl;
    //included in exec_3.hpp
    out = exec_3(command3);
    cout << "Output:" << endl;
    cout << out << endl;
*/

    cout << " Test ended: (press key)" << endl;

    getchar();

    return 0;
}
