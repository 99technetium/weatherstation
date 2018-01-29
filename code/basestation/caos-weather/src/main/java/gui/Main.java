package gui;

import database.DataBaseConfig;
import database.DataBaseSetup;
import database.WeatherObject;
import datapoint.DataPoint;
import javafx.application.Application;
import network.Server;

import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        DataBaseConfig config = new DataBaseConfig();

        if(!config.isDbConfiged()){
            new DataBaseSetup();
        }

        Server server = new Server();
        server.start();

        Scanner input = new Scanner(System.in);
        
        for (;;){
            String command = input.nextLine();
            handleCommand(command);
        }
    }

    static private void handleCommand(String command){
        String[] commandArray = command.split(" ");

        if (command.equals("help")){
            printHelp();
        }

        else if (commandArray[0].equals("msd")){
            if(commandArray.length != 4){
                System.out.println("malformed command");
            }
            else {
                int start = Integer.parseInt(commandArray[1]);
                int end = Integer.parseInt(commandArray[1]);
                int type = Integer.parseInt(commandArray[1]);
                printMesuredData(start, end, type);
            }
        }

        else if (commandArray[0].equals("gui")){
            String[] args = commandArray;
            Application.launch(Gui.class, args);
        }

        else {
            System.out.println("is not a valid command");
        }
    }

    static private void printHelp(){
        System.out.println(
                "msd (measured data) [startdate YYYYMMDD] [enddate YYYYMMDD] [data type] - prints collected data by type\n\n" +
                "gui [startdate YYYYMMDD] [enddate YYYYMMDD] [data type] - starts a gui with data graphed in it\n\n" +
                "Battery level         - 1\n" +
                "Light Sensor          - 2\n" +
                "Magnetic Field Sensor - 3\n");
    }

    static private void printMesuredData(int start, int end, int datatype){
        WeatherObject weather = new WeatherObject(start, end);
        List<DataPoint> dataPoints = weather.getByType(datatype);

        for (DataPoint d : dataPoints){
            System.out.println(d.getValue());
        }
    }

    static private void startGui(){}
}
