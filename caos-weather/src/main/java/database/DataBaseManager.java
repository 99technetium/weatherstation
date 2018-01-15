package database;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

/**
 * DataBaseManger abstracts access to the sql database.
 */
public class DataBaseManager {
    DataBaseConfig config = new DataBaseConfig();;
    static final String JDBC_DRIVER = "org.apache.derby.jdbc.EmbeddedDriver";
    static String DB_NAME;

    /**
     * Constructor initialises the db_config and gives access to the database settings.
     */
    public DataBaseManager(){
        this.DB_NAME = config.getDatabase();
    }



    static final String DB_URL = "jdbc:derby:" + DB_NAME + ";create=true";

    /**
     * config Database is used to configure the database, it should only be used with sql statements that do not return any statements.
     *
     * @param sqlStatement for configuring to configure the database
     */
    public void configDatabase(String sqlStatement){
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
     * sendQuery is used to send a query to the database. This will return an sql
     */
    //TODO: implement query
    public void sendQuery(String sqlQuery){}
}
