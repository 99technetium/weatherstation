/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package basisstation;

import gui.Home;

/**
 *
 * @author deki
 */
public class Basis {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        
        
        // Start the GUI
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                Home main = new Home();
                main.dateTime();
                main.setVisible(true);
            }
        });
    }
    
}
