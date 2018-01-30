package datapoint;

/**
 * The DataPoint class represents a single datapoint that was received from the sensor station.
 * DataPoints are returned when queering the SQL database through the WeatherObject and the data
 * that is sent form the Sensor station is parsed and saved in a Data point in the JsonHandler
 * class.
 *
 * A data point contains a value, unit, date and time of the measurement.
 */

public class DataPoint {
    private final String deviceID;
    private final String type;
    private final double value;
    private final int date;
    private final int time;

    public String getDeviceID() {
        return deviceID;
    }

    public String getType() {
        return type;
    }

    public double getValue() {
        return value;
    }

    public long getDate() {
        return date;
    }

    public int getTime() {
        return time;
    }

    /**
     * A DataPoint is immutable and all values are initialized in the constructor.
     *
     * @param deviceID unique id for sensor station device
     * @param type of data that was measured, example temperature
     * @param value of measurement preformed by sensor station
     * @param date with YYYYMMDD, example 20180124, this makes it very easy to compare dates
     * @param time with HHMM, example 1506, this makes it very easy to compare times
     */
    public DataPoint(String deviceID, String type, double value, int date, int time){
        this.deviceID = deviceID;
        this.type = type;
        this.value = value;
        this.date = date;
        this.time = time;
    }
}
