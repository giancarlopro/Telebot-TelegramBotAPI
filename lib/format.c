#include <telebot.h>

#define MAX_URL_SZ 2000

char *escape_string(char *str) {
	CURL *curl = curl_easy_init();
	if (curl) {
		char *out = curl_easy_escape(curl, str, 0);
		return out;
	}
	return NULL;
}

char *format(char *formats, ...) {

	va_list params;
	va_start(params, formats);
	
	char *buffer = (char *)malloc(MAX_URL_SZ);
	
	vsprintf(buffer, formats, params);

	va_end(params);

	return buffer;
}