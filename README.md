Drone
Piercen Lewis and Evan Buck
5/9/2023
Finished Project:
![IMG_8348](https://github.com/Leg0evan/Capstone-Project/assets/90726739/8d6bf448-03c5-48ce-b79a-c450ba503b25)

Overview
This drone will have a take off and landing buttons on the control, and when it is in the air, you can change altitude, you can pitch left, right, forward and backward, and you can yaw left or right. We are using the app Blynk to control it, and using an ESP to connect to the app. 

Schematic Diagram
![IMG_8349](https://github.com/Leg0evan/Capstone-Project/assets/90726739/5a4b19c2-555c-4dfd-a974-7f471f18448d)

Circuit Without Top Plate
![IMG_8350](https://github.com/Leg0evan/Capstone-Project/assets/90726739/5955f5e1-e540-47df-8296-3166f50b614d)


We used 4 brushless DC motors to fly the project, which you can see in the finished project picture on all four legs of the drone. We also soldered two battery packs together, which when full, it comes up to 12 volts. You can see those on the top of the drone in the finished project Picture. In the circuit picture, you can see the ESP under all of the wires. You ccan also seee the 4 Electronic speed controllers that are colored yellow. We used these to program the motors to move at different speeds.

Design Evaluation
The drone has not actually flown yet, but I have done a lot of math to figure out that theoritically, if everything goes right, it should fly. The drone itself is 834 grams, and to calculate force with that number, you do mass * acceleration due to gravity, which is 9.8 m/s^2. You need to convert the wieght of the object into kilograms for mass, which is 0.834 kg. Multiply that number by 9.8, and you get around 8.1 Newtons. The force of all four propellers moving at max speed is over 10 Newtons of downward force, so if everytihing works, it should fly. In the end, two of the motors broke, so it didn't fly.

Lessons Learned
We learned a lot in this project, like how a brushless motor requires a brushless motor controller to spin. But at the start of the project, like a month in, we thought we had more than enough time. That was our first mistake. We did not hit the early bird date, because we were working onjust the motors at the time, so we didn't have everything done. About two weeks out from the final day, our esp burnt out. This started a whole lot of stress and rushing for the next two weeks, and everything after that was rushed and slopy. If I could do this project again,, I would not spend so much time on just testing the motors over and over, and get to the actual flying part way sooner.

Parts list:
https://docs.google.com/spreadsheets/d/1QK6QRX9OQN_NeLa8jLGlPvSDyvxlf5u8o5dP0R86LW4/edit?usp=sharing
