#include "ofxGraph.h"

ofxGraph::ofxGraph()
{
    
}

ofxGraph::~ofxGraph()
{
    
}

void ofxGraph::saveSettings()
{
    xml_settings.setValue("settings:x", r.x);
    xml_settings.setValue("settings:y", r.y);
    xml_settings.setValue("settings:w", r.width);
    xml_settings.setValue("settings:h", r.height);

    xml_settings.saveFile(ofToDataPath("ofxGraph/"+name+".xml"));
}
void ofxGraph::setup(int _x, int _y, int _w, int _h)
{
    r.set(_x, _y, _w, _h);
    dx = 1.0;                 // default
    max_length_of_data = 128; // default
    color.set(255,255,255);   // default
    max_data = 10;            // default
    min_data = 0;             // default
    name = "noname";          // default
    
    font_title.load(ofToDataPath("ofxGraph/DIN Alternate Bold.ttf"), 18);
    font_parameter.load(ofToDataPath("ofxGraph/DIN Alternate Bold.ttf"), 10);
    img_expand.load(ofToDataPath("ofxGraph/expand.png"));
    img_move.load(ofToDataPath("ofxGraph/move.png"));
    
    button_save_csv.addListener(this, &ofxGraph::saveCSV);
    slider_bufsize.addListener(this, &ofxGraph::setMaxLengthOfData);
    button_clear.addListener(this, &ofxGraph::clear);

    panel_size.set(100, 16);
    panel.setup();
    panel.setSize(panel_size.x, panel_size.y);
    panel.setDefaultHeight(panel_size.y);
    panel.setDefaultWidth(panel_size.x);
    panel.setName("Options");
    
    panel.add(slider_bufsize.setup("BufSize", 128, 32, 512));
    panel.add(button_save_csv.setup("Save CSV"));
    panel.add(toggle_pause.setup("Pause", false));
    panel.add(toggle_no_draw.setup("No draw", false));
    panel.add(button_clear.setup("Clear"));
    
    min_height = panel.getHeight()+20;
    min_width  = panel.getWidth()+100;
}

void ofxGraph::setColor(ofColor _color)
{
    color = _color;
    c_text = color;
    c_background = color.getInverted();
    c_background.set(c_background.r, c_background.g, c_background.b, 160);
    
    c_fill = color.getLerped(color.getInverted(), 0.5);
    c_fill.set(c_fill.r, c_fill.g, c_fill.b, 160);

    slider_bufsize.setTextColor(c_text);
    slider_bufsize.setBackgroundColor(c_background);
    slider_bufsize.setFillColor(c_fill);
    
    button_save_csv.setTextColor(c_text);
    button_save_csv.setBackgroundColor(c_background);
    button_save_csv.setFillColor(c_fill);

    button_clear.setTextColor(c_text);
    button_clear.setBackgroundColor(c_background);
    button_clear.setFillColor(c_fill);
    
    toggle_pause.setTextColor(c_text);
    toggle_pause.setBackgroundColor(c_background);
    toggle_pause.setFillColor(c_fill);
    
    toggle_no_draw.setTextColor(c_text);
    toggle_no_draw.setBackgroundColor(c_background);
    toggle_no_draw.setFillColor(c_fill);



    
    panel.setTextColor(c_text);
    panel.setFillColor(c_fill);
    panel.setBackgroundColor(c_background);
    panel.setHeaderBackgroundColor(c_background);
}
void ofxGraph::saveCSV()
{
    ofFile csvfile;
    csvfile.open(ofToDataPath("ofxGraph/csv/"+name)+ofGetTimestampString()+".csv", ofFile::WriteOnly);
    for( int i = data.size()-1; i >= 0; i-- ){
        csvfile << ofToString(dx*(data.size()-1 - i)) << ",";
        csvfile << ofToString(data[i]) << "\n";
    }
}


void ofxGraph::setName(string _name)
{
    name = _name;
    if( xml_settings.loadFile(ofToDataPath("ofxGraph/"+name+".xml") )){
        cout << "load settings" << endl;
        r.x = xml_settings.getValue("settings:x",0);
        r.y = xml_settings.getValue("settings:y",0);
        r.width = xml_settings.getValue("settings:w",0);
        r.height = xml_settings.getValue("settings:h",0);
    }
}

