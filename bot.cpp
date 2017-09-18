#include <stdio.h>
#include <signal.h>
#include <iostream>
#include "tgbot/tgbot.h"
#include "Api.h"
#include "InlineKeyboardButton.h"
using namespace std;
using namespace TgBot;
string photoFilePath;
const string photoMimeType = "image/jpeg";

int main(void) {
    TgBot::Bot bot("449744418:AAEVEmgyIs1IUC0nu8poWS1C3wrl3nQUmo8");
    //bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
      //  bot.getApi().sendMessage(message->chat->id, "Privet, Andrey!");
    //});
    TgBot::InlineKeyboardMarkup::Ptr keyboard0(new TgBot::InlineKeyboardMarkup);
    TgBot::InlineKeyboardMarkup::Ptr keyboard1(new TgBot::InlineKeyboardMarkup);
    vector<TgBot::InlineKeyboardButton::Ptr> row0;
    vector<TgBot::InlineKeyboardButton::Ptr> row1;
    TgBot::InlineKeyboardButton::Ptr firstButton(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr secondButton(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr thirdButton(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr goback_button(new TgBot::InlineKeyboardButton);
    TgBot::User::Ptr username(new TgBot::User);

    
        firstButton->text = "first_button_row0";
        firstButton->callbackData = "first0";
        row0.push_back(firstButton);
        secondButton->text = "second_button_row0";
        secondButton->callbackData = "second0";
        row0.push_back(secondButton);
        thirdButton->text = "third_button_row0";
        thirdButton->callbackData = "third0";
        row0.push_back(thirdButton);
        keyboard0->inlineKeyboard.push_back(row0);

        firstButton->text = "send_cat";
        firstButton->callbackData = "cat";
        row1.push_back(firstButton);
        secondButton->text = "second_button_row1";
        secondButton->callbackData = "second1";
        row1.push_back(secondButton);
        thirdButton->text = "third_button_row1";
        thirdButton->callbackData = "third1";
        row1.push_back(thirdButton);
        goback_button->text = "return_to_the_main_menu";
        goback_button->callbackData = "return";
        row1.push_back(goback_button);
        keyboard1->inlineKeyboard.push_back(row1);

        // deleteMessage(int64_t chatId, int32_t messageId) const;


    bot.getEvents().onCommand("start", [&bot, &keyboard0](TgBot::Message::Ptr message) 
    {
        string response = "Privet!";
        bot.getApi().sendMessage(message->chat->id, response, false, 0, keyboard0);
    });
    bot.getEvents().onCommand("help", [&bot, &keyboard0](TgBot::Message::Ptr message) 
    {
        //bot.getApi().deleteMessage(TgBot::Chat->id, message->chat->id);
        string response = "Pomowi ne budet";
        bot.getApi().sendMessage(message->chat->id, response, false, 0, keyboard0);
    });
    bot.getEvents().onCommand("check", [&bot, &keyboard0](TgBot::Message::Ptr message) 
    {
        string response = "ok";
        bot.getApi().sendMessage(message->chat->id, response, false, 0, keyboard0);
    });
    bot.getEvents().onCallbackQuery([&bot, &keyboard0, &keyboard1](TgBot::CallbackQuery::Ptr query) 
    {
        if (StringTools::startsWith(query->data, "first0")) 
        {
            string response = "first_0_ok";
            bot.getApi().sendMessage(query->message->chat->id, response, false, 0, keyboard1);
        }
        else if(StringTools::startsWith(query->data, "second0"))
        {
            string response = "second_0_ok";
            bot.getApi().sendMessage(query->message->chat->id, response, false, 0, keyboard1);   
        }
        else if(StringTools::startsWith(query->data, "third0"))
        {
            string response = "third_0_ok";
            bot.getApi().sendMessage(query->message->chat->id, response, false, 0, keyboard1);   
        }
        else if(StringTools::startsWith(query->data, "cat"))
        {
            string response = "meow";
            string photoFilePath = "cat.jpg";
            bot.getApi().sendPhoto(query->message->chat->id, InputFile::fromFile(photoFilePath, photoMimeType));
            bot.getApi().sendMessage(query->message->chat->id, response, false, 0, keyboard0);   
        }
        else if(StringTools::startsWith(query->data, "second1"))
        {
            string response = "second_1_ok";
            bot.getApi().sendMessage(query->message->chat->id, response, false, 0, keyboard1);   
        }
        else if(StringTools::startsWith(query->data, "third1"))
        {
            string response = "third_1_ok";
            bot.getApi().sendMessage(query->message->chat->id, response, false, 0, keyboard1);   
        } 
        else if(StringTools::startsWith(query->data, "return"))
        {
            string response = "went_back";
            bot.getApi().sendMessage(query->message->chat->id, response, false, 0, keyboard0);   
        }
    });

    //signal(SIGINT, [](int s) {
      //  printf("SIGINT got");
        //sigintGot = true;
    //});
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}
