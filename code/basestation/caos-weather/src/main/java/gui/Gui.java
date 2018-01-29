package gui;

import database.DataBaseConfig;
import database.DataBaseSetup;
import database.WeatherObject;
import datapoint.DataPoint;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.stage.Stage;
import network.Server;

import java.util.List;


public class Gui extends Application {
    private Stage stage;

    @Override public void start(Stage stage) {
        this.stage = stage;

        stage.setTitle("Collected Data");
        final CategoryAxis xAxis = new CategoryAxis();
        final NumberAxis yAxis = new NumberAxis();
        xAxis.setLabel("Measurement Date");
        yAxis.setLabel("Temperature in C");
        final LineChart<String,Number> lineChart =
                new LineChart<String,Number>(xAxis,yAxis);

        lineChart.setTitle("Temperature");

        WeatherObject object = new WeatherObject(20180119,20180131);
        List<DataPoint> dataPoints = object.getByType(3);

        XYChart.Series series1 = new XYChart.Series();
        series1.setName("Sensor 1");

        for (DataPoint d : dataPoints) {
            series1.getData().add(new XYChart.Data("" + d.getDate() +" "+d.getTime()+"", d.getValue()));
        }

        Scene scene  = new Scene(lineChart,800,600);
        lineChart.getData().addAll(series1);//, series2, series3);

        stage.setScene(scene);
        stage.show();
    }
}
