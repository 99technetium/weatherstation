package jsonObjects;

import com.google.gson.Gson;
import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import database.DataBaseManager;
import datapoint.DataPoint;
import network.SenderThread;

import java.time.Instant;
import java.time.LocalDate;
import java.util.Map;

public class JsonHandler {
    DataBaseManager manager = new DataBaseManager();
    String deviceID;
    JsonObject commandObject;

    public JsonHandler(JsonObject commandObject, String deviceID) {
        Gson gson = new Gson();
        System.out.println(gson.toJson(commandObject));

        System.out.println(Integer.parseInt(LocalDate.now().getYear()+""+LocalDate.now().getMonthValue()+""+LocalDate.now().getDayOfMonth()));

        this.deviceID = deviceID;
        this.commandObject = commandObject;

        for (Map.Entry<String,JsonElement> entry : commandObject.entrySet()) {
            if(entry.getKey().equals("data")){
                JsonObject json1 = entry.getValue().getAsJsonObject();
                if(json1.has("action_add_sensor_data")){
                    JsonObject json2 = json1.getAsJsonObject("action_add_sensor_data");
                    if(json2.has("HALL")) addDatapointsToDb(json2.getAsJsonArray("HALL"), "HALL");
                    if(json2.has("VBAT")) addDatapointsToDb(json2.getAsJsonArray("VBAT"), "VBAT");
                    if(json2.has("LDR")) addDatapointsToDb(json2.getAsJsonArray("LDR"), "LDR");
                    if(json2.has("TEMP")) addDatapointsToDb(json2.getAsJsonArray("TEMP"), "TEMP");
                }
            }

            else if(entry.getKey().equals("config")){
                JsonObject json = entry.getValue().getAsJsonObject();
                if(json.has("get_sys_time")){
                    String unixTime = "{\"config\":{\"set_sys_time\":" + Instant.now().getEpochSecond() + "}}";
                    SenderThread senderThread = new SenderThread(unixTime, deviceID);
                    senderThread.start();
                }
            }

            else {
                System.out.println("not a valid json command");
            }
        }
    }

    public String getJson(){
        return "";
    }

    //TODO: implement function
    public String getConfigJson(){
        return "";
    }

    //TODO: implement function
    public void addDatapointsToDb(JsonArray array, String type){
        int month = LocalDate.now().getMonthValue();
        String smonth = ""+month+"";
        if(month < 10){
            smonth = ""+0+""+month+"";
        }
        int date = Integer.parseInt(LocalDate.now().getYear()+smonth+LocalDate.now().getDayOfMonth());
        array.size();
        for(int i = 0; i < array.size(); i++){
            JsonArray jsonArray = array.get(i).getAsJsonArray();
            manager.addDataPoint(new DataPoint(
                    deviceID,
                    type,
                    jsonArray.get(0).getAsInt(),
                    date,
                    jsonArray.get(1).getAsInt()));
        }
    }
}