void ofxGraph::setPosition(float _x, float _y)
{
    r.x = _x;
    r.y = _y;
}

void ofxGraph::setSize(float _w, float _h)
{
    r.width = _w;
    r.height = _h;
}


void ofxGraph::setMaxLengthOfData(int &_max_length_of_data)
{
    max_length_of_data = _max_length_of_data;
}

void ofxGraph::setDx(float _dx)
{
    dx = _dx;
}

void ofxGraph::add(float _data)
{
    if( !toggle_pause ){
        data.push_back(_data);
        while( data.size() > max_length_of_data ){
            data.erase(data.begin());
        }
        
        max_data = *max_element(data.begin(), data.end());
        min_data = *min_element(data.begin(), data.end());
    }
}

void ofxGraph::clear()
{
    data.clear();
}

void ofxGraph::basicOperation(ofxPanel _panel)
{
    static bool flg_inside_pressed = false;
    static bool flg_inside_r_data = false;
    static bool flg_inside_r_expand = false;
    static bool flg_inside_r_gui = false;
    
    ofRectangle r_expand;
    r_expand.set(r.x+r.width-_panel.getWidth(),
               r.y+_panel.getHeight(),
               _panel.getWidth(),
               r.height-_panel.getHeight());
    ofRectangle r_gui;
    r_gui.set(r.x+r.width-_panel.getWidth(),
              r.y,
              _panel.getWidth(),
              _panel.getHeight());
    ofRectangle r_data;
    r_data.set(r.x, r.y,
               r.width-_panel.getWidth(),
               r.height);
    

    if( ofGetMousePressed() == true && r_data.inside(ofGetMouseX(), ofGetMouseY()) && !flg_mouse_dragged){
        flg_inside_pressed = true;
        flg_inside_r_data = true;
    }
    else if( ofGetMousePressed() == false ){
        flg_inside_pressed = false;
        flg_inside_r_data = false;
    }
    
    if( ofGetMousePressed() == true && r_expand.inside(ofGetMouseX(), ofGetMouseY()) && !flg_mouse_dragged){
        flg_inside_pressed = true;
        flg_inside_r_expand = true;
    }
    else if( ofGetMousePressed() == false ){
        flg_inside_pressed = false;
        flg_inside_r_expand = false;
    }
    
    // dragg operation
    if( flg_mouse_dragged && flg_inside_pressed == true){
        
        // Expand
        if( flg_inside_r_expand == true  ){
            r.width = r.width + ofGetMouseX()-dragged_start_point.x;
            r.height = r.height + ofGetMouseY()-dragged_start_point.y;
            if( r.height < min_height ){
                r.height = min_height;
            }
            if( r.width < min_width ){
                r.width = min_width;
            }
            
        }
        else if( flg_inside_r_gui == true ){
            
        }
        else if( flg_inside_r_data == true ){
            setPosition(r.x+ofGetMouseX()-dragged_start_point.x,
                        r.y+ofGetMouseY()-dragged_start_point.y);
        }
        dragged_start_point.set(ofGetMouseX(), ofGetMouseY());
    }

    
    
    
    if( flg_inside_r_data == true  ){
        ofSetColor(color);
        img_move.draw(ofGetMouseX()-img_move.getWidth(),
                      ofGetMouseY()-img_move.getHeight());
    }
    if( flg_inside_r_expand == true ){
        ofSetColor(color);
        img_expand.draw(ofGetMouseX()-img_expand.getWidth(),
                        ofGetMouseY()-img_expand.getHeight());
    }


    if( ofGetMousePressed() && flg_mouse_dragged == false ){
        flg_mouse_dragged = true;
        dragged_start_point.set(ofGetMouseX(), ofGetMouseY());
    }
    else if( !ofGetMousePressed() && flg_mouse_dragged == true ){
        flg_mouse_dragged = false;
        saveSettings();
    }

    
   
}

