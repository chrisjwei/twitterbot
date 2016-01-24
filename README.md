## Gauntlet: Twitter Image Bot
##### Summary
This is my twitter image bot for **IACD Spring 2016**. Includes as script that runs the twitter bot, posting tweets every 30 minutes depicting a fictional planet and fictional stats alongside the planet. The program that generates the images of the planets can be compiled by moving the `planetGenerator_vs` folder into your `openframeworks/apps/myApps` folder, and building from Visual Studios, or by a typical OpenFrameworks Makefile.\
After building, you can try and make a couple fake planets before tweeting. Move `planetGenerator` into the top directory, and run with `./planetGenerator sourceimage.jpg outputimage.jpg`, where your sourceimage lives in `data/source_images/` and your output image will live in `data/`\
Now, create file `secret.py` and define your own twitter app's\
`CONSUMER_SECRET = "xxx"`\
`CONSUMER_KEY = "xxx"`\
`ACCESS_TOKEN = "xxx"`\
`ACCESS_TOKEN_SECRET = "xxx"`\
From here you can now run your own twitter bot with `python run.py`

##### Twitter Handle
Follow me at on [@fermib0t].
##### Technology
Runs on [Python 2.7] and [tweepy]. Image generator runs on [OpenFrameworks].
##### Image Database
Special thanks to [NASA Astronomy Picture of the Day]

[@fermib0t]: https://twitter.com/fermib0t
[Python 2.7]: https://www.python.org/download/releases/2.7/
[tweepy]: http://www.tweepy.org/
[OpenFrameworks]: http://www.openframeworks.cc/
[NASA Astronomy Picture of the Day]: http://apod.nasa.gov/
