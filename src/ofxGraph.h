#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxGui.h"

#define OFXGRAPH_LABEL_MARKER 1
#define OFXGRAPH_LABEL_NONE 2


class ofxGraph{
public:
    ofxGraph();
    ~ofxGraph();
    void setup(int _x, int _y, int _w, int _h);
    void setup();
    void setMaxLengthOfData(int &_max_length_of_data);
    void setDx(float _dx);
    void add(float _data);
    void add(float _data, int _label);
    void draw();
    void setName(string _name);
    void setPosition(float _x, float _y);
    void setColor(ofColor _color);
    void setSize(float _w, float _h);
    void clear();
    void saveSettings();
    void saveCSV();
    void basicOperation(ofxPanel _panel);
    void setBufSize(int _bufsize);
    int  getGrid(int _value, int _gris);
    int max_length_of_data;
    ofColor color;
    ofColor c_text;
    ofColor c_background;
    ofColor c_fill;
    ofRectangle r;
    ofImage img_move;
    ofImage img_expand;
    
    bool flg_inside_pressed = false;
    bool flg_inside_r_data = false;
    bool flg_inside_r_expand = false;
    bool flg_inside_r_gui = false;
    
    
    vector<float> data;
    vector<int>   label;

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
