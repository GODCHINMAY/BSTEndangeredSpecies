//
// Created by Chinmay Agrawal on 10/15/24.
//

#include <iostream>
#include <stdlib.h>
using namespace std;

#ifndef SPECIES_HPP
#define SPECIES_HPP

class Species {
    friend class Interface;
    friend class BSTNode;
    friend class BST;
    string name;
    string status;
    string info;

public:
    Species();
    Species(string s, string st, string inf);
    ~Species();

};


#endif //SPECIES_HPP
