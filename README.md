IBM Watson Personality Insights Badge
=====================================

Arduino Yún-based demo that displays your Twitter handle and "Big 5" personality traits.

Uses IBM Watson [Personality Insights](http://www.ibm.com/smarterplanet/us/en/ibmwatson/developercloud/personality-insights.html) service to calculate your personality traits based on
your recent tweets.

[![Picture of badge in action](https://watson-developer-cloud.github.io/arduino-pi-badge-demo/watson-pi-twitter-badge-small.jpg)](https://watson-developer-cloud.github.io/arduino-pi-badge-demo/watson-pi-twitter-badge.jpg)

Set Up
------

### Parts and Wiring:

![Breadboard layout](https://watson-developer-cloud.github.io/arduino-pi-badge-demo/arduino-pi-badge-bb.png)

Part | Price | Vendor
-----|-------|-------
Arduino Yún | $55.01 | [Arduino Store](http://store.arduino.cc/product/A000008)
1.8" EDS TFT LCD | $6.80 | [Electrodragon](www.electrodragon.com/product/eds-tft-lcd-lcm-spi-interface-variable1-82-2/)
Male-to-Female Wires | $2.30 | [Electrodragon](http://www.electrodragon.com/product/prototype-cable-female-and-male-end-40p/)
Female-to-Female Wires | $1.80 | [Electrodragon](http://www.electrodragon.com/product/ff-40p-dupont-prototype-cables-female-female-end/)

If you'd prefer a single, US-based vendor, Adafruit sells an [equivalent display](https://www.adafruit.com/products/358) and the [other](https://www.adafruit.com/products/1498) [necessary](https://www.adafruit.com/products/826) [parts](https://www.adafruit.com/product/266).

Note: while the EDS TFT display is avaliable in larger sizes, only the 1.8" is 5v tolerant. Adafruit offers several options for [larger 5v-tollerant displays](https://www.adafruit.com/categories/97).

Also note that even on the 1.8" EDS TFT, the LED pin only accepts 3.3v.

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


### Bringing it all together: 

Upload the sketch and wait a minute or two for it to process things, then enjoy your new
Personality Insights Badge!

The sketch defaults @nfriedly, but you can change it to any twitter username you like. A 
potential enhancement could be to add a web interface for setting the username at runtime.
