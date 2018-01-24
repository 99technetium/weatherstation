package network;

import com.google.gson.Gson;
import datapoint.DataPoint;

public class JsonHandler {
    String inputString;
    public JsonHandler(String inputString) {
        this.inputString = inputString;
    }

    public String getJson(){
        return "";
    }

    public DataPoint getDatapoint(){
        String jsonString = inputString;
        DataPoint dataPoint;// = new DataPoint("","",1,1,1);
        Gson gson = new Gson();

        dataPoint = gson.fromJson(jsonString, DataPoint.class);

        return dataPoint;
    }
}
