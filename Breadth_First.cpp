//
// Created by 81406 on 2019/11/9.
//

#ifndef ARTIFICIALINTELLIGENCEPROJECT_WIDTH_FIRST_CPP
#define ARTIFICIALINTELLIGENCEPROJECT_WIDTH_FIRST_CPP

#include <iostream>
#include <ctime>
#include "Eight_Puzzle.h"
#include "Queue.h"
void Write_Breadth_First(Eight_Puzzle p, int count, double clock){
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
    }
    Result <<"使用宽度优先搜索算法拓展节点总数为："<<count<<endl;
    Result <<"使用宽度优先搜索算法总耗时为："<< clock <<endl;
}

int Breadth_First(Eight_Puzzle& puzzle) {
    clock_t start = clock ();
    int count = 0;
    bool end = false;
    Queue<Eight_Puzzle> open;
    Queue<Eight_Puzzle> close;
    Eight_Puzzle goal;
    open.EnQueue (puzzle);
    if (!puzzle.isGoal ()) {
        while (open.DeQueue (puzzle)) {
            close.EnQueue (puzzle);
            int index = puzzle.getSpaceIndex ();


            if (index - 3 >= 0 && puzzle.flag != 3) {
                Eight_Puzzle temp = Eight_Puzzle::move (puzzle, index - 3);
                temp.flag = 0;
                open.EnQueue (temp);
                count++;
                if (temp.isGoal ()) {
                    goal = temp;
                    end = true;
                }
            }

            if (index % 3 != 0 && index - 1 >= 0 && puzzle.flag != 2) {
                Eight_Puzzle temp = Eight_Puzzle::move (puzzle, index - 1);
                temp.flag = 1;
                open.EnQueue (temp);
                count++;
                if (temp.isGoal ()) {
                    goal = temp;
                    end = true;
                }
            }

            if ((index + 1) % 3 != 0 && index + 1 < 9 && puzzle.flag != 1) {
                Eight_Puzzle temp = Eight_Puzzle::move (puzzle, index + 1);
                temp.flag = 2;
                open.EnQueue (temp);
                count++;
                if (temp.isGoal ()) {
                    goal = temp;
                    end = true;
                }
            }

            if (index + 3 < 9 && puzzle.flag != 0) {
                Eight_Puzzle temp = Eight_Puzzle::move (puzzle, index + 3);
                temp.flag = 3;
                open.EnQueue (temp);
                count++;
                if (temp.isGoal ()) {
                    goal = temp;
                    end = true;
                }
            }

            if (end) {
                clock_t end2 = clock();
                Write_Breadth_First (goal, count, (double) end2 - start);
                return EXIT_SUCCESS;
            }
        }
    } else {
        clock_t end2 = clock();
        Write_Breadth_First (puzzle, count, (double) end2 - start);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

#endif //ARTIFICIALINTELLIGENCEPROJECT_WIDTH_FIRST_CPP
