require 'discordrb'

bot = Discordrb::Commands::CommandBot.new(
  token: 'your_bot_token_here',
  prefix: '!'
)

bot.command(:ping) do |event|
  m = event.respond('Pong!')
  m.edit("Pong! Time taken: #{Time.now - event.timestamp} seconds.")
end

bot.command(:roll, min_args: 1, max_args: 2) do |event, sides, num_rolls = 1|
  sides = sides.to_i
  num_rolls = num_rolls.to_i

  if sides < 1 || num_rolls < 1
    event.respond('Invalid arguments! Usage: !roll [sides] [num_rolls]')
    next
  end

  rolls = []
  num_rolls.times { rolls << rand(1..sides) }

  total = rolls.inject(:+)
  avg = total.to_f / num_rolls.to_f

  event.respond("#{num_rolls}d#{sides}: #{rolls.join(', ')} (Total: #{total}, Avg: #{avg})")
end

bot.command(:server_info) do |event|
  server = event.server

  embed = Discordrb::Webhooks::Embed.new(
    title: server.name,
    description: server.id,
    thumbnail: { url: server.icon_url },
    fields: [
      { name: 'Region', value: server.region, inline: true },
      { name: 'Owner', value: server.owner.mention, inline: true },
      { name: 'Members', value: server.member_count, inline: true }
    ]
  )

  event.channel.send_embed('', embed)
end

bot.run
