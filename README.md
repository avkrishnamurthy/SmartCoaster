# Smart Coaster
Ajay Krishnamurthy, Anthony Fernando, Patrick Hardison, Ryan D'Cunha, Shaan Narayan

According to the NIH, 75% of Americans are chronically dehydrated. Our smart coaster promotes hydration by alerting users to drink water via text message and LEDs throughout the workday. 
 
## Inspiration
You might be wondering: Is dehydration really an issue? With an increasing number of sedentary lifestyles due to the workforce, people find themselves sitting down the majority of the day, and in a stressful work environment, water is the last thing on anyone's mind. According to the NIH, 75% of Americans are chronically dehydrated. Dehydration is linked to low blood pressure, seizures, and kidney failure in severe cases. We are all guilty of not drinking enough water, and in honor of that, we set out to create an innovative, cost-efficient system to help us all stay hydrated.

## What it does
Our product is a smart water bottle coaster that tracks how much water a user drinks and alerts the user via text and visual aid (LEDs) when they are not drinking enough water. To use our product, the user has to place their water bottle on the coaster and wait. After some time, the Particle Photon microcontroller inside the device will check the weight of the bottle using a force-sensing resistor to determine if enough water was consumed. If the user has been drinking enough water, no notification will be sent, and the LEDs will stay off. However, if not enough water has been consumed, a text notification is sent via Twilio to the user’s phone number, and the LEDs on the coaster will slowly pulse until the user drinks enough water.

## How we built it
The main housing of our smart coaster is 3D printed using PLA filament. Our microcontroller is a Particle Photon board. We opted for this instead of an Arduino for WiFi capability, as we are using the Photon to send text message notifications. We also use LED lights in combination with the text message notifications to alert the user that they need to drink water. The weight of the water and water bottle is measured using a force-sensing resistor (FSR).  Both the FSR and LED lights are soldered to a perf board connecting them to the Photon. To convert the sensor reading into a measurable liquid volume, we took several data points and used linear regression to find the optimal conversion. In software, we have programmed our Photon to take a sample of the FSR data to determine how much water has been consumed. If our software determines that the user hasn’t had enough water, the Photon will send a text message to the user using Twilio’s SMS API and webhook and pulse the LEDs until they grab the bottle to drink.

## Challenges we ran into
We ran into several challenges in our first hackathon. Our first issue was inconsistency with our force-sensing resistor (FSR). Originally, the FSR values were heavily influenced by the specific weight distribution of the water bottle. If the water bottle was placed in a different spot, the load would be distributed differently, and our FSR would have a different reading. To solve this issue, we 3D printed a plate to evenly distribute the weight of the bottle and used an FSR with a larger surface area. Another challenge was setting up and connecting WiFi to our Particle Photon. After we did some troubleshooting regarding the connection errors, we found that the WiFi couldn’t be a WPA-2 Enterprise network, so we ended up using the DukeVisitor network. We also had software issues related to our Photon. We struggled to implement the Twilio SMS API and webhook because of API authentication errors. We consulted several online resources to troubleshoot this error, and we managed to resolve it and now have a working Photon-Twilio-SMS workflow. The final issue we faced was with using Wix to send user response data through Wix forms to our Photon because Wix requires an account upgrade to use Wix forms.
 
## Accomplishments that we're proud of
Since HackDuke was our first hackathon, getting a working product was our biggest accomplishment. In only 24 hours we managed to integrate functional hardware and software components. Another major accomplishment for the team is that we learned several new technologies within the period of HackDuke. We learned to work with the Twilio API, webhooks, Wix backend and automation, a Particle Photon, and an FSR. All in all, troubleshooting each step of the process and being able to create a functional product with time constraints was a major success.

## What we learned
During the 24 hours, we had to troubleshoot many steps during the iterative design process, leading to a far greater understanding of our software and hardware components. We have to learn the division of labor to work efficiently and how to brainstorm/troubleshoot challenges in a group setting. The original pressure sensor used was inaccurate and unreliable for data collection. After switching to the FSR, data was more consistent, but the water bottle wasn’t always being read by the sensor. We learned we needed to concentrate the load onto the sensor to maximize data collection. This was done by placing washers on the sensor and placing the bottle on top of it. Next, we had to learn to deploy code to the Particle Photon and connect it using webhooks and APIs to send data. 

## What's next for Smart Coaster
The next steps for Smart Coaster include improving the precision, durability, and user interface of our product. Instead of using an FSR to measure the weight of the bottle, we hope to implement a load cell sensor that can better measure the amount of water still left in the bottle. We also hope to improve our system's waterproofing capabilities to better protect the electronics in our device. Lastly, we would like to improve the user customizability of the Smart Coaster by having the user enter their height, weight, gender, and other information to better inform the water calibration curve. We also want to implement an interface so users can see their water drinking statistics over some time.

## Demo
Click to watch
[![Watch the video](https://img.youtube.com/vi/L-6ZjFuQa9M/maxresdefault.jpg)](https://youtu.be/L-6ZjFuQa9M)


## Technologies

<img src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white"/>
<img src="https://img.shields.io/badge/twilio-%23F22F46.svg?&style=for-the-badge&logo=twilio&logoColor=white" />

