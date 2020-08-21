/** 
 * Author: Jialu Xu
 * Login: cs8bwatd
 * Date: 2/11/2019
 * File: Streamline.java
 * Sources of Help: PSA3 writeup
 * https://docs.oracle.com/javase/10/docs/api/java/lang/StringBuilder.html
 * https://docs.oracle.com/javase/10/docs/api/java/lang/String.html
 * https://docs.oracle.com/javase/10/docs/api/java/util/ArrayList.html
 * CSE8B PA3.
 * This file contains the class Streamline, which contains some basic methods
 * to play the Streamline game.
 **/


import java.util.*;
import java.io.*;

/** 
 * Name: Streamline
 * Purpose: Containing some basic methods to play the Streamline game.
 **/  
public class Streamline {
    final static int DEFAULT_HEIGHT = 6;
    final static int DEFAULT_WIDTH = 5;
    final static int NumsOfObstacles = 3;
    final static String left = "a";
    final static String right = "d";
    final static String up = "w";
    final static String down = "s";
    final static String quit = "q";
    final static String save = "o";
    final static String undo = "u";
    final static String OUTFILE_NAME = "saved_streamline_game";
    final static String NEXT_CHAR = ">";

    GameState currentState;
    List<GameState> previousStates;


    /**
     * This constructor takes in no argument, which initializes the Streamline 
     * Objects.
     * @param     None
     **/
    public Streamline() {
        // TODO
        this.currentState = new GameState(DEFAULT_HEIGHT,DEFAULT_WIDTH,
                DEFAULT_HEIGHT-1,0,0,DEFAULT_WIDTH-1);
        this.currentState.addRandomObstacles(NumsOfObstacles);
        this.previousStates = new ArrayList<GameState>();
    }

    /**
     * This constructor takes in the filename, which initializes the Streamline 
     * Objects.
     * @param   filename  input String filename to be read 
     **/
    public Streamline(String filename) {
        try {
            loadFromFile(filename);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * This helper method takes in the parameter filename, which reads the 
     * file's content, and initialize the appropriate instance variables.
     * @param  filename  input String filename to be read
     * @return           None
     **/
    protected void loadFromFile(String filename) throws IOException {
        // TODO
        //check if the filename string is null
        if(filename == null){
            return;
        }
        Scanner scanner = new Scanner(new File(filename));
        //check if the file has next input
        while(scanner.hasNext()){
            int height = scanner.nextInt();
            int width = scanner.nextInt();
            scanner.nextLine();
            int playerRow = scanner.nextInt();
            int playerCol = scanner.nextInt();
            scanner.nextLine();
            int goalRow = scanner.nextInt();
            int goalCol = scanner.nextInt();
            scanner.nextLine();          
            GameState newState = new GameState(height,width,playerRow,
                    playerCol,goalRow,goalCol);             
            StringBuilder original = new StringBuilder("");
            //check if the file has next line 
            while(scanner.hasNextLine()){
                original.append(scanner.nextLine());
            }
            //iterate through the file to fulfill the board
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    newState.board[i][j] = original.charAt(i * width + j);
                }
            }
            //check if the file has already passed the level            
            if(playerCol == goalCol && playerRow == goalRow){
                newState.levelPassed = true;
            }                        
            currentState = new GameState(newState);
            this.previousStates = new ArrayList<GameState>();
        }   
    }

    /**
     * This method first updates previousStates by saving a copy of the current 
     * state into the list and then makes a move in the given direction on 
     * currentState.
     * @param  direction  input Direction direction to turn to
     * @return            None
     **/
    void recordAndMove(Direction direction) {
        // TODO
        //check if the direction is null
        if(direction == null){
            return;
        }
        //check if the currentState is null
        if(currentState == null){
            return;
        }
        GameState state = new GameState(currentState);
        currentState.move(direction);
        //if current states is the same as previous one, then exit
        if(currentState.equals(state)){              
            return;
        }
        else{
            previousStates.add(state);
        }
    } 

    /**
     * This method allows the player to undo their last step, which updates 
     * previousStates and currentState appropriately to undo the most recent 
     * move made by the player.
     * @param   None
     * @return  None
     **/
    void undo() {
        // TODO
        //check if the arraylist doesn't contain any element
        if(previousStates.size() == 0){
            return;
        }
        int length = previousStates.size();
        currentState = new GameState(previousStates.get(length - 1));
        previousStates.remove(length-1);
    }

    /**
     * This method handles the interactive part of the program. Users could use
     * "a" to let player to go left; "w" to let player to go up; "d" to let 
     * player to go right; "s" to let player to go down; "u" to go back to 
     * previous step; "q" to quit the game; "o" to save the game. Other inputs
     * will be disgarded.
     * @param    None
     * @return   None
     **/
    void play() {
        // TODO
        //check if the currentState is null
        if(currentState != null){
            Scanner sc = new Scanner(System.in);
            //check if the game passed
            while(currentState.levelPassed != true){
                System.out.println(currentState.toString());
                System.out.print(NEXT_CHAR); 
                String input = sc.nextLine();
                switch(input){
                    case up :
                        recordAndMove(Direction.UP);
                        break;
                    case left:
                        recordAndMove(Direction.LEFT);
                        break;
                    case down:
                        recordAndMove(Direction.DOWN);
                        break;
                    case right:
                        recordAndMove(Direction.RIGHT);
                        break;
                    case undo:
                        undo();
                        break;
                    case save:
                        saveToFile();
                        break;
                    case quit:
                        return;
                    default:
                        break;
                }
            }
            System.out.print(currentState.toString());
            System.out.println("Level Passed!");
        }
    }

    /**
     * This method writes the Streamline game to a file in a certain format.
     * @param   None
     * @return  None
     **/
    void saveToFile() {
        try {
            //check if the currentState is null
            if(currentState == null){
                return;
            }
            // TODO: use OUTFILE_NAME as the filename and save
            PrintWriter file = new PrintWriter(OUTFILE_NAME);
            file.print(currentState.board.length);
            file.print(" ");
            file.print(currentState.board[0].length);
            file.println();
            file.print(currentState.playerRow);
            file.print(" ");
            file.print(currentState.playerCol);
            file.println();  
            file.print(currentState.goalRow);
            file.print(" ");
            file.print(currentState.goalCol);
            file.println();  
            StringBuilder toFile = new StringBuilder("");
            //iterate through the board to copy every element to the file
            for(int i = 0 ; i < currentState.board.length; i++){
                for(int j = 0 ; j < currentState.board[0].length; j++){        
                    toFile.append(currentState.board[i][j]);
                }
                toFile.append("\n");
            }
            file.print(toFile.toString());
            System.out.println("Saved current state to: " + OUTFILE_NAME);
            file.close();
        } 
        catch (IOException e) {
            e.printStackTrace();
        }
    }

}



