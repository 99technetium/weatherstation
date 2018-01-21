package database;

public class DataBaseSetup {
    static String PASS = "bad_password";

    DataBaseConfig config = new DataBaseConfig();

    public DataBaseSetup(){
        config.createPropFile(PASS);

        DataBaseManager dataBaseManager = new DataBaseManager();

        DataBaseManager dbManager = new DataBaseManager();

        String sql = "CREATE TABLE WEATHER_DATA "
                + "(DEVICE_ID BIGINT NOT NULL GENERATED ALWAYS AS IDENTITY, "
                + "SENSOR_ID BIGINT, "
                + "UNIT INTEGER, "
                + "VALUE BIGINT, "
                + "DATE INTEGER, "
                + "TIME INTEGER) ";

        dbManager.configDatabase(sql);
    }
}
