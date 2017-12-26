package datapoint;

/**
 * The DataPoint class represents a single datapoint that was received from the sensor station.
 * DataPoints are returned when queering the SQL database through the WeatherObject.
 *
 * A data point contains a value, unit, date and time of the measurement.
 */

public class DataPoint {
    private String sensorID;
    private String deviceID;
    private double value;
    private int date;
    private int time;
    public DataPoint(String deviceID, String sensorID, double value, int date, int time){
        this.deviceID = deviceID;
        this.sensorID = sensorID;
        this.value = value;
        this.date = date;
        this.time = time;
    }
}
