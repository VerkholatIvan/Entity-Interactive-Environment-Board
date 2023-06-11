# Entity-Interactive-Environment-Board


Classes
  In the code, there are 8 classes, and there are two main ones: entity and room, and six 
  subclasses: stone, hole, animated_ent, human, dragon, and monster. For better coordination I
  have created a flowchart of the programm:
      ![image](https://github.com/VerkholatIvan/Entity-Interactive-Environment-Board/assets/123458146/e54dea59-f740-4dcc-ad22-6471687e9782)


  Each class has its own role:
    • Entity - class for containing all of the common entity information including both animated 
    and non-animated ones, for example, location coordinates. From the flowchart, it can be 
    seen that all of the subclasses are connected with it, except from “room”.
    • Stone – class, which contains information only about its symbol and location since this 
    entity has no special attributes. Moreover, all of the non-animated objects have no 
    special elements, so they do not require extra classes.
    • Hole – class similar to stone, but has a depth attribute, which is randomized each new 
    board.
    • Animated – main class for all of the animated entities, in other words, those, who can 
    move through the map. All of the movable objects have health, which decreases with 
    every move.
    • Human – class, which has a moving function and a Name as a string, which can be 
    shown by using the “void show_info();” method. The movement of each step is going 
    right on the board unless it is the end of the map or the place is not empty. Health is 
    reduced by one each step.
    • Dragon – another animated class, which moves randomly up, down, left, and right, the 
    conditions for movement are the same, except for always moving right. Health is 
    reduced by the random number from 0 to 5.
    • Monster – the last movable entity, which jumps randomly up, down, left, and right, the 
    distance of the step depends on the monster’s strength, which is a random number from 
    0 to 5. Health is reduced by the entity’s strength.


Testing
  After completing the code, I started to put the wrong input to find where it can break the code. 
  For example, in the main part of the code there is a while loop, which except a number as an 
  input for the switch cases, but if the user enters a string, it will lead to the infinite loop. To 
  prevent it, I used “cin.fail();”, which can work similarly to “try” and “except” in Python, but it works 
  only on the input. Then just clear the memory by clearing the input and ignoring the given data, 
  writing down in the code “cin.clear():” and “cin.ignore():”, respectively. The only bug I had with 
  this debugging is, when the user enters, for example, two letters, the program will show that he 
  gave incorrect data twice.
  
  
Bugs (Faced problems and their solutions)
  One of the biggest problems was resetting the room function, which was not so obvious to code 
  in the first place because the main idea of resetting the room is to create a new object from the 
  class, but it is impossible to do it whenever the code is already running. So, there appeared a 
  very tricky way to make it work. The solution was both easy and non-straightforward, the thing is 
  that I should have defined the class object as a pointer and made it equal to the same class 
  using the command “new”, which is used to store some data inside the computer for some time, 
  it can work almost similar to RAM (random-access memory) in computers. Whenever user asks 
  for resetting the room we use the command “delete” to clear the memory of the room and make
  the pointer equal to the class again
