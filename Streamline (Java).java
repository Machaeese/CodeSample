/**
 * Author: Jialu Xu
 * Login: cs8bwatd
 * Date: 3/2/2019
 * File: GuiStreamline.java
 * Source of Help: PSA6 writeup
 * CSE8B PA6.
 * This file contains the class GuiStreamline, which contains some basic
 * methods to visualize the Streamline game.
 **/
import javafx.scene.*;
import javafx.scene.shape.*;
import javafx.stage.Stage;

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import javafx.animation.*;
import javafx.animation.PathTransition.*;
import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.event.ActionEvent;
import javafx.scene.Group;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.paint.*;
import javafx.util.Duration;
import javafx.beans.value.*;

/**
 * Name: GuiStreamline
 * Purpose: Containing some basic methods to visualize the Streamline game.
 **/
public class GuiStreamline extends Application {
    static final double SCENE_WIDTH = 500;
    static final double SCENE_HEIGHT = 600;
    static final String TITLE = "CSE 8b Streamline GUI";
    static final String USAGE =
        "Usage: \n" +
        "> java GuiStreamline               - to start a game with default" +
        " size 6*5 and random obstacles\n" +
        "> java GuiStreamline <filename>    - to start a game by reading g" +
        "ame state from the specified file\n" +
        "> java GuiStreamline <directory>   - to start a game by reading a" +
        "ll game states from files in\n" +
        "                                     the specified directory and " +
        "playing them in order\n";

    static final Color TRAIL_COLOR = Color.PINK;
    static final Color GOAL_COLOR = Color.LAVENDER;
    static final Color OBSTACLE_COLOR = Color.LIGHTSKYBLUE;
    static final Color TRANSPARENT_COLOR = Color.TRANSPARENT;

    static final char TRAIL_CHAR = '.';
    static final char OBSTACLE_CHAR = 'X';
    static final char SPACE_CHAR = ' ';

    // Trail radius will be set to this fraction of the size of a board square.
    static final double TRAIL_RADIUS_FRACTION = 0.1;

    // Squares will be resized to this fraction of the size of a board square.
    static final double SQUARE_FRACTION = 0.8;

    Stage stage;
    double width;
    double height;
    Scene mainScene;
    Group levelGroup;                   // For obstacles and trails
    Group rootGroup;                    // Parent group for everything else
    Player playerRect;                  // GUI representation of the player
    RoundedSquare goalRect;             // GUI representation of the goal

    Shape[][] grid;                     // Same dimensions as the game board

    Streamline game;                    // The current level
    ArrayList<Streamline> nextGames;    // Future levels

    MyKeyHandler myKeyHandler;          // for keyboard input

    /**
     * This method returns the width of the board for the current level.
     * @param      None
     * @return     the width of the board for the current level
     **/
    public int getBoardWidth() {
        return this.game.currentState.board[0].length;
    }

    /**
     * This method returns the height of the board for the current level.
     * @param      None
     * @return     the height of the board for the current level
     **/
    public int getBoardHeight() {
        return this.game.currentState.board.length;
    }

    /**
     * This method decides the new size of the window
     * @param  None
     * @return None
     **/
    public void resize(){
        //check if the the number of Column is bigger than Row
        if(getBoardHeight()>=getBoardWidth()){
            stage.setHeight(SCENE_HEIGHT);
            stage.setWidth(SCENE_HEIGHT/getBoardHeight()*getBoardWidth());
        }
        //check if the the number of Column is bigger than Row
        if(getBoardHeight()<getBoardWidth()){
            stage.setHeight(SCENE_HEIGHT/getBoardWidth()*getBoardHeight());
            stage.setWidth(SCENE_HEIGHT);
        }
    }

    /**
     * This method finds a size for a single square of the board that will fit
     * nicely in the current scene size.
     * @param     None
     * @return    proper size for the single square
     **/
    public double getSquareSize() {
        /* For example, given a scene size of 1000 by 600 and a board size
           of 5 by 6, we have room for each square to be 200x100. Since we
           want squares not rectangles, return the minimum which is 100
           in this example. */
        double width = mainScene.getWidth()/this.getBoardWidth();
        double height = mainScene.getHeight()/this.getBoardHeight();
        //check if the width is bigger than height
        if(width >= height) return height;
        return width;
    }

