import urllib2, urllib, string
from bs4 import BeautifulSoup
url="http://apod.nasa.gov/apod/archivepix.html"
page=urllib2.urlopen(url)
data=page.read().split("</a>")
tag="<a href=\""
endtag="\">"
count = 0
for item in data:
    if "<a href" in item:
        try:
            ind = item.index(tag)
            item=item[ind+len(tag):]
            end=item.index(endtag)
        except: pass
        else:
            suburl = item[:end]
            if suburl[0:2] != 'ap':
              continue
            count += 1;
            imgurl = "http://apod.nasa.gov/apod/" + item[:end]
            print imgurl
            htmtifl = urllib2.urlopen(imgurl)
            soup = BeautifulSoup(htmtifl)
            try:
              imgs = soup.find('img')['src']
            except:
              print "not an image",
              print imgurl
            else:
              filename = (imgs.split("/"))[-1]
              imurl = "http://apod.nasa.gov/apod/" + imgs
              resource = urllib.urlopen(imurl)
              output = open("images/" + filename,"wb")
              output.write(resource.read())
              output.close()
              
            

print "number of images read: " + str(count)