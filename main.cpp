#include <iostream>
#include <ctime>
#include "Eight_Puzzle.h"
#include "Width_First.cpp"
#include "Best_First.cpp"
#include "A_Star.cpp"
using namespace std;

void showMenu(){
    int i;


}

int main() {

    int result = -1;
    int method = -1;
    while(true){
        int i;
        Eight_Puzzle puzzle;
        puzzle.ReadFile ();
        if (!puzzle.isSolveable ()) {
            cout << "您输入的八数码问题无解" << endl;
        }
        cout<<"********八数码问题求解程序*********"<<endl;
        cout<<"1.盲目搜索中的宽度优先搜索算法"<<endl;
        cout<<"2.启发式搜索中的全局择优搜索算法"<<endl;
        cout<<"3.A*算法"<<endl;
        cout<<"0.退出"<<endl;
        cout<<"请输入执行的算法序号：";
        cin >> i;
        if(i == 1){
            result = Width_First (puzzle);
        } else if(i == 2){
            cout << "请输入使用的启发策略：";
            cin >> method;
            result = Best_First (puzzle,method);
        }else if(i == 3){
            result = A_Star (puzzle);
        }else if( i == 0){
            cout << "感谢使用！"<<endl;
            break;
        }else{
            cout<<"输入格式错误，请重新输入。"<<endl;
        }
        if(result == EXIT_SUCCESS){
            cout << "计算成功，结果可在Result.txt文件中查看。"<<endl;
            cout << "感谢使用！"<<endl;
        }
    }
}