    /**
     * This methods destroys and recreates grid and all trail and obstacle
     * shapes. Assumes the dimensions of the board may have changed.
     * @param   None
     * @return  None
     **/
    public void resetGrid() {
        // Hints: Empty out grid, trailsGroup, and obstaclesGroup.
        // Also makes sure grid is the right size, in case the size of the
        // board changed.
        levelGroup.getChildren().clear();
        grid = new Shape[getBoardHeight()][getBoardWidth()];
        //iterate through the board to fill in all trial and obstacle
        for(int i = 0; i < getBoardHeight(); i++){
            for(int j = 0; j < getBoardWidth(); j++){
                grid[i][j] = new Circle(boardIdxToScenePos(j,i)[0],
                        boardIdxToScenePos(j,i)[1],
                        getSquareSize()*TRAIL_RADIUS_FRACTION,
                        TRANSPARENT_COLOR);
                //if it is an obstacle, then put a square
                if(game.currentState.board[i][j] == OBSTACLE_CHAR){
                    RoundedSquare roundedsquare = new RoundedSquare(
                            boardIdxToScenePos(j,i)[0],
                            boardIdxToScenePos(j,i)[1],
                            getSquareSize()*SQUARE_FRACTION);
                    roundedsquare.setFill(OBSTACLE_COLOR);
                    grid[i][j] = roundedsquare;
                }
                //if it is an space or a trail put a circle
                if(game.currentState.board[i][j] == TRAIL_CHAR ){
                    grid[i][j].setFill(TRAIL_COLOR);
                }
                //add all the shapes back to group
                levelGroup.getChildren().add(grid[i][j]);
            }
        }
    }

    /**
     * This method sets the fill color of all trail Circles making them visible
     * or not depending on if that board position equals TRAIL_CHAR.
     * @param   None
     * @return  None
     **/
    public void updateTrailColors() {
        //iterate through the board to check if there is a trail
        for(int i = 0; i < getBoardHeight(); i++){
            for(int j = 0; j < getBoardWidth(); j++){
                grid[i][j].setFill(Color.TRANSPARENT);
                //if there is a trail, then set cirlce to be visible
                if(game.currentState.board[i][j] == TRAIL_CHAR){
                    grid[i][j].setFill(TRAIL_COLOR);
                }
                //if there is a obstacle, then color it
                if(game.currentState.board[i][j] == OBSTACLE_CHAR){
                    grid[i][j].setFill(OBSTACLE_COLOR);
                }
            }
        }
    }

    /**
     * Coverts the given board column and row into scene coordinates.
     * Gives the center of the corresponding tile.
     *
     * @param boardCol a board column to be converted to a scene x
     * @param boardRow a board row to be converted to a scene y
     * @return scene coordinates as length 2 array where index 0 is x
     */
    static final double MIDDLE_OFFSET = 0.5;
    public double[] boardIdxToScenePos (int boardCol, int boardRow) {
        double sceneX = ((boardCol + MIDDLE_OFFSET) *
                (mainScene.getWidth() - 1)) / getBoardWidth();
        double sceneY = ((boardRow + MIDDLE_OFFSET) *
                (mainScene.getHeight() - 1)) / getBoardHeight();
        return new double[]{sceneX, sceneY};
    }

