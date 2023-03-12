-- Load the Discordia library
local discordia = require('discordia')

-- Create a new Discord client
local client = discordia.Client()

-- Define a command prefix
local prefix = '!'

-- Define a table of commands
local commands = {
  ['ping'] = function(message)
    message.channel:send('Pong!')
  end,
  ['hello'] = function(message)
    message.channel:send('Hello, ' .. message.author.name .. '!')
  end,
  ['echo'] = function(message, args)
    message.channel:send(table.concat(args, ' '))
  end,
}

-- Define a function to handle messages
local function handleMessage(message)
  -- Check if the message starts with the command prefix
  if message.content:sub(1, #prefix) ~= prefix then return end
  
  -- Split the message into arguments
  local args = {}
  for arg in message.content:sub(#prefix + 1):gmatch('%S+') do
    table.insert(args, arg)
  end
  
  -- Get the command name from the first argument
  local commandName = table.remove(args, 1)
  
  -- Get the command function from the commands table
  local command = commands[commandName]
  
  -- If the command exists, call it with the message and arguments
  if command then
    command(message, args)
  end
end

-- Register the handleMessage function to handle all messages
client:on('messageCreate', handleMessage)

-- Log in to the Discord API with your bot token
client:run('your-bot-token')
