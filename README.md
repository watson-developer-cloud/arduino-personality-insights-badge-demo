IBM Watson Personality Insights Badge
=====================================

Arduino Yún-based demo that displays your Twitter handle and "Big 5" personality traits.

Uses IBM Watson [Personality Insights](http://www.ibm.com/smarterplanet/us/en/ibmwatson/developercloud/personality-insights.html) service to calculate your personality traits based on
your recent tweets.

[![Picture of badge in action](https://watson-developer-cloud.github.io/arduino-pi-badge-demo/watson-pi-twitter-badge-small.jpg)](https://watson-developer-cloud.github.io/arduino-pi-badge-demo/watson-pi-twitter-badge.jpg)

Set Up
------

### Credentials:

Create a Personality Insights service instance at http://bluemix.net/ and bind it to a 
server instance. Then view the server's dashboard and click View Credentials on the service.
Copy the credentials to `linux/twitter-personality-insights/credentials.json`.

Instructions on how to get credentials for a Watson service can be found [here](http://www.ibm.com/smarterplanet/us/en/ibmwatson/developercloud/doc/getting_started/gs-quick-nodejs.shtml#credentials).

Create a twitter app at https://apps.twitter.com/ and also copy it's credentials to `credentials.json`.

### Linux Setup:

Copy the `arduino/pibadge/` folder into your Arduino Projects folder.

Copy the `linux/twitter-personality-insights/` folder onto a MicroSD card and insert it into the Yun.

SSH into the linux side of the Yun and run the following commands to install dependencies:

```
opkg update #updates the available packages list
opkg install distribute #it contains the easy_install command line tool
opkg install python-openssl #adds ssl support to python
easy_install pip #installs pip
mkdir /mnt/sda1/python-packages
pip install --target /mnt/sda1/python-packages twitter # current release of twitter
pip install --target /mnt/sda1/python-packages requests==2.5.3 # outdated release of requests that works on Yun's outdated python version
```

### Wiring:

You'll need to connect a display such as [this one](https://www.adafruit.com/products/358) - 
note that on the Yun, the only SPI pins are on the ICSP header, so you'll need a female 
connector on at least two of your wires.

### Bringing it all together: 

Upload the sketch and wait a minute or two for it to process things, then enjoy your new
Personality Insights Badge!

The sketch defaults @nfriedly, but you can change it to any twitter username you like. A 
potential enhancement could be to add a web interface for setting the username at runtime.