    // milliseconds for pathtransition animation
    static final double TRANSITION_TIME = 80;
    static final int CYCLECOUNT = 2;
    static final int MOVE = 10;
    /**
     * This method makes trail markers visible and changes player position. To
     * be called when the user moved the player and the GUI needs to be updated
     * to show the new position.
     * @param  fromCol  input int fromCol as the old position
     * @param  fromRow  input int fromRow as the old position
     * @param  toCol    input int toCol as the new position
     * @param  toRow    input int toRow as the new position
     * @param  isUndo   input boolean isUndo decides whether it is an undo
     *                  movement
     **/
    public void onPlayerMoved(int fromCol, int fromRow, int toCol, int toRow,
            boolean isUndo){
        // If the position is the same, just return
        if (fromCol == toCol && fromRow == toRow) {
            return;
        }
        //if the level is passed, call onLevelFinished
        if(game.currentState.levelPassed == true){
            onLevelFinished();
        }
        // Update the player position
        double[] playerPos = boardIdxToScenePos(toCol, toRow);
        playerRect.setCenterX(playerPos[0]);
        playerRect.setCenterY(playerPos[1]);
        updateTrailColors();

        //EC#1
        double[] prePlayerPos = boardIdxToScenePos(fromCol, fromRow);
        Path path = new Path();
        path.getElements().add(new MoveTo(prePlayerPos[0],prePlayerPos[1]));
        path.getElements().add(new LineTo(playerPos[0],playerPos[1]));
        PathTransition pathTransition = new PathTransition(
                Duration.millis(TRANSITION_TIME),path);
        pathTransition.setNode(playerRect);
        pathTransition.play();

        //EC#2
        //if player is going up
        if(fromCol == toCol && fromRow > toRow &&
                toRow > 0 && isUndo == false &&
                game.currentState.board[toRow-1][toCol] == OBSTACLE_CHAR){
            Path wiggle = new Path();
            double[] obstacle = boardIdxToScenePos(toCol, toRow-1);
            wiggle.getElements().add(new MoveTo(obstacle[0],obstacle[1]));
            wiggle.getElements().add(new LineTo(obstacle[0],
                        (obstacle[1]-MOVE)));
            PathTransition wiggleT = new PathTransition();
            wiggleT.setDuration(Duration.millis(TRANSITION_TIME));
            wiggleT.setPath(wiggle);
            wiggleT.setNode(grid[toRow-1][toCol]);
            wiggleT.setCycleCount(CYCLECOUNT);
            wiggleT.setAutoReverse(true);
            wiggleT.play();
        }

        //if player is going down
        if(fromCol == toCol && fromRow < toRow &&
                toRow < getBoardHeight()-1  && isUndo == false &&
                game.currentState.board[toRow+1][toCol] == OBSTACLE_CHAR){
            Path wiggle = new Path();
            double[] obstacle = boardIdxToScenePos(toCol, toRow+1);
            wiggle.getElements().add(new MoveTo(obstacle[0],obstacle[1]));
            wiggle.getElements().add(new LineTo(obstacle[0],
                        (obstacle[1]+MOVE)));
            PathTransition wiggleT = new PathTransition();
            wiggleT.setDuration(Duration.millis(TRANSITION_TIME));
            wiggleT.setPath(wiggle);
            wiggleT.setNode(grid[toRow+1][toCol]);
            wiggleT.setCycleCount(CYCLECOUNT);
            wiggleT.setAutoReverse(true);
            wiggleT.play();
        }

        //if play is going left
        if(fromRow == toRow && fromCol > toCol &&
                toCol > 0 && isUndo == false &&
                game.currentState.board[toRow][toCol-1] == OBSTACLE_CHAR){
            Path wiggle = new Path();
            double[] obstacle = boardIdxToScenePos(toCol-1, toRow);
            wiggle.getElements().add(new MoveTo(obstacle[0],obstacle[1]));
            wiggle.getElements().add(new LineTo((obstacle[0]-MOVE),
                        obstacle[1]));
            PathTransition wiggleT = new PathTransition();
            wiggleT.setDuration(Duration.millis(TRANSITION_TIME));
            wiggleT.setPath(wiggle);
            wiggleT.setNode(grid[toRow][toCol-1]);
            wiggleT.setCycleCount(CYCLECOUNT);
            wiggleT.setAutoReverse(true);
            wiggleT.play();
        }

        //if play is going right
        if(fromRow == toRow && fromCol < toCol &&
                toCol < getBoardWidth()-1 && isUndo == false &&
                game.currentState.board[toRow][toCol+1] == OBSTACLE_CHAR){
            Path wiggle = new Path();
            double[] obstacle = boardIdxToScenePos(toCol+1, toRow);
            wiggle.getElements().add(new MoveTo(obstacle[0],obstacle[1]));
            wiggle.getElements().add(new LineTo((obstacle[0]+MOVE),
                        obstacle[1]));
            PathTransition wiggleT = new PathTransition();
            wiggleT.setDuration(Duration.millis(TRANSITION_TIME));
            wiggleT.setPath(wiggle);
            wiggleT.setNode(grid[toRow][toCol+1]);
            wiggleT.setCycleCount(CYCLECOUNT);
            wiggleT.setAutoReverse(true);
            wiggleT.play();
        }
    }

