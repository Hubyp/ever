#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include "Discord.h"

using namespace std;

const string BOT_TOKEN = "YOUR_BOT_TOKEN_HERE";

// Discord client
Discord client;

// List of commands
vector<string> commands = {"!hello", "!time", "!random"};

// Event handler for ready event
void onReady()
{
    cout << "Bot is ready!" << endl;
}

// Event handler for message event
void onMessage(DiscordMessage message)
{
    // Check if the message starts with a command
    if (find(commands.begin(), commands.end(), message.content) != commands.end()) {
        if (message.content == "!hello") {
            client.sendMessage(message.channelID, "Hello, " + message.author.username + "!");
        } else if (message.content == "!time") {
            time_t t = time(0);
            struct tm* now = localtime(&t);
            client.sendMessage(message.channelID, asctime(now));
        } else if (message.content == "!random") {
            srand(time(NULL));
            int random_number = rand() % 100 + 1;
            client.sendMessage(message.channelID, "Your random number is " + to_string(random_number));
        }
    }
}

int main()
{
    // Set up client
    client.setToken(BOT_TOKEN);
    client.onReady = onReady;
    client.onMessage = onMessage;

    // Connect to Discord
    client.run();

    return 0;
}
