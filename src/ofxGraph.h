#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxGui.h"

#define OFXGRAPH_POINT_LABEL_MARKER 1
#define OFXGRAPH_POINT_LABEL_NONE 2

#define OFXGRAPH_TYPE_PLOT 10
#define OFXGRAPH_TYPE_BAR 11


class ofxGraph{
public:
    ofxGraph();
    ~ofxGraph();
    void setup(int _x, int _y, int _w, int _h);
    void setup(string _name);
    void setMaxLengthOfData(int &_max_length_of_data);
    void setDx(float _dx);
    void add(float _data);
    void add(float _data, int _label);
    void add(vector<float> _data, int _label);
    void add(vector<float> _data);
    void setLabel(vector<string>_label);
    void draw();
    void drawPlot();
    void drawBar();
    void drawtest();
    ofPoint getMaxPoint(float _x_left, float x_right);
    float getY(float _x);
    float getY(float _x, int _number);
    void setName(string _name);
    void setPosition(float _x, float _y);
    void setColor(ofColor _color);
    void setAutoScale(bool _is_auto_scale, float _scale);
    void setSize(float _w, float _h);
    void setGraphType(int _type);
    void clear();
    void saveSettings();
    void saveCSV();
    void basicOperation(ofxPanel _panel);
    void setBufSize(int _bufsize);
    int  getGrid(int _value, int _gris);
    vector<float> getPlotdataY(int _number);
    vector<float> getPlotdataY();
    int getPlotdataSize();
    int max_length_of_data;
    vector<ofColor> color;
    ofColor c_text;
    ofColor c_background;
    ofColor c_fill;
    ofRectangle r;
    ofImage img_move;
    ofImage img_expand;
    int graph_type;
    
    bool flg_inside_pressed = false;
    bool flg_inside_r_data = false;
    bool flg_inside_r_expand = false;
    bool flg_inside_r_gui = false;
    bool is_auto_scale = true;
    
    float scale;
    
    vector<float> data;
    vector<vector<float>> plotdata;
    vector<vector<int>> plotlabel;
    
    vector<string>label;

    float dx;
    float min_height;
    float min_width;
    float max_data;
    float min_data;
    string name;
    ofTrueTypeFont font_title;
    ofTrueTypeFont font_parameter;
    
    bool flg_mouse_dragged;
    ofPoint dragged_start_point;
    
    ofxXmlSettings xml_settings;
    ofxPanel panel;
    ofVec2f panel_size;
    ofxIntSlider slider_bufsize;
    ofxButton button_save_csv;
    ofxButton button_clear;
    ofxToggle toggle_pause;
    ofxToggle toggle_no_draw;
    ofxToggle toggle_auto_scale;
    ofxToggle toggle_graph_type;
    ofxFloatSlider slider_scale;
    int grid;
};

class ofxGraph2D : public ofxGraph
{
public:
    ofxGraph2D();
    ~ofxGraph2D();

    vector< vector<float> >data;
    void add(vector<float> _data);
    void setup(int _x, int _y, int _w, int _h);
    void draw();
    void clear();
    void saveCSV();
    int max_length_of_data2d;
    void setMaxLengthOfData2D(int &_max_length_of_data2d);
    float max_size_of_data2d;
    float min_size_of_data2d;
    
    ofxXmlSettings xml_settings;
    ofxPanel panel;
    ofxButton button_save_csv;
    ofxButton button_clear;
    ofxIntSlider slider_bufsize;



};
