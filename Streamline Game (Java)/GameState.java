/**
 * Author: Jialu Xu
 * Login: cs8bwatd
 * Date: 2/5/2019
 * File: GameState.java
 * Source of Help: PSA3 writeup
 * https://docs.oracle.com/javase/10/docs/api/java/lang/Object.html
 * CSE8B PA3.
 * This file contains the class GameState, which contains some basic methods
 * to play the Streamline game.
 **/

import java.util.*;

/** 
 * Name: GameState
 * Purpose: Containing some basic methods to play the Streamline game.
 **/  
public class GameState {

    // Used to populate char[][] board below and to display the
    // current state of play.
    final static char TRAIL_CHAR = '.';
    final static char OBSTACLE_CHAR = 'X';
    final static char SPACE_CHAR = ' ';
    final static char CURRENT_CHAR = 'O';
    final static char GOAL_CHAR = '@';
    final static char NEWLINE_CHAR = '\n';
    final static char BOARDER_CHAR = '-';
    final static char SIDEBOARDER_CHAR = '|';
    private static final int TWO = 2;
    private static final int THREE = 3;
    private static final int ROUND = 4;

    // This represents a 2D map of the board
    char[][] board;

    // Location of the player
    int playerRow;
    int playerCol;

    // Location of the goal
    int goalRow;
    int goalCol;

    // true means the player completed this level
    boolean levelPassed;

    /**
     * This constructor initializes a board of given parameters, fill the board 
     * with SPACE_CHAR and set corresponding fields to parameters.
     * @param height     input int height as the number of rows the board have
     * @param width      input int width as the number of columns the board have
     * @param playerRow  input int playerRow is which row the player is in 
     * @param playerCol  input int playerCol is which column the player is in
     * @param goalRow    input int goalRow is which row the goal is in
     * @param goalCol    input int goalCol is which column the goal is in
     **/
    public GameState(int height, int width, int playerRow, int playerCol,
            int goalRow, int goalCol) {
        // TODO
        //set all elements in the board as space
        this.board = new char[height][width];
        for(int i = 0; i < height; i ++){
            for(int j = 0; j < width; j ++){
                board[i][j] = SPACE_CHAR;
            }
        }
        this.playerRow = playerRow;
        this.playerCol = playerCol;
        this.goalRow = goalRow;
        this.goalCol = goalCol;
    }

    /**
     * This is a copy constructor, which returns a same GameState Object as 
     * input.
     * @param other input GameState other as the original GameState Object
     **/

    public GameState(GameState other) {
        // TODO
        //deep copy every char in the original GameState Object 
        this.board = new char[other.board.length][other.board[0].length];
        for(int i = 0; i < other.board.length; i ++){
            for(int j = 0; j < other.board[0].length; j ++){
                board[i][j] = other.board[i][j];
            }
        }
        this.playerRow = other.playerRow;
        this.playerCol = other.playerCol;
        this.goalRow = other.goalRow;
        this.goalCol = other.goalCol;
        this.levelPassed = other.levelPassed;
    }

    /**
     * This method adds count random blocks into this.board, avoiding player 
     * position and goal position.
     * @param count input int count random blocks
     * @return      None
     **/
    void addRandomObstacles(int count) {
        // TODO
        int height = board.length;
        int width =  board[0].length;
        //check if the input is valid
        if(count > height * width-TWO || count < 0){
            return;
        }
        //iterate through the number of counts to set random obstacles once a
        //time
        for(int k = 0; k < count; k++){
            Random rand = new Random();
            int x = rand.nextInt(height);
            int y = rand.nextInt(width);
            char target = board[x][y];
            //check if the random position has player or goal
            if((x == playerRow && y == playerCol) || 
                    (x == goalRow && y == goalCol)) {
                k--;
            }
            //check if the random position already has an obstacle
            else if(board[x][y] == OBSTACLE_CHAR){
                k--;
            }
            else{
                board[x][y] = OBSTACLE_CHAR;
            }
        }
    }

    /**
     * This method rotates the board clockwise once and also rotates current 
     * position, goal position.
     * @param     None
     * @return    None
     **/ 
    void rotateClockwise() {
        // TODO
        int height = board.length;
        int width =  board[0].length;
        char[][] rotated = new char[width][height];
        //rotate the board
        for(int i = 0; i < width; i ++){
            for(int j = 0; j < height; j ++){
                rotated[i][j] = board[height-j-1][i];
            }
        }
        board = rotated;
        //rotate play's position and goal's position
        int x1 = playerRow;
        int y1 = playerCol;
        int x2 = goalRow;
        int y2 = goalCol;
        playerRow = y1;
        playerCol = height - x1 - 1;
        goalRow = y2;
        goalCol = height - x2 -1;
    }

