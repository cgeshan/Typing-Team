# **About**
Our vision was to create a game to:
   - Teach kids to type correctly so they can focus more on what they’re typing (code, writing, etc.) and less on the actual typing
   - Reinforce correct spelling, grammar, and punctuation

# **Game Overview**
When beginning a new save, all the minigames will be locked. To start a locked level the user must enter the Overworld first. After going through the Overworld and entering the transport portal the user then progresses to the locked minigame. Three things can happen from here, the user can successfully complete the game by typing in 10 words, the user can lose all of their lives, or the user can simply press the Escape key and exit the game returning to the menu.  During each Mini-Game the user can type and submit words as many times as they wish. If the input word is spelled correctly they gain 20 points, if the input word is spelled incorrectly they lose 10 points, and if a life is lost they lose five points. Points are updated after each completion of the Overworld as well as each mini game won. When a game is beaten, it is unlocked on the Overworld and can be replayed as many times as the player wishes. You have beaten the entire game once you unlock and complete the last minigame (Minigame 4: Rover). The objective of the game is to type the words or letters that appear on the screen as quickly and accurately as possible. Practice regularly to improve your skills and progress through the game. As you practice, you will become more familiar with the keyboard and the game, and you will be able to type more quickly and accurately.


# **Platforms**
This is a cross-platform application which utilizes C++ 11 Standard specific features and CMake version 3.8 or newer. 

This game also uses the following libraries from [CaptainYS](https://github.com/captainys):

    - FsSimpleWindow
    - YsSimpleSound
    - YsPng
    - YsGLFontData
    - GenericCharArray

# **Building**

Instructions for building the application, please see [install.md](https://github.com/cgeshan/Typing-Team/blob/main/install.md). 

# **More Information**
Team Members: 

   - [Madewa Adeniyi](https://www.linkedin.com/in/madewa-adeniyi/)

   - [Charlotte Avra](https://www.linkedin.com/in/charlotteavra/)

   - [Dexter Czuba](https://www.linkedin.com/in/dexter-czuba-3b6536218/)


   - [Connor Geshan](https://cgeshan.github.io)


   - [Clifton McKenzie](https://www.linkedin.com/in/clifton-mckenzie/)

# **Gameplay**
## Menu
### Reset
Game data is saved between play sessions. You can click the reset button to reset your points and level progression back to zero. 

### Tutorial
You can click the tutorial to load into an interactive practice area. In this area, the user is allowed to practice typing words and then submit them for verification. After submitting each word, via the enter key, the user is told whether they are correct or not. If incorrect, the user is given a chance to retry typing in the prompted word. The tutorial has the same 5 practice words which the user can practice over and over again until they are finished practicing. 

### Minigames/Overworld
You can click overworld or minigame rocks 1-4 (if they are unlocked) to begin.

### Exit
You can press the escape key to exit the game, overworld, and/or minigames. 

### Overworld
You must navigate through the moonscape moving left to right to reach the end where a portal will take you to the next minigame. Along the way, you can collect coins to increase your points. You are free to replay levels that you beat, but you must use the overworld to progress the game and unlock the next levels. 

### Controls:
Arrow keys: Move
Esc: Exit the level

### Mini-Game 1: Mars 
You’re a rover sliding down a sand hill on Mars! Words are speeding toward you on rocks and you must type each word correctly and select Enter to initiate a jump over the obstacle. If you miss a word or spell it incorrectly, you lose a life. Help the rover return to its Mars base by typing each word correctly before it is smashed to pieces!   

### Mini-Game 2: Shoot-Em-Up (Galaga)
You are currently flying towards the Moon in your triangular spacecraft, but as you approach your destination, a series of enemy spacecraft begin to approach you, ready to crash into and destroy your ship! Fortunately, your ship is equipped with a laser that can be used to shoot these enemies down before they collide with you. However, to activate this laser, you need to type out words given to you for each spacecraft. If you type a word correctly you shoot an enemy down, but if you type it incorrectly the enemy will continue to approach you. If the enemy reaches you, you will lose a life. Lose 3 lives and your spacecraft will be destroyed, and you will need to retry this mini-game. Once you type 10 words correctly, you will have shot down all of the enemy ships, and you will unlock the next mini-game.

### Mini-Game 3: Rockets
Sit and watch the rockets fly by, but make sure you type all the words attached to each one. Everytime you see a word, type all the letters correctly and select enter. If correct, the rocket will speed off into space. If any word is typed incorrectly or the rocket flies off screen before you get a chance to type the word, you will lose one life. You have three lives in total.   

### Mini-Game 4: Rover Race
While on the Moon, a rival space organization has challenged you to a race, with the winner being able to travel to Mars. The rival driver gets a much better start, and is now a good way ahead of your car, and with each car being of similar speed, it would be very hard to catch up. Fortunately, your rover has a boost feature installed that can allow you to catch up. However, you need to type in words that you see on the signs you are passing to activate it. If you type a word correctly you get a boost, putting you closer to the rival rover, but if you type it incorrectly the other rover will stay just as far ahead of you, and you will damage your turbo system. If you fail to type 3 words before they reach the end of the screen, your turbo will fail and your rover will break down, so you will need to retry this mini-game. Once your rover reaches your rival's rover, you will be able to pass them, allowing you to win the race, finishing all of the mini-games.

   
