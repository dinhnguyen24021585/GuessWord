#ifndef _LOGIC__H
#define _LOGIC__H

#include<vector>
#include<iostream>
#include<fstream>
#include"graphics.h"

using namespace std;

#define maxlvl 6
struct GuessWord{
    int cur_lvl = 1;
    string player_ans;
    vector<string> lvl_ans;
    vector<string> lvl_ans_vn;
    vector<int> space_cnt;
    vector<string> img_path;
    vector<string> question;
    void init_logic(){
        int line = 0;
        ifstream file;
        file.open("assets/question/lvl_ans.txt");
        while(!file.eof()){
            if(line % 3 == 0){
                string s;
                getline(file,s);
                lvl_ans.push_back(s);
            }
            else if (line % 3 == 1){
                string s;
                getline(file,s);
                lvl_ans_vn.push_back(s);
            }
            else if (line % 3 == 2){
                string s;
                getline(file,s);
                int a = stoi(s);
                space_cnt.push_back(a);
            } 
            line++;
        }
        file.close();
        file.open("assets/question/img_path.txt");
        while(!file.eof()){
                string s;
                getline(file,s);
                img_path.push_back(s);
        }
        file.close();
    }
    bool check(string _ans){
        return (_ans == lvl_ans[cur_lvl-1]);
    }
    
};

#endif