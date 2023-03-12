const { Client, Intents } =require("discord.js");

const client = new Client({ intents: [Intents.FLAGS.GUILDS, Intents.FLAGS.GUILD_MESSAGES] });

client.once('ready', () => {
    console.log('Bot is online!');
});

client.on('messageCreate', message => {
    if (message.content === '!Hi') {
        message.channel.send('Hi !');
    }
});

client.login(process.env.TOKEN);
