//
// Created by 81406 on 2019/11/9.
//

#ifndef ARTIFICIALINTELLIGENCEPROJECT_A_STAR_CPP
#define ARTIFICIALINTELLIGENCEPROJECT_A_STAR_CPP

#include <iostream>
#include "Eight_Puzzle.h"
#include "Queue.h"

void Write_A_Star(Eight_Puzzle p, int count, double clock) {
    int depth = p.getDepth ();
    int *a;
    ofstream Result;
    Result.open ("../data/Result.txt");
    auto goal_list = new Eight_Puzzle[depth + 1];
    for (int i = 0; i <= depth; ++i) {
        goal_list[i] = p;
        if (p.getDepth () == 0)
            break;
        p = *p.getFather ();
    }


    for (int i = depth; i >= 0; i--) {
        a = goal_list[i].getS0 ();
        Result << "-----深度：" << goal_list[i].getDepth () << "-----" << endl;
        for (int j = 0; j < 9; ++j) {
            if (j % 3 != 2)
                Result << a[j] << " ";
            if (j % 3 == 2)
                Result << a[j] << endl;
        }
        Result << "估计函数值为：" << goal_list[i].getF () << endl;
    }
    Result << "A*算法拓展节点总数为：" << count << endl;
    Result << "A*算法拓展总耗时为：" << clock << endl;
}

int A_Star(Eight_Puzzle puzzle) {
    clock_t start = clock ();
    bool end = false;
    int count = 0;
    Eight_Puzzle goal;
    Queue<Eight_Puzzle> open;
    Queue<Eight_Puzzle> close;

    puzzle.Heuristic_Method (2);
    if (puzzle.isGoal ()) {
        clock_t end2 = clock ();
        Write_A_Star (goal, count, end2 - start);
        return EXIT_SUCCESS;
    }
    open.InList (puzzle);
    while (open.DeQueue (puzzle)) {
        if (puzzle.isGoal ()) {
            clock_t end2 = clock ();
            Write_A_Star (goal, count, end2 - start);
            return EXIT_SUCCESS;
        }
        int index = puzzle.getSpaceIndex ();

        if (index - 3 >= 0 && puzzle.flag != 3) {
            Eight_Puzzle temp = Eight_Puzzle::move (puzzle, index - 3, 2);
            temp.flag = 0;
            bool ifIn = false;
            if (temp.getDepth () < open.isInQueue (temp).getDepth ()) {
                open.Replace (temp);
                ifIn = true;
            }
            if (temp.getDepth () < close.isInQueue (temp).getDepth ()) {
                close.OutList (temp);
                open.InList (temp);
                ifIn = true;
            }
            if(!ifIn) {
                open.InList (temp);
            }
            count++;
            if (temp.isGoal ()) {
                goal = temp;
                end = true;
            }

        }

        if (index % 3 != 0 && index - 1 >= 0 && puzzle.flag != 2) {
            Eight_Puzzle temp = Eight_Puzzle::move (puzzle, index - 1, 2);
            temp.flag = 1;
            bool ifIn = false;
            if (temp.getDepth () < open.isInQueue (temp).getDepth ()) {
                open.Replace (temp);
                ifIn = true;
            }
            if (temp.getDepth () < close.isInQueue (temp).getDepth ()) {
                close.OutList (temp);
                open.InList (temp);
                ifIn = true;
            }
            if (!ifIn) {
                open.InList (temp);
            }
            count++;
            if (temp.isGoal ()) {
                goal = temp;
                end = true;
            }
        }

        if ((index + 1) % 3 != 0 && index + 1 < 9 && puzzle.flag != 1) {
            Eight_Puzzle temp = Eight_Puzzle::move (puzzle, index + 1, 2);
            bool ifIn = false;
            temp.flag = 2;
            if (temp.getDepth () < open.isInQueue (temp).getDepth ()) {
                open.Replace (temp);
                ifIn = true;
            }
            if (temp.getDepth () < close.isInQueue (temp).getDepth ()) {
                close.OutList (temp);
                open.InList (temp);
                ifIn = true;
            }
            if (!ifIn) {
                open.InList (temp);
                if (temp.isGoal ()) {
                    goal = temp;
                    end = true;
                }
            }
            count++;

        }

        if (index + 3 < 9 && puzzle.flag != 0) {
            Eight_Puzzle temp = Eight_Puzzle::move (puzzle, index + 3, 2);
            bool ifIn = false;
            temp.flag = 3;
            if (temp.getDepth () < open.isInQueue (temp).getDepth ()) {
                open.Replace (temp);
                ifIn = true;
            }
            if (temp.getDepth () < close.isInQueue (temp).getDepth ()) {
                close.OutList (temp);
                open.InList (temp);
                ifIn = true;
            }
            if (!ifIn) {
                open.InList (temp);
            }
            count++;
            if (temp.isGoal ()) {
                goal = temp;
                end = true;
            }
        }
        if (end) {
            clock_t end2 = clock ();
            Write_A_Star (goal, count, end2 - start);
            return EXIT_SUCCESS;
        }
        close.InList (puzzle);
    }
    return EXIT_FAILURE;
}

#endif //ARTIFICIALINTELLIGENCEPROJECT_A_STAR_CPP
