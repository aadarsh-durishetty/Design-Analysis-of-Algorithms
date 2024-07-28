@startuml

skinparam defaultFontName Arial Bold

|**Collect Historical Data**| **as CollectData**
start

: **Handle Missing Values**;
: **Remove Redundant Columns**;
|**Perform Exploratory Data Analysis**| **as EDA**
while (**Data is Not Suitable**?) is (**yes**)
    : **Notify User of Data Issue**;
    stop
endwhile
: **Visualize Data**;
: **Analyze Patterns and Trends**;
|**Derive Additional Features**| **as FeatureEngineering**
: **Train Machine Learning Models**;
: **Evaluate Model Performance**;
: **Select Best Model**;
|**Integrate Best Model**| **as Integration**
: **Generate Buy/Sell Signals**;
|**Monitor Performance**| **as PerformanceMonitoring**
stop

@enduml
