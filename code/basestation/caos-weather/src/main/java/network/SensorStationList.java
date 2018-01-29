package network;


import java.util.HashMap;

/**
 * A list of all base stations that are connected to the base station.
 * This is used mostly so that when the SensorStation connects to the BaseStation, the BaseStation can see this and send
 * updates to the SensorStation.
 */
public class SensorStationList {
    private HashMap<String, SensorStation> list = new HashMap<>();

    private static SensorStationList instance = new SensorStationList();

    public static SensorStationList getInstance() {
        return instance;
    }

    private SensorStationList(){}

    //TODO: make sure this really works
    public void addStation(String key, SensorStation sensorStation){
        list.put(key, sensorStation);
    }

    public SensorStation getSensorStation(String  key){
        SensorStation sensorStation = list.get(key);

        return sensorStation;
    }

    //TODO: make sure this really works
    public void removeStation(String key){
        list.remove(key);
    }
}
