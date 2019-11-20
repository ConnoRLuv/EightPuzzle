//
// Created by 81406 on 2019/11/10.
//

#include "Queue.h"
#include "Eight_Puzzle.h"

void Write_Best_First(Eight_Puzzle p, int count, double clock){
    int depth = p.getDepth ();
    int* a;
    ofstream Result;
    Result.open ("../data/Result.txt");
    auto goal_list = new Eight_Puzzle[depth+1];
    for (int i = 0; i <= depth; ++i) {
        goal_list[i] = p;
        if(p.getDepth () == 0)
            break;
        p = *p.getFather ();
    }


    for (int i = depth; i >= 0; i--) {
        a = goal_list[i].getS0 ();
        Result << "-----深度：" << goal_list[i].getDepth () << "-----"<<endl;
        for (int j = 0; j < 9; ++j) {
            if(j % 3 != 2 )
                Result << a[j] << " ";
            if(j % 3 == 2)
                Result << a[j] <<endl;
        }
        Result << "估价函数值为：" << goal_list[i].getF () << endl;
    }
    Result << "全局择优搜索算法拓展节点总数为："<<count<<endl;
    Result << "全局择优搜索算法拓展总耗时为："<< clock <<endl;
}

int Best_First(Eight_Puzzle &puzzle,int method){
    clock_t start = clock ();
    int count = 0;
    bool end = false;
    Eight_Puzzle goal;
    Queue<Eight_Puzzle> open;
    Queue<Eight_Puzzle> close;

    puzzle.Heuristic_Method (method);
    open.InList (puzzle);
    if(puzzle.isGoal ()){
        clock_t end2 = clock ();
        Write_Best_First (puzzle, count, (double)end2 - start);
        return EXIT_SUCCESS;
    }
    while (open.DeQueue (puzzle)){
        close.InList (puzzle);
        int index = puzzle.getSpaceIndex ();

        if(index - 3 >= 0 && puzzle.flag != 3){
            Eight_Puzzle temp = Eight_Puzzle::move (puzzle,index - 3,method);
            temp.flag = 0;
            open.InList (temp);
            count++;
            if(temp.isGoal ()){
                goal =temp;
                end = true;
            }
        }

        if(index % 3 != 0 && index - 1 >=0 && puzzle.flag != 2){
            Eight_Puzzle temp = Eight_Puzzle::move (puzzle,index - 1,method);
            temp.flag = 1;
            open.InList (temp);
            count++;
            if(temp.isGoal ()){
                goal =temp;
                end = true;
            }
        }

        if((index + 1) % 3 != 0 && index + 1 < 9 && puzzle.flag != 1){
            Eight_Puzzle temp = Eight_Puzzle::move (puzzle, index + 1,method);
            temp.flag = 2;
            open.InList (temp);
            count++;
            if(temp.isGoal ()){
                goal =temp;
                end = true;
            }
        }

        if(index + 3 < 9 && puzzle.flag != 0){
            Eight_Puzzle temp = Eight_Puzzle::move (puzzle,index + 3 ,method);
            temp.flag = 3;
            open.InList (temp);
            count++;
            if(temp.isGoal ()){
                goal =temp;
                end = true;
            }
        }

        if(end){
            clock_t end2 = clock ();
            Write_Best_First (goal, count, (double)end2 - start);
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}
