#include <telebot.h>

#pragma comment(lib, "wldap32.lib" )
#pragma comment(lib, "crypt32.lib" )
#pragma comment(lib, "Ws2_32.lib")
#define CURL_STATICLIB 
#include <curl/curl.h>

#define TOKEN "312367410:AAE0GKFSHt8CId9sQ8yKOODnRF8j-Kk_avQ"

int main(){
	telebot_init();

	Bot *bot = telebot(TOKEN);

	Update *up = get_updates(bot,NULL);
	Update *tmp = NULL;
	int i = 0;
	for (; i < update_len(up); i++) {
		tmp = update_get(up, i);

		if (tmp && tmp->message) {
			
			printf("Mensagem %d: %s\n", (i + 1), tmp->message->text);
		}
	}

	return 0;
}
