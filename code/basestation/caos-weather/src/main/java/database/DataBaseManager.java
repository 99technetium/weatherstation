package database;

import datapoint.DataPoint;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

/**
 * DataBaseManger abstracts access to the sql database.
 */
public class DataBaseManager {
    DataBaseConfig config = new DataBaseConfig();
    static final String JDBC_DRIVER = "org.apache.derby.jdbc.EmbeddedDriver";
    static String DB_NAME;

    /**
     * Constructor initialises the db_config and gives access to the database settings.
     */
    public DataBaseManager(){
        this.DB_NAME = config.getDatabase();
    }



    static final String DB_URL = "jdbc:derby:" + DB_NAME + ";create=true";

    public void initalConfig(String sqlStatement){
        sendToDatabase(sqlStatement);

    }

    /**
     * config Database is used to configure the database, it should only be used
     * with sql statements that do not return any statements.
     *
     * @param sqlStatement for configuring to configure the database
     */
    private void sendToDatabase(String sqlStatement){
        Connection connection;
        Statement statement = null;

        try{
            Class.forName(JDBC_DRIVER);

            connection = DriverManager.getConnection(DB_URL, config.getDatabaseUser(), config.getDatabasePassword());

            //connecting to database
            statement = connection.createStatement();

            //setting up database
            statement.executeUpdate(sqlStatement);

        } catch (SQLException se) {
            se.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } finally {
            try {
                if (statement != null) {
                    statement.close();
                }
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * Adds a single DataPoint to the database
     *
     * @param dataPoint new data that is to be added to database
     */
    public void addDataPoint(DataPoint dataPoint){
        String sql = "INSERT INTO WEATHER_DATA VALUES ("
                + "'" + dataPoint.getDeviceID()+ "'" + ","
                + "'" +dataPoint.getType() + "'" + ","
                + dataPoint.getValue()+ ","
                + dataPoint.getDate() + ","
                + dataPoint.getTime() + ")";

        sendToDatabase(sql);
    }

    /**
     * getDataPoint is used to send a query to the database. This will return a List with the DataPoints that match the sql query
     *
     * @param sqlQuery to search database with
     * @return a List with all the DataPoints that match the sql query
     */
    //TODO: find something better then returning List
    public List<DataPoint> getDataPoint(String sqlQuery){
        List<DataPoint> dataPoints = new ArrayList<>();

        Connection connection;
        Statement statement = null;

        try{

            Class.forName(JDBC_DRIVER);

            connection = DriverManager.getConnection(DB_URL, config.getDatabaseUser(), config.getDatabasePassword());

            //connecting to database
            statement = connection.createStatement();

            //setting up database
            ResultSet result = statement.executeQuery(sqlQuery);

            while (result.next()){
                DataPoint dataPoint = new DataPoint(
                        result.getString("DEVICE_ID"),
                        result.getString("TYPE"),
                        result.getInt("VALUE"),
                        result.getInt("DATE"),
                        result.getInt("TIME")
                );

                dataPoints.add(dataPoint);
            }

        } catch (SQLException se) {
            se.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } finally {
            try {
                if (statement != null) {
                    statement.close();
                }
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return dataPoints;
    }
}
