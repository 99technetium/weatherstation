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
    private final String sensorID;
    private final double value;
    private final int date;
    private final int time;

    public String getDeviceID() {
        return deviceID;
    }

    public String getSensorID() {
        return sensorID;
    }

    public double getValue() {
        return value;
    }

    public int getDate() {
        return date;
    }

    public int getTime() {
        return time;
    }

    public DataPoint(String deviceID, String sensorID, double value, int date, int time){
        this.deviceID = deviceID;
        this.sensorID = sensorID;
        this.value = value;
        this.date = date;
        this.time = time;
    }
}
