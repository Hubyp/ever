import discord
from discord.ext import commands

# Defining the client
client = commands.Bot(command_prefix='!')

# Defining the command
@client.command()
async def hello(ctx):
    await ctx.send('Hello!')

# Defining a command with arguments
@client.command()
async def greet(ctx, name):
    await ctx.send(f'Hello, {name}!')

# Event listener for bot startup
@client.event
async def on_ready():
    print(f'Logged in as {client.user.name}')

# Event listener for member join
@client.event
async def on_member_join(member):
    channel = discord.utils.get(member.guild.channels, name='general')
    await channel.send(f'Welcome to the server, {member.mention}!')

# Event listener for member leave
@client.event
async def on_member_remove(member):
    channel = discord.utils.get(member.guild.channels, name='general')
    await channel.send(f'{member.name} has left the server.')

# Command error handling
@client.event
async def on_command_error(ctx, error):
    if isinstance(error, commands.errors.CommandNotFound):
        await ctx.send('Command not found.')

# Run the bot with your token
client.run('your-token-here')
