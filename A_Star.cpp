//
// Created by 81406 on 2019/11/9.
//

#ifndef ARTIFICIALINTELLIGENCEPROJECT_A_STAR_CPP
#define ARTIFICIALINTELLIGENCEPROJECT_A_STAR_CPP

#include <iostream>
#include "Eight_Puzzle.h"
#include "Queue.h"

int A_Star(Eight_Puzzle puzzle){
    clock_t start = clock ();
    bool end = false;
    int count = 0;
    Eight_Puzzle goal;
    Queue<Eight_Puzzle> open;
    Queue<Eight_Puzzle> close;

    puzzle.Heuristic_Method (2);
    if(puzzle.isGoal ()){
        Width_First (puzzle);
        return EXIT_SUCCESS;
    }
    open.InList (puzzle);
    while(open.DeQueue (puzzle)){
        close.InList (puzzle);
        if(puzzle.isGoal ()){
            cout << count;
            return EXIT_SUCCESS;
        }
        int index = puzzle.getSpaceIndex ();

        if(index - 3 >= 0 && puzzle.flag != 3){
            Eight_Puzzle temp = Eight_Puzzle::move (puzzle,index - 3,2);
            temp.flag = 0;
            bool ifIn = false;
            if(temp < open.isInQueue (temp)){
                open.InList_A_Star (temp);
                ifIn = true;
            }
            if(temp < close.isInQueue (temp)){
                close.OutList (temp);
                open.InList_A_Star (temp);
                ifIn = true;
            }
            if(!ifIn){
                open.InList (temp);
            }
            count++;
                if(temp.isGoal ()){
                    goal = temp;
                    end = true;
            }

        }

        if(index % 3 != 0 && index - 1 >=0 && puzzle.flag != 2){
            Eight_Puzzle temp = Eight_Puzzle::move (puzzle,index - 1,2);
            temp.flag = 1;
            bool ifIn = false;
            if(temp < open.isInQueue (temp)){
                open.InList_A_Star (temp);
                ifIn = true;
            }
            if(temp < close.isInQueue (temp)){
                close.OutList (temp);
                ifIn = true;
            }
            if(!ifIn){
                open.InList (temp);
            }
            count++;
            if(temp.isGoal ()){
                goal = temp;
                end = true;
            }
        }

        if((index + 1) % 3 != 0 && index + 1 < 9 && puzzle.flag != 1){
            Eight_Puzzle temp = Eight_Puzzle::move (puzzle, index + 1,2);
            bool ifIn = false;
            temp.flag = 2;
            if(temp < open.isInQueue (temp)){
                open.InList_A_Star (temp);
                ifIn = true;
            }
            if(temp < close.isInQueue (temp)){
                close.OutList (temp);
                ifIn = true;
            }
            if(!ifIn){
                open.InList (temp);
                if(temp.isGoal ()){
                    goal = temp;
                    end = true;
                }
            }
            count++;

        }

        if(index + 3 < 9 && puzzle.flag != 0){
            Eight_Puzzle temp = Eight_Puzzle::move (puzzle,index + 3 ,2);
            bool ifIn = false;
            temp.flag = 3;
            if(temp < open.isInQueue (temp)){
                open.InList_A_Star (temp);
                ifIn = true;
            }
            if(temp < close.isInQueue (temp)){
                close.OutList (temp);
                ifIn = true;
            }
            if(!ifIn){
                open.InList (temp);
            }
            count++;
            if(temp.isGoal ()){
                goal = temp;
                end = true;
            }
        }
        if(end){
            clock_t end2 = clock ();
            Write1 (goal,count,end2-start);
            return EXIT_SUCCESS;
        }

    }
    return 0;
}
#endif //ARTIFICIALINTELLIGENCEPROJECT_A_STAR_CPP
