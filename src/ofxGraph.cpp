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
    setColor(ofColor::white);   // default
    max_data = -100000;            // default
    min_data = 100000;             // default
    name = "noname";          // default
    label.resize(1);
    
    font_title.load(ofToDataPath("ofxGraph/DIN Alternate Bold.ttf"), 12);
    font_parameter.load(ofToDataPath("ofxGraph/DIN Alternate Bold.ttf"), 9);
    img_expand.load(ofToDataPath("ofxGraph/expand.png"));
    img_move.load(ofToDataPath("ofxGraph/move.png"));
    
    button_save_csv.addListener(this, &ofxGraph::saveCSV);
    slider_bufsize.addListener(this, &ofxGraph::setMaxLengthOfData);
    button_clear.addListener(this, &ofxGraph::clear);

    panel_size.set(120, 16);
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
    panel.add(toggle_auto_scale.setup("Auto Scale", false));
    panel.add(slider_scale.setup("Y-Max", 1.0, 1.0, 1000.0));
    min_height = panel.getHeight()+20;
    min_width  = panel.getWidth()+100;
    
    grid = 10;
}

void ofxGraph::setup(string _name)
{
    setup(ofRandom(300)+200, ofRandom(200)+200, 500, 250);
    scale = 1.0;
    toggle_auto_scale = true;
    setName(_name);
}

