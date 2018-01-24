package network;


/**
 * A list of all base stations that are connected to the base station.
 * This is used mostly so that when the SensorStation connects to the BaseStation, the BaseStation can see this and send
 * updates to the SensorStation.
 */
public class SensorStationList {
    private static SensorStationList instance = new SensorStationList();

    public static SensorStationList getInstance() {
        return instance;
    }

    private SensorStationList(){}

    //TODO: implement function
    public void addStation(int key, SensorStation sensorStation){
    }

    //TODO: implement function
    public void removeStation(SensorStation sensorStation){
    }
}
