# Bunnies
+ Create a Bunny Class that has variables for: 
+ Sex: 		Male, Female
+ Colour: 	White, brown, black, spotted
+ Age: 		int 
+ Name: 	string
+ Infected: 	True/false
+ In its constructor:
+ Set Sex using 50/50 chance
+ Set random colour
+ Set age to 0 years old
+ Set name to a random name (Pick one from a list/array)
+ Set infected with 2% chance of true (random number 1-100 if 1 or 2 etc)

# Bunny List
+ Create Bunny Manager Class
+ Make it hold a list of bunnys (pointers)
+ Create a AddBunny function thats adds a new bunny to the list.
+ In its constructor, add 5 random bunnies to the list.
 
# Bunnies Grow Older
+ Create a function in the bunny class that makes the bunny 1 year older
+ Create a function in the Bunny manager class that loops through all the bunnies and calls their age 1 year older function.
+ Make an instance of the bunny manager in main.
+ Create a loop in main (Your main loop) and call the AgeAllBunnies function so each turn (loop) they get one year older.
 
# Breeding Part 1
+ Create a bool (flag) for if we have a breedable male, inside of the bunny manager.
+ Before we loop through the list of bunnies, set it to false as we dont know if we have a old enough male.
+ When we loop through the list of bunnies in order to age them, if we find a male bunny older then 2, set the flag to true.
 
# Breeding Part 2
+ Create a list of bunny pointers inside of the bunny manager, for all the breedable females.
+ Before we loop through the list of bunnies, clear the list.
+ When we loop throguh the list of bunnies, add any bunny that is a breedable female. (think shared_pointers)
+ Create a bunny constructor that takes in a bunny as an argument.
+ With this constructor, set al the vales as normal, but then set the colour to the same as thebunny passed in.
+ After looping through all bunnies to age them up. We now have a flag for if we have a male thats old enough, and a list of mothers.
+ Loop through all the mothers and create a new bunny using the mother, only if the Male flag is true.

# Bunny Death
+ In our loop to age a bunny, before we age them up, check how old the bunny is.
+ If > 10, kill the bunny and remove it from the list.
+ NOTE: When removing from the list you can use listname.erase(++bunnyToRemove)
+             However if you do this, then you will be setting the bunny itterator to the next bunny, so only do a bunny++ if you age up the bunny
+             and use listname.erase(++bunny) if you are killing it off. (While loop might be useful)

# Infected Part 1
+ When you loop through all the bunnies, count how many are infected. (store it in bunny manager)
+ After loop ends, use a function that will infect that many healthy bunnies.
+ (loop through all the bunnies, and if healthy make it infected untill we have infected the needed amount)

# Infected Part 2
+ Update the breedable male check, to not include infected males.
+ Update the adding to list of possible mothers check to not add infected.
+ Update the death check to see if they are >10 and healthy OR >50
 
# Display Info
+ Make a function in the bunny manager that loops through all the bunnies and prints out their info.
+ Place this in th emain loop
+ Make a function that displays a bunny being boorn/dying/being infected
+ Everytime a action is called in the main aging loop call the fcorrect info function 

# When all the bunnies have died the program terminates.
+ Make a function that returns the size of the list
+ Make tha main loop exit if that returns 0

# Culling
+ If bunnylist.size >1000
+ Kill off half the bunnies
+ How you kill them is up to you.
+ One example is to :
+ Set an int to bunnylist.size/2 so that you know how many you want to kill
+ Then pick a random bunny and kill it.
+ When you kill the bunny add that to a counter so you know how many you have killed.
+ When the kill counter == how many you need to kill, then stop killing them.

# 1 STAR (Run Realtime)
+ Look at using the sleep function
+ OR
+ If you want to look at         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
+ Thats a non system specific version of waiting a set time. You will need 2 includes 
+ ;)

# 2 STAR (k to cull)
+ Posted in chat friday I believe was the _kbhit() function
+ This will check to see if a key is sitting in the keyboard buffer, and if so then return true.
+ You can use this with a if check. so 
+ if (_kbhit()) { // Do something }
+ Whena key is in the buffer, you can use getch() to return that key.
+ Again, if you need an example, I posted a image of it in use in the chat.
+ Now using this you can check the keyboard bugger for a key, but if some time passes, then just continue anyway.
+ (Makes use of the 1 STAR stuff to wait)

# 4 STAR
+# Mark bunnies
+ When created, set either m,f or X as their character to display
+ When infected set to a X
+ When they hit the age of 2, if they arent infected, update the character to be M or F

# Modify the program to place the rabbits in an 80x80 grid.
# Have the rabbits move one space each turn randomly.
+ Create a GridSpace class that holds a bunny pointer (set to NULL in constructor - meaning its pointing to nothing)
+ Add a SetPointerFunction (Updates the pointer with a bunny address)
+ Add a CheckPointerFunction (Returns  true if there is a bunny, false if its NULL)
+ Create an array/list of GridSpaces (Maybe in a grid manager)
+ Each GridSpace should point to NULL when setup
+ When a bunny is created, find empty spot and place bunny 
+ (Start with find first empty slot by checking if pointer points to NULL)

# Random placement
+ Now try and make it randomply place a bunny.
+ Create a list of AvailableGridSpace pointers (std::list<std::shared_ptr<GridSpace>>)
+ Loop through all the grid spaces and add the ones that are available
+ When adding a bunny, pick a random available gridspace.
+ Add the bunny to that space, then remove the pointer from the list.
 
# Movement
+ At end of each turn, loop throguh the bunnies.
+ work out the GridSpots that are next to the bunny (We did this in the first project)
+ If there is one available move the bunnys shared pointer from the current space to a new one.
+ Remove that space from the list of available spaces
+ Then add the old space to the list of available spaces
+ (if struggleing to work out what spot you need to remove from the list, maybe give them all a ID (this could be their index value)
+ (Then you can look for the slot with the ID the bunny just moved to and remove that one)
 
# Infection
+ Modify the program so that radioactive mutant vampire bunnies only convert bunnies that end a turn on an adjacent square.
+ When looping through the bunnies, if the bunny is infected, check the Spaces it is next tooo and see if there is a healthy bunny.
+ If so keep track of the bunnies (as we may have all 4 connected)
+ Pick a random one from the list of healthy bunnies and add it to a list of bunnies that should be infected.
+ Once all the bunnies have been checked, THEN infect the list of bunnies.
+ Also make sure you do this AFTER ALL the bunnies have moved.
 
# Modify the program so that new babies are born in an empty random adjacent square next to the mother bunny. 
+(if no empty square exits then the baby bunny isn't born)
+ When creating a bunny, pass in the Space the Mother is in.
+ Find an empty Space next to the mother and spawn them there.
+ Otherwise dont create the bunny at all.