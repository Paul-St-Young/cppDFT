#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

#include <map>
#include <vector>

typedef std::map<std::string,std::string> Input;

class InputManager{
std::map<std::string,Input> _inputs;
std::string _remove_comments(std::string input);
void _strip_empties(std::vector<std::string>& vec);
public:
    InputManager(std::string filename);
    Input operator[](std::string input){ return _inputs[input]; };
};



#endif