void ofxGraph::draw()
{
    ofNoFill();
    ofSetColor(color);
    ofDrawRectangle(r);
    font_title.drawString(name, r.x, r.y);
    
    panel.setPosition(r.x+r.width-panel_size.x, r.y);
    float x = 0;
    float rate = 0.0;

    if( data.size() > 0 ){

        if( max_data > fabs(min_data) ){
            rate = max_data;
        }
        else{
            rate = min_data;
        }
        rate = fabs(rate);

        if( toggle_no_draw == false ){
            ofSetPolyMode(OF_POLY_WINDING_ODD);
            ofBeginShape();
            for( int i = data.size()-1; i >= 0; i-- ){
                ofVertex(r.x + x,
                         -0.8*(r.height/2)*(data[i]/rate) + r.y + r.height/2);
                x = x + r.width/(float)data.size();
            }
            ofEndShape();
        }
        
    }
    x = 0.0;
    

    
    basicOperation(panel);
    
    // Show detail information
    if( r.inside(ofGetMouseX(), ofGetMouseY()) ){
        

        if( data.size() > 0 && toggle_no_draw == false ){
            float d = 1000.0;
            int pos = 0;
            int pos_x = 0;
            for( int i = data.size()-1; i >= 0; i-- ){
                ofDrawCircle(r.x + x,
                             -0.8*(r.height/2)*(data[i]/rate) + r.y + r.height/2,
                             2.0);
                if( ofDist(ofGetMouseX(), ofGetMouseY(),
                           r.x+x,-0.8*(r.height/2)*(data[i]/rate) + r.y + r.height/2) < d ){
                    pos = i;
                    d = ofDist(ofGetMouseX(), ofGetMouseY(),
                               r.x+x,-0.8*(r.height/2)*(data[i]/rate) + r.y + r.height/2);
                    pos_x = x;
                }
                x = x + r.width/(float)data.size();
            }
            
            // show nearest plot information
            ofDrawLine(ofGetMouseX(), ofGetMouseY(),
                       r.x+pos_x,-0.8*(r.height/2)*(data[pos]/rate) + r.y + r.height/2);
            ofFill();
            ofSetColor(c_fill);
            ofDrawRectangle(font_parameter.getStringBoundingBox(ofToString(dx*(data.size()-pos-1))+","+ofToString(data[pos]), ofGetMouseX(), ofGetMouseY()));
            ofDrawRectangle(font_parameter.getStringBoundingBox("data size: "+ofToString(data.size()),r.x, r.y+r.height));
            ofSetColor(color);
            font_parameter.drawString(ofToString(dx*(data.size()-pos-1))+","+ofToString(data[pos]), ofGetMouseX(), ofGetMouseY());
            
            string str = ofToString(max_data);
            font_parameter.drawString(str,
                                      r.x-font_parameter.getStringBoundingBox(str, 0, 0).width,
                                      r.y+r.height/2 + font_parameter.getStringBoundingBox(str, 0, 0).height/2 - 0.8*(r.height/2)*(max_data/rate));
            str = ofToString(min_data);
            font_parameter.drawString(str,
                                      r.x-font_parameter.getStringBoundingBox(str, 0, 0).width,
                                      r.y+r.height/2+font_parameter.getStringBoundingBox(str, 0, 0).height/2 - 0.8*(r.height/2)*(min_data/rate));
            
            str = "data size: "+ofToString(data.size());
            font_parameter.drawString(str,
                                      r.x,
                                      r.y+r.height);
        }
        
        
        panel.draw();
    }
    
}




//ofxGraph2D--------------------------------------------------
ofxGraph2D::ofxGraph2D()
{
    max_length_of_data2d = 2048;
    max_size_of_data2d = -1000;
    min_size_of_data2d = 1000;
    
}
ofxGraph2D::~ofxGraph2D()
{
    
}

void ofxGraph2D::setMaxLengthOfData2D(int &_max_length_of_data2d)
{
    max_length_of_data2d = _max_length_of_data2d;
}