void ofxGraph::setColor(ofColor _color)
{
    color.clear();
    color.push_back(_color);
    {
        color.push_back(ofColor::lightBlue);
        color.push_back(ofColor::lightPink);
        color.push_back(ofColor::lightGreen);
        color.push_back(ofColor::lightSalmon);
        color.push_back(ofColor::lightYellow);
        color.push_back(ofColor::lightSeaGreen);
        color.push_back(ofColor::lightGray);
        color.push_back(ofColor::lightGoldenRodYellow);
        color.push_back(ofColor::lightGrey);
    }
    
    c_text = _color;
    c_background = _color.getInverted();
    c_background.set(c_background.r, c_background.g, c_background.b, 160);
    
    c_fill = _color.getLerped(_color.getInverted(), 0.5);
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
    
    toggle_auto_scale.setTextColor(c_text);
    toggle_auto_scale.setBackgroundColor(c_background);
    toggle_auto_scale.setFillColor(c_fill);
    
    panel.setTextColor(c_text);
    panel.setFillColor(c_fill);
    panel.setBackgroundColor(c_background);
    panel.setHeaderBackgroundColor(c_background);
    
    
    

}
void ofxGraph::saveCSV()
{
    ofFile csvfile;
    ofFileDialogResult result = ofSystemSaveDialog(name+"-"+ofGetTimestampString()+".csv", "Choose save directory");
    cout << result.getName() << endl;
    cout << result.getPath() << endl;

    csvfile.open(result.getPath(), ofFile::WriteOnly);

    int j = plotdata[0].size()-1;
    while( j >= 0 ){
        csvfile << ofToString(plotdata[0].size()-1-dx*j) << ",";
        for( int i = 0; i < plotdata.size(); i++ ){
            csvfile << ofToString(plotdata[i][j]) << ",";
        }
        csvfile << "\n";
        j--;
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

int ofxGraph::getGrid(int _value, int _grid)
{
    int result;
    result = _grid*(_value/_grid);
    return result;
}
void ofxGraph::setPosition(float _x, float _y)
{
    r.x = _x;
    r.y = _y;
}

void ofxGraph::setSize(float _w, float _h)
{
    r.width = getGrid(_w, grid);
    r.height = _h;
}

void ofxGraph::setBufSize(int _bufsize)
{
    slider_bufsize = _bufsize;
}

void ofxGraph::setMaxLengthOfData(int &_max_length_of_data)
{
    max_length_of_data = _max_length_of_data;
}

void ofxGraph::setDx(float _dx)
{
    dx = _dx;
}

void ofxGraph::add(vector<float> _data)
{
    add(_data, OFXGRAPH_POINT_LABEL_NONE);
}

void ofxGraph::add(vector<float> _data, int _label)
{
    vector<float> max;
    vector<float> min;
    
    if( _data.size() > label.size() ){
        label.resize(_data.size());
    }
    
    
    if( !toggle_pause ){
        if( plotdata.size() < _data.size() ){
            plotdata.clear();
            plotdata.resize(_data.size());
            plotlabel.clear();
            plotlabel.resize(_data.size());
        }
        
        for( int i = 0; i < _data.size(); i++ ){
            plotdata[i].push_back(_data[i]);
            plotlabel[i].push_back(_label);
            while( plotdata[i].size() > max_length_of_data ){
                plotdata[i].erase(plotdata[i].begin());
                plotlabel[i].erase(plotlabel[i].begin());
            }
            max.push_back(*max_element(plotdata[i].begin(), plotdata[i].end()));
            min.push_back(*min_element(plotdata[i].begin(), plotdata[i].end()));
        }
        
        max_data = *max_element(max.begin(), max.end());
        min_data = *min_element(min.begin(), min.end());
    }
}

//! get Y value of plotdata[0]
float ofxGraph::getY(float _x)
{
    return getY(_x, 0);
}

//! get Y plotdata.
//! \param _number: default is  plotdata[0]
vector<float> ofxGraph::getPlotdataY(int _number)
{
    vector<float>result;
    if( _number+1 > plotdata.size() ){
        return result;
    }

    for( int i = 0; i < plotdata[_number].size(); i++ ){
        result.push_back(plotdata[_number][i]);
    }
    return result;
}

int ofxGraph::getPlotdataSize()
{
    if( plotdata.size() > 0 ){
        return plotdata[0].size();
    }
}

vector<float> ofxGraph::getPlotdataY()
{
    return getPlotdataY(0);
}

//! get Y value of plotdata[_number]
float ofxGraph::getY(float _x, int _number)
{
    if( plotdata.size() < _number ){
        return -1;
    }
    vector<float>v;
    for( int i = plotdata[0].size()-1; i >= 0; i--){
        v.push_back(plotdata[0][i]);
    }
    
    int index = _x/dx;
    return v[index];
    
}

ofPoint ofxGraph::getMaxPoint(float _x_left, float x_right)
{
    ofPoint p_result;
    int max = -10000;
    int pos;
    vector<float>v;
    for( int j = 0; j < plotdata.size(); j++ ){

        for( int i = plotdata[j].size()-1; i >= 0; i--){
            v.push_back(plotdata[j][i]);
        }
        
        for( float i = _x_left; i <= x_right; i = i + dx){
            int index = i/dx;
            if( v[index] > max ){
                max = v[index];
                pos = index;
            }
        }
    }
    p_result.set(pos*dx, max);
    return p_result;
}



void ofxGraph::add(float _data)
{
    add(_data, OFXGRAPH_POINT_LABEL_NONE);
}

void ofxGraph::add(float _data, int _label)
{
    vector<float>d;
    d.push_back(_data);
    add(d, _label);
}

void ofxGraph::clear()
{
    plotdata.clear();
    plotlabel.clear();
}

void ofxGraph::basicOperation(ofxPanel _panel)
{
        
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
    
    // Mouse drag operation
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
        ofSetColor(color[0]);
        img_move.draw(ofGetMouseX()-img_move.getWidth(),
                      ofGetMouseY()-img_move.getHeight());
    }
    if( flg_inside_r_expand == true ){
        ofSetColor(color[0]);
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

void ofxGraph::setLabel(vector<string>_label)
{
    label.clear();
    label = _label;
}

void ofxGraph::setAutoScale(bool _is_auto_scale, float _scale)
{
    toggle_auto_scale = _is_auto_scale;
    slider_scale = _scale;
}

void ofxGraph::draw()
{

    ofNoFill();
    ofSetColor(color[0]);
    ofSetLineWidth(1.0f);
    ofDrawRectangle(r);
    font_title.drawString(name, r.x, r.y);
    
    panel.setPosition(r.x+r.width-panel_size.x, r.y);
    float x = 0;
    float rate = 0.0;
    
    for( int j = 0; j < plotdata.size(); j++ ){
        if( plotdata[j].size() > 0 ){
            
            if( toggle_auto_scale ){
                if( max_data > fabs(min_data) ){
                    rate = max_data;
                }
                else{
                    rate = min_data;
                }
                rate = fabs(rate);
            }
            else{
                rate = slider_scale;
            }
            
            if( toggle_no_draw == false ){
                ofSetColor(color[j%10]);
                ofSetPolyMode(OF_POLY_WINDING_ODD);
                ofBeginShape();
                for( int i = plotdata[j].size()-1; i >= 0; i-- ){
                    if( plotlabel[j][i] == OFXGRAPH_POINT_LABEL_MARKER ){
                        ofSetColor(ofColor::red);
                        ofDrawCircle(r.x + x,
                                     -0.8*(r.height/2)*(plotdata[j][i]/rate) + r.y + r.height/2 ,
                                     8);
                    }
                    else{
                        ofSetColor(color[j%10]);
                    }
                    ofVertex(r.x + x,
                             -0.8*(r.height/2)*(plotdata[j][i]/rate) + r.y + r.height/2);
                    x = x + r.width/(float)plotdata[j].size();
                    
                }

                ofEndShape();
            }
            
        }
        x = 0.0;
    }
    ofSetColor(color[0]);
    
    
    
    basicOperation(panel);
    
    // Show detail information
    if( r.inside(ofGetMouseX(), ofGetMouseY()) ){
        
        
        if( plotdata.size() > 0 && toggle_no_draw == false ){

            for( int j = 0; j < plotdata.size(); j++ ){
                ofSetColor(color[j%10]);
                float d = 1000.0;
                int pos = 0;
                int pos_x = 0;
                x = 0.0;
                for( int i = plotdata[j].size()-1; i >= 0; i-- ){
                    ofDrawCircle(r.x + x,
                                 -0.8*(r.height/2)*(plotdata[j][i]/rate) + r.y + r.height/2,
                                 2.0);
                    if( ofDist(ofGetMouseX(), ofGetMouseY(),
                               r.x+x,-0.8*(r.height/2)*(plotdata[j][i]/rate) + r.y + r.height/2) < d ){
                        pos = i;
                        d = ofDist(ofGetMouseX(), ofGetMouseY(),
                                   r.x+x,-0.8*(r.height/2)*(plotdata[j][i]/rate) + r.y + r.height/2);
                        pos_x = x;
                    }
                    x = x + r.width/(float)plotdata[j].size();
                }
                
                string str;
                
                // show nearest plot information
                ofDrawLine(ofGetMouseX()+10, ofGetMouseY()-12*j,
                           r.x+pos_x,-0.8*(r.height/2)*(plotdata[j][pos]/rate) + r.y + r.height/2);
                ofFill();
                ofSetColor(c_fill);
                str = label[j] + ":" +ofToString(dx*(plotdata[j].size()-pos-1))+", "+ofToString(plotdata[j][pos]);
                ofRectangle r_background = font_parameter.getStringBoundingBox(str, ofGetMouseX()+10, ofGetMouseY()-12*j);
                r_background.set(r_background.x, r_background.y, r_background.width, r_background.height);
                ofDrawRectangle(r_background);
                
                ofSetColor(color[j%10]);
                font_parameter.drawString(str, ofGetMouseX()+10, ofGetMouseY()-12*j);
                
                
                // max y
                str = ofToString(max_data);
                r_background.set(font_parameter.getStringBoundingBox(str, 0,0));
                r_background.setX(r.x+10);
                r_background.setY(r.y+r.height/2 - r_background.height/2 - 0.8*(r.height/2)*(max_data/rate));
                ofSetColor(c_fill);
                ofDrawRectangle(r_background);
                ofSetColor(color[0]);
                ofDrawLine(r_background.x-15, r_background.y+r_background.height/2,
                           r_background.x-5, r_background.y+r_background.height/2);
                font_parameter.drawString(str,
                                          r.x+10,
                                          r.y+r.height/2 + r_background.height/2 - 0.8*(r.height/2)*(max_data/rate));
                
                // min y
                str = ofToString(min_data);
                r_background.set(font_parameter.getStringBoundingBox(str, 0,0));
                r_background.setX(r.x+10);
                r_background.setY(r.y+r.height/2 - r_background.height/2 - 0.8*(r.height/2)*(min_data/rate));
                ofSetColor(c_fill);
                ofDrawRectangle(r_background);
                ofSetColor(color[0]);
                ofDrawLine(r_background.x-15, r_background.y+r_background.height/2,
                           r_background.x-5, r_background.y+r_background.height/2);
                font_parameter.drawString(str,
                                          r.x+10,
                                          r.y+r.height/2+font_parameter.getStringBoundingBox(str, 0, 0).height/2 - 0.8*(r.height/2)*(min_data/rate));
                
                
                // data size
                str = "data size["+ofToString(j)+"]: "+ ofToString(plotdata[j].size());
                ofSetColor(c_fill);
                ofDrawRectangle(font_parameter.getStringBoundingBox(
                                                                    str,
                                                                    r.x,
                                                                    r.y+r.height+j*12
                                                                    ));
                ofSetColor(color[0]);
                font_parameter.drawString(str,
                                          r.x,
                                          r.y+r.height+j*12);
            }
            
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
    setColor(ofColor::white);
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
    ofSetColor(color[0]);
    ofDrawRectangle(r);
    font_title.drawString(name, r.x, r.y);
    panel.setPosition(r.x+r.width-80, r.y);
    
    float x = 0.0;
    if( toggle_no_draw == false ){
        glPointSize(1.0);
        glBegin(GL_POINTS);
        
        for( int i = 0; i < data.size(); i++ ){
            for( int j = 0; j < data[i].size(); j++ ){
                glColor4f(color[0].r/255.0, color[0].g/255.0, color[0].b/255.0, data[i][j]/max_data);
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
        
        ofSetColor(color[0]);
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



