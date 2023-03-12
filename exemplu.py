import discord
from discord.ext import commands

bot = commands.Bot(command_prefix='!')

@bot.command()
async def hello(ctx):
    await ctx.send('Hello!')

@bot.event
async def on_ready():
    print(f'{bot.user.name} has connected to Discord!')

bot.run('your_bot_token_here')
