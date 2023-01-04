//
// Created by Bartek on 04/01/2023.
//

#ifndef LFU_FETCHDATA_H
#define LFU_FETCHDATA_H

#include "iostream"
#include <bits/stdc++.h>

using namespace std;

void getPagesFromFile(vector<int> &pages) {
    string line;
    ifstream sourcefile ("../pages_LFU.txt");
    if (sourcefile.is_open())
    {
        cout << "Retrieving data from file: \n";
        while ( getline (sourcefile,line) )
        {
            cout << line << '\n';
            pages.push_back(stoi(line));
        }
        sourcefile.close();
    }
    else cout << "Error: Unable to open data source file!\n";
}

void getRemovedFromFile(vector<pair<int, bool>> &removedPages) {
    string data;
    ifstream sourcefile ("../rm_pages_LFU.txt");
    if (sourcefile.is_open())
    {
        cout << "Retrieving data from file: \n";
        bool even = true;
        pair<int, int> tempPair;
        while ( sourcefile >> data )
        {
            if(even) {
                tempPair.first = stoi(data);
            } else {
                tempPair.second = data == "1";

                cout << "Pair: " << tempPair.first << " " << tempPair.second << '\n';
                removedPages.push_back(tempPair);
            }
            even = even ? false : true;
        }
        sourcefile.close();
    }
    else cout << "Error: Unable to open data source file!\n";
}

#endif //LFU_FETCHDATA_H
