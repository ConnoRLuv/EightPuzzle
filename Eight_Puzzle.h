//
// Created by 81406 on 2019/10/27.
//

#ifndef ARTIFICIALINTELLIGENCEPROJECT_EIGHT_PUZZLE_H
#define ARTIFICIALINTELLIGENCEPROJECT_EIGHT_PUZZLE_H


#include <fstream>
int ERROR = -1;

using namespace std;
class Eight_Puzzle;


class Eight_Puzzle{
public:
    int depth = 0;
    int flag = -1;

    Eight_Puzzle()= default;
    void ReadFile();
    bool isSolveable();
//    static Eight_Puzzle move(Eight_Puzzle old_puzzle, int i);
    int getSpaceIndex();
    int getf();

    int Heuristic_Method(int method);
    int Heuristic_Method1();
    int Heuristic_Method2();
    void Heuristic_Method3();
    void Heuristic_Method4();
    bool isGoal();
    void move(int i);
    static Eight_Puzzle move(Eight_Puzzle puzzle, int i);
    static Eight_Puzzle move(Eight_Puzzle puzzle,int i, int method);
    void setFather(Eight_Puzzle puzzle);
    bool operator<(Eight_Puzzle p2);
    bool operator==(Eight_Puzzle p2);
    int* getS0();
    Eight_Puzzle* getFather();

private:
    int h = 0;
    int Sg[9]{};
    int S0[9]{};
    Eight_Puzzle *n = nullptr;

    int f = 0;
};



void Eight_Puzzle::ReadFile() {
    ifstream Sg_File, S0_File;                //打开存储了初始状态与目标状态的TXT文件
    Sg_File.open ("../data/Sg.txt");
    S0_File.open ("../data/S0.txt");

    int i = 0;
    while(!Sg_File.eof ()){                   //将TXT文件中保存的初始状态与目标状态存入对应的数组中
        Sg_File >> Sg[i++];

    }

    i = 0;
    while(!S0_File.eof ()){
        S0_File >> S0[i++];
    }

    Sg_File.close ();                         //关闭文件流
    S0_File.close ();

}

bool Eight_Puzzle::isSolveable() {
    int *Sg_without0 = new int[8];
    int *S0_without0 = new int[8];
    int Sg_InverseNum = 0;
    int S0_InverseNum = 0;

    for (int i = 0; i < 9; ++i) {
        if(Sg[i] != 0){
            *Sg_without0 = Sg[i];
            Sg_without0++;
        }

        if(S0[i] != 0){
            *S0_without0 = Sg[i];
            S0_without0++;
        }

    }

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (Sg_without0[i] > Sg_without0[j])
                Sg_InverseNum++;
            if (S0_without0[i] > S0_without0[j])
                S0_InverseNum++;
        }
    }

    return Sg_InverseNum % 2 == S0_InverseNum % 2;
}


void Eight_Puzzle::Heuristic_Method4() {
    int count = 0;
    for(int i = 0; i < 9 && S0[i] != 0; i++){
        for(int j = 0; S0[i]!=0 && j < 9; j++){
            if(S0[i] == Sg[j])
                count++;
        }
    }
}

bool Eight_Puzzle::isGoal() {
    int i;
    for (i = 0; i < 9; ++i) {
        if(S0[i] != Sg[i])
            break;
    }
    return i == 9;
}

int Eight_Puzzle::getSpaceIndex() {
    for (int i = 0; i < 9; ++i)
        if(S0[i] == 0)
            return i;
    return ERROR;
}

void Eight_Puzzle::move(int i) {
    int temp = S0[i];
    int index = getSpaceIndex ();
    S0[i] = S0[index];
    S0[index] = temp;
}



void Eight_Puzzle::setFather(Eight_Puzzle puzzle) {
    n = new Eight_Puzzle;
    *n = puzzle;
    depth = puzzle.depth+1;
}

Eight_Puzzle Eight_Puzzle::move(Eight_Puzzle puzzle,int i) {
    Eight_Puzzle new_puzzle = puzzle;
    new_puzzle.move (i);
    new_puzzle.setFather (puzzle);
    return new_puzzle;
}


Eight_Puzzle Eight_Puzzle::move(Eight_Puzzle puzzle,int i,int method) {
    Eight_Puzzle new_puzzle = puzzle;
    new_puzzle.move (i);
    new_puzzle.setFather (puzzle);
    new_puzzle.Heuristic_Method (method);
    return new_puzzle;
}


bool Eight_Puzzle::operator<(Eight_Puzzle p2) {
    if(p2.flag == -1)
        return false;
    return  f < p2.f;
}

int Eight_Puzzle::getf() {
    return f;
}



bool Eight_Puzzle::operator==(Eight_Puzzle p2) {
    int i;
    for (i = 0; i < 9; ++i) {
        if(S0[i] != p2.S0[i])
            break;
    }
    return i == 9;
}

int* Eight_Puzzle::getS0() {
    return S0;
}

Eight_Puzzle* Eight_Puzzle::getFather() {
    return n;
}

int Eight_Puzzle::Heuristic_Method(int method) {
    switch(method){
        case 1:
            h = 0;
            for(int i = 0;i < 9;i++){
                if(S0[i]!=0 && Sg[i] != S0[i] )
                    h++;
            }
            f = depth + h;
            return f;

        case 2:
            h = 0;
            int x0, y0, xg, yg;
            for(int i = 0; i < 9 ; i++){
                if(S0[i] == 0 || S0[i] == Sg[i])
                    continue;
                for(int j = 0; j < 9 ; j++){
                    if(S0[i] == Sg[j]){
                        x0 = i%3;
                        y0 = i/3;
                        xg = j%3;
                        yg = j/3;
                        h += abs(xg - x0) + abs (yg - y0);
                        break;
                    }
                }
            }
            f = depth + h;
            return f;

        case 3:
            break;
        case 4:
            break;
        default:
            break;
    }
    return 0;
}


#endif //ARTIFICIALINTELLIGENCEPROJECT_EIGHT_PUZZLE_H
