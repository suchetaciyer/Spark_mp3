/*
 * BT_message.c
 *
 *  Created on: May 5, 2018
 *      Author: Sucheta
 */

#include "printf_lib.h"
#include "BT_message.hpp"
#include <string>
//#include <string.h>
#include <iostream>
#include <stdlib.h>
#include "printf_lib.h"

using namespace std;

bool validate_song_number(string temp)
{
    int song_number = atoi(temp.c_str());
    if (song_number > 0 && song_number < 100) return true;
    else
        return false;
}
int validate_command(string temp)
{
    int command = atoi(temp.c_str());
    int ret =0;
    if (command == 0) {
       ret = 2; //stop
    }
    else if (command == 1) {
        ret = 1; //play
    }

    return ret;
}

int validate_BT_message(char msg[])
{
    int i = 0;
    bool song_validated = false;
    int start_stop =0;
    string temp = "";       //We can store no more than 99 songs in the list
    //Play song command comes is the form
    //  #song_number\n
    if (msg[i] == '#') {
        i++;
        while (msg[i] != '\n') {
            temp += msg[i];
            i++;
        }
        song_validated = validate_song_number(temp);
        u0_dbg_printf("song_validated = %d", song_validated);
        temp = "";
        return 3; // received song number
        i++;
    }
    //start stop
    else if (msg[i] == '*') {

        i++;
        while (msg[i] != '\n') {
            temp += msg[i];
            i++;
        }

        start_stop = validate_command(temp);
        //u0_dbg_printf("command validated = %d",song_validated);
        temp = "";
        return start_stop; //start stop command
        i++;
    }
    if (song_validated) return true;
    else
        return false;
}