void ofxGraph2D::setup(int _x, int _y, int _w, int _h)
{
    r.set(_x, _y, _w, _h);
    dx = 1.0;
    max_length_of_data = 128;
    color.set(255,255,255);
    max_data = 10;
    min_data = 0;
    name = "noname";
    
    font_title.load(ofToDataPath("ofxGraph/DIN Alternate Bold.ttf"), 18);
    font_parameter.load(ofToDataPath("ofxGraph/DIN Alternate Bold.ttf"), 10);
    img_expand.load(ofToDataPath("ofxGraph/expand.png"));
    img_move.load(ofToDataPath("ofxGraph/move.png"));
    
    button_save_csv.addListener(this, &ofxGraph2D::saveCSV);
    slider_bufsize.addListener(this, &ofxGraph2D::setMaxLengthOfData2D);
    button_clear.addListener(this, &ofxGraph2D::clear);
    
    panel_size.set(80, 100);
    panel.setup();
    panel.setSize(panel_size.x,panel_size.y);
    panel.setDefaultWidth(panel_size.x);
    panel.setName("Options");
    
    panel.add(slider_bufsize.setup("BufSize",16384, 1, 16384));
    panel.add(button_save_csv.setup("Save CSV"));
    panel.add(toggle_pause.setup("Pause", false));
    panel.add(toggle_no_draw.setup("No draw", false));
    panel.add(button_clear.setup("Clear"));
    
    min_height = panel.getHeight()+20;
    min_width  = panel.getWidth()+100;

}
void ofxGraph2D::add(vector<float>_data)
{
    if( !toggle_pause ){
        data.push_back(_data);
        
        if( _data.size() > max_size_of_data2d ){
            max_size_of_data2d = _data.size();
        }
        if( _data.size() < min_size_of_data2d ){
            min_size_of_data2d = _data.size();
        }
        
        float max,min;
        max = *max_element(_data.begin(), _data.end());
        min = *min_element(_data.begin(), _data.end());
        if( max > max_data ){
            max_data = max;
        }
        if( min < min_data ){
            min_data = min;
        }
        
        
        while( data.size() > max_length_of_data2d ){
            data.erase(data.begin());
        }
    }
}

void ofxGraph2D::draw()
{
    ofNoFill();
    ofSetColor(color);
    ofDrawRectangle(r);
    font_title.drawString(name, r.x, r.y);
    panel.setPosition(r.x+r.width-80, r.y);
    
    float x = 0.0;
    if( toggle_no_draw == false ){
        glPointSize(1.0);
        glBegin(GL_POINTS);
        
        for( int i = 0; i < data.size(); i++ ){
            for( int j = 0; j < data[i].size(); j++ ){
                glColor4f(color.r/255.0, color.g/255.0, color.b/255.0, data[i][j]/max_data);
                glVertex2f(r.x+x,
                           r.y +  r.height*j/max_size_of_data2d);
                
            }
            x = x + r.width/(float)data.size();
        }
        glEnd();
    }
    
    if( r.inside(ofGetMouseX(), ofGetMouseY()) ){
        
        basicOperation(panel);
        
        string str = "data size: "+ofToString(data.size());
        ofSetColor(c_fill);
        ofDrawRectangle(font_parameter.getStringBoundingBox(str, r.x, r.y+r.height));
        
        ofSetColor(color);
        font_parameter.drawString(str,
                                  r.x,
                                  r.y+r.height);
        
        panel.draw();

    }
}

void ofxGraph2D::clear()
{
    for( int i = 0; i < data.size(); i++ ){
        data[i].clear();
    }
    data.clear();
    max_data = -1000;
    min_data = 1000;
}

void ofxGraph2D::saveCSV()
{
    ofFile csvfile;
    csvfile.open(ofToDataPath("ofxGraph/csv/"+name)+ofGetTimestampString()+".csv", ofFile::WriteOnly);
    for( int i = data.size()-1; i >= 0; i-- ){
        for( int j = data[i].size()-1; j >= 0; j-- ){
            csvfile << ofToString(data[i][j]) << ",";
        }
        csvfile << "\n";
    }
    
}



