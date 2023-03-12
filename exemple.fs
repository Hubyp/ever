open Discord
open Discord.Commands

[<EntryPoint>]
let main argv =

    // Create a new Discord client
    let client = new DiscordSocketClient()

    // Define the command prefix
    let prefix = "!"

    // Register the command module
    let commands = new CommandService()
    client.AddService<CommandService>(fun c -> commands)

    // Define the ping command
    commands.CreateCommand("ping")
        .Description("Ping the bot")
        .Do(fun (context: CommandContext) ->
            context.Channel.SendMessageAsync("Pong!").Wait())

    // Define the greet command
    commands.CreateCommand("greet")
        .Description("Greet a user")
        .Parameter(fun p -> p.AddUserParameter())
        .Do(fun (context: CommandContext) ->
            let user = context.Parameters.[0] :?> IUser
            context.Channel.SendMessageAsync(sprintf "Hello %s!" user.Username).Wait())

    // Connect to Discord
    let token = "<insert your bot token here>"
    client.LoginAsync(TokenType.Bot, token).Wait()
    client.StartAsync().Wait()

    // Wait indefinitely
    System.Console.ReadLine() |> ignore
    0 // Exit with success
