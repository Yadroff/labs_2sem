//
// Created by Temi4 on 04.03.2021.
//

#ifndef LAABS_PASSENGER_H
#define LAABS_PASSENGER_H
typedef struct{
    int hour, minute;
} TIME;
typedef struct {
    char surname[25];
    char initials[2];
    int num;
    int weight;
    char to[50];
    TIME time;
    int transfer;
    int child;
} passenger;
#endif //LAABS_PASSENGER_H
