import * as Discord from 'discord.js';
import * as dotenv from 'dotenv';

dotenv.config();

const client = new Discord.Client();

client.on('ready', () => {
  console.log(`Logged in as ${client.user?.tag}!`);
});

client.on('message', async message => {
  if (message.author.bot) return;

  if (message.content === '!ping') {
    const pingMessage = await message.channel.send('Pinging...');

    pingMessage.edit(`Pong! Latency is ${pingMessage.createdTimestamp - message.createdTimestamp}ms.`);
  }
});

client.login(process.env.DISCORD_TOKEN);
