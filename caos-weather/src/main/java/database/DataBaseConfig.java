package database;

import java.io.*;
import java.security.SecureRandom;
import java.util.Properties;

/**
 * Configures the database at first install with sensible and secure defaults. Additionaly the class can be used to change the default password.
 */
public class DataBaseConfig {
    InputStream inputStream;


    public DataBaseConfig(){}


    public boolean initalConfig() throws IOException {
        String result;
        boolean success;
        SecureRandom randomPass;
        randomPass = new SecureRandom();

        if (!testIfPropFilePresent()){
            createPropFile("");
        }
        readPropFile();
        return true;
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

    private void createPropFile(String password){
        Properties prop = new Properties();
        OutputStream output = null;
        //TODO: use a truly random default password
        String defaultPassword = "badbassword";

        if(password.equals("")){
            password = defaultPassword;
        }

        try {

            output = new FileOutputStream("config.properties");

            // set the properties value
            prop.setProperty("database", "hostDB");
            prop.setProperty("dbuser", "weather_station");

            prop.setProperty("dbpassword", password);

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

    /**
     * Method can be used to change the password for the database.
     * @param password new password for DB
     */
    public void changePassword(String password){
        createPropFile(password);
    }

    public void readPropFile(){
        Properties prop = new Properties();
        InputStream input = null;

        try {

            input = new FileInputStream("config.properties");

            // load a properties file
            prop.load(input);

            // get the property value and print it out
            System.out.println(prop.getProperty("database"));
            System.out.println(prop.getProperty("dbuser"));
            System.out.println(prop.getProperty("dbpassword"));

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
    }
}
