package database;

/**
 * WeatherObject creates an object that can be used to query the collected data.
 */
public class WeatherObject {
    private int deviceID;
    private int unit;

    /**
     * Constructor for a WeatherObject object if one of the unites is set to 0,
     * only functions that do not need the specific unite for their call can be used.
     *
     * @param deviceID
     * @param unit
     */
    public WeatherObject(int deviceID, int unit){
        this.deviceID = deviceID;
        this.unit = unit;
    }

    /**
     * If the Constructor is called without any Parameters,
     * the object can only be used to query the devices that have connected to the base station
     */
    public WeatherObject(){
        deviceID = 0;
        unit = 0;
    }

    //TODO: implement function
    public void getAllDevices(){}

    //TODO: implement function
    public void getAllUnits(){}

    //TODO: implement function
    public void getDataBetween(int sdate, int stime, int ldate, int ltime){}



    //TODO: implement function
    //public DataPoint getSpecificDataPoint(int date, int time){
    //    DataPoint data = new DataPoint("dkkdkdk134","asdfasdf", 1, 12022017,132430);
    //    return data;
    //}

    //TODO: implement function
    //public void getAllDataPointsFromDevice(){}

    //TODO: implement function
    //public void getAllDataPointsPerUnit(){}

    ///**
    // * Counts all data in the database that has the specified unit and returns the total.
     //* @param unit
     //* @return
     //*/
    //TODO: implement function
    //public int getTotalPerUnit(String unit){
    //    int total = 0;
    //    return total;
    //}

    //TODO:
    //public int getDateOfEarliestUnit(){return 5;}

    //TODO:
    //public void getAvgForTimeInterval(int intervel, int unitType){
        //return
    //}


}
