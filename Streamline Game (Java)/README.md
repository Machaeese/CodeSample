/**
 * Author: Jialu Xu
 * Login: cs8bwatd
 * Date: 3/2/2019
 * File: README.md
 * Source of Help: PSA6 writeup
 * CSE8B PA6.
 * This file answers README questions. 
 **/

##Extra Credit
Player Animation
Bump Animation
Resizable Window
Window Autosized 

##Program Description
This program basically visualizes the game streamline. I set the background of
my game as blue, with pink obstacles and yellow goal and yellow player. As my 
player moves, the scene will have pink circles to represent its trail. After it
reaches the goal, the screen will be filled with the color of goal and start 
the next game.

##Short Response
#Unix/Linux Question
1. mkdir fooBar fooBar/dirDir
2. One example of using asterisk(*) is javac *.java, which compiles all java 
files in the current directory.
3. ls -lR
#JavaFX Question
1. An alternative way is to creat an anonymous inner class of the current 
class, such as
       scene.setOnKeyPressed(new EventHandler<KeyEvent>(){
		public void handle(KeyEvent e){
		//TODO
		}
	} );
2. The group class is a helper class that governs where my obstacles, goal,
	player and trails should appear in the Scene.
