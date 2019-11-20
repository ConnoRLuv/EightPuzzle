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

    int flag = -1;

    bool operator<(Eight_Puzzle p2);

    bool operator==(Eight_Puzzle p2);


    Eight_Puzzle()= default;
    void ReadFile();
    bool isSolveable();
    int getSpaceIndex();
    int getF();
    int getH();
    int getDepth();
    void Heuristic_Method(int method);
    bool isGoal();
    void move(int i);
    static Eight_Puzzle move(Eight_Puzzle puzzle, int i);
    static Eight_Puzzle move(Eight_Puzzle puzzle,int i, int method);
    void setFather(Eight_Puzzle puzzle);

    int* getS0();
    Eight_Puzzle* getFather();

private:
    int Sg[9]{};
    int S0[9]{};
    int S0_InverseNum = 0;
    int h = 0;
    int depth = 0;
    Eight_Puzzle *n = nullptr;

    int f = 0;
};



void Eight_Puzzle::ReadFile() {
    Eight_Puzzle();
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
    int Sg_without0[8];
    int S0_without0[8];
    int Sg_InverseNum = 0;
    S0_InverseNum = 0;

    int i1 = 0,m = 0;
    for (int i = 0; i < 9; ++i) {
        if(Sg[i] != 0){
            Sg_without0[i1] = Sg[i];
            i1++;
        }

        if(S0[i] != 0){
            S0_without0[m] = S0[i];
            m++;
        }

    }

    for (int i = 0; i < 8; ++i) {
        for (int j = i + 1; j < 8; ++j) {
            if (Sg_without0[i] > Sg_without0[j])
                Sg_InverseNum++;
            if (S0_without0[i] > S0_without0[j])
                S0_InverseNum++;
        }
    }

    return Sg_InverseNum % 2 == S0_InverseNum % 2;
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

int Eight_Puzzle::getDepth() {
    return depth;
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
    Eight_Puzzle new_puzzle= puzzle;
    new_puzzle.h = 0;
    new_puzzle.f = 0;
    new_puzzle.S0_InverseNum = 0;
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



int Eight_Puzzle::getF() {
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

void Eight_Puzzle::Heuristic_Method(int method) {
    switch(method){
        default:
            break;
        case 1:
            h = 0;
            f = 0;
            for(int i = 0;i < 9;i++){
                if(S0[i]!=0 && Sg[i] != S0[i] )
                    h++;
            }
            f = depth + h;
            break;

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
            break;

        case 3:
            h = 0;
            for(int i = 0,zero_S0 = 0; i < 9;i++){
                if(S0[i] == 0){
                    zero_S0 = 1;
                    continue;
                }

                for (int j = 0,zero_Sg = 0; j < 9;j++) {
                    if(Sg[j] == 0) {
                        zero_Sg = 1;
                        continue;
                    }
                    if(S0[i] == Sg[j] && zero_S0 == zero_Sg)
                        h += abs (i - j);
                    if(S0[i] == Sg[j] && zero_S0 != zero_Sg)
                        h += abs (i - j) - 1;
                }
            }
            f = 3 * h + depth;
            break;

        case 4:
            h = 0;
            S0_InverseNum = 0;
            for(int i = 0;i < 9;i++){
                if(S0[i]!=0 && Sg[i] != S0[i] )
                    h++;
            }
            for(int i = 0,zero_S0 = 0; i < 9;i++){
                if(S0[i] == 0){
                    zero_S0 = 1;
                    continue;
                }

                for (int j = 0,zero_Sg = 0; j < 9;j++) {
                    if(Sg[j] == 0) {
                        zero_Sg = 1;
                        continue;
                    }
                    if(S0[i] == Sg[j] && zero_S0 == zero_Sg)
                        S0_InverseNum += abs (i - j);
                    if(S0[i] == Sg[j] && zero_S0 != zero_Sg)
                        S0_InverseNum += abs (i - j) - 1;
                }
            }
            h += 3 *S0_InverseNum;
            f = depth + h;
            break;
    }
}

int Eight_Puzzle::getH() {
    return h;
}


#endif //ARTIFICIALINTELLIGENCEPROJECT_EIGHT_PUZZLE_H
