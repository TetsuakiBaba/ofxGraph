#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    // ofxGraph uses ofxGui as a internal setting UI
    ofxGuiSetFont(ofToDataPath("ofxGraph/DIN Alternate Bold.ttf"), 10);
    
    // ofxGraph Init
    graph.setup("Sample");
    graph.setDx(1.0); // which means delta of time
    graph.setColor(ofColor::white);  // ofColor(255,255,255)
    
    // multiplotting ofxGraph
    graph_multiplot.setup("Multiplot Sample");
    graph_multiplot.setDx(1.0);
    graph_multiplot.setColor(ofColor::azure);
    graph_multiplot.setLabel({"Noise[0.1]","Noise[0.2]","Noise[0.5]"});

}

//--------------------------------------------------------------
void ofApp::update(){
    static float x=0.0;
    static float y=0.0;
    static float z=0.0;
    graph.add(ofRandom(-100,100));
    
    x=x+0.1;
    y=y+0.2;
    z=z+0.5;
    
    vector<float>value;
    value.push_back(ofNoise(x)-0.5);
    value.push_back(ofNoise(y)-0.5);
    value.push_back(ofNoise(z)-0.5);
    graph_multiplot.add(value);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(50,50,50);
    graph.draw();
    graph_multiplot.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 's' ){
        graph.saveSettings(); // save setting graph size and position
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
