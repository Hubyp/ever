const Discord = require("discord.js");
const client = new Discord.Client();

client.on("ready", () => {
  console.log(`Logged in as ${client.user.tag}!`);
});

client.on("message", (msg) => {
  if (msg.content === "ping") {
    msg.reply("Pong!");
  }
});

client.on("guildMemberAdd", (member) => {
  const channel = member.guild.channels.cache.find(
    (ch) => ch.name === "welcome"
  );
  if (!channel) return;
  channel.send(`Welcome to the server, ${member}`);
});

client.on("messageReactionAdd", (reaction, user) => {
  if (reaction.emoji.name === "👍") {
    const role = reaction.message.guild.roles.cache.find(
      (r) => r.name === "Supporter"
    );
    const member = reaction.message.guild.members.cache.find(
      (m) => m.id === user.id
    );
    member.roles.add(role);
  }
});

client.on("messageDelete", (msg) => {
  const channel = msg.guild.channels.cache.find(
    (ch) => ch.name === "logs"
  );
  if (!channel) return;
  channel.send(`Message deleted: ${msg.content}`);
});

client.login("your-token-goes-here");
