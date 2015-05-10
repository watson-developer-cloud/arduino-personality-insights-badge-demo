# Update Python path to include libraries on SD card.
import sys
sys.path.append('/mnt/sda1/python-packages')

import json
from pprint import pprint
from twitter import *
import requests

# optionally load from cache to test faster (and free-er)
offline_mode = False

twitter_username = sys.argv[1]

with open('./config.json') as data_file:    
    config = json.load(data_file)

#pprint(config)


if offline_mode:
	with open('./twitter_response.json') as data_file:
		statuses = json.load(data_file)
else:
	t = Twitter(auth=OAuth(config["twitter"]["token"], config["twitter"]["token_secret"], config["twitter"]["consumer_key"], config["twitter"]["consumer_secret"]))
	statuses = t.statuses.user_timeline(screen_name=twitter_username)

#pprint(len(statuses))

input_text = '\n'.join([tweet["text"] for tweet in statuses])

#pprint(text)

if offline_mode:
	with open('./pi_response.json') as data_file:
		piData = json.load(data_file)
else:
	#we only get 100 free requests and I've already burned a few of them. Read from a JSON file instead of wasting any more
	piconf = config["personality_insights"]
	response = requests.post(piconf["url"] + "/v2/profile",
			auth=(piconf["username"], piconf["password"]),
			headers = {"content-type": "text/plain"},
			data={'body': input_text}
			)
	#pprint(response.text)
	piData = json.loads(response.text)
	
big5 = piData["tree"]["children"][0]["children"][0]["children"]

#lines = ["@nfriedly"]
#lines.append(big5[0]["id"])

# output percentage values as CSV
output_text = ",".join([str(round(trait["percentage"]*100,1)) for trait in big5]) + "," # comma marks the end of each number, so we need one at the end

print(output_text)
