package database;

import java.io.*;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Properties;

/**
 * Configures the database at first install with sensible and secure defaults. Additionaly the class can be used to change the default password.
 */
public class DataBaseConfig {
    InputStream inputStream;

    static final String DB_NAME = "WEATHER_STATION_DATABASE";
    static final String USER = "weather_station";
    static String PASS = "bad_password";


    public DataBaseConfig(){}


    public boolean initialConfig() throws IOException {
        DataBaseManager dbManager = new DataBaseManager();

        String sql = "CREATE TABLE WEATHER_DATA "
                + "(DEVICE_ID BIGINT NOT NULL GENERATED ALWAYS AS IDENTITY, "
                + "SENSOR_ID BIGINT, "
                + "UNIT INTEGER, "
                + "VALUE BIGINT, "
                + "DATE INTEGER, "
                + "TIME INTEGER) ";

        String result;
        boolean success = false;
        SecureRandom randomPass;
        randomPass = new SecureRandom();

        if (!testIfPropFilePresent()){
            createPropFile("");
            success = true;
        }

        dbManager.configDatabase(sql);

        //dbManager.configDatabase(sql2);

        return success;
    }

    private boolean testIfPropFilePresent(){
        Properties prop = new Properties();
        InputStream input = null;
        boolean present = true;

        try {

            input = new FileInputStream("config.properties");

            // load a properties file
            prop.load(input);
        } catch (IOException ex) {
            present = false;
        } finally {
            if (input != null) {
                try {
                    input.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        return present;
    }

    //creates a new properties file, if no password is set it uses the default password.
    private void createPropFile(String password){
        Properties prop = new Properties();
        OutputStream output = null;
        //TODO: use a truly random default password
        String defaultPassword = PASS;

        if(password.equals("")){
            PASS = defaultPassword;
        }

        try {
            output = new FileOutputStream("config.properties");

            // set the properties value
            prop.setProperty("database", DB_NAME);
            prop.setProperty("dbuser", USER);
            prop.setProperty("dbpassword", PASS);

            // save properties to project root folder
            prop.store(output, null);

        } catch (IOException io) {
            io.printStackTrace();
        } finally {
            if (output != null) {
                try {
                    output.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    private String readPropFile(String key){
        Properties prop = new Properties();
        InputStream input = null;
        String setting = "";

        try {

            input = new FileInputStream("config.properties");

            // load a properties file
            prop.load(input);

            // get the property value and print it out
            setting = prop.getProperty(key);

        } catch (IOException ex) {
            ex.printStackTrace();
        } finally {
            if (input != null) {
                try {
                    input.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        return setting;
    }

    /**
     * Method can be used to change the password for the database.
     * @param password new password for DB
     */
    public void changePassword(String password){
        createPropFile(password);
    }

    public String getDatabase(){
        return readPropFile("database");
    }

    public String getDatabaseUser(){
        return readPropFile("dbuser");
    }

    public String getDatabasePassword(){
        return readPropFile("dbpassword");
    }
}
