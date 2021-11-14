#define PURPLE_PLUGINS

#include <glib.h>

#include "notify.h"
#include "plugin.h"
#include "version.h"
#include "gtkplugin.h"
#include "gtkconv.h"

#define PLUGIN_VERSION "0.1.1"

static void make_it_minimal(PurpleConversation *conv) {
    PidginConversation *gtkconv;
    PidginWindow *win;


    if (!conv) {
        return;
    }

    gtkconv = PIDGIN_CONVERSATION(conv);
    if (!gtkconv || !gtkconv->infopane) {
        return;
    }

    win = pidgin_conv_get_window(gtkconv);
    if (!win || !win->menu.menubar) {
        return;
    }

    gtk_container_set_border_width(GTK_CONTAINER(gtkconv->tab_cont), 0);
    gtk_widget_hide (gtkconv->infopane);
    gtk_widget_hide (GTK_WIDGET (win->menu.menubar));
}

static void
received_im_msg_cb(PurpleAccount *account, char *sender, char *message,
                   PurpleConversation *conv, PurpleMessageFlags flags) {
    make_it_minimal(conv);
}

static void
conversation_created_cb(PurpleConversation *conv) {
    make_it_minimal(conv);
}

static void
received_chat_msg_cb(PurpleAccount *account, char *sender, char *message,
                     PurpleConversation *conv, PurpleMessageFlags flags) {
    make_it_minimal(conv);
}

static void
got_attention_cb(PurpleAccount *account, const char *who,
                 PurpleConversation *conv, guint type) {
    make_it_minimal(conv);
}

static gboolean
plugin_load(PurplePlugin *plugin) {
    void *convs_handle;
    convs_handle = purple_conversations_get_handle();

    purple_signal_connect(convs_handle, "received-im-msg", plugin,
                          PURPLE_CALLBACK(received_im_msg_cb), NULL);

    purple_signal_connect(convs_handle, "conversation-created", plugin,
                          PURPLE_CALLBACK(conversation_created_cb), NULL);

    purple_signal_connect(convs_handle, "received-chat-msg", plugin,
                          PURPLE_CALLBACK(received_chat_msg_cb), NULL);

    purple_signal_connect(convs_handle, "got-attention", plugin,
                          PURPLE_CALLBACK(got_attention_cb), NULL);

    return TRUE;
}

static PurplePluginInfo info = {
    PURPLE_PLUGIN_MAGIC,
    PURPLE_MAJOR_VERSION,
    PURPLE_MINOR_VERSION,
    PURPLE_PLUGIN_STANDARD,
    PIDGIN_PLUGIN_TYPE,
    0,
    NULL,
    PURPLE_PRIORITY_DEFAULT,

    "gtk-budrich-minimal_conversation",
    "Minimal conversation",
    PLUGIN_VERSION,

    "Removes the info-pane and the menu-bar in conversation windows.",
    "So you can focus on the conversation",
    "budRich",
    "http://github.com/budrich/pidgin-minimal-conversation-plugin",

    plugin_load,
    NULL,
    NULL,

    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static void
init_plugin(PurplePlugin *plugin) {
}

PURPLE_INIT_PLUGIN(minimal_conversation, init_plugin, info)
