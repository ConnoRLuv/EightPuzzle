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
        cout << "������İ����������޽�" << endl;
        system ("PAUSE");
        return 0;
    } else
        cout <<"������İ���������ɽ�"<<endl;

    while (true) {
        Eight_Puzzle puzzle;
        puzzle.ReadFile ();
        int i;
        cout << "********����������������*********" << endl;
        cout << "1.äĿ�����еĿ�����������㷨" << endl;
        cout << "2.����ʽ�����е�ȫ�����������㷨" << endl;
        cout << "3.A*�㷨" << endl;
        cout << "0.�˳�" << endl;
        cout << "������ִ�е��㷨��ţ�";
        cin >> i;
        switch (i) {
            case 1:
                result = Breadth_First (puzzle);
                break;
            case 2:
                cout << "������ʹ�õ��������ԣ�";
                cin >> method;
                result = Best_First (puzzle, method);
                break;
            case 3:
                result = A_Star (puzzle);
                break;
            case 0:
                cout << "��лʹ�ã�" << endl;
                system ("PAUSE");
                return 0;
            default:
                cout << "�����ʽ�������������롣" << endl;
                break;
        }
        if (result == EXIT_SUCCESS) {
            cout << "����ɹ����������Result.txt�ļ��в鿴��" << endl;
            cout << "��лʹ�ã�" << endl;
        } else if (result == EXIT_FAILURE) {
            cout << "����ʧ��";
        }
        result = -1;
    }
}


