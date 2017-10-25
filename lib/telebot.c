#include <telebot.h>

void telebot_init () {

//#ifndef CONFIG_DEFAULT /* read or not read config file */
//    read_config();
//#endif
    network_init();
/*    log_init();*/
}

/* Authentic bot token */
Bot * telebot(const char *token) {

    User *bot_user = get_me(token);
    
    if (bot_user) {
        Bot *obot = bot(token, bot_user);
        return obot;
    }

    return NULL;
}
/**
 * Returns a User object of the owner bot.
 */ 
User *get_me (const char *token) {
    
    if (!token)
        return NULL;

    json_t *get_me_res = generic_method_call(token, "getMe");
    return user_parse(get_me_res);
}
/**
 * Returns the updates list
 */ 
Update *get_updates (Bot *bot, char *extra) {

    json_t *update_array;
    if (extra) {
        update_array = generic_method_call(bot->token, "getUpdates?%s", extra);
    } else {
        update_array = generic_method_call(bot->token, "getUpdates");
    }
    
    size_t length, i;
    length = json_array_size(update_array);

    Update *up = NULL, *_temp = NULL;

    if (length > 0) {
        up = update_parse(json_array_get(update_array, 0));

        for (i = 1; i < length; i++) {
            _temp = update_parse(json_array_get(update_array, i));
            if (_temp) {
                update_add(up, _temp);
            }
        }
    }

    return up;
}
/**
 * Sends the given message to the given chat.
 * TODO:
 *  - Change the type of 'chat_id'
 */
int send_message (Bot *bot, long int chat_id, char *text, char *extra) {
    if (!text || chat_id == 0) {
        return 0;
    }

    json_t *is_send_message;
    if (extra) {
        is_send_message = generic_method_call(bot->token, "sendMessage?chat_id=%ld&text=%s&%s", chat_id, text, extra);
        free(extra);
    } else {
        is_send_message = generic_method_call(bot->token, "sendMessage?chat_id=%ld&text=%s", chat_id, text);
    }

    return json_is_object(is_send_message);
}

/**
 * Returns the Chat object of the given chat_id
 */ 
Chat *get_chat (Bot *bot, char *chat_id) {

    if (!chat_id) 
        return 0;
    
    json_t *chat_res = generic_method_call(bot->token, "getChat?chat_id=%s", chat_id);
    return chat_parse(chat_res);
}
/**
 * Changes the title of the given chat_id
 * Returns 1 in success, 0 otherwise
 */
int set_chat_title (Bot *bot, char *chat_id, char *title) {

    if(!chat_id || !title)
        return 0;
    
    json_t *is_chat_title = generic_method_call(bot->token, "setChatTitle?chat_id=%s&title=%s", chat_id, title);
    return json_is_true(is_chat_title);
}
/**
 * Returns the requested ChatMember object.
 */
ChatMember *get_chat_member (Bot *bot, char *chat_id, char *user_id) {

    if (!chat_id || !user_id)
        return NULL;
    
    json_t *chat_member = generic_method_call(bot->token, "getChatMember?chat_id=%s&user_id=%s", chat_id, user_id);
    return chat_member_parse(chat_member);
}
/**
 * Changes the given chat or channel description
 */
bool set_chat_description (Bot *bot, char *chat_id, char *description) {
    if (!chat_id) 
        return false;
    
    json_t *is_description = generic_method_call(bot->token, "setChatDescription?chat_id=%s&description=%s", chat_id, description);
    return json_is_true(is_description);
}
/**
 * Returns the number of members in the given chat
 */ 
int get_chat_member_count (Bot *bot, char *chat_id) {
    if (!chat_id)
        return false;
    
    json_t *count = generic_method_call(bot->token, "getChatMemberCount?chat_id=%s", chat_id);
    return json_integer_value(count);
}
/**
 * Ban a chat user
 */
bool kick_chat_member (Bot *bot, char *chat_id, char *user_id, char *until_date) {
    if(!chat_id || !user_id)
        return false;

    json_t *is_kicked = generic_method_call(bot->token, "kickChatMember?chat_id=%s&user_id=%s&until_date=%s", chat_id, user_id, until_date);
    return json_is_true(is_kicked);
}
/**
 * Generic method to handle Telegram API Methods responses
 * TODO:
 *  - Error filtering
 */
json_t *generic_method_call (const char *token, char *formats, ...) {
    va_list params;
    va_start(params, formats);

    char *method_base = vsformat(formats, params);
    MemStore *response = call_method(token, method_base);
    free(method_base);

    json_t *root = load(response->content),
           *ok,
           *result;
    
    mem_store_free(response);
    
    if (json_is_object(root)) {
        ok = json_object_get(root, "ok");
        if (json_is_true(ok)) {
            return json_object_get(root, "result");
        }
    }

    return NULL;
}