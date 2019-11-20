#include <iostream>

#include "Breadth_First.cpp"
#include "Best_First.cpp"
#include "A_Star.cpp"

using namespace std;

int main() {
    int result = -1;
    int method = -1;
    Eight_Puzzle puzzle;
    puzzle.ReadFile ();
    if (!puzzle.isSolveable ()) {
        cout << "您输入的八数码问题无解" << endl;
        system ("PAUSE");
        return 0;
    } else
        cout <<"您输入的八数码问题可解"<<endl;

    while (true) {
        Eight_Puzzle puzzle;
        puzzle.ReadFile ();
        int i;
        cout << "********八数码问题求解程序*********" << endl;
        cout << "1.盲目搜索中的宽度优先搜索算法" << endl;
        cout << "2.启发式搜索中的全局择优搜索算法" << endl;
        cout << "3.A*算法" << endl;
        cout << "0.退出" << endl;
        cout << "请输入执行的算法序号：";
        cin >> i;
        switch (i) {
            case 1:
                result = Breadth_First (puzzle);
                break;
            case 2:
                cout << "请输入使用的启发策略：";
                cin >> method;
                result = Best_First (puzzle, method);
                break;
            case 3:
                result = A_Star (puzzle);
                break;
            case 0:
                cout << "感谢使用！" << endl;
                system ("PAUSE");
                return 0;
            default:
                cout << "输入格式错误，请重新输入。" << endl;
                break;
        }
        if (result == EXIT_SUCCESS) {
            cout << "计算成功，结果可在Result.txt文件中查看。" << endl;
            cout << "感谢使用！" << endl;
        } else if (result == EXIT_FAILURE) {
            cout << "计算失败";
        }
        result = -1;
    }
}