    /**
     * This method handles the input keycode.
     * @param   keyCode  input KeyCode
     * @return  None
     **/
    void handleKeyCode(KeyCode keyCode) {
        //if keyCode is null, return
        if(keyCode == null){
            return;
        }
        //if the level is passed, return
        if(game.currentState.levelPassed == true){
            return;
        }
        int fromCol = game.currentState.playerCol;
        int fromRow = game.currentState.playerRow;
        boolean isUndo = false;
        switch (keyCode) {
            case UP:
                game.recordAndMove(Direction.UP);
                break;
            case DOWN:
                game.recordAndMove(Direction.DOWN);
                break;
            case RIGHT:
                game.recordAndMove(Direction.RIGHT);
                break;
            case LEFT:
                game.recordAndMove(Direction.LEFT);
                break;
            case U:
                game.undo();
                isUndo = true;
                break;
            case O:
                game.saveToFile();
                break;
            case Q:
                System.exit(0);
                break;
            default:
                System.out.println("Possible commands:\n w - up\n " +
                        "a - left\n s - down\n d - right\n u - undo\n " +
                        "q - quit level");
                break;
        }
        // Call onPlayerMoved() to update the GUI to reflect the player's
        // movement (if any)
        int toCol = game.currentState.playerCol;
        int toRow = game.currentState.playerRow;
        onPlayerMoved(fromCol,fromRow,toCol,toRow,isUndo);
    }

    /**
     * Name: MyKeyHandler
     * This nested class handles keyboard input and calls handleKeyCode()
     **/
    class MyKeyHandler implements EventHandler<KeyEvent> {

        /**
         * This method calls handleKeyCode() to handle the input
         * @param   e   input KeyEvent e as the input
         * @return  None
         **/
        @Override
            public void handle(KeyEvent e) {
                KeyCode code = e.getCode();
                handleKeyCode(code);
            }
    }


    /**
     * This method is called whenever the UI needs to be completely redone to
     * reflect a new level.
     * @param   None
     * @return  None
     **/
    public void onLevelLoaded() {
        resetGrid();
      //  resize();

        double squareSize = getSquareSize() * SQUARE_FRACTION;

        // Update the player position
        double[] playerPos = boardIdxToScenePos(
                game.currentState.playerCol, game.currentState.playerRow
                );
        playerRect.setSize(squareSize);
        playerRect.setCenterX(playerPos[0]);
        playerRect.setCenterY(playerPos[1]);

        // Update the goal position
        double[] goalPos = boardIdxToScenePos(
                game.currentState.goalCol, game.currentState.goalRow
                );
        goalRect.setSize(squareSize);
        goalRect.setCenterX(goalPos[0]);
        goalRect.setCenterY(goalPos[1]);
    }

    static final double SCALE_TIME = 175;  // milliseconds for scale animation
    static final double FADE_TIME = 250;   // milliseconds for fade animation
    static final double DOUBLE_MULTIPLIER = 2;

    /**
     * This method is called when the player reaches the goal.Shows the winning
     * animation and loads the next level if there is one.
     * @param   None
     * @return  None
     **/
    public void onLevelFinished() {
        // Clone the goal rectangle and scale it up until it covers the screen

        // Clone the goal rectangle
        Rectangle animatedGoal = new Rectangle(
                goalRect.getX(),
                goalRect.getY(),
                goalRect.getWidth(),
                goalRect.getHeight()
                );
        animatedGoal.setFill(goalRect.getFill());

        // Add the clone to the scene
        List<Node> children = rootGroup.getChildren();
        children.add(children.indexOf(goalRect), animatedGoal);

        // Create the scale animation
        ScaleTransition st = new ScaleTransition(
                Duration.millis(SCALE_TIME), animatedGoal
                );
        st.setInterpolator(Interpolator.EASE_IN);

        // Scale enough to eventually cover the entire scene
        st.setByX(DOUBLE_MULTIPLIER *
                mainScene.getWidth() / animatedGoal.getWidth());
        st.setByY(DOUBLE_MULTIPLIER *
                mainScene.getHeight() / animatedGoal.getHeight());

        /*
         * This will be called after the scale animation finishes.
         * If there is no next level, quit. Otherwise switch to it and
         * fade out the animated cloned goal to reveal the new level.
         */
        st.setOnFinished(e1 -> {

                //check if the object is null
                if(nextGames == null){
                return;
                }

                //check if there is no next game
                if(nextGames.size() == 0){
                System.exit(0);
                }

                // update the instances variables game and nextGames
                //to switch to the next level
                game = nextGames.get(0);
                nextGames.remove(0);

                // Update UI to the next level, but it won't be visible yet
                // because it's covered by the animated cloned goal
                onLevelLoaded();
                resize();
                // use a FadeTransition on animatedGoal, with FADE_TIME as
                // the duration. Use setOnFinished() to schedule code to
                //run after this animation is finished. When the animation
                //finishes, remove animatedGoal from rootGroup.
                FadeTransition ft = new FadeTransition(
                        Duration.millis(FADE_TIME), animatedGoal);
                ft.play();
                children.remove(animatedGoal);
        });
        // Start the scale animation
        st.play();
    }

