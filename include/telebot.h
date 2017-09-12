#ifndef TELEBOT_H
#define TELEBOT_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

//cURL Fix
#pragma comment(lib, "wldap32.lib" )
#pragma comment(lib, "crypt32.lib" )
#pragma comment(lib, "Ws2_32.lib")
#define CURL_STATICLIB
// --//--

#define CSCREEN "\e[1;1H\e[2J"

#include <curl/curl.h>
#include <jansson.h>
#include <pthread.h>

#include <memory.h>
#include <objects.h>
#include <network.h>
#include <json.h>
#include <format.h>
#include <log.h>
#include <json_user.h>
#include <config.h>

void telebot_init();
Bot * telebot(char *token);
User * get_me(char *token);
Update *get_updates(Bot *bot, char *extra);
void handle_data(Bot *bot);
void telebot_polling(Bot *bot);
int to_process_message(Bot *bot, Message *message);
char *comands_bot(const char *text);
int send_message(Bot *bot, long int chat_id, char *text, char *extra);
void to_message(Bot *bot, Update *update);

#endif
