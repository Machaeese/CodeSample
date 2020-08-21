/**
 * Author: Jialu Xu
 * Login: cs8bwatd
 * Date: 3/2/2019
 * File: Player.java
 * Source of Help: PSA6 writeup
 * CSE8B PA6.
 * This file contains the class Player, which contains some basic methods to 
 * initialize the player.
 **/
import javafx.scene.paint.Color;
import javafx.scene.shape.StrokeType;

/** 
 * Name: Player
 * Purpose: Containing some basic methods to initialize the player.
 **/ 
public class Player extends RoundedSquare {
    final static double STROKE_FRACTION = 0.1;

    final static Color PLAYER_COLOR = Color.LIGHTPINK;
    final static Color STROKE_COLOR = Color.MISTYROSE;

    /**
     * This constructor takes in no argument, which initializes the Player 
     * Objects.
     * @param     None
     **/
    public Player() {
        // set a fill color, a stroke color, and set the stroke type to
        // centered
        setFill(PLAYER_COLOR);
        setStroke(STROKE_COLOR);
        setStrokeType(StrokeType.CENTERED);
    }
    
    @Override
    /**
     * This method set the size of the player objects.
     * @param   size  input double size as the side size of the player object.
     * @return  None
     **/
    public void setSize(double size) {
        //1. update the stroke width based on the size and 
        //         STROKE_FRACTION
        // 2. call super setSize(), bearing in mind that the size
        //         parameter we are passed here includes stroke but the
        //         superclass's setSize() does not include the stroke
        setStrokeWidth(size*STROKE_FRACTION);
        super.setSize(size*(1-STROKE_FRACTION));
    }
}
