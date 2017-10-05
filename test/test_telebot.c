#include <telebot.h>
#include <string.h>

#define TOKEN "312367410:AAE0GKFSHt8CId9sQ8yKOODnRF8j-Kk_avQ"

void test_set_chat_title(Bot *test_bot) {
    char test_chat_id[] = "-220937252";
    char test_new_title[] = "newtitletest";
    
    printf("\n[?] Testing set_chat_title()");
    int r = set_chat_title(test_bot, test_chat_id, test_new_title);

    if (r == 1) {
        Chat *chat = get_chat(test_bot, test_chat_id);

        if (strcmp(chat->title, test_new_title) == 0) {
            printf("\n[!] set_chat_title() OK!");
        } else {
            printf("\n[?] set_chat_title() ERROR!");
        }
    }
}

void test_get_chat_member(Bot *bot) {
    char test_chat_id[] = "-220937252";
    char test_user_id[] = "124296363";
    char test_chat_member_string[] = "{\"user\":{\"id\":124296363,\"is_bot\":false,\"first_name\":\"Gian\",\"username\":\"niiag\",\"language_code\":\"pt-BR\"},\"status\":\"creator\"}";
    ChatMember *test_chat_member = chat_member_parse(load(test_chat_member_string));

    ChatMember *chat_member = get_chat_member(bot, test_chat_id, test_user_id);

    if (strcmp(test_chat_member->status, chat_member->status) == 0 && (test_chat_member->user->id == chat_member->user->id)) {
        printf("\n[!] get_chat_member() OK!");
    }
}
 
int main(void) {
    telebot_init();
    Bot *test_bot = telebot(TOKEN);
    printf("[!] Starting tests...\n");

    test_set_chat_title(test_bot);
    test_get_chat_member(test_bot);
    
    return 0;
}