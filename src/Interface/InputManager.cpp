#include "InputManager.h"

#include <fstream>
#include <boost/algorithm/string.hpp>

#include <set>
#include <iostream>
using namespace std;

InputManager::InputManager(string filename){

    fstream f;
    f.open(filename.c_str(),ios::in);
    string line;
    
    string currentBlock="";
    while ( getline (f,line) ){
        // remove comments
        line = _remove_comments(line);
        // split with :
        vector<string> strs;
        boost::split(strs,line,boost::is_any_of(":"));
        // mark the start of a new block
        if (strs.size()>1){
            currentBlock=strs[0];
            Input inp;
            _inputs[currentBlock]=inp;
        } else {
            boost::split(strs,line,  boost::is_any_of( " ,\t" )  );
            _strip_empties(strs);
            if (strs.size()>1){
                _inputs[currentBlock][strs[1]]=strs[2];
            }
        }
    }
    
    
    f.close();
    
}

string InputManager::_remove_comments(string input){
    return input.substr(0, input.find("#") );
}

void InputManager::_strip_empties(vector<string>& vec){
    vector<string>::iterator begin=vec.begin();
    vector<string>::iterator end=vec.end();
    while (begin!=end){
        if (*begin==""){
            vec.erase(begin);
            begin = vec.begin();
            end=vec.end();
        }
        begin++;
    }
    /*
    for (vector<string>::iterator it=vec.begin();it!=vec.end();++it){
        if (*it=="" && vec.size()>=2){
            cout << vec.size() << endl;
            vec.erase(it);
            
        }
    }*/
}
