//import required libraries
import discord4j.core.DiscordClient;
import discord4j.core.event.domain.message.MessageCreateEvent;
import discord4j.core.object.entity.Message;
import discord4j.core.object.entity.channel.TextChannel;

//create the main class
public class MyDiscordBot {

   //declare the Discord client and the prefix to use for commands
   private static final String PREFIX = "!";
   private final DiscordClient client;

   //constructor to initialize the client
   public MyDiscordBot(String token) {
      this.client = DiscordClient.create(token);
   }

   //method to start the bot
   public void start() {
      client.login().block();
      client.getEventDispatcher().on(MessageCreateEvent.class)
            .map(MessageCreateEvent::getMessage)
            .filter(message -> message.getAuthor().map(user -> !user.isBot()).orElse(false))
            .filter(message -> message.getContent().startsWith(PREFIX))
            .flatMap(Message::getChannel)
            .ofType(TextChannel.class)
            .flatMap(channel -> channel.createMessage("Hello, I'm a Discord bot!"))
            .subscribe();
   }

   //main method to run the bot
   public static void main(String[] args) {
      MyDiscordBot bot = new MyDiscordBot("your-bot-token-here");
      bot.start();
   }
}