    /**
     * Performs file IO to populate game and nextGames using filenames from
     * command line arguments.
     */
    public void loadLevels() {
        game = null;
        nextGames = new ArrayList<Streamline>();

        List<String> args = getParameters().getRaw();
        if (args.size() == 0) {
            System.out.println("Starting a default-sized random game...");
            game = new Streamline();
            return;
        }

        // at this point args.length == 1

        File file = new File(args.get(0));
        if (!file.exists()) {
            System.out.printf("File %s does not exist. Exiting...",
                    args.get(0));
            return;
        }

        // if is not a directory, read from the file and start the game
        if (!file.isDirectory()) {
            System.out.printf("Loading single game from file %s...\n",
                    args.get(0));
            game = new Streamline(args.get(0));
            return;
        }

        // file is a directory, walk the directory and load from all files
        File[] subfiles = file.listFiles();
        Arrays.sort(subfiles);
        for (int i=0; i<subfiles.length; i++) {
            File subfile = subfiles[i];

            // in case there's a directory in there, skip
            if (subfile.isDirectory()) continue;

            // assume all files are properly formatted games,
            // create a new game for each file, and add it to nextGames
            System.out.printf("Loading game %d/%d from file %s...\n",
                    i+1, subfiles.length, subfile.toString());
            nextGames.add(new Streamline(subfile.toString()));
        }

        // Switch to the first level
        game = nextGames.get(0);
        nextGames.remove(0);
    }

    /**
     * This main entry point for all JavaFX Applications. Initializes instance
     * variables, creates the scene, and sets up the UI
     * @param   primaryStage  input Stage primaryStage
     * @return  None
     */
    @Override
        public void start(Stage primaryStage) throws Exception {
            this.stage = primaryStage;
            // Populate game and nextGames
            loadLevels();
            resize();
            // Initialize the scene and our groups
            rootGroup = new Group();
            mainScene = new Scene(rootGroup, SCENE_WIDTH, SCENE_HEIGHT,
                    Color.LEMONCHIFFON);
            levelGroup = new Group();
            rootGroup.getChildren().add(levelGroup);

            // initialize goalRect and playerRect, add them to rootGroup,
            // call onLevelLoaded(), and set up keyboard input handling
            goalRect = new RoundedSquare();
            goalRect.setSize(getSquareSize());
            playerRect = new Player();
            playerRect.setSize(getSquareSize());
            goalRect.setFill(GOAL_COLOR);
            rootGroup.getChildren().add(goalRect);
            rootGroup.getChildren().add(playerRect);
            onLevelLoaded();

            //set up keyboard input handling
            myKeyHandler = new MyKeyHandler();
            mainScene.setOnKeyPressed(myKeyHandler);

            //adding the listener to change the width of scene
            mainScene.widthProperty().
                addListener(new ChangeListener<Number>(){
                        /**
                         * This method changes the width of the scene.
                         * @param   arg0    ObservableValue  arg0
                         * @param   arg1    Number arg1
                         * @param   arg2    NUmber arg2
                         * @return  None
                         **/
                        public void changed(ObservableValue<? extends Number> arg0,
                            Number arg1,Number arg2){
                        onLevelLoaded();
                        }
                        });

            //adding the listener to change the height of scene
            mainScene.heightProperty().
                addListener(new ChangeListener<Number>(){
                        /**
                         * This method changes the height of the scene.
                         * @param   arg0    ObservableValue  arg0
                         * @param   arg1    Number arg1
                         * @param   arg2    NUmber arg2
                         * @return  None
                         **/
                        public void changed(
                            ObservableValue<? extends Number> arg0,
                            Number arg1,Number arg2){
                        onLevelLoaded();
                        }
                        });

            // Make the scene visible
            stage.setTitle(TITLE);
            stage.setScene(mainScene);
            stage.setResizable(true);
            stage.show();
        }

    /**
     * Execution begins here, but at this point we don't have a UI yet
     * The only thing to do is call launch() which will eventually result in
     * start() above being called.
     */
    public static void main(String[] args) {
        if (args.length != 0 && args.length != 1) {
            System.out.print(USAGE);
            return;
        }
        launch(args);
    }
}
