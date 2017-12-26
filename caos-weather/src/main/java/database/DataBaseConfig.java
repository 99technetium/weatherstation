package database;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.security.SecureRandom;
import java.util.Properties;

/**
 * source: http://crunchify.com/java-properties-file-how-to-read-config-properties-values-in-java/
 */

public class DataBaseConfig {
    String result = "";
    InputStream inputStream;


    DataBaseConfig(){
    }

    public boolean initalDBConfig() throws IOException {
        SecureRandom randomPass;
        randomPass = new SecureRandom();
        try {

        } catch (Exception e){
            System.out.println("Exception: " + e);
        }
        return true;
    }

    public String getPropValues()throws IOException{
        try {
            Properties prop = new Properties();
            String propFileName = "config.properties";

            inputStream = getClass().getClassLoader().getResourceAsStream(propFileName);

            if(inputStream != null){
                prop.load(inputStream);
            } else {
                throw new FileNotFoundException("prperty file '"+ propFileName + "' not found in the classpath");
            }

            String firstopen = prop.getProperty("fistopen");
            result = firstopen;
        } catch (Exception e){
            System.out.println("Exception: " + e);
        } finally {
            inputStream.close();
        }
        return result;
    }
}
