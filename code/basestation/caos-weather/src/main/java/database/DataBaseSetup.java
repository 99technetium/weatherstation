package database;

public class DataBaseSetup {
    //TODO: use a truly random password
    static String PASS = "bad_password";

        DataBaseConfig config = new DataBaseConfig();

    public DataBaseSetup(){
        config.createPropFile(PASS);

        DataBaseManager dataBaseManager = new DataBaseManager();



        String sql = "CREATE TABLE WEATHER_DATA "
                + "(DEVICE_ID VARCHAR(50) not NULL, "
                + "TYPE VARCHAR(50), "
                + "VALUE BIGINT, "
                + "DATE INTEGER, "
                + "TIME INTEGER) ";

        dataBaseManager.initalConfig(sql);
    }
}
