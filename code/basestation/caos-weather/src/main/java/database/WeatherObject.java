package database;

import datapoint.DataPoint;

import java.util.List;

/**
 * WeatherObject creates an object that can be used toDate query the collected data.
 */
public class WeatherObject {
    private int fromDate;
    private int toDate;

    /**
     * Constructor is called with parameters fromDate toDate which define the time period in which to search for DataPoints
     *
     * @param fromDate defines from what past data the query should start looking
     * @param toDate defines to what date the query should look
     */
    public WeatherObject(int fromDate, int toDate){
        this.fromDate = fromDate;
        this.toDate = toDate;
    }

    /**
     * If the Constructor is called without any Parameters,
     * WeatherObject returns all available DataPoints that match the query
     */
    public WeatherObject(){
        fromDate = 0;
        toDate = 0;
    }


    /**
     * method returns all available types in database
     */
    //TODO: implement method
    public void availableTypes(){}

    /**
     * function searches for and returns all values of a given type
     *
     * @param type for which to search the database
     * @return List of DataPoints
     */
    //TODO: implement method
    public List<DataPoint> getByType(int type){
        DataBaseManager manager = new DataBaseManager();
        String sql;

        if(fromDate != 0 && toDate != 0) {
            sql = "SELECT DEVICE_ID, SENSOR_ID, TYPE, VALUE, DATE, TIME FROM WEATHER_DATA "
                    + "WHERE TYPE = " + type + " "
                    + "AND (DATE >= " + fromDate + " "
                    + "AND DATE <= " + toDate + " )";
        }
        else {
            sql = "SELECT DEVICE_ID, SENSOR_ID, TYPE, VALUE, DATE, TIME FROM WEATHER_DATA "
                    + "WHERE TYPE = " + type + " ";
        }

        List<DataPoint> dataPoints = manager.getDataPoint(sql);

        return dataPoints;
    }

    //TODO: remove unused code and functions
    //public void getAllDevices(){}

    //public void getAllUnits(){}

    //public void getDataBetween(int startDate, int startTime, int endDate, int endTime){}

    //public DataPoint getSpecificDataPoint(int date, int time){
    //    DataPoint data = new DataPoint("dkkdkdk134","asdfasdf", 1, 12022017,132430);
    //    return data;
    //}

    //public void getAllDataPointsFromDevice(){}

    //public void getAllDataPointsPerUnit(){}

    ///**
    // * Counts all data in the database that has the specified unit and returns the total.
     //* @param unit
     //* @return
     //*/

    //public int getTotalPerUnit(String unit){
    //    int total = 0;
    //    return total;
    //}

    //public int getDateOfEarliestUnit(){return 5;}

    //public void getAvgForTimeInterval(int intervel, int unitType){
        //return
    //}
}