    /**
     * This method moves player's current position towards right until stopped
     * by obstacle / edge and leave a trail of dots for all positions that we
     * walked through before stopping.
     * @param None
     * @return None
     **/
    void moveRight() {
        // TODO
        // iterate through current position to the right side board 
        for(int i = playerCol; i < board[0].length - 1; i++){
            //check if next position is emtpy
            if(board[playerRow][playerCol+1] != SPACE_CHAR){
                return;
            }
            board[playerRow][playerCol] = TRAIL_CHAR;
            playerCol++;
            //check if the player reach the goal    
            if(playerRow == goalRow && playerCol  == goalCol){
                this.levelPassed = true;
                return;
            }
        }
    }

    /**
     * This method moves towards any direction given and accomplish this by 
     * rotating, move right, rotating back.
     * @param direction input Direction direction to decide which direction to
     *                  move
     * @return          None
     **/
    void move(Direction direction) {
        // TODO
        int times = direction.getRotationCount();
        //rotate the board for the given time 
        for(int i = 0; i < times; i++){
            rotateClockwise();
        }
        moveRight();
        //rotate the board back
        for(int j = 0; j < ROUND - times; j++){
            rotateClockwise();
        }
    }

    @Override
        /**
         * This method compares two game state objects and returns true if all
         * fields match.
         * @param  other input Object other to be compared with the GameState 
         *               object
         * @return       true if all fields match
         **/
        public boolean equals(Object other) {
            // TODO: check for any conditions that should return false
            // We have exhausted all possibility of mismatch, they're identical
            // check if the input is null
            if(other == null){
                return false;
            }
            //check if the input is GameState object
            if((other instanceof GameState) != true){
                return false;
            }
            GameState newone = (GameState)other;
            //check if other.board is exactly the same with this.board
            if(this.playerRow == newone.playerRow &&
                    this.playerCol == newone.playerCol && 
                    this.goalRow == newone.goalRow && 
                    this.goalCol == newone.goalCol && 
                    this.levelPassed == newone.levelPassed){
                //if this.board and newone.board are both null, then return true
                if(this.board == null && newone.board == null){
                    return true;
                }
                if(this.board != null){
                    if(newone.board == null){
                        return false;
                    }
                    if(board.length == newone.board.length && 
                            board[0].length == newone.board[0].length){
                        boolean same = false;
                        for(int i = 0; i < board.length; i++){
                            for(int j = 0; j < board[0].length; j++){
                                if(board[i][j] == newone.board[i][j]){
                                    same = true;                            
                                }
                                if(board[i][j] != newone.board[i][j]){
                                    return false;                            
                                }
                            }
                        }
                        return same;
                    }
                }
            }
            return false;
        }

    @Override
        /** This method should return a String representation of the calling 
         * GameState object.
         * @param       None
         * @return      String representation of the calling GameState object
         **/
        public String toString() {
            // TODO
            //put player and goal in right positions
            board[goalRow][goalCol] = GOAL_CHAR;
            board[playerRow][playerCol] = CURRENT_CHAR;
            StringBuilder result = new StringBuilder("");
            int width = board[0].length * TWO + THREE;
            //create the first line border with the length width
            for(int k = 0; k < width; k++){
                result.append(BOARDER_CHAR);
            }
            //append a new line for the actual board
            result.append(NEWLINE_CHAR);
            //iterate through the char[][] to have every character in the right
            //posion
            for(int i = 0; i < board.length; i ++){
                for(int j = 0; j < board[0].length; j ++){
                    //set the first element in rows is '|'
                    if(j == 0 ){
                        result.append(SIDEBOARDER_CHAR);
                    }
                    result.append(SPACE_CHAR).append(board[i][j]);
                }
                //set the last element in rows is '|'
                result.append(SPACE_CHAR).append(SIDEBOARDER_CHAR).append(NEWLINE_CHAR);
            }
            //create the last line border with the length width
            for(int k = 0; k < width; k++){
                result.append(BOARDER_CHAR);
            }
            result.append(NEWLINE_CHAR);
            //reset player's and goal's position as spaces
            board[playerRow][playerCol] = SPACE_CHAR;
            board[goalRow][goalCol] = SPACE_CHAR;
            return result.toString();
        }
}

