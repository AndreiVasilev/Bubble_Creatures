# Bubble Creatures - Simulated Evolution Environment
This program creates a population of "bubble creatures" that bounce around and consume food (orange squares) whenever they fall within the bubble's radius. Whenever a bubble consumes food it gains the ability to reproduce for a short time. Each bubble is given an initial set of characterstics such as size, speed, and direction which collectively determine their health decay rate and overall lifespan. The speed * radius of a bubble is ultimately what determines the rate of health decay. For larger bubbles to surive they must be born with a lower speed, otherwise they die out very quickly. Their larger size means an extended reach for food, but their slower speed means they are less likely to get to food quickly. With smaller bubbles it is the opposite. They are able to move quickly without dying due to their smaller radius, but they are less likely to run into food.
<br><br>
The population is initialized with random values for speed, direction, and radius; and then health decay rate is calculated from these quantities. When a bubble captures food and ends up reproducing, the newly produced bubble has a small chance to be randomly mutated, resulting in a bubble with slightly different characteristics.  
<br>
In the end, the manipulation of the food supply ultimately determines who survives and who doesn't. Depending on how much food is generated, different outcomes can be obtained which can be seen below.

<h2>Initial Population</h2>
<img src="https://media.giphy.com/media/GqHPOCoQ428BW/giphy.gif" />

<h2>Population after 30 min with food surplus. Biodiverstiy is high.</h2>
<img src="https://media.giphy.com/media/vOTsHHMobm6mk/giphy.gif" />

<h2>Population after 30 min with food scarcity. Biodiversity is low.</h2>
<img src="https://media.giphy.com/media/wvjFdpyTr7d96/giphy.gif" />

<h2>Population with extreme food surplus. Exponential growth.</h2>
<img src="https://media.giphy.com/media/lrNM8jWRHOPzW/giphy.gif" />
