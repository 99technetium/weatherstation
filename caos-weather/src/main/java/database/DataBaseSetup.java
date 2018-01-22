package database;

public class DataBaseSetup {
    //TODO: use a trully random password
    static String PASS = "bad_password";

        DataBaseConfig config = new DataBaseConfig();

    public DataBaseSetup(){
        config.createPropFile(PASS);

        DataBaseManager dataBaseManager = new DataBaseManager();



        String sql = "CREATE TABLE WEATHER_DATA "
                + "(DEVICE_ID BIGINT NOT NULL GENERATED ALWAYS AS IDENTITY, "
                + "SENSOR_ID BIGINT, "
                + "VALUE BIGINT, "
                + "DATE INTEGER, "
                + "TIME INTEGER) ";

        dataBaseManager.initalConfig(sql);
    }
}
