package datapoint;

public class SensorType implements Sensor {
    int HashID;

    public SensorType(int sensorHashID){
        this.HashID = sensorHashID;
    }

    public SensorType(int sensorHashID, DataPoint dataPoint){
        this.HashID = sensorHashID;
        addDataPoint(dataPoint);
    }

    public void addDataPoint(DataPoint dataPoint){}

    public void getDataPoint(){
        //return new DataPoint();
    }
}
