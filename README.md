# winter-lights

## Sensors/Pins

### Eyes (Brake Lights)

(A1, A2) - Left Eye. (255, 255)=OFF, (0, 255)=DIM, (255, 0)=BRIGHT

(D8, D9) - Right Eye. (HIGH, HIGH)=OFF,(LOW, HIGH)=DIM, (HIGH, LOW)=BRIGHT 

### Plunger

D0 - Read pin. 0 means the button was depressed.

### Other

A3 - Used for randomizing start of loop

## Loop

Eyes are dim and kitty is purring.

When the button is pressed, eyes brighten and a greeting is played. The first greeting is random, but play proceeds in order after that.

Data processing sounds play while eyes blink. 

Eyes brighten again while the Haiku is read. This will also start on a random Haiku and proceed in order.

Ending sound while eyes blink.

Delay 1.5 seconds before looping.

## Feedback

The delay at the end should be removed or greatly shortened. Usually a long line had formed, and the button was pushed immediately after the ending sound, but didn't register due to the 1.5 second timeout. Then the user would wait, confused about why their interaction hadn't started. Each interaction was about 30 seconds, and a loop of all haikus about 24 minutes. Interactions could be slightly shortened, but not too much - users liked the personal experience.

The greetings that didn't specifically ask the person to wait sometimes confused people, and they would push the button again during the data processing phase.

Data processing sounds were a little muted in a large crowd, which may also have led to confusion.

Funny haikus were most popular, and those that were kid-friendly given the crowd.
