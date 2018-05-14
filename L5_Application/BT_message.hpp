/*
 * BT_message.hpp
 *
 *  Created on: May 5, 2018
 *      Author: Sucheta
 */

#ifndef BT_MESSAGE_HPP_
#define BT_MESSAGE_HPP_

#include<iostream>
#include <stdlib.h>
#include <string>


using namespace std;

bool validate_song_number(string temp);
int validate_command(string temp);
int validate_BT_message(char msg[]);

void BTSendSongList(char msg[]);

#endif /* BT_MESSAGE_HPP_ */
