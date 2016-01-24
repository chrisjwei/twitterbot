#!/usr/bin/env python
# -*- coding: utf-8 -*-
from secret import * 
import tweepy, subprocess, time, csv, random, os

SRC_IMAGE_DIR = "data/source_images/"
OUT_IMAGE_DIR = "data/"
OUT_IMAGE_PREFIX = "planet_"
OUT_IMAGE_SUFFIX = ".jpg"
PERIOD = 1800 #seconds

class Tweet():
  
  def __init__(self, tweet, mediadir):
    self.tweet = tweet
    self.mediadir = mediadir

  def post(self, api):
    api.update_with_media(filename=self.mediadir, status=self.tweet)

class Planet():

  def isHabitable(self):
    temp = (273 < self.temp and self.temp < 373)
    radius = (self.radius < 1.4 and self.radius > 0.8)
    mass = (self.mass < 1.4 and self.mass > 0.8)

    return (mass and radius and temp)

  def isLife(self):
    return (random.random() < 0.0001 and isHabitable())
  
  def generateName(self):
    c = ""
    for i in xrange(random.randint(2,3)):
      c += chr(random.randint(ord('A'),ord('Z')))
    if (random.randint(0,1) == 1):
      c += " "
    else:
      c += "-"
    for i in xrange(random.randint(2,5)):
      c += chr(random.randint(ord('0'),ord('9')))
    c += " "
    c += chr(random.randint(ord('a'),ord('f')))
    return c

  def classify(self):
    if self.isHabitable(): return "Terran Planet"
    
    if (self.radius <= 0.8):
      size = "Dwarf"
    elif self.radius <= 20.0:
      size = "Planet"
    else:
      size = "Giant"

    density = self.mass/(self.radius)
    if (density < 0.8):
      desc = "Gas"
    elif (density < 1.2):
      if (self.temp < 273):
        desc = "Ice"
      elif (self.temp < 473):
        desc = "Hot"
      else:
        desc = "Pulsar"
    else:
      if self.temp > 473:
        desc = "Molten"
      elif self.temp > 373:
        desc = "Desert"
      else:
        desc = "Rocky"

    return desc + " " + size

  def generateMedia(self, file):
    currentTime = int(time.time())
    cmd = "./planetGenerator " + SRC_IMAGE_DIR + file + " " + str(currentTime)
    subprocess.call(cmd, shell=True)
    return OUT_IMAGE_DIR + OUT_IMAGE_PREFIX + str(currentTime) + OUT_IMAGE_SUFFIX

  def __init__(self):
    self.name = self.generateName()
    self.mass = round(random.uniform(0.0000021, 63.4) * 317.83, 1) # units of earth mass
    self.radius = round(random.uniform(0.03, 2.5) * 10.97, 1) # radius of earth
    self.temp = random.randint(32,2987)

  def toString(self):
    if (self.isLife()):
      life = "Life detected."
    else:
      life = "No life detected."
    classification = self.classify()
    return '"' + self.name + '" ' + classification + ' (' + str(self.mass) +\
      'Me, '+ str(self.radius) + 'Re).\n A balmy ' + str(self.temp) + \
      'K surface temperature. ' + life

def generateTweet(file):
  planet = Planet(); # generate a new planet
  filename = planet.generateMedia(file);
  tweet = planet.toString();
  return Tweet(tweet, filename)

def main():
  auth = tweepy.OAuthHandler(CONSUMER_KEY, CONSUMER_SECRET)
  auth.set_access_token(ACCESS_TOKEN, ACCESS_TOKEN_SECRET)
  api = tweepy.API(auth)
  files = [f for f in os.listdir(SRC_IMAGE_DIR)]
  numFiles = len(files)
  while(1):
    i = random.randint(0, numFiles-1)
    tweet = generateTweet(files[i]);
    tweet.post(api);
    time.sleep(PERIOD) # every 15 minutes

main()
