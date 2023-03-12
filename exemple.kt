import discord4j.core.DiscordClientBuilder
import discord4j.core.`object`.entity.Message

fun main() {
    val token = "your-bot-token"
    val client = DiscordClientBuilder(token).build()

    client.login().block()

    client.eventDispatcher.on(Message::class.java)
        .map { it.content }
        .filter { it.startsWith("!") }
        .flatMap { command ->
            val commandName = command.substring(1)
            when (commandName) {
                "ping" -> handlePingCommand()
                "hello" -> handleHelloCommand()
                "roll" -> handleRollCommand()
                else -> handleUnknownCommand(commandName)
            }
        }
        .flatMap { response -> client.eventDispatcher.emit(response) }
        .onErrorResume { error ->
            println("Error: ${error.message}")
            client.logout().block()
            client.login().block()
        }
        .subscribe()
}

fun handlePingCommand(): String {
    return "Pong!"
}

fun handleHelloCommand(): String {
    return "Hello, world!"
}

fun handleRollCommand(): String {
    val random = (1..6).random()
    return "You rolled a $random!"
}

fun handleUnknownCommand(commandName: String): String {
    return "Unknown command: $commandName"
}
